import sympy as sp

def main():
    print("Initializing symbols...")
    # 1. Define Symbolic Variables
    # Joint Space
    q1, q2, q3 = sp.symbols('q1 q2 q3')
    
    # Base Orientation (Input)
    theta_xb, theta_yb, theta_zb = sp.symbols(r'\theta_{xb} \theta_{yb} \theta_{zb}')
    
    # Desired End Effector Orientation (Input for IK)
    theta_x_d, theta_y_d, theta_z_d = sp.symbols('theta_{xd} theta_{yd} theta_{zd}')

    L1, L2 = sp.symbols('L1 L2')

    # Constants
    alpha1_val = sp.pi * 75 / 180
    alpha2_val = sp.pi * -75 / 180

    # 2. Helper Functions
    def dh_matrix(theta, d, a, alpha):
        return sp.Matrix([
            [sp.cos(theta), -sp.sin(theta)*sp.cos(alpha),  sp.sin(theta)*sp.sin(alpha), a*sp.cos(theta)],
            [sp.sin(theta),  sp.cos(theta)*sp.cos(alpha), -sp.cos(theta)*sp.sin(alpha), a*sp.sin(theta)],
            [0,              sp.sin(alpha),                sp.cos(alpha),              d],
            [0,              0,                            0,                          1]
        ])

    def rotation_matrix_zyx(tx, ty, tz):
        # Z-Y-X Convention
        Rz = sp.Matrix([[sp.cos(tz), -sp.sin(tz), 0], [sp.sin(tz), sp.cos(tz), 0], [0, 0, 1]])
        Ry = sp.Matrix([[sp.cos(ty), 0, sp.sin(ty)], [0, 1, 0], [-sp.sin(ty), 0, sp.cos(ty)]])
        Rx = sp.Matrix([[1, 0, 0], [0, sp.cos(tx), -sp.sin(tx)], [0, sp.sin(tx), sp.cos(tx)]])
        return Rz * Ry * Rx

    # 3. Compute Forward Kinematics
    print("Computing Forward Kinematics...")
    
    # Base Transformation
    R_base = rotation_matrix_zyx(theta_xb, theta_yb, theta_zb)
    TB0 = sp.Matrix.vstack(sp.Matrix.hstack(R_base, sp.Matrix([0,0,0])), sp.Matrix([[0,0,0,1]]))
    
    # Arm Transformations
    T01 = dh_matrix(q1, L1, 0, alpha1_val)
    T12 = dh_matrix(q2, L2, 0, alpha2_val)
    T23 = dh_matrix(q3, 0,  0, 0)

    # Total Transformation (Base -> End Effector)
    TB3 = TB0 * T01 * T12 * T23

    # Extract FK Outputs (Fully Expanded)
    Px = TB3[0, 3]
    Py = TB3[1, 3]
    Pz = TB3[2, 3]
    
    # Orientation Matrix Elements for FK equations
    # We use these to write theta_z = atan2(r21, r11) etc.
    r11_fk = TB3[0, 0]; r21_fk = TB3[1, 0]
    r31_fk = TB3[2, 0]; r32_fk = TB3[2, 1]; r33_fk = TB3[2, 2]

    # 4. Compute Inverse Kinematics
    print("Computing Inverse Kinematics...")
    
    # Desired Rotation Matrix (Global)
    R_des = rotation_matrix_zyx(theta_x_d, theta_y_d, theta_z_d)

    # Decouple Base: R_arm_needed = R_base.T * R_des
    # This matrix contains ONLY Base angles and Desired angles.
    R_arm_needed = R_base.T * R_des
    
    # Extract elements of the required arm rotation (The M matrix)
    M13 = R_arm_needed[0, 2]
    M23 = R_arm_needed[1, 2]
    M33 = R_arm_needed[2, 2]
    M31 = R_arm_needed[2, 0]
    M32 = R_arm_needed[2, 1]

    # Analyze Structure for q2 coefficients
    # r33_struct = A*cos(q2) + B
    T03_struct = T01 * T12 * T23
    r33_struct = T03_struct[2, 2]
    
    A_coeff = sp.simplify((r33_struct.subs(q2, 0) - r33_struct.subs(q2, sp.pi)) / 2)
    B_coeff = sp.simplify((r33_struct.subs(q2, 0) + r33_struct.subs(q2, sp.pi)) / 2)

    # 5. Generate LaTeX
    output_filename = "dh_kinematics_base.tex"
    print(f"Writing to {output_filename}...")

    # Formatter with Font Limit
    def fmt(expr):
        s = sp.latex(expr)
        # Robotics Notation
        s = s.replace(r"\sin", "S").replace(r"\cos", "C")
        s = s.replace(r"\operatorname{S}", "S").replace(r"\operatorname{C}", "C")
        # Adjustbox with max width constraint + footnotesize
        return r"\adjustbox{max width=\linewidth}{$ \footnotesize " + s + r" $}"

    try:
        with open(output_filename, 'w') as f:
            f.write(r"\documentclass[10pt, a4paper]{article}" + "\n")
            f.write(r"\usepackage[a4paper, margin=0.5cm]{geometry}" + "\n")
            f.write(r"\usepackage{amsmath}" + "\n")
            f.write(r"\usepackage{adjustbox}" + "\n") # Crucial for constraints
            f.write(r"\title{Gimbal Kinematics (Base Coupled)}" + "\n")
            f.write(r"\date{}" + "\n")
            f.write(r"\begin{document}" + "\n")
            f.write(r"\maketitle" + "\n")
            f.write(r"\noindent\textbf{Notation:} $S_{...} = \sin(...), C_{...} = \cos(...)$" + "\n")
            f.write(r"\vspace{0.5cm}" + "\n")
            
            # --- FORWARD KINEMATICS ---
            f.write(r"\section*{1. Forward Kinematics (Task Space)}" + "\n")
            f.write(r"Calculated directly from $T_{Total} = T_{Base} T_{01} T_{12} T_{23}$." + "\n\n")

            f.write(r"\subsection*{Position $x, y, z$}" + "\n")
            f.write(r"\noindent $x = $ " + fmt(Px) + "\n\n")
            f.write(r"\noindent $y = $ " + fmt(Py) + "\n\n")
            f.write(r"\noindent $z = $ " + fmt(Pz) + "\n\n")

            f.write(r"\subsection*{Orientation $\theta_x, \theta_y, \theta_z$ (End Effector)}" + "\n")
            
            f.write(r"\noindent $\theta_z \text{ (Yaw)} = \operatorname{atan2}(Y_{term}, X_{term})$ where:" + "\n")
            f.write(r"\noindent $Y_{term} = $ " + fmt(r21_fk) + "\n\n")
            f.write(r"\noindent $X_{term} = $ " + fmt(r11_fk) + "\n\n")

            f.write(r"\noindent $\theta_y \text{ (Pitch)} = \operatorname{atan2}(Y_{term}, X_{term})$ where:" + "\n")
            f.write(r"\noindent $Y_{term} = $ " + fmt(-r31_fk) + "\n\n")
            f.write(r"\noindent $X_{term} = \sqrt{(\text{Roll}_Y)^2 + (\text{Roll}_X)^2}$ (Terms below)" + "\n\n")

            f.write(r"\noindent $\theta_x \text{ (Roll)} = \operatorname{atan2}(Y_{term}, X_{term})$ where:" + "\n")
            f.write(r"\noindent $Y_{term} = $ " + fmt(r32_fk) + "\n\n")
            f.write(r"\noindent $X_{term} = $ " + fmt(r33_fk) + "\n\n")

            # --- INVERSE KINEMATICS ---
            f.write(r"\clearpage" + "\n")
            f.write(r"\section*{2. Inverse Kinematics (Corrected)}" + "\n")
            f.write(r"Solutions for $q_1, q_2, q_3$ given Base Orientation ($\theta_{xb...}$) and Desired End-Effector ($\theta_{xd...}$)." + "\n\n")

            # Q2
            f.write(r"\subsection*{Joint $q_2$}" + "\n")
            f.write(r"$$ q_2 = \operatorname{acos}\left( \frac{M_{33} - B_{coeff}}{A_{coeff}} \right) $$" + "\n")
            f.write(r"\noindent where $M_{33}$ (from Base and Desired matrices) is:" + "\n")
            f.write(r"\noindent" + fmt(M33) + "\n\n")
            f.write(r"\noindent and coefficients (from Link twists) are:" + "\n")
            f.write(r"\noindent $ A_{coeff} = $ " + fmt(A_coeff) + "\n\n")
            f.write(r"\noindent $ B_{coeff} = $ " + fmt(B_coeff) + "\n\n")

            # Q1
            f.write(r"\subsection*{Joint $q_1$}" + "\n")
            f.write(r"$$ q_1 = \operatorname{atan2}(M_{13}, -M_{23}) $$" + "\n")
            f.write(r"\noindent Expansion of term $M_{13}$:" + "\n")
            f.write(r"\noindent" + fmt(M13) + "\n\n")
            f.write(r"\noindent Expansion of term $-M_{23}$:" + "\n")
            f.write(r"\noindent" + fmt(-M23) + "\n\n")

            # Q3
            f.write(r"\subsection*{Joint $q_3$}" + "\n")
            f.write(r"$$ q_3 = \operatorname{atan2}(M_{32}, M_{31}) $$" + "\n")
            f.write(r"\noindent Expansion of term $M_{32}$:" + "\n")
            f.write(r"\noindent" + fmt(M32) + "\n\n")
            f.write(r"\noindent Expansion of term $M_{31}$:" + "\n")
            f.write(r"\noindent" + fmt(M31) + "\n\n")

            f.write(r"\end{document}" + "\n")
        
        print(f"Success. Saved to {output_filename}")

    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    sp.init_printing(use_unicode=True)
    main()