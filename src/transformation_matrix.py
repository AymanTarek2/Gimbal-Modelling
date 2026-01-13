import sympy as sp
import re
import os
import math

# ==============================================================================
# 1. PARSING FUNCTION (FIXED)
#    Handles "0.75q1", numbers, AND existing SymPy expressions
# ==============================================================================
def parse_user_input(val):
    """
    Parses a value into a SymPy object.
    """
    if val is None:
        return None
    
    # FIX: If it is already a SymPy object (like sp.rad(165)), return it directly.
    if isinstance(val, sp.Basic):
        return val
    
    if isinstance(val, (int, float)):
        return sp.sympify(val)

    if isinstance(val, str):
        val = val.replace(" ", "")
        try:
            return sp.sympify(val)
        except:
            pass

        match = re.match(r'^(-?\d*\.?\d*)([a-zA-Z_].*)$', val)
        if match:
            coeff_str, var_name = match.groups()
            if coeff_str == "" or coeff_str == "+": coeff = 1
            elif coeff_str == "-": coeff = -1
            else: coeff = float(coeff_str)
            
            if re.search(r'\d+$', var_name) and '_' not in var_name:
                name_match = re.match(r'([a-zA-Z]+)(\d+)$', var_name)
                if name_match:
                    base, num = name_match.groups()
                    var_name = f"{base}_{num}"

            return coeff * sp.Symbol(var_name)
            
    return sp.Symbol(val)

# ==============================================================================
# 2. MATRIX BUILDER FUNCTION
# ==============================================================================
def build_transformation_matrix(index=None, **kwargs):
    
    def get_var(base_name):
        if base_name in kwargs:
            return parse_user_input(kwargs[base_name])
        
        if index is not None:
            if "theta" in base_name:
                axis = base_name.split('_')[1]
                latex_name = fr"\theta_{{{axis}{index}}}"
                return sp.Symbol(latex_name)
            else:
                return sp.Symbol(f"{base_name}_{index}")
        
        if "theta" in base_name:
            axis = base_name.split('_')[1]
            return sp.Symbol(fr"\theta_{axis}")
        return sp.Symbol(base_name)

    x = get_var('x')
    y = get_var('y')
    z = get_var('z')
    tx = get_var('theta_x')
    ty = get_var('theta_y')
    tz = get_var('theta_z')

    Rx = sp.Matrix([[1, 0, 0], [0, sp.cos(tx), -sp.sin(tx)], [0, sp.sin(tx), sp.cos(tx)]])
    Ry = sp.Matrix([[sp.cos(ty), 0, sp.sin(ty)], [0, 1, 0], [-sp.sin(ty), 0, sp.cos(ty)]])
    Rz = sp.Matrix([[sp.cos(tz), -sp.sin(tz), 0], [sp.sin(tz), sp.cos(tz), 0], [0, 0, 1]])

    R = Rz * Ry * Rx
    T = sp.eye(4)
    T[0:3, 0:3] = R
    T[0, 3] = x
    T[1, 3] = y
    T[2, 3] = z

    return sp.simplify(T)

