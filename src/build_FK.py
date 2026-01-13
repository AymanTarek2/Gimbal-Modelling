import sympy as sp
from sympy.codegen.rewriting import create_expand_pow_optimization

# 1. Define Symbols
base_roll, base_pitch, base_yaw = sp.symbols('base_roll base_pitch base_yaw')
q1, q2, q3 = sp.symbols('q1 q2 q3')

# Helper: Axis-Angle to Matrix (Rodrigues Formula)
def axis_angle_matrix(axis, theta):
    x, y, z = axis
    c = sp.cos(theta)
    s = sp.sin(theta)
    C = 1 - c
    
    # 3x3 Rotation Matrix
    return sp.Matrix([
        [c + x*x*C,    x*y*C - z*s,  x*z*C + y*s, 0],
        [y*x*C + z*s,  c + y*y*C,    y*z*C - x*s, 0],
        [z*x*C - y*s,  z*y*C + x*s,  c + z*z*C,   0],
        [0, 0, 0, 1]
    ])

# Helper: Fixed Transform Matrix from your JSON data
def trans_matrix(vals):
    # vals is a list of lists 4x4
    return sp.Matrix(vals)

# --- 2. INPUT YOUR CONSTANTS HERE (From your C code) ---

# Axes
AXIS_X = [1, 0, 0]
AXIS_Y = [0, 1, 0]
AXIS_Z = [0, 0, 1]

# Gimbal Joint Axes
AXIS_J1 = [0, 1, 0]
# Your specific J2 axis
AXIS_J2 = [0, 0.2582889370066548, -0.966067712440475] 
AXIS_J3 = [0, 1, 0]

# Base Offset Rotation (R_BASE_0)
T_base_0 = sp.Matrix([
    [-1, 0, 0, 0],
    [ 0, 0, 1, 0],
    [ 0, 1, 0, 0],
    [ 0, 0, 0, 1]
])

# Fixed Link Matrices (A01, A12, etc.)
A01 = sp.Matrix([
    [1.0, 0.0, 0.0, 0.02741],
    [0.0, 1.0, 0.0, 0.17774],
    [0.0, 0.0, 1.0, 0.09305],
    [0.0, 0.0, 0.0, 1.0]
])

A12 = sp.Matrix([
    [1.0, 0.0, 0.0, 0.0],
    [0.0, 1.0, 0.0, 0.12422],
    [0.0, 0.0, 1.0, -0.00288],
    [0.0, 0.0, 0.0, 1.0]
])

A23 = sp.Matrix([
    [1.0, 0.0, 0.0, -0.01406],
    [0.0, 1.0, 0.0, 0.01942],
    [0.0, 0.0, 1.0, -0.09140],
    [0.0, 0.0, 0.0, 1.0]
])

A3E = sp.Matrix([
    [1.0, 0.0, 0.0, 0.01406],
    [0.0, 1.0, 0.0, 0.01678],
    [0.0, 0.0, 1.0, 0.00119],
    [0.0, 0.0, 0.0, 1.0]
])

# --- 3. BUILD THE CHAIN ---

print("Calculating Base Rotation...")
# Base: Rx -> Ry -> Rz
R_x = axis_angle_matrix(AXIS_X, base_roll)
R_y = axis_angle_matrix(AXIS_Y, base_pitch)
R_z = axis_angle_matrix(AXIS_Z, base_yaw)

# T_base = T_base_0 * (Rx * Ry * Rz)
T_base = T_base_0 * (R_x * R_y * R_z)

print("Calculating Gimbal Chain...")
# Chain: A01 -> R(q1) -> A12 -> R(q2) -> A23 -> R(q3) -> A3E
T_chain = A01 * \
          axis_angle_matrix(AXIS_J1, q1) * \
          A12 * \
          axis_angle_matrix(AXIS_J2, q2) * \
          A23 * \
          axis_angle_matrix(AXIS_J3, q3) * \
          A3E

# Total: T_ee = T_base * T_chain
print("Combining everything (this may take a moment)...")
T_ee = T_base * T_chain

# --- 4. EXTRACT RPY FORMULAS ---

# We only need the Rotation part (3x3 top left)
# Pitch = asin(-R31)
# Roll  = atan2(R32, R33)
# Yaw   = atan2(R21, R11)

r11 = T_ee[0, 0]
r21 = T_ee[1, 0]
r31 = T_ee[2, 0]
r32 = T_ee[2, 1]
r33 = T_ee[2, 2]

# --- 5. CODE GENERATION WITH CSE ---
# CSE (Common Subexpression Elimination) finds repeated math (like sin(q1))
# and creates temporary variables for them, making the code super fast.

print("Optimizing C code...")
replacements, (calc_r11, calc_r21, calc_r31, calc_r32, calc_r33) = sp.cse(
    [r11, r21, r31, r32, r33], 
    symbols=sp.numbered_symbols("tmp_")
)

# --- 6. WRITE TO FILE ---

with open("fast_fk.c", "w") as f:
    f.write("#include <math.h>\n\n")
    f.write("void fast_fk(double base_roll, double base_pitch, double base_yaw, \n")
    f.write("             double q1, double q2, double q3, \n")
    f.write("             double *ee_roll, double *ee_pitch, double *ee_yaw) {\n\n")
    
    f.write("    // Optimized Intermediate Variables\n")
    for symbol, expr in replacements:
        # Convert sympy syntax to C syntax
        c_expr = sp.printing.ccode(expr)
        f.write(f"    double {symbol} = {c_expr};\n")
    
    f.write("\n    // Rotation Matrix Elements\n")
    f.write(f"    double r11 = {sp.printing.ccode(calc_r11)};\n")
    f.write(f"    double r21 = {sp.printing.ccode(calc_r21)};\n")
    f.write(f"    double r31 = {sp.printing.ccode(calc_r31)};\n")
    f.write(f"    double r32 = {sp.printing.ccode(calc_r32)};\n")
    f.write(f"    double r33 = {sp.printing.ccode(calc_r33)};\n")
    
    f.write("\n    // Final RPY Extraction\n")
    f.write("    *ee_pitch = asin(-r31);\n")
    f.write("    if (fabs(*ee_pitch) >= 1.5707) {\n")
    f.write("        *ee_roll = 0.0;\n")
    f.write("        // Simplify for gimbal lock if needed, or keep generic\n")
    f.write("        *ee_yaw = 0.0; // Fallback\n")
    f.write("    } else {\n")
    f.write("        *ee_roll = atan2(r32, r33);\n")
    f.write("        *ee_yaw  = atan2(r21, r11);\n")
    f.write("    }\n")
    f.write("}\n")

print("Done! Generated 'fast_fk.c'")