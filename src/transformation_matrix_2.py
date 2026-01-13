import sympy as sp
import os
import shutil
import re

def generate_dynamics():
    print("Initializing Symbolic Variables...")

    # 1.1 Generalized Coordinates (9 DOF)
    q1, q2, q3 = sp.symbols('q1 q2 q3')
    dq1, dq2, dq3 = sp.symbols('dq1 dq2 dq3')

    # Base Orientation (Euler XYZ - MuJoCo Standard)
    bx, by, bz = sp.symbols('bx by bz')
    dbx, dby, dbz = sp.symbols('dbx dby dbz')  # Euler rates

    # Base Position (World Frame)
    px, py, pz = sp.symbols('px py pz')
    dpx, dpy, dpz = sp.symbols('dpx dpy dpz')  # World linear velocity rates

    # --- HARDCODED PARAMETERS ---
    L1 = 0.08822
    L2 = 0.13548
    g = 9.81

    # Groupings
    dq_all = sp.Matrix([dq1, dq2, dq3, dbx, dby, dbz, dpx, dpy, dpz])
    q_all = sp.Matrix([q1, q2, q3, bx, by, bz, px, py, pz])


    # ======================================================================
    # 2. KINEMATICS
    # ======================================================================
    print("Computing Kinematics...")

    def RotX(t): return sp.Matrix([[1, 0, 0], [0, sp.cos(t), -sp.sin(t)], [0, sp.sin(t), sp.cos(t)]])
    def RotY(t): return sp.Matrix([[sp.cos(t), 0, sp.sin(t)], [0, 1, 0], [-sp.sin(t), 0, sp.cos(t)]])
    def RotZ(t): return sp.Matrix([[sp.cos(t), -sp.sin(t), 0], [sp.sin(t), sp.cos(t), 0], [0, 0, 1]])

    # *** FIX: XYZ CONVENTION (Rx * Ry * Rz) ***
    R_base = RotX(bx) * RotY(by) * RotZ(bz)
    
    T_base = sp.eye(4)
    T_base[0:3, 0:3] = R_base
    T_base[0, 3] = px
    T_base[1, 3] = py
    T_base[2, 3] = pz

    # Base COM offset (local)
    T_base_com_offset = sp.eye(4)
    T_base_com_offset[1, 3] = -0.05531
    T_com_base = T_base * T_base_com_offset

    # Link 1
    T_rot_q1 = sp.eye(4)
    T_rot_q1[0:3, 0:3] = RotY(q1)
    
    T_com1_offset = sp.eye(4)
    T_com1_offset[1, 3] = L1
    T_com1_offset[2, 3] = 0.02554
    
    T_link1 = T_base * T_rot_q1
    T_com1 = T_link1 * T_com1_offset

    # Link 2
    T_m1_m2 = sp.eye(4)
    T_m1_m2[1, 3] = L2
    
    tilt = sp.rad(15 - 180)
    T_static_tilt = sp.eye(4)
    T_static_tilt[0:3, 0:3] = RotX(tilt)
    
    T_dynamic_q2 = sp.eye(4)
    T_dynamic_q2[0:3, 0:3] = RotZ(q2)
    
    T_link2 = T_link1 * T_m1_m2 * T_static_tilt * T_dynamic_q2

    P_local_2 = RotX(tilt).T * sp.Matrix([0, -0.00051, -0.06656])
    T_com2_offset = sp.eye(4)
    T_com2_offset[0:3, 3] = P_local_2
    T_com2 = T_link2 * T_com2_offset

    # Link 3
    P_local_m2_m3 = RotX(tilt).T * sp.Matrix([0, 0.03734, -0.09309])
    T_link3_local = sp.eye(4)
    T_link3_local[0:3, 3] = P_local_m2_m3
    T_link3_local[0:3, 0:3] = RotX(-tilt) * RotY(q3)
    T_com3 = T_link2 * T_link3_local


    # ======================================================================
    # 3. ENERGIES
    # ======================================================================
    print("Computing Energy (Lagrangian)...")

    def get_linear_vel(T_com):
        p = T_com[0:3, 3]
        v = p.jacobian(q_all) * dq_all
        return v

    # Angular Velocity Construction for XYZ
    z, y, x = sp.Matrix([0,0,1]), sp.Matrix([0,1,0]), sp.Matrix([1,0,0])
    w_base_world = (dq_all[3]*x) + (RotX(bx)*dq_all[4]*y) + (RotX(bx)*RotY(by)*dq_all[5]*z)
    
    # Project to body frame
    w_base_body = R_base.T * w_base_world

    # Angular velocities for links (World Frame)
    w_link1 = w_base_world + T_base[0:3, 0:3] * (dq1 * y)
    w_link2 = w_link1 + (T_link1 * T_m1_m2 * T_static_tilt)[0:3, 0:3] * (dq2 * z)
    w_link3 = w_link2 + ((T_link2 * sp.eye(4))[0:3,0:3] * RotX(-tilt)) * (dq3 * y)

    # Project link angular velocities to their body frames
    w_link1_body = T_link1[0:3, 0:3].T * w_link1
    w_link2_body = T_link2[0:3, 0:3].T * w_link2
    w_link3_body = T_com3[0:3, 0:3].T * w_link3

    # Inertia & masses
    scale = 1e-9
    m_base, m1, m2, m3 = 0.95669, 0.25728, 0.24066, 0.07284
    
    I_base = sp.Matrix([[3124751.81, -5480.21, 0.05], [-5480.21, 1644545.27, -22.76], [0.05, -22.76, 3126941.96]]) * scale
    I1 = sp.Matrix([[897498.65, 0.62, 0.24],[0.62, 210513.19, 114397.38],[0.24, 114397.38, 804807.69]]) * scale
    I2 = sp.Matrix([[540057.38, 2.31, -0.68],[2.31, 500181.27, 49080.71],[-0.68, 49080.71, 157559.95]]) * scale
    I3 = sp.Matrix([[28901.95, 0.0, 0.0],[0.0, 53236.19, 0.0],[0.0, 0.0, 28901.95]]) * scale

    # Body-frame velocity symbols and substitution
    wb1, wb2, wb3 = sp.symbols('wb1 wb2 wb3')   # base angular velocity (body frame)
    bv1, bv2, bv3 = sp.symbols('bv1 bv2 bv3')   # base linear velocity (body frame)

    w_body_sym = sp.Matrix([wb1, wb2, wb3])
    v_body_sym = sp.Matrix([bv1, bv2, bv3])

    # Build T_eul mapping
    T_eul = sp.Matrix.hstack(sp.diff(w_base_body, dbx),
                             sp.diff(w_base_body, dby),
                             sp.diff(w_base_body, dbz))
    T_eul_inv = T_eul.inv()

    # world linear velocity
    v_world_expr = R_base * v_body_sym

    # Substitution dictionary
    subs_for_rates = {
        dbx: T_eul_inv[0,0]*wb1 + T_eul_inv[0,1]*wb2 + T_eul_inv[0,2]*wb3,
        dby: T_eul_inv[1,0]*wb1 + T_eul_inv[1,1]*wb2 + T_eul_inv[1,2]*wb3,
        dbz: T_eul_inv[2,0]*wb1 + T_eul_inv[2,1]*wb2 + T_eul_inv[2,2]*wb3,
        dpx: v_world_expr[0],
        dpy: v_world_expr[1],
        dpz: v_world_expr[2]
    }

    # Substitute into velocities
    v_com_base = get_linear_vel(T_com_base).subs(subs_for_rates)
    v_com1 = get_linear_vel(T_com1).subs(subs_for_rates)
    v_com2 = get_linear_vel(T_com2).subs(subs_for_rates)
    v_com3 = get_linear_vel(T_com3).subs(subs_for_rates)

    w_base_body_sub = w_base_body.subs(subs_for_rates)
    w_link1_body_sub = w_link1_body.subs(subs_for_rates)
    w_link2_body_sub = w_link2_body.subs(subs_for_rates)
    w_link3_body_sub = w_link3_body.subs(subs_for_rates)

    # Linear KE
    KE_lin = sp.Rational(1,2) * (
        m_base * (v_com_base.dot(v_com_base)) +
        m1 * (v_com1.dot(v_com1)) +
        m2 * (v_com2.dot(v_com2)) +
        m3 * (v_com3.dot(v_com3))
    )

    # Rotational KE
    KE_rot = sp.Rational(1,2)*( w_base_body_sub.dot(I_base * w_base_body_sub)
                               + w_link1_body_sub.dot(I1 * w_link1_body_sub)
                               + w_link2_body_sub.dot(I2 * w_link2_body_sub)
                               + w_link3_body_sub.dot(I3 * w_link3_body_sub) )

    T_total_sub = KE_lin + KE_rot

    # Potential Energy
    PE = g * ( m_base * T_com_base[1,3] + m1 * T_com1[1,3] + m2 * T_com2[1,3] + m3 * T_com3[1,3] )


    # ======================================================================
    # 4. DERIVE EQUATIONS (M, G, C)
    # ======================================================================
    vel_syms = [dq1, dq2, dq3, wb1, wb2, wb3, bv1, bv2, bv3]

    print("Deriving Equations of Motion (M, G, C)...")
    M = sp.zeros(9,9)
    for i in range(9):
        for j in range(i, 9):
            val = sp.diff(T_total_sub, vel_syms[i], vel_syms[j])
            M[i,j] = M[j,i] = val

    G = sp.zeros(9,1)
    for i in range(9):
        G[i] = sp.diff(PE, q_all[i])

    print("Deriving Coriolis Matrix...")
    C = sp.zeros(9,9)
    dM_dq = [sp.diff(M, q_all[k]) for k in range(9)]
    for i in range(9):
        for j in range(9):
            term = 0
            for k in range(9):
                term += sp.Rational(1,2) * ( dM_dq[k][i,j] + dM_dq[j][i,k] - dM_dq[i][j,k] ) * vel_syms[k]
            C[i,j] = term


    # ======================================================================
    # 5. CODE GENERATION
    # ======================================================================
    output_folder = "dynamics_c_xyz"
    if os.path.exists(output_folder): 
        shutil.rmtree(output_folder)
    os.makedirs(output_folder)

    print("Generating Optimized C Code...")

    def stringify_expr(expr):
        subs_dict = {}
        # joint trig
        for i, s in enumerate([q1, q2, q3]):
            subs_dict[sp.sin(s)] = sp.Symbol(f"sq[{i}]")
            subs_dict[sp.cos(s)] = sp.Symbol(f"cq[{i}]")
        # base orientation trig
        for i, s in enumerate([bx, by, bz]):
            subs_dict[sp.sin(s)] = sp.Symbol(f"sbo[{i}]")
            subs_dict[sp.cos(s)] = sp.Symbol(f"cbo[{i}]")
        
        subs_replace = expr.subs(subs_dict)
        c_str = sp.ccode(subs_replace)

        c_str = c_str.replace("dq1", "dq[0]").replace("dq2", "dq[1]").replace("dq3", "dq[2]")
        c_str = c_str.replace("wb1", "base_dori[0]").replace("wb2", "base_dori[1]").replace("wb3", "base_dori[2]")
        c_str = c_str.replace("bv1", "base_vel[0]").replace("bv2", "base_vel[1]").replace("bv3", "base_vel[2]")
        c_str = c_str.replace("bx", "base_ori[0]").replace("by", "base_ori[1]").replace("bz", "base_ori[2]")
        c_str = c_str.replace("px", "base_pos[0]").replace("py", "base_pos[1]").replace("pz", "base_pos[2]")
        c_str = c_str.replace("ddq1", "ddq[0]").replace("ddq2", "ddq[1]").replace("ddq3", "ddq[2]")
        return c_str

    def get_smart_signature(func_name, code_body):
        args = []
        if re.search(r'\bq\[', code_body): args.append("const double q[3]")
        if re.search(r'\bdq\[', code_body): args.append("const double dq[3]")
        if "ddq[" in code_body: args.append("const double ddq[3]")
        if "base_pos[" in code_body: args.append("const double base_pos[3]")
        if "base_vel[" in code_body: args.append("const double base_vel[3]")
        if "base_acc[" in code_body: args.append("const double base_acc[3]")
        if "base_ori[" in code_body: args.append("const double base_ori[3]")
        if "base_dori[" in code_body: args.append("const double base_dori[3]")
        if "base_ddori[" in code_body: args.append("const double base_ddori[3]")
        if "sq[" in code_body: args.append("const double sq[3]")
        if "cq[" in code_body: args.append("const double cq[3]")
        if "sbo[" in code_body: args.append("const double sbo[3]")
        if "cbo[" in code_body: args.append("const double cbo[3]")
        args.append("double *val")
        return f"void {func_name}({', '.join(args)})"

    def write_single_file(matrix_name, i, j, expr):
        func_name = f"calculate_{matrix_name}_{i}_{j}" if j is not None else f"calculate_{matrix_name}_{i}"
        
        if expr == 0:
            body = "  *val = 0.0;\n"
            sig = f"void {func_name}(double *val)"
        else:
            replacements, reduced_expr = sp.cse(expr)
            c_lines = []
            for sym, val in replacements:
                c_lines.append(f"  double {sym} = {stringify_expr(val)};")
            c_lines.append(f"  *val = {stringify_expr(reduced_expr[0])};")
            body = "\n".join(c_lines) + "\n"
            sig = get_smart_signature(func_name, body)

        safety_block = """#define _USE_MATH_DEFINES
#include <math.h>
#include "model.h"

#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
"""
        with open(os.path.join(output_folder, f"{func_name}.c"), "w") as f:
            f.write(safety_block + "\n" + f"{sig} {{\n" + body + "}\n")
        return sig

    print("Writing files...")
    m_signatures = [write_single_file("M", r, c, M[r, c]) + ";" for r in range(9) for c in range(9)]
    c_signatures = [write_single_file("C", r, c, C[r, c]) + ";" for r in range(9) for c in range(9)]
    g_signatures = [write_single_file("G", r, None, G[r]) + ";" for r in range(9)]


    # ======================================================================
    # 6. MODEL HEADER & SOURCE
    # ======================================================================
    with open(os.path.join(output_folder, "model.h"), "w") as f:
        f.write("#ifndef DYNAMICS_MODEL_H\n#define DYNAMICS_MODEL_H\n\n")
        f.write("// Mass Matrix\n" + "\n".join(m_signatures) + "\n\n")
        f.write("// Coriolis Matrix\n" + "\n".join(c_signatures) + "\n\n")
        f.write("// Gravity Vector\n" + "\n".join(g_signatures) + "\n\n")
        f.write("void compute_dynamics(const double q[3], const double dq[3], const double ddq[3], \n")
        f.write("    const double base_pos[3], const double base_vel[3], const double base_acc[3], \n")
        f.write("    const double base_ori[3], const double base_dori[3], const double base_ddori[3], \n")
        f.write("    double M[9][9], double C[9][9], double G[9], double tau[9]);\n")
        f.write("\n#endif\n")

    with open(os.path.join(output_folder, "model.c"), "w") as f:
        f.write("#define _USE_MATH_DEFINES\n#include <math.h>\n#include \"model.h\"\n\n")
        f.write("void compute_dynamics(\n")
        f.write("    const double q[3], const double dq[3], const double ddq[3],\n")
        f.write("    const double base_pos[3], const double base_vel[3], const double base_acc[3],\n")
        f.write("    const double base_ori[3], const double base_dori[3], const double base_ddori[3],\n")
        f.write("    double M[9][9], double C[9][9], double G[9], double tau[9]) {\n\n")
        
        f.write("  double sq[3], cq[3], sbo[3], cbo[3];\n")
        f.write("  for(int i=0; i<3; i++) {\n")
        f.write("      sq[i] = sin(q[i]);          cq[i] = cos(q[i]);\n")
        f.write("      sbo[i] = sin(base_ori[i]);  cbo[i] = cos(base_ori[i]);\n")
        f.write("  }\n\n")
        
        f.write("  // Base Rotation Matrix (Body -> World)\n")
        f.write("  double R[3][3];\n")
        for r in range(3):
            for c in range(3):
                val_str = stringify_expr(R_base[r, c])
                f.write(f"  R[{r}][{c}] = {val_str};\n")
        f.write("\n")
        
        def write_calls(signatures, name, is_matrix=True):
            f.write(f"  // {name} Calls\n")
            for idx, sig in enumerate(signatures):
                r, c = (idx // 9, idx % 9) if is_matrix else (idx, 0)
                args_part = sig[sig.find('(')+1 : sig.find(')')]
                call_args = []
                for arg_def in args_part.split(','):
                    arg_def = arg_def.strip()
                    clean_name = arg_def.replace('const', '').replace('double', '').replace('*', '').strip()
                    clean_name = clean_name.split('[')[0].strip()
                    
                    if clean_name == "val":
                        call_args.append(f"&{name}[{r}][{c}]" if is_matrix else f"&{name}[{r}]")
                    else:
                        call_args.append(clean_name)
                
                suffix = f"_{r}_{c}" if is_matrix else f"_{r}"
                f.write(f"  calculate_{name}{suffix}({', '.join(call_args)});\n")

        write_calls(m_signatures, "M", True)
        write_calls(c_signatures, "C", True)
        write_calls(g_signatures, "G", False)

        f.write("\n  // Torque = M*ddq + C*dq + G\n")
        f.write("  double f_dq[9] = {dq[0], dq[1], dq[2], base_dori[0], base_dori[1], base_dori[2], base_vel[0], base_vel[1], base_vel[2]};\n")
        f.write("  double f_ddq[9] = {ddq[0], ddq[1], ddq[2], base_ddori[0], base_ddori[1], base_ddori[2], base_acc[0], base_acc[1], base_acc[2]};\n\n")
        f.write("  for(int i=0; i<9; i++) {\n")
        f.write("      tau[i] = 0.0;\n")
        f.write("      for(int j=0; j<9; j++) tau[i] += M[i][j] * f_ddq[j];\n")
        f.write("      for(int j=0; j<9; j++) tau[i] += C[i][j] * f_dq[j];\n")
        f.write("      tau[i] += G[i];\n")
        f.write("  }\n")
        f.write("}\n")

    print(f"Done. Files generated in {output_folder}")

if __name__ == "__main__":
    generate_dynamics()