import sympy as sp

def main():
    # 1. Define Symbolic Variables
    q1, q2, q3 = sp.symbols('q1 q2 q3')
    # New symbols for velocities (q_dot)
    dq1 = sp.symbols(r'\dot{q}_{1}')
    dq2 = sp.symbols(r'\dot{q}_{2}')
    dq3 = sp.symbols(r'\dot{q}_{3}')
    L1, L2 = sp.symbols('L1 L2')

    # SymPy's trig functions expect radians
    alpha1_val = sp.pi * 75 / 180
    alpha2_val = sp.pi * -75 / 180

    # 2. Define the DH Parameter Table
    dh_params = [
        (q1, L1, 0, alpha1_val),  # Joint 1
        (q2, L2, 0, alpha2_val),  # Joint 2
        (q3, 0,  0, 0)            # Joint 3
    ]

    # 3. Define a function for the standard DH Transformation Matrix
    def dh_matrix(theta, d, a, alpha):
        return sp.Matrix([
            [sp.cos(theta), -sp.sin(theta)*sp.cos(alpha),  sp.sin(theta)*sp.sin(alpha), a*sp.cos(theta)],
            [sp.sin(theta),  sp.cos(theta)*sp.cos(alpha), -sp.cos(theta)*sp.sin(alpha), a*sp.sin(theta)],
            [0,              sp.sin(alpha),               sp.cos(alpha),              d],
            [0,              0,                           0,                          1]
        ])

    # 4. Compute Transformation Matrices
    p = dh_params[0]; T01 = dh_matrix(*p)
    p = dh_params[1]; T12 = dh_matrix(*p)
    p = dh_params[2]; T23 = dh_matrix(*p)

    # Compute T02
    T02 = sp.simplify(T01 * T12)

    # 5. Compute Total Forward Kinematics
    T03 = sp.simplify(T01 * T12 * T23)

    # --- Define all terms for 6-DOF Equations ---

    # Position
    Px = T03[0, 3]
    Py = T03[1, 3]
    Pz = T03[2, 3]

    # Get matrix elements
    a11 = T03[0, 0]
    a21 = T03[1, 0]
    a31 = T03[2, 0]
    a32 = T03[2, 1]
    a33 = T03[2, 2]

    # Yaw (Z) arguments
    Yz_A = a21.args[0] if hasattr(a21, 'args') and len(a21.args) > 0 else a21
    Yz_B = a21.args[1] if hasattr(a21, 'args') and len(a21.args) > 1 else 0
    Xz_C = a11.args[0] if hasattr(a11, 'args') and len(a11.args) > 0 else a11
    Xz_D = a11.args[1] if hasattr(a11, 'args') and len(a11.args) > 1 else 0

    # Pitch (Y) arguments
    Yy_A = -a31.args[0] if hasattr(a31, 'args') and len(a31.args) > 0 else -a31
    Yy_B = -a31.args[1] if hasattr(a31, 'args') and len(a31.args) > 1 else 0
    Yy_C = -a31.args[2] if hasattr(a31, 'args') and len(a31.args) > 2 else 0
    Yy_D = -a31.args[3] if hasattr(a31, 'args') and len(a31.args) > 3 else 0
    Xy_E_arg = a11
    Xy_F_arg = a21

    # Roll (X) arguments
    Yx_A = a32.args[0] if hasattr(a32, 'args') and len(a32.args) > 0 else a32
    Yx_B = a32.args[1] if hasattr(a32, 'args') and len(a32.args) > 1 else 0
    Yx_C = a32.args[2] if hasattr(a32, 'args') and len(a32.args) > 2 else 0
    Yx_D = a32.args[3] if hasattr(a32, 'args') and len(a32.args) > 3 else 0
    Xx_E = a33.args[0] if hasattr(a33, 'args') and len(a33.args) > 0 else a33
    Xx_F = a33.args[1] if hasattr(a33, 'args') and len(a33.args) > 1 else 0
    Xx_G = a33.args[2] if hasattr(a33, 'args') and len(a33.args) > 2 else 0
    Xx_H = a33.args[3] if hasattr(a33, 'args') and len(a33.args) > 3 else 0

    # ---------------------------------------------------------
    # --- VELOCITY KINEMATICS (JACOBIAN) LOGIC ---
    # ---------------------------------------------------------

    # A. Extract Origins
    O0 = sp.Matrix([0, 0, 0])
    O1 = T01[0:3, 3]
    O2 = T02[0:3, 3]
    O3 = T03[0:3, 3]

    # B. Extract Z-Axes
    Z0 = sp.Matrix([0, 0, 1])
    Z1 = T01[0:3, 2]
    Z2 = T02[0:3, 2]

    # C. Compute Jacobian Columns
    Jv1 = sp.simplify(Z0.cross(O3 - O0))
    Jw1 = sp.simplify(Z0)
    Jv2 = sp.simplify(Z1.cross(O3 - O1))
    Jw2 = sp.simplify(Z1)
    Jv3 = sp.simplify(Z2.cross(O3 - O2))
    Jw3 = sp.simplify(Z2)

    # D. Assemble Jacobian Matrix
    J_col1 = sp.Matrix.vstack(Jv1, Jw1)
    J_col2 = sp.Matrix.vstack(Jv2, Jw2)
    J_col3 = sp.Matrix.vstack(Jv3, Jw3)

    J = sp.Matrix.hstack(J_col1, J_col2, J_col3)
    J = sp.simplify(J)

    # -------------------------
    # Inverse kinematics setup (FAST analytic)
    # -------------------------
    theta_x_d, theta_y_d, theta_z_d = sp.symbols('theta_x_d theta_y_d theta_z_d')

    # Build desired rotation matrix
    thx = theta_x_d
    thy = theta_y_d
    thz = theta_z_d

    Rz = sp.Matrix([
        [sp.cos(thz), -sp.sin(thz), 0],
        [sp.sin(thz),  sp.cos(thz), 0],
        [0,            0,           1]
    ])
    Ry = sp.Matrix([
        [sp.cos(thy), 0, sp.sin(thy)],
        [0,           1, 0],
        [-sp.sin(thy),0, sp.cos(thy)]
    ])
    Rx = sp.Matrix([
        [1, 0,           0],
        [0, sp.cos(thx), -sp.sin(thx)],
        [0, sp.sin(thx),  sp.cos(thx)]
    ])

    R_des = sp.simplify(Rz * Ry * Rx)
    R_03 = sp.simplify(T03[0:3, 0:3])

    r13 = sp.simplify(R_03[0, 2])
    r23 = sp.simplify(R_03[1, 2])
    r33 = sp.simplify(R_03[2, 2])

    rd13 = sp.simplify(R_des[0, 2])
    rd23 = sp.simplify(R_des[1, 2])
    rd33 = sp.simplify(R_des[2, 2])

    # Analytic Extraction Logic
    try:
        # 1. Solve for q2 using r33
        c2 = sp.symbols('c2')
        r33_sub = sp.simplify(r33.subs(sp.cos(q2), c2).subs(sp.sin(q2), sp.sqrt(1 - c2**2)))
        
        # Calculate coefficients for cos(q2)
        val_plus = sp.simplify(r33.subs(q2, 0))   # cos(q2)=1
        val_minus = sp.simplify(r33.subs(q2, sp.pi))  # cos(q2)=-1
        a_c = sp.simplify((val_plus - val_minus) / 2)   
        b_c = sp.simplify((val_plus + val_minus) / 2)   
        
        cos_q2_expr = sp.simplify((rd33 - b_c) / a_c)
        q2_sol = sp.acos(sp.simplify(cos_q2_expr))
        sin_q2_expr = sp.simplify(sp.sqrt(1 - sp.simplify(cos_q2_expr**2)))

        # 2. Solve for q1 using r13, r23
        k = sp.simplify((sp.sqrt(6) + sp.sqrt(2)) / 4)
        A_expr = sp.simplify((1 - cos_q2_expr) / 4)
        B_expr = sp.simplify(-k * sin_q2_expr)

        s_num = sp.simplify(A_expr * rd13 + B_expr * rd23)
        c_num = sp.simplify(B_expr * rd13 - A_expr * rd23)
        q1_sol = sp.atan2(s_num, c_num)

        # 3. Solve for q3 using R02 and R_des
        R02 = sp.simplify(T02[0:3, 0:3])
        R02_sub = sp.simplify(R02.subs({q1: q1_sol, q2: q2_sol}))
        M = sp.simplify(R02_sub.T * R_des)
        q3_sol = sp.atan2(sp.simplify(M[1, 0]), sp.simplify(M[0, 0]))

        # Store the FULL analytic solution including q3
        ik_solution_full = [{q1: sp.simplify(q1_sol), q2: sp.simplify(q2_sol), q3: sp.simplify(q3_sol)}]

    except Exception as e:
        ik_solution_full = []
        print(f"Analytic solver error: {e}")

    # Compute Pseudoinverse (for velocity section)
    try:
        JtJ = sp.simplify(J.T * J)
        JtJ_inv = sp.simplify(JtJ.inv())
        J_plus = sp.simplify(JtJ_inv * J.T)
    except Exception as e:
        J_plus = sp.simplify((J.T * J).pinv() * J.T)

    # 6. Save results to LaTeX file
    output_filename = "dh_matrices_kinematics.tex"

    try:
        with open(output_filename, 'w') as f:
            # --- HEADER ---
            f.write(r"\documentclass[11pt, a4paper]{article}" + "\n")
            f.write(r"\usepackage[a4paper, margin=0.5cm]{geometry}" + "\n")
            f.write(r"\usepackage{amsmath}" + "\n")
            f.write(r"\usepackage{lmodern}" + "\n")
            f.write(r"\usepackage[T1]{fontenc}" + "\n")
            f.write(r"\usepackage{graphicx}" + "\n")
            f.write(r"\usepackage{breqn}" + "\n")
            f.write(r"\title{Symbolic DH Transformation Matrices \& Kinematics}" + "\n")
            f.write(r"\author{Computed by SymPy}" + "\n")
            f.write(r"\date{}" + "\n")
            f.write(r"\begin{document}" + "\n")
            f.write(r"\maketitle" + "\n")

            f.write(r"\noindent\textbf{Link lengths:} $L_1 = 13.548\ \text{cm},\; L_2 = 9.637\ \text{cm}$" + "\n")
            spacer = r"\vspace{0.5cm}" + "\n"

            # 1. Matrices
            f.write(r"\section*{Matrix $T_{0 \to 1}$}" + "\n")
            f.write(spacer)
            f.write("$$" + sp.latex(T01) + "$$" + "\n\n")

            f.write(r"\section*{Matrix $T_{1 \to 2}$}" + "\n")
            f.write(spacer)
            f.write("$$" + sp.latex(T12) + "$$" + "\n\n")

            f.write(r"\section*{Matrix $T_{0 \to 2}$ (Computed)}" + "\n")
            f.write(spacer)
            f.write(r"\noindent\resizebox{\textwidth}{!}{$" + "\n")
            f.write(sp.latex(T02))
            f.write(r"$}" + "\n\n")

            f.write(r"\section*{Matrix $T_{2 \to 3}$}" + "\n")
            f.write(spacer)
            f.write("$$" + sp.latex(T23) + "$$" + "\n\n")

            f.write(r"\section*{Final Matrix $T_{0 \to 3}$ (Simplified)}" + "\n")
            f.write(spacer)
            f.write(r"\noindent\resizebox{\textwidth}{!}{$" + "\n")
            f.write(sp.latex(T03))
            f.write(r"$}" + "\n\n")

            f.write(r"\vspace{1cm}" + "\n\n")

            # 3. Individual Terms
            f.write(r"\subsection*{Individual Matrix Terms ($a_{11}$ to $a_{44}$)}" + "\n")
            f.write(spacer)
            for i in range(4):
                for j in range(4):
                    term = T03[i, j]
                    f.write(r"\begin{dmath*}" + "\n")
                    f.write(f"a_{{{i+1}{j+1}}} = " + sp.latex(term))
                    f.write(r"\end{dmath*}" + "\n")

            f.write(r"\hrule" + "\n\n")

            # 4. Forward Kinematics Equations
            f.write(r"\section*{Forward Kinematics: 6-DOF Equations}" + "\n")
            f.write(r"\subsection*{Position ($x, y, z$)}" + "\n")
            f.write(spacer)
            f.write(r"$$ x = " + sp.latex(Px) + r" $$" + "\n")
            f.write(r"$$ y = " + sp.latex(Py) + r" $$" + "\n")
            f.write(r"$$ z = " + sp.latex(Pz) + r" $$" + "\n")

            f.write(r"\subsection*{Orientation ($\theta_x, \theta_y, \theta_z$)}" + "\n")
            f.write(r"\textit{Note: Calculated using Z-Y-X (Yaw-Pitch-Roll) convention.}" + "\n\n")
            f.write(r"\vspace{1cm}" + "\n")

            f.write(r"$$ \theta_z \text{ (Yaw)} = \operatorname{atan2}(A_z + B_z, C_z + D_z) \quad \text{where:}$$" + "\n")
            f.write(r"\begin{dmath*} A_z = " + sp.latex(Yz_A) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} B_z = " + sp.latex(Yz_B) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} C_z = " + sp.latex(Xz_C) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} D_z = " + sp.latex(Xz_D) + r"\end{dmath*}" + "\n\n")

            f.write(r"\vspace{1cm}" + "\n")
            f.write(r"$$ \theta_y \text{ (Pitch)} = \operatorname{atan2}(A_y + B_y + C_y + D_y, \sqrt{E_y^2 + F_y^2}) \quad \text{where:}$$" + "\n")
            f.write(r"\begin{dmath*} A_y = " + sp.latex(Yy_A) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} B_y = " + sp.latex(Yy_B) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} C_y = " + sp.latex(Yy_C) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} D_y = " + sp.latex(Yy_D) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} E_y = " + sp.latex(Xy_E_arg) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} F_y = " + sp.latex(Xy_F_arg) + r"\end{dmath*}" + "\n\n")

            f.write(r"\vspace{1cm}" + "\n")
            f.write(r"$$ \theta_x \text{ (Roll)} = \operatorname{atan2}(A_x + B_x + C_x + D_x, E_x + F_x + G_x + H_x) \quad \text{where:}$$" + "\n")
            f.write(r"\begin{dmath*} A_x = " + sp.latex(Yx_A) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} B_x = " + sp.latex(Yx_B) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} C_x = " + sp.latex(Yx_C) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} D_x = " + sp.latex(Yx_D) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} E_x = " + sp.latex(Xx_E) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} F_x = " + sp.latex(Xx_F) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} G_x = " + sp.latex(Xx_G) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} H_x = " + sp.latex(Xx_H) + r"\end{dmath*}" + "\n\n")

            # -------------------------
            # INVERSE KINEMATICS (Fixed for Gimbal)
            # -------------------------
            f.write(r"\hrule" + "\n\n")
            f.write(r"\section*{Inverse Kinematics (Joints from Orientation)}" + "\n")
            f.write(r"\textit{Since this is a gimbal system, the 'position' is defined by the end-effector orientation.}" + "\n")
            f.write(r"\textit{The following equations solve for $q_1, q_2, q_3$ given desired angles $\theta_x, \theta_y, \theta_z$.}" + "\n")
            f.write(spacer)

            # Show desired angles
            f.write(r"\begin{dmath*} \theta_x = " + sp.latex(theta_x_d) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} \theta_y = " + sp.latex(theta_y_d) + r"\end{dmath*}" + "\n")
            f.write(r"\begin{dmath*} \theta_z = " + sp.latex(theta_z_d) + r"\end{dmath*}" + "\n\n")
            f.write(r"\vspace{0.5cm}" + "\n")

            if ik_solution_full:
                for sol in ik_solution_full:
                    # q1 on its own line
                    if q1 in sol:
                        f.write(r"\noindent\resizebox{\textwidth}{!}{$" + "\n")
                        f.write(r"q_1 = " + sp.latex(sp.simplify(sol[q1])))
                        f.write(r"$}" + "\n\n")
                        f.write(r"\vspace{0.5cm}" + "\n")
                    
                    # q2 on its own line
                    if q2 in sol:
                        f.write(r"\noindent\resizebox{\textwidth}{!}{$" + "\n")
                        f.write(r"q_2 = " + sp.latex(sp.simplify(sol[q2])))
                        f.write(r"$}" + "\n\n")
                        f.write(r"\vspace{0.5cm}" + "\n")
                    
                    # q3 on its own line (Now strictly calculated)
                    if q3 in sol:
                        f.write(r"\noindent\resizebox{\textwidth}{!}{$" + "\n")
                        f.write(r"q_3 = " + sp.latex(sp.simplify(sol[q3])))
                        f.write(r"$}" + "\n\n")
                        f.write(spacer)
            else:
                f.write(r"\noindent\textit{Analytic extraction failed symbolically.}" + "\n\n")

            # -------------------------
            # INVERSE VELOCITY KINEMATICS
            # -------------------------
            f.write(r"\hrule" + "\n\n")
            f.write(r"\section*{Inverse Velocity Kinematics (Pseudoinverse)}" + "\n")
            f.write(r"$$ J^{+} = (J^\top J)^{-1} J^\top $$" + "\n\n")
            f.write(spacer)

            f.write(r"\noindent\resizebox{\textwidth}{!}{$" + "\n")
            f.write(r"J^{+} = " + sp.latex(sp.simplify(J_plus)))
            f.write(r"$}" + "\n\n")

            f.write(spacer)
            f.write(r"\noindent\resizebox{\textwidth}{!}{$" + "\n")
            f.write(r"\begin{bmatrix} \dot{q}_1 \\ \dot{q}_2 \\ \dot{q}_3 \end{bmatrix} = " + sp.latex(sp.simplify(J_plus)) + r" \cdot " +
                    r"\begin{bmatrix} \dot{x} \\ \dot{y} \\ \dot{z} \\ \omega_x \\ \omega_y \\ \omega_z \end{bmatrix}" + "\n")
            f.write(r"$}" + "\n\n")

            f.write(r"\end{document}" + "\n")

        print(f"\nSuccessfully saved matrices and kinematics to '{output_filename}'")
        if ik_solution_full:
            print("Analytic inverse kinematics computed symbolically.")
        else:
            print("Analytic extraction failed.")

    except Exception as e:
        print(f"\nAn error occurred while writing to file: {e}")

if __name__ == "__main__":
    sp.init_printing(use_unicode=True)
    main()