# ==============================================================================
# 3. LATEX WRITER FUNCTION (UPDATED PREAMBLE FOR LEFT ALIGNMENT)
# ==============================================================================
def append_matrix_to_tex(matrix, filename, description="Transformation Matrix"):
    
    subs_map = {}
    for term in matrix.atoms(sp.sin, sp.cos):
        args = term.args[0]
        angle_latex = sp.latex(args)
        
        if angle_latex.startswith('{') and angle_latex.endswith('}'):
            angle_latex = angle_latex[1:-1]
            
        if r"\theta_" in angle_latex:
            angle_latex = angle_latex.replace(r"\theta_", "")
            angle_latex = angle_latex.replace("{", "").replace("}", "")
            
        if isinstance(term, sp.sin):
            new_sym = sp.Symbol(fr"S_{{{angle_latex}}}")
            subs_map[term] = new_sym
        elif isinstance(term, sp.cos):
            new_sym = sp.Symbol(fr"C_{{{angle_latex}}}")
            subs_map[term] = new_sym
            
    # Force decimal representation with .evalf(3)
    matrix_compact = matrix.subs(subs_map).evalf(3)
    
    rows, cols = matrix_compact.shape
    col_spec = ":".join(["c"] * cols)
    
    row_lines = []
    for i in range(rows):
        cell_strs = [sp.latex(matrix_compact[i, j]) for j in range(cols)]
        row_str = " & ".join(cell_strs)
        row_lines.append(row_str)
    
    body_str = ""
    for i, line in enumerate(row_lines):
        body_str += line + r" \\"
        if i < rows - 1:
            body_str += "\n" + r"\hdashline" + "\n"
            
    latex_code = (
        r"\left[" + "\n"
        r"\begin{array}{" + col_spec + r"}" + "\n"
        + body_str + "\n"
        r"\end{array}" + "\n"
        r"\right]"
    )

    file_exists = os.path.isfile(filename)
    with open(filename, "a") as f:
        if not file_exists:
            # FIX: Use [fleqn] to force left alignment of equations
            f.write(r"\documentclass[fleqn]{article}" + "\n")
            f.write(r"\usepackage{amsmath}" + "\n")
            f.write(r"\usepackage{graphicx}" + "\n")
            f.write(r"\usepackage{arydshln}" + "\n") 
            f.write(r"\usepackage[a4paper, margin=0.5in, landscape]{geometry}" + "\n")
            # FIX: Add breqn package for splitting long scalar equations
            f.write(r"\usepackage{breqn}" + "\n")
            # FIX: Set math indent to 0 to ensure it starts at the very left
            f.write(r"\setlength{\mathindent}{0pt}" + "\n")
            f.write(r"\renewcommand{\arraystretch}{1.5}" + "\n") 
            # FIX: Define a savebox for handling large equations
            f.write(r"\newsavebox{\mybox}" + "\n")
            f.write(r"\begin{document}" + "\n")
        
        f.write(r"\section*{" + description + "}" + "\n")
        f.write(r"\noindent" + "\n")
        
        # FIX: Use lrbox environment instead of \sbox to prevent overflow
        f.write(r"\begin{lrbox}{\mybox}" + "\n")
        f.write(r"$" + latex_code + r"$" + "\n")
        f.write(r"\end{lrbox}" + "\n")
        
        f.write(r"\ifdim\wd\mybox>\textwidth" + "\n")
        f.write(r"\resizebox{\textwidth}{!}{\usebox{\mybox}}" + "\n") 
        f.write(r"\else" + "\n")
        f.write(r"\usebox{\mybox}" + "\n")
        f.write(r"\fi" + "\n")
        f.write(r"\vspace{0.5cm}" + "\n")

    print(f"Added '{description}' to {filename}")

# ==============================================================================
# NEW: EQUATION WRITER FUNCTION (UPDATED FOR SCALAR SPLITTING & DOT NOTATION)
# ==============================================================================
def append_equations_to_tex(filename, title, equations):
    """
    Appends equations. Use dmath for scalars (breaking lines) and resizebox for matrices.
    Also substitutes 'd' variables (dx, dtheta) with proper LaTeX dot notation.
    """
    with open(filename, "a") as f:
        f.write(r"\section*{" + title + "}" + "\n")
        for lhs, rhs in equations:
            
            # 1. Velocity Formatting (Convert 'dtheta_x0' to '\dot{\theta}_{x0}')
            vel_map = {}
            for sym in rhs.free_symbols:
                name = str(sym)
                # Handle first derivative (d...)
                if name.startswith("d") and not name.startswith("dd"):
                    base_name = name[1:]
                    if "_" in base_name:
                        base, sub = base_name.split("_", 1)
                        sub_clean = sub.replace("{", "").replace("}", "")
                        new_latex = fr"\dot{{{base}}}_{{{sub_clean}}}"
                    elif re.search(r'\d+$', base_name):
                        match = re.match(r"([a-zA-Z]+)(\d+)", base_name)
                        if match: new_latex = fr"\dot{{{match.group(1)}}}_{match.group(2)}"
                        else: new_latex = fr"\dot{{{base_name}}}"
                    else: new_latex = fr"\dot{{{base_name}}}"
                    vel_map[sym] = sp.Symbol(new_latex)
                # Handle second derivative (dd...)
                elif name.startswith("dd"):
                    base_name = name[2:]
                    if "_" in base_name:
                        base, sub = base_name.split("_", 1)
                        sub_clean = sub.replace("{", "").replace("}", "")
                        new_latex = fr"\ddot{{{base}}}_{{{sub_clean}}}"
                    elif re.search(r'\d+$', base_name):
                        match = re.match(r"([a-zA-Z]+)(\d+)", base_name)
                        if match: new_latex = fr"\ddot{{{match.group(1)}}}_{match.group(2)}"
                        else: new_latex = fr"\ddot{{{base_name}}}"
                    else: new_latex = fr"\ddot{{{base_name}}}"
                    vel_map[sym] = sp.Symbol(new_latex)
            
            rhs = rhs.subs(vel_map)

            # 2. Trig Formatting (Convert sin/cos)
            subs_map = {}
            for term in rhs.atoms(sp.sin, sp.cos):
                args = term.args[0]
                angle_latex = sp.latex(args)
                if angle_latex.startswith('{') and angle_latex.endswith('}'): angle_latex = angle_latex[1:-1]
                if r"\theta_" in angle_latex:
                    angle_latex = angle_latex.replace(r"\theta_", "").replace("{", "").replace("}", "")
                
                if isinstance(term, sp.sin): subs_map[term] = sp.Symbol(fr"S_{{{angle_latex}}}")
                elif isinstance(term, sp.cos): subs_map[term] = sp.Symbol(fr"C_{{{angle_latex}}}")
            
            # Force decimal and apply substitution
            rhs_clean = rhs.subs(subs_map).evalf(3)
            
            # Check if result is a Matrix or Scalar
            is_matrix = getattr(rhs_clean, 'is_Matrix', False) or isinstance(rhs_clean, sp.Matrix)
            
            latex_rhs = sp.latex(rhs_clean)

            if is_matrix:
                # MATRIX: Use resizebox to fit on one line/block
                eq_code = r"$" + lhs + r" = " + latex_rhs + r"$"
                f.write(r"\noindent" + "\n")
                f.write(r"\begin{lrbox}{\mybox}" + "\n")
                f.write(eq_code + "\n")
                f.write(r"\end{lrbox}" + "\n")
                f.write(r"\ifdim\wd\mybox>\textwidth" + "\n")
                f.write(r"\resizebox{\textwidth}{!}{\usebox{\mybox}}" + "\n")
                f.write(r"\else" + "\n")
                f.write(r"\usebox{\mybox}" + "\n")
                f.write(r"\fi" + "\n")
            else:
                # SCALAR (KE/PE): Use dmath environment to break lines automatically
                # FIX: Remove \left and \right to prevent unbreakable blocks in dmath
                latex_rhs = latex_rhs.replace(r"\left", "").replace(r"\right", "")
                
                # FIX: SMART LINE BREAKING to prevent "Document Too Long"
                # Insert newline after operator if line is > 500 chars
                clean_rhs = ""
                line_len = 0
                for i, char in enumerate(latex_rhs):
                    clean_rhs += char
                    line_len += 1
                    # Break line nicely after + or -
                    if line_len > 500 and char in ['+', '-']:
                        clean_rhs += "\n"
                        line_len = 0
                latex_rhs = clean_rhs

                # FIX: Make font SMALLEST POSSIBLE specifically for huge equations
                if "Rotational" in title or "Equation" in title or "Torque" in title:
                    f.write(r"{\fontsize{1}{2}\selectfont" + "\n")
                
                # FIX: [indentstep=0pt] ensures subsequent lines are NOT indented/shifted right
                f.write(r"\begin{dmath*}[indentstep=0pt]" + "\n")
                f.write(lhs + r" = " + latex_rhs + "\n")
                f.write(r"\end{dmath*}" + "\n")
                
                if "Rotational" in title or "Equation" in title or "Torque" in title:
                    f.write(r"}" + "\n")
            
            # Add explicit vertical space between elements
            f.write(r"\vspace{0.8cm}" + "\n")
            
    print(f"Added equations for '{title}' to {filename}")

# ==============================================================================
# NEW: JACOBIAN WRITER FUNCTION
# ==============================================================================
def append_jacobian_to_tex(filename, title, jacobian_matrix, vel_symbols, index=""):
    """
    Writes the Jacobian equation v = J * q_dot in the requested format.
    """
    
    # 1. Process Jacobian Matrix (Decimal + Trig subs)
    subs_map = {}
    for term in jacobian_matrix.atoms(sp.sin, sp.cos):
        args = term.args[0]
        angle_latex = sp.latex(args)
        if angle_latex.startswith('{') and angle_latex.endswith('}'): angle_latex = angle_latex[1:-1]
        if r"\theta_" in angle_latex:
            angle_latex = angle_latex.replace(r"\theta_", "").replace("{", "").replace("}", "")
        
        if isinstance(term, sp.sin): subs_map[term] = sp.Symbol(fr"S_{{{angle_latex}}}")
        elif isinstance(term, sp.cos): subs_map[term] = sp.Symbol(fr"C_{{{angle_latex}}}")
            
    jacobian_clean = jacobian_matrix.subs(subs_map).evalf(3)
    
    # 2. Build LaTeX for Jacobian Matrix
    rows, cols = jacobian_clean.shape
    col_spec = ":".join(["c"] * cols)
    
    row_lines = []
    for i in range(rows):
        cell_strs = [sp.latex(jacobian_clean[i, j]) for j in range(cols)]
        row_str = " & ".join(cell_strs)
        row_lines.append(row_str)
    
    jac_body = ""
    for i, line in enumerate(row_lines):
        jac_body += line + r" \\"
        if i < rows - 1:
            jac_body += "\n" + r"\hdashline" + "\n"
            
    latex_jac = (
        r"\left[" + "\n"
        r"\begin{array}{" + col_spec + r"}" + "\n"
        + jac_body + "\n"
        r"\end{array}" + "\n"
        r"\right]"
    )
    
    # 3. Build Velocity Vector (q_dot)
    # FIX: Logic to place dot strictly over the base symbol
    vel_lines = []
    for s in vel_symbols:
        s_str = str(s)
        if "_" in s_str:
            base, sub = s_str.split("_", 1)
            sub_clean = sub.replace("{", "").replace("}", "")
            # Place dot over base, subscript outside
            latex_s = fr"\dot{{{base}}}_{{{sub_clean}}}"
        else:
            latex_s = fr"\dot{{{s_str}}}"
        vel_lines.append(latex_s)
        
    vel_vec_latex = r"\begin{bmatrix} " + r" \\ ".join(vel_lines) + r" \end{bmatrix}"
    
    # 4. LHS Vector - Use Index
    idx_str = str(index) if index else ""
    lhs_vec = r"\begin{bmatrix} v_{x" + idx_str + r"} \\ v_{y" + idx_str + r"} \\ v_{z" + idx_str + r"} \end{bmatrix}"
    
    # 5. Combine
    full_eq = r"$" + lhs_vec + r" = " + latex_jac + vel_vec_latex + r"$"

    with open(filename, "a") as f:
        f.write(r"\section*{" + title + "}" + "\n")
        f.write(r"\noindent" + "\n")
        
        # FIX: THE CRITICAL FIX IS HERE - use lrbox instead of sbox
        f.write(r"\begin{lrbox}{\mybox}" + "\n")
        f.write(full_eq + "\n") # Write content on new line inside box
        f.write(r"\end{lrbox}" + "\n")
        
        f.write(r"\ifdim\wd\mybox>\textwidth" + "\n")
        f.write(r"\resizebox{\textwidth}{!}{\usebox{\mybox}}" + "\n") 
        f.write(r"\else" + "\n")
        f.write(r"\usebox{\mybox}" + "\n")
        f.write(r"\fi" + "\n")
        f.write(r"\vspace{0.8cm}" + "\n")
        
    print(f"Added Jacobian for '{title}' to {filename}")

# ==============================================================================
# NEW: DYNAMICS DECOMPOSITION WRITER
# ==============================================================================
def append_dynamics_decomposition(filename, tau_vector, active_q_ddot, active_q_dot, q_ddot_syms, q_dot_syms):
    """
    Decomposes Tau = M(q)q_dd + C(q, q_d) + G(q) and prints M, C, G matrices.
    """
    print("Decomposing Dynamics (Matrix Form)...")
    
    # 1. Extract Mass Matrix (Jacobian of Torque w.r.t Acceleration)
    # NO SIMPLIFY - SPEED OPTIMIZATION
    M_mat = tau_vector.jacobian(active_q_ddot)
    
    # 2. Extract Gravity (Torque when velocities and accelerations are zero)
    # Map all derivatives to 0
    zero_subs = {sym: 0 for sym in q_dot_syms}
    zero_subs.update({sym: 0 for sym in q_ddot_syms})
    
    # Use xreplace for speed
    G_vec = tau_vector.xreplace(zero_subs)
    
    # 3. Extract Coriolis/Centrifugal (The remainder)
    # C(q, q_dot) = Tau - M*q_ddot - G
    # NO SIMPLIFY - SPEED OPTIMIZATION
    C_vec = tau_vector - M_mat * active_q_ddot - G_vec
    
    # --- WRITE TO FILE ---
    
    with open(filename, "a") as f:
        f.write(r"\section*{9. Equations of Motion (Matrix Form)}" + "\n")
        f.write(r"\noindent The system dynamics are described by: " + "\n")
        f.write(r"\begin{equation*} \mathbf{M}(q)\ddot{\mathbf{q}} + \mathbf{C}(q, \dot{q}) + \mathbf{G}(q) = \boldsymbol{\tau} \end{equation*}" + "\n")
        f.write(r"\vspace{0.5cm}" + "\n")

    # B. Mass Matrix (Square)
    append_matrix_to_tex(M_mat, filename, r"9.1 Mass Matrix ($\mathbf{M}_{3 \times 3}$)")

    # C. Coriolis Vector (Column Vector)
    append_matrix_to_tex(C_vec, filename, r"9.2 Coriolis \& Centrifugal Vector ($\mathbf{C}_{3 \times 1}$)")
    
    # D. Gravity Vector (Column Vector)
    append_matrix_to_tex(G_vec, filename, r"9.3 Gravity Vector ($\mathbf{G}_{3 \times 1}$)")

# ==============================================================================
# 4. SUBSTITUTE & PRINT FUNCTION
# ==============================================================================
def substitute_matrix(matrix, **kwargs):
    """
    Substitutes values with smart symbol matching and cleans float errors.
    """
    symbol_map = {}
    for sym in matrix.free_symbols:
        raw_name = str(sym)
        clean_name = raw_name.replace("\\", "").replace("{", "").replace("}", "")
        symbol_map[clean_name] = sym
        symbol_map[raw_name] = sym

    subs_dict = {}
    for key, val in kwargs.items():
        # FIX: Skip substitution if val is None, leaving the symbol as is
        if val is None:
            continue

        parsed_val = parse_user_input(val)
        if key in symbol_map:
            actual_symbol = symbol_map[key]
            subs_dict[actual_symbol] = parsed_val
        else:
            subs_dict[sp.Symbol(key)] = parsed_val
        
    new_matrix = matrix.subs(subs_dict).evalf()
    
    threshold = 1e-6
    def clean_element(elem):
        if elem.is_number:
            try:
                if abs(float(elem)) < threshold:
                    return sp.Integer(0)
            except (TypeError, ValueError):
                pass
        return elem

    new_matrix = new_matrix.applyfunc(clean_element)
    
    print(f"\n>>> Substitution Result ({kwargs}):")
    remaining = [str(s) for s in new_matrix.free_symbols]
    print(f"    Remaining vars: {remaining}")
    
    return new_matrix

