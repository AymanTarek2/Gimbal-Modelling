import sympy as sp
import os

def generate_symbolic_kinematics():
    # ======================================================================
    # 1. SETUP FOLDER
    # ======================================================================
    output_folder = "latex"
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)
    
    output_file = os.path.join(output_folder, "kinematics.tex")
    print(f"Generating Symbolic Kinematics to: {output_file}")

    # ======================================================================
    # 2. DEFINING SYMBOLS
    # ======================================================================
    # System Variables
    phi, theta, psi = sp.symbols(r'\phi \theta \psi')       
    x, y, z = sp.symbols('x y z')                           
    tr, tp, ty = sp.symbols(r'\theta_{r} \theta_{p} \theta_{y}') 

    # System Parameters
    l1, l2 = sp.symbols(r'l_1 l_2')                         
    alpha = sp.symbols(r'\alpha')                           
    
    # Local COM/Offset Coordinates
    z_c1 = sp.symbols(r'z_{c1}')
    y_c2, z_c2 = sp.symbols(r'y_{c2} z_{c2}')
    y_23, z_23 = sp.symbols(r'y_{23} z_{23}')

    # Values for the Table
    # Note: Keys are raw strings
    param_values = {
        r"l_1": "0.08822 m",
        r"l_2": "0.13548 m",
        r"\alpha": r"15^{\circ}",
        r"z_{c1}": "0.02554 m",
        r"y_{c2}": "-0.00051 m",
        r"z_{c2}": "-0.06656 m",
        r"y_{23}": "0.03734 m",
        r"z_{23}": "-0.09309 m"
    }

    # ======================================================================
    # 3. MATRIX HELPERS
    # ======================================================================
    def RotX(t): return sp.Matrix([[1, 0, 0], [0, sp.cos(t), -sp.sin(t)], [0, sp.sin(t), sp.cos(t)]])
    def RotY(t): return sp.Matrix([[sp.cos(t), 0, sp.sin(t)], [0, 1, 0], [-sp.sin(t), 0, sp.cos(t)]])
    def RotZ(t): return sp.Matrix([[sp.cos(t), -sp.sin(t), 0], [sp.sin(t), sp.cos(t), 0], [0, 0, 1]])
    
    # Homogeneous Wrapper
    def H(rot_mat, trans_vec):
        T = sp.eye(4)
        T[0:3, 0:3] = rot_mat
        T[0:3, 3] = trans_vec
        return T

    # Helper to write clean LaTeX sections
    def write_block(f, title, main_eq, definitions):
        f.write(f"% --- {title} ---\n")
        f.write(r"\subsection*{" + title + "}\n")
        f.write(r"\begin{equation}" + "\n")
        f.write(f"  {main_eq}\n")
        f.write(r"\end{equation}" + "\n")
        
        if definitions:
            f.write(r"\noindent Where:" + "\n")
            f.write(r"\begin{align*}" + "\n")
            for i, (name, mat) in enumerate(definitions):
                term = r"\\" if i < len(definitions)-1 else ""
                # Directly write latex if it's already a string, otherwise convert
                if isinstance(mat, str):
                    f.write(f"  {name} &= {mat} {term}\n")
                else:
                    f.write(f"  {name} &= {sp.latex(mat)} {term}\n")
            f.write(r"\end{align*}" + "\n")
        f.write("\n")

    # ======================================================================
    # 4. GENERATING MATRICES
    # ======================================================================
    with open(output_file, "w") as f:
        
        # --- 1. T_BASE ---
        # T_base = T_pos * Rx * Ry * Rz
        T_pos = H(sp.eye(3), sp.Matrix([x,y,z]))
        R_phi = H(RotX(phi), sp.zeros(3,1))
        R_theta = H(RotY(theta), sp.zeros(3,1))
        R_psi = H(RotZ(psi), sp.zeros(3,1))

        write_block(f, "1. Base Transformation ($T_{base}$)", 
                    r"T_{base} = T_{pos} \cdot R_{x}(\phi) \cdot R_{y}(\theta) \cdot R_{z}(\psi)",
                    [("T_{pos}", T_pos), 
                     (r"R_{x}(\phi)", R_phi), 
                     (r"R_{y}(\theta)", R_theta), 
                     (r"R_{z}(\psi)", R_psi)])

        # --- 2. T_COM1 ---
        # T_com1 = T_base * RotY(tr) * Offset1
        R_roll = H(RotY(tr), sp.zeros(3,1))
        T_off1 = H(sp.eye(3), sp.Matrix([0, l1, z_c1]))

        write_block(f, "2. Link 1 COM ($T_{com1}$)",
                    r"T_{com1} = T_{base} \cdot R_{y}(\theta_r) \cdot T_{off1}",
                    [(r"R_{y}(\theta_r)", R_roll), 
                     (r"T_{off1}", T_off1)])

        # --- 3. T_COM2 ---
        T_disp = H(sp.eye(3), sp.Matrix([0, l2, 0]))
        T_tilt = H(RotX(alpha), sp.zeros(3,1))
        R_pitch = H(RotZ(tp), sp.zeros(3,1))
        
        # FIX: Expand T_off2 to full 4x4 matrix
        # T_off2 = Trans( RotX(-alpha) * [0, yc2, zc2] )
        vec_c2 = sp.Matrix([0, y_c2, z_c2])
        rotated_vec_c2 = RotX(-alpha) * vec_c2
        T_off2_full = H(sp.eye(3), rotated_vec_c2)

        write_block(f, "3. Link 2 COM ($T_{com2}$)",
                    r"T_{com2} = T_{link1} \cdot T_{disp} \cdot T_{tilt} \cdot R_{z}(\theta_p) \cdot T_{off2}",
                    [(r"T_{disp}", T_disp), 
                     (r"T_{tilt}", T_tilt), 
                     (r"R_{z}(\theta_p)", R_pitch), 
                     (r"T_{off2}", T_off2_full)])

        # --- 4. T_COM3 ---
        # FIX: Expand T_disp23 to full 4x4 matrix
        vec_23 = sp.Matrix([0, y_23, z_23])
        rotated_vec_23 = RotX(-alpha) * vec_23
        T_disp23_full = H(sp.eye(3), rotated_vec_23)
        
        T_untilt = H(RotX(-alpha), sp.zeros(3,1))
        R_yaw = H(RotY(ty), sp.zeros(3,1))

        write_block(f, "4. Link 3 COM ($T_{com3}$)",
                    r"T_{com3} = T_{link2} \cdot T_{disp23} \cdot T_{untilt} \cdot R_{y}(\theta_y)",
                    [(r"T_{disp23}", T_disp23_full), 
                     (r"T_{untilt}", T_untilt), 
                     (r"R_{y}(\theta_y)", R_yaw)])

        # --- PARAMETER TABLE ---
        f.write("% --- Parameters Table ---\n")
        f.write(r"\section*{System Parameters}" + "\n")
        f.write(r"\begin{table}[H]" + "\n") # Changed to H for strict placement if float package used
        f.write(r"\centering" + "\n")
        f.write(r"\begin{tabular}{|c|c|l|}" + "\n")
        f.write(r"\hline" + "\n")
        f.write(r"\textbf{Symbol} & \textbf{Value} & \textbf{Description} \\ \hline" + "\n")
        
        # PRE-EXTRACT VALUES to avoid backslash in f-string expression
        v_l1 = param_values[r'l_1']
        v_l2 = param_values[r'l_2']
        v_alpha = param_values[r'\alpha']
        v_zc1 = param_values[r'z_{c1}']
        v_yc2 = param_values[r'y_{c2}']
        v_zc2 = param_values[r'z_{c2}']
        v_y23 = param_values[r'y_{23}']
        v_z23 = param_values[r'z_{23}']
        
        # Using double backslash \\ inside string literal to result in single \ in latex
        f.write(f"${sp.latex(l1)}$ & {v_l1} & Link 1 Length \\\\ \\hline\n")
        f.write(f"${sp.latex(l2)}$ & {v_l2} & Link 2 Length \\\\ \\hline\n")
        f.write(f"${sp.latex(alpha)}$ & ${v_alpha}$ & Structural Tilt Angle \\\\ \\hline\n")
        f.write(f"${sp.latex(z_c1)}$ & {v_zc1} & Link 1 COM Z-offset \\\\ \\hline\n")
        f.write(f"${sp.latex(y_c2)}$ & {v_yc2} & Link 2 COM Y-local \\\\ \\hline\n")
        f.write(f"${sp.latex(z_c2)}$ & {v_zc2} & Link 2 COM Z-local \\\\ \\hline\n")
        f.write(f"${sp.latex(y_23)}$ & {v_y23} & Joint 2-3 Y-offset \\\\ \\hline\n")
        f.write(f"${sp.latex(z_23)}$ & {v_z23} & Joint 2-3 Z-offset \\\\ \\hline\n")
        
        f.write(r"\end{tabular}" + "\n")
        f.write(r"\caption{Geometric parameters of the Gimbal System.}" + "\n")
        f.write(r"\end{table}" + "\n")

    print("Done. Files generated successfully.")

if __name__ == "__main__":
    generate_symbolic_kinematics()