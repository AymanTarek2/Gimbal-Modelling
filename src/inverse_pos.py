import sympy as sp

def compute_orientation_ik():
    # Symbolic joint variables
    q1, q2, q3 = sp.symbols('q1 q2 q3')

    # Link lengths (symbolic)
    L1, L2 = sp.symbols('L1 L2')

    # DH constants (angles in radians)
    alpha1_val = sp.pi * 75 / 180
    alpha2_val = sp.pi * -75 / 180

    # Build standard DH transform (no heavy simplify)
    def dh_matrix(theta, d, a, alpha):
        return sp.Matrix([
            [sp.cos(theta), -sp.sin(theta)*sp.cos(alpha),  sp.sin(theta)*sp.sin(alpha), a*sp.cos(theta)],
            [sp.sin(theta),  sp.cos(theta)*sp.cos(alpha), -sp.cos(theta)*sp.sin(alpha), a*sp.sin(theta)],
            [0,               sp.sin(alpha),               sp.cos(alpha),               d],
            [0,               0,                           0,                           1]
        ])

    T01 = dh_matrix(q1, L1, 0, alpha1_val)
    T12 = dh_matrix(q2, L2, 0, alpha2_val)
    T23 = dh_matrix(q3, 0,  0, 0)

    T02 = T01 * T12            # avoid simplify for speed
    T03 = T02 * T23

    # Rotation submatrix of the forward kinematics
    R_03 = T03[0:3, 0:3]

    # Desired Euler angles (Z-Y-X: yaw-pitch-roll)
    theta_x_d, theta_y_d, theta_z_d = sp.symbols('theta_x_d theta_y_d theta_z_d')
    thx = theta_x_d; thy = theta_y_d; thz = theta_z_d

    Rz = sp.Matrix([[sp.cos(thz), -sp.sin(thz), 0],
                    [sp.sin(thz),  sp.cos(thz), 0],
                    [0,            0,           1]])
    Ry = sp.Matrix([[sp.cos(thy), 0, sp.sin(thy)],
                    [0,           1, 0],
                    [-sp.sin(thy),0, sp.cos(thy)]])
    Rx = sp.Matrix([[1, 0,           0],
                    [0, sp.cos(thx), -sp.sin(thx)],
                    [0, sp.sin(thx),  sp.cos(thx)]])
    R_des = Rz * Ry * Rx  # no simplify (fast)

    # Third column from forward rotation (depends mainly on q1,q2)
    r13 = R_03[0, 2]
    r23 = R_03[1, 2]
    r33 = R_03[2, 2]

    # Third column from desired rotation (pure functions of theta_x,y,z)
    rd13 = R_des[0, 2]
    rd23 = R_des[1, 2]
    rd33 = R_des[2, 2]

    # ANALYTIC EXTRACTION (fast, avoids sp.solve on 9 eqs)
    # Step 1: determine cos(q2) from r33 = a*cos(q2) + b form
    val_plus = r33.subs(q2, 0)        # r33 at cos(q2)=1
    val_minus = r33.subs(q2, sp.pi)   # r33 at cos(q2)=-1

    a_c = (val_plus - val_minus) / 2
    b_c = (val_plus + val_minus) / 2

    # cos(q2) expressed in terms of desired rotation (rd33)
    cos_q2_expr = sp.simplify((rd33 - b_c) / a_c)    # one simplify here is cheap

    # principal q2 branch
    q2_expr = sp.acos(cos_q2_expr)

    # positive sin(q2) branch (choose + by default; enumerate branches later if needed)
    sin_q2_expr = sp.sqrt(1 - cos_q2_expr**2)

    # constants derived from DH geometry (these come from algebra of your T03)
    k = (sp.sqrt(6) + sp.sqrt(2)) / 4

    # A and B used in the linear combination for the 3rd column
    A_expr = (1 - cos_q2_expr) / 4
    B_expr = -k * sin_q2_expr

    # form linear combination s_num, c_num used to compute q1 via atan2
    s_num = A_expr * rd13 + B_expr * rd23
    c_num = B_expr * rd13 - A_expr * rd23
    q1_expr = sp.atan2(s_num, c_num)

    # compute q3: after q1,q2 fixed, R02.T * R_des should be rotation about Z by q3
    R02 = T02[0:3, 0:3]
    R02_sub = R02.subs({q1: q1_expr, q2: q2_expr})
    M = R02_sub.T * R_des
    q3_expr = sp.atan2(M[1, 0], M[0, 0])

    # Return symbolic expressions
    return {sp.Symbol('q1'): sp.simplify(q1_expr),
            sp.Symbol('q2'): sp.simplify(q2_expr),
            sp.Symbol('q3'): sp.simplify(q3_expr),
            'R_03': R_03, 'R_des': R_des, 'T01': T01, 'T12': T12, 'T23': T23}

def main():
    sol = compute_orientation_ik()
    q1_expr = sol[sp.Symbol('q1')]
    q2_expr = sol[sp.Symbol('q2')]
    q3_expr = sol[sp.Symbol('q3')]

    print("\nSymbolic inverse-orientation solutions (in terms of theta_x_d,theta_y_d,theta_z_d):\n")
    print("q1 =")
    sp.pprint(q1_expr, use_unicode=True)
    print("\nq2 =")
    sp.pprint(q2_expr, use_unicode=True)
    print("\nq3 =")
    sp.pprint(q3_expr, use_unicode=True)

    # Optional quick numeric test (toggle to True to run)
    NUMERIC_TEST = False
    if NUMERIC_TEST:
        # set numeric link lengths and desired Euler angles (example)
        subs = {
            'L1': 13.548, 'L2': 9.637,
            'theta_x_d': 0.1, 'theta_y_d': 0.2, 'theta_z_d': -0.3
        }
        q1_num = float(q1_expr.subs(subs).evalf())
        q2_num = float(q2_expr.subs(subs).evalf())
        q3_num = float(q3_expr.subs(subs).evalf())
        print("\nNumeric test:")
        print("q1 =", q1_num, "q2 =", q2_num, "q3 =", q3_num)

if __name__ == '__main__':
    main()