# ==============================================================================
# MAIN EXECUTION BLOCK
# ==============================================================================
if __name__ == "__main__":
    output_file = "gimbal_matrices.tex"
    if os.path.exists(output_file):
        os.remove(output_file)


    # ==========================================================================
    # 1. LINK 1: BASE -> MOTOR 1 -> COM 1
    # ==========================================================================
    T_base = build_transformation_matrix(index=0)
    append_matrix_to_tex(T_base, output_file, r"1.1 Base Transformation ($T_{W \to B}$)")

    T_rot_q1 = build_transformation_matrix(index=1, x=0, y=0, z=0, theta_x=0, theta_y="q1", theta_z=0)
    append_matrix_to_tex(T_rot_q1, output_file, r"1.2 Link 1 Rotation ($T_{Rot(q1)}$)")

    T_com1_offset = build_transformation_matrix(index=None, x=0, y="0.08822", z="0.02554", theta_x=0, theta_y=0, theta_z=0)
    
    # OPTIMIZATION: Calculate the chain up to link 1 end once
    T_chain_1 = sp.simplify(T_base * T_rot_q1)
    
    T_com1 = sp.simplify(T_chain_1 * T_com1_offset)
    append_matrix_to_tex(T_com1, output_file, r"1.3 Absolute $T_{com1}$")

    T_com1_subbed = substitute_matrix(T_com1, x_0=0, y_0=0, z_0=0, theta_x0=0, theta_y0=0, theta_z0=0, q1=0)
    append_matrix_to_tex(T_com1_subbed, output_file, r"1.4 Substituted $T_{com1}$")


    # ==========================================================================
    # 2. LINK 2: MOTOR 1 -> MOTOR 2 -> COM 2
    # ==========================================================================
    T_mot1_to_mot2 = build_transformation_matrix(index=None, x=0, y="0.13548", z="0", theta_x=0, theta_y=0, theta_z=0)
    append_matrix_to_tex(T_mot1_to_mot2, output_file, r"2.1 Arm Translation ($T_{J1 \to J2}$)")
    
    tilt_angle = sp.rad(15 - 180)
    
    T_Static_Tilt = build_transformation_matrix(index=None, x=0, y=0, z=0, theta_x=tilt_angle, theta_y=0, theta_z=0)
    T_Dynamic_q2 = build_transformation_matrix(index=2, x=0, y=0, z=0, theta_x=0, theta_y=0, theta_z="q2")
    
    T_rot_q2 = sp.simplify(T_Static_Tilt * T_Dynamic_q2)
    append_matrix_to_tex(T_rot_q2, output_file, "2.2 Motor 2 Full Rotation (Tilt + Spin)")
    
    
    P_global = sp.Matrix([0, -0.00051, -0.06656])
    
    c_tilt, s_tilt = sp.cos(tilt_angle), sp.sin(tilt_angle)
    Rx_tilt = sp.Matrix([[1, 0, 0], [0, c_tilt, -s_tilt], [0, s_tilt, c_tilt]])
    P_local = Rx_tilt.T * P_global
    
    T_Offset_to_COM2 = build_transformation_matrix(index=None, x=0, y=P_local[1], z=P_local[2], theta_x=0, theta_y=0, theta_z=0)
    
    # OPTIMIZATION: Calculate chain up to link 2 end using T_chain_1
    T_chain_2 = sp.simplify(T_chain_1 * T_mot1_to_mot2 * T_rot_q2)
    
    T_com2 = sp.simplify(T_chain_2 * T_Offset_to_COM2)
    append_matrix_to_tex(T_com2, output_file, r"2.3 Absolute $T_{com2}$")

    T_com2_subbed = substitute_matrix(T_com2, x_0=0, y_0=0, z_0=0, theta_x0=0, theta_y0=0, theta_z0=0, q1=0, q2=0)
    append_matrix_to_tex(T_com2_subbed, output_file, r"2.4 Substituted $T_{com2}$")
    
    
    # ==========================================================================
    # 3. LINK 3: MOTOR 2 -> MOTOR 3 -> COM 3
    # ==========================================================================    
    P_global_m2_m3 = sp.Matrix([0, 0.03734, -0.09309]) 
    P_local_m2_m3 = Rx_tilt.T * P_global_m2_m3
    
    T_Link3_Combined = build_transformation_matrix(index=3, x=0, y=P_local_m2_m3[1], z=P_local_m2_m3[2], 
                                               theta_x=-tilt_angle, theta_y="q3", theta_z=0)
    
    append_matrix_to_tex(T_Link3_Combined, output_file, r"3.1 Link 3 Combined (Trans+Nullify+Rot)")

    # OPTIMIZATION: Use T_chain_2 for the final link
    T_com3 = sp.simplify(T_chain_2 * T_Link3_Combined)
    append_matrix_to_tex(T_com3, output_file, r"3.2 Absolute $T_{com3}$")

    # CORRECTED LINE: REMOVED THE INCORRECT TUPLE/PARENTHESIS STRUCTURE
    T_com3_subbed = substitute_matrix(T_com3, x_0=0, y_0=0, z_0=0, theta_x0=0, theta_y0=0, theta_z0=0, q1=0, q2=0, q3=0)
    append_matrix_to_tex(T_com3_subbed, output_file, r"3.3 Substituted $T_{com3}$")

    # ==========================================================================
    # 4. EXPLICIT HEIGHTS AND POSITIONS OUTPUT
    # ==========================================================================
    
    # Extract Heights (Y value is index 1 in [x,y,z])
    h1 = T_com1[1, 3]
    h2 = T_com2[1, 3]
    h3 = T_com3[1, 3]
    
    # Separate calls to prevent stacking issues
    append_equations_to_tex(output_file, "Height 1", [("h_1", h1)])
    append_equations_to_tex(output_file, "Height 2", [("h_2", h2)])
    append_equations_to_tex(output_file, "Height 3", [("h_3", h3)])

    # Extract Full XYZ Positions (First 3 rows of last column)
    pos1 = T_com1[0:3, 3]
    pos2 = T_com2[0:3, 3]
    pos3 = T_com3[0:3, 3]
    
    # Separate calls to prevent stacking issues and use Vector notation for LHS
    append_equations_to_tex(output_file, "COM 1 Position", [(r"\begin{bmatrix} x_1 \\ y_1 \\ z_1 \end{bmatrix}", pos1)])
    append_equations_to_tex(output_file, "COM 2 Position", [(r"\begin{bmatrix} x_2 \\ y_2 \\ z_2 \end{bmatrix}", pos2)])
    append_equations_to_tex(output_file, "COM 3 Position", [(r"\begin{bmatrix} x_3 \\ y_3 \\ z_3 \end{bmatrix}", pos3)])

    # ==========================================================================
    # 5. LINEAR VELOCITY JACOBIANS (NEW)
    # ==========================================================================
    
    # Define the 9 generalized coordinates
    # These must match the Symbols used in build_transformation_matrix
    q_vars = [
        sp.Symbol("x_0"), sp.Symbol("y_0"), sp.Symbol("z_0"),
        sp.Symbol(r"\theta_{x0}"), sp.Symbol(r"\theta_{y0}"), sp.Symbol(r"\theta_{z0}"),
        sp.Symbol("q1"), sp.Symbol("q2"), sp.Symbol("q3")
    ]
    
    # Symbols for display in the velocity vector (for the LaTeX writer)
    vel_display_names = [
        "x_0", "y_0", "z_0",
        r"\theta_{x0}", r"\theta_{y0}", r"\theta_{z0}",
        "q_1", "q_2", "q_3"
    ]

    # Compute and Write Jacobians
    # Jacobian is computed by differentiating the Position Vector (pos) w.r.t the 9 variables
    
    J1 = sp.simplify(pos1.jacobian(q_vars))
    append_jacobian_to_tex(output_file, "Linear Jacobian 1 ($J_{v1}$)", J1, vel_display_names, index=1)

    J2 = sp.simplify(pos2.jacobian(q_vars))
    append_jacobian_to_tex(output_file, "Linear Jacobian 2 ($J_{v2}$)", J2, vel_display_names, index=2)

    J3 = sp.simplify(pos3.jacobian(q_vars))
    append_jacobian_to_tex(output_file, "Linear Jacobian 3 ($J_{v3}$)", J3, vel_display_names, index=3)
    
    
    # Create velocity state vector (q_dot)
    q_dot = sp.Matrix([sp.Symbol(f"d{v.name}") for v in q_vars]) # dName for derivative
    
    # Calculate Velocity Vectors: v = J * q_dot
    v1 = sp.simplify(J1 * q_dot)
    append_equations_to_tex(output_file, "Velocity 1", [("v_1", v1)])
    
    v2 = sp.simplify(J2 * q_dot)
    append_equations_to_tex(output_file, "Velocity 2", [("v_2", v2)])
    
    v3 = sp.simplify(J3 * q_dot)
    append_equations_to_tex(output_file, "Velocity 3", [("v_3", v3)])
    
    
    # ==========================================================================
    # 6. POTENTIAL ENERGY (PE = m * g * h)
    # ==========================================================================
    
    g = 9.81
    m1 = 0.25728 # 257.28g in kg
    m2 = 0.24066 # 240.66g in kg
    m3 = 0.07284 # 72.84g in kg
    
    PE1 = sp.simplify(m1 * g * h1)
    append_equations_to_tex(output_file, "Potential Energy 1", [("PE_1", PE1)])

    PE2 = sp.simplify(m2 * g * h2)
    append_equations_to_tex(output_file, "Potential Energy 2", [("PE_2", PE2)])

    PE3 = sp.simplify(m3 * g * h3)
    append_equations_to_tex(output_file, "Potential Energy 3", [("PE_3", PE3)])

    # ==========================================================================
    # 7. LINEAR KINETIC ENERGY (KE = 0.5 * m * v.T * v)
    # ==========================================================================
    
    KE1 = (0.5 * m1 * (v1.dot(v1)))
    append_equations_to_tex(output_file, "Linear Kinetic Energy 1", [("KE_{linear,1}", KE1)])
    
    KE2 = (0.5 * m2 * (v2.dot(v2)))
    append_equations_to_tex(output_file, "Linear Kinetic Energy 2", [("KE_{linear,2}", KE2)])

    KE3 = (0.5 * m3 * (v3.dot(v3)))
    append_equations_to_tex(output_file, "Linear Kinetic Energy 3", [("KE_{linear,3}", KE3)])

    # ==========================================================================
    # 8. ROTATIONAL KINETIC ENERGY (New Section)
    # ==========================================================================
    
    # 1. Define Inertia Tensors (scaled by 1e-9 for SI units kg*m^2)
    scale = 1e-9
    I1 = sp.Matrix([
        [897498.65, 0.62, 0.24],
        [0.62, 210513.19, 114397.38],
        [0.24, 114397.38, 804807.69]
    ]) * scale

    I2 = sp.Matrix([
        [540057.38, 2.31, -0.68],
        [2.31, 500181.27, 49080.71],
        [-0.68, 49080.71, 157559.95]
    ]) * scale

    I3 = sp.Matrix([
        [28901.95, 0.0, 0.0],
        [0.0, 53236.19, 0.0],
        [0.0, 0.0, 28901.95]
    ]) * scale

    # 2. Recursive Angular Velocity Calculation
    # Base Angular Velocity (Quasi-coordinate derivative)
    w_base = sp.Matrix([q_dot[3], q_dot[4], q_dot[5]]) # dtheta_x0, dtheta_y0, dtheta_z0

    # Extract Rotation Matrices
    R_base = sp.simplify(T_base[0:3, 0:3])
    R1 = sp.simplify(T_chain_1[0:3, 0:3]) # World to Link 1
    R2 = sp.simplify(T_chain_2[0:3, 0:3]) # World to Link 2
    R3 = sp.simplify(T_com3[0:3, 0:3])    # World to Link 3 (End)

    # Link 1: Rotates around Y of Base (Column 1 of R_base)
    axis_1 = R_base.col(1) 
    dq1 = q_dot[6]
    w_1_world = sp.simplify(w_base + dq1 * axis_1)
    w_1_body = sp.simplify(R1.T * w_1_world)
    
    append_equations_to_tex(output_file, "Body Angular Velocity 1", [(r"\boldsymbol{\omega}_{1,body}", w_1_body)])

    # Link 2: Rotates around Z of Link 1 (Column 2 of R1)
    axis_2 = R1.col(2)
    dq2 = q_dot[7]
    w_2_world = sp.simplify(w_1_world + dq2 * axis_2)
    w_2_body = sp.simplify(R2.T * w_2_world)

    append_equations_to_tex(output_file, "Body Angular Velocity 2", [(r"\boldsymbol{\omega}_{2,body}", w_2_body)])

    # Link 3: Rotates around Y of Link 2 (Column 1 of R2)
    axis_3 = R2.col(1)
    dq3 = q_dot[8]
    w_3_world = sp.simplify(w_2_world + sp.simplify(dq3 * axis_3))
    w_3_body = (R3.T * w_3_world)

    append_equations_to_tex(output_file, "Body Angular Velocity 3", [(r"\boldsymbol{\omega}_{3,body}", w_3_body)])

    # 4. Calculate Rotational Energies
    # T_rot = 0.5 * w.T * I * w
    KE_rot_1 = 0.5 * w_1_body.dot(I1 * w_1_body)  #, list(q_dot))
    append_equations_to_tex(output_file, "Rotational Kinetic Energy 1", [("KE_{rot,1}", KE_rot_1)])

    KE_rot_2 = 0.5 * w_2_body.dot(I2 * w_2_body)  #, list(q_dot))
    append_equations_to_tex(output_file, "Rotational Kinetic Energy 2", [("KE_{rot,2}", KE_rot_2)])

    KE_rot_3 = 0.5 * w_3_body.dot(I3 * w_3_body)  #, list(q_dot))
    append_equations_to_tex(output_file, "Rotational Kinetic Energy 3", [("KE_{rot,3}", KE_rot_3)])

    # ==========================================================================
    # 9. LAGRANGIAN & EQUATIONS OF MOTION (New Section)
    # ==========================================================================

    # 1. Total Energies
    T_total = KE1 + KE2 + KE3 + KE_rot_1 + KE_rot_2 + KE_rot_3
    V_total = PE1 + PE2 + PE3
    L = T_total - V_total

    # 2. Acceleration State Vector (q_ddot)
    # For time derivative calculation: d(q)/dt = q_dot, d(q_dot)/dt = q_ddot
    q_ddot = sp.Matrix([sp.Symbol(f"dd{v.name}") for v in q_vars])

    # Helper function for time derivative (chain rule)
    def time_derivative(expr, q, dq, ddq):
        dt_expr = 0
        # Partial wrt q * q_dot
        for i in range(len(q)):
            dt_expr += sp.diff(expr, q[i]) * dq[i]
        # Partial wrt q_dot * q_ddot
        for i in range(len(dq)):
            dt_expr += sp.diff(expr, dq[i]) * ddq[i]
        return dt_expr

    # 3. Compute Euler-Lagrange Equations for q1, q2, q3 (Indices 6, 7, 8)
    # equation: d/dt (dL/d(dq)) - dL/dq = tau
    
    torque_eqs = []
    active_joints = [6, 7, 8] # q1, q2, q3
    
    for i in active_joints:
        q_i = q_vars[i]
        dq_i = q_dot[i]
        
        # Term 1: Partial L wrt q_dot
        dL_ddq = sp.diff(L, dq_i)
        
        # Term 2: Time derivative of Term 1
        # Note: We strictly use the manual chain rule to avoid sympy mechanics overhead
        d_dt_dL_ddq = time_derivative(dL_ddq, q_vars, q_dot, q_ddot)
        
        # Term 3: Partial L wrt q
        dL_dq = sp.diff(L, q_i)
        
        # Torque Equation
        tau = d_dt_dL_ddq - dL_dq
        
        # Save just the expression
        torque_eqs.append(tau)

    # 4. Append to Document (MATRIX DECOMPOSITION)
    # Form the Torque Vector
    tau_vector = sp.Matrix(torque_eqs)
    
    # Active Acceleration Vector for the 3 joints
    active_q_ddot = sp.Matrix([q_ddot[6], q_ddot[7], q_ddot[8]])
    active_q_dot = sp.Matrix([q_dot[6], q_dot[7], q_dot[8]])
    
    # Use the new function to print the Matrix Form M(q)q_dd + C + G = tau
    append_dynamics_decomposition(output_file, tau_vector, active_q_ddot, active_q_dot, q_ddot, q_dot)


    with open(output_file, "a") as f:
        f.write(r"\end{document}" + "\n")
        
    print(f"\nDone! Output saved to {output_file}")