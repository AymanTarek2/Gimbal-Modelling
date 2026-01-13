# gimbal_dynamics_with_export.py
# Computes symbolic dynamics (M, C, G, tau) for your 3-DOF gimbal
# and exports tau to a LaTeX file (gimbal_equations.tex).
# Requires: sympy

import sympy as sp

def dh_matrix(theta, d, a, alpha):
    return sp.Matrix([
        [sp.cos(theta), -sp.sin(theta)*sp.cos(alpha),  sp.sin(theta)*sp.sin(alpha), a*sp.cos(theta)],
        [sp.sin(theta),  sp.cos(theta)*sp.cos(alpha), -sp.cos(theta)*sp.sin(alpha), a*sp.sin(theta)],
        [0,              sp.sin(alpha),                sp.cos(alpha),              d],
        [0,              0,                            0,                          1]
    ])


def compute_dynamics(simplify_result=False):
    q1, q2, q3 = sp.symbols('q1 q2 q3')
    qd1, qd2, qd3 = sp.symbols('qd1 qd2 qd3')
    qdd1, qdd2, qdd3 = sp.symbols('qdd1 qdd2 qdd3')

    q = sp.Matrix([q1, q2, q3])
    qd = sp.Matrix([qd1, qd2, qd3])
    qdd = sp.Matrix([qdd1, qdd2, qdd3])

    L1, L2 = sp.symbols('L1 L2')
    alpha1 = sp.pi * 75 / 180
    alpha2 = sp.pi * -75 / 180

    dh_params = [
        (q1, L1, 0, alpha1),
        (q2, L2, 0, alpha2),
        (q3, 0,  0, 0)
    ]

    T01 = dh_matrix(*dh_params[0])
    T12 = dh_matrix(*dh_params[1])
    T23 = dh_matrix(*dh_params[2])

    T0_0 = sp.eye(4)
    T0_1 = T01
    T0_2 = sp.simplify(T01 * T12)
    T0_3 = sp.simplify(T0_2 * T23)

    R0_1 = sp.simplify(T0_1[0:3, 0:3])
    R0_2 = sp.simplify(T0_2[0:3, 0:3])
    R0_3 = sp.simplify(T0_3[0:3, 0:3])

    p0 = sp.Matrix([0, 0, 0])
    p1 = sp.simplify(T0_1[0:3, 3])
    p2 = sp.simplify(T0_2[0:3, 3])
    p3 = sp.simplify(T0_3[0:3, 3])

    # symbolic inertial parameters
    m1, m2, m3 = sp.symbols('m1 m2 m3')
    c1x, c1y, c1z = sp.symbols('c1x c1y c1z')
    c2x, c2y, c2z = sp.symbols('c2x c2y c2z')
    c3x, c3y, c3z = sp.symbols('c3x c3y c3z')

    r_c1 = sp.Matrix([c1x, c1y, c1z, 1])
    r_c2 = sp.Matrix([c2x, c2y, c2z, 1])
    r_c3 = sp.Matrix([c3x, c3y, c3z, 1])

    rC1_base = sp.simplify(T0_1 * r_c1)[0:3, 0]
    rC2_base = sp.simplify(T0_2 * r_c2)[0:3, 0]
    rC3_base = sp.simplify(T0_3 * r_c3)[0:3, 0]

    I1xx, I1yy, I1zz, I1xy, I1xz, I1yz = sp.symbols('I1xx I1yy I1zz I1xy I1xz I1yz')
    I2xx, I2yy, I2zz, I2xy, I2xz, I2yz = sp.symbols('I2xx I2yy I2zz I2xy I2xz I2yz')
    I3xx, I3yy, I3zz, I3xy, I3xz, I3yz = sp.symbols('I3xx I3yy I3zz I3xy I3xz I3yz')

    I1 = sp.Matrix([[I1xx, I1xy, I1xz],
                    [I1xy, I1yy, I1yz],
                    [I1xz, I1yz, I1zz]])
    I2 = sp.Matrix([[I2xx, I2xy, I2xz],
                    [I2xy, I2yy, I2yz],
                    [I2xz, I2yz, I2zz]])
    I3 = sp.Matrix([[I3xx, I3xy, I3xz],
                    [I3xy, I3yy, I3yz],
                    [I3xz, I3yz, I3zz]])

    I1_base = sp.simplify(R0_1 * I1 * R0_1.T)
    I2_base = sp.simplify(R0_2 * I2 * R0_2.T)
    I3_base = sp.simplify(R0_3 * I3 * R0_3.T)

    # Jacobians
    def jacobian_linear(rC_base):
        Jv = sp.zeros(3, 3)
        for j in range(3):
            Jv[:, j] = sp.simplify(sp.diff(rC_base, [q1, q2, q3][j]))
        return Jv

    Jv1 = jacobian_linear(rC1_base)
    Jv2 = jacobian_linear(rC2_base)
    Jv3 = jacobian_linear(rC3_base)

    z0 = sp.Matrix([0, 0, 1])
    z1 = R0_1[:, 2]
    z2 = R0_2[:, 2]

    Jw1 = sp.Matrix.hstack(z0, sp.zeros(3,1), sp.zeros(3,1))
    Jw2 = sp.Matrix.hstack(z0, z1, sp.zeros(3,1))
    Jw3 = sp.Matrix.hstack(z0, z1, z2)

    M = sp.zeros(3, 3)
    M += m1 * (Jv1.T * Jv1) + (Jw1.T * I1_base * Jw1)
    M += m2 * (Jv2.T * Jv2) + (Jw2.T * I2_base * Jw2)
    M += m3 * (Jv3.T * Jv3) + (Jw3.T * I3_base * Jw3)
    M = sp.simplify(M)

    g = sp.symbols('g')
    g_vec = sp.Matrix([0, 0, -g])
    U = m1 * (g_vec.dot(rC1_base)) + m2 * (g_vec.dot(rC2_base)) + m3 * (g_vec.dot(rC3_base))
    G = sp.Matrix([sp.simplify(sp.diff(U, q_i)) for q_i in (q1, q2, q3)])

    # Christoffel symbols and Coriolis matrix
    n = 3
    Gamma = {}
    for i in range(n):
        for j in range(n):
            for k in range(n):
                val = sp.Rational(1,2) * (sp.diff(M[i, j], [q1, q2, q3][k]) +
                                           sp.diff(M[i, k], [q1, q2, q3][j]) -
                                           sp.diff(M[j, k], [q1, q2, q3][i]))
                Gamma[(i,j,k)] = sp.simplify(val)

    C = sp.zeros(n, n)
    qd = sp.Matrix([qd1, qd2, qd3])
    for i in range(n):
        for j in range(n):
            s = 0
            for k in range(n):
                s += Gamma[(i,j,k)] * qd[k]
            C[i, j] = sp.simplify(s)

    Cvec = sp.simplify(C * qd)
    qdd = sp.Matrix([qdd1, qdd2, qdd3])
    tau = sp.simplify(M * qdd + Cvec + G)

    symbols = {
        'q': sp.Matrix([q1, q2, q3]), 'qd': qd, 'qdd': qdd, 'L1': L1, 'L2': L2, 'g': g,
        'm1': m1, 'm2': m2, 'm3': m3,
        'c1': (c1x, c1y, c1z), 'c2': (c2x, c2y, c2z), 'c3': (c3x, c3y, c3z),
        'I1_elems': (I1xx, I1yy, I1zz, I1xy, I1xz, I1yz),
        'I2_elems': (I2xx, I2yy, I2zz, I2xy, I2xz, I2yz),
        'I3_elems': (I3xx, I3yy, I3zz, I3xy, I3xz, I3yz)
    }

    outputs = {
        'M': M,
        'C': C,
        'Cvec': Cvec,
        'G': G,
        'tau': tau,
        'T0_1': T0_1, 'T0_2': T0_2, 'T0_3': T0_3,
        'rC1_base': rC1_base, 'rC2_base': rC2_base, 'rC3_base': rC3_base,
        'Jv1': Jv1, 'Jv2': Jv2, 'Jv3': Jv3,
        'Jw1': Jw1, 'Jw2': Jw2, 'Jw3': Jw3
    }

    return symbols, outputs


if __name__ == "__main__":
    # Replace the old (invalid) sp.set_printoptions(...) with init_printing
    sp.init_printing(use_unicode=True)

    symbols, outputs = compute_dynamics(simplify_result=False)

    print("Computed symbolic dynamics for 3-DOF gimbal.")
    print("Returned objects (in `outputs`): M, C, Cvec, G, tau\n")

    # Print short summaries (M and G)
    print("Mass matrix M(q):")
    sp.pprint(outputs['M'])

    print("\nGravity vector G(q):")
    sp.pprint(outputs['G'])

    print("\nCoriolis/centripetal vector C(q,qd)*qd:")
    sp.pprint(outputs['Cvec'])

    # --- Export torque tau to LaTeX (uncommented & guarded) ---
    try:
        tex_filename = 'gimbal_equations.tex'
        print(f"\nExporting tau to LaTeX file: {tex_filename} (this may take some time)...")
        with open(tex_filename, 'w', encoding='utf-8') as f:
            f.write(r'\documentclass{article}' + '\n')
            f.write(r'\usepackage{amsmath}' + '\n')
            f.write(r'\usepackage{lmodern}' + '\n')
            f.write(r'\usepackage[T1]{fontenc}' + '\n')
            f.write(r'\begin{document}' + '\n\n')
            # Write a small header, then the LaTeX for tau
            f.write(r'\section*{Torque vector $\tau(q,\dot q,\ddot q)$}' + '\n\n')
            f.write(r'\[' + '\n')
            f.write(sp.latex(outputs['tau']) + '\n')
            f.write(r'\]' + '\n\n')
            f.write(r'\end{document}' + '\n')
        print("LaTeX export completed successfully.")
    except MemoryError:
        print("MemoryError: Tau is too large to convert to LaTeX on this machine.")
    except Exception as e:
        print("An error occurred while exporting LaTeX:", repr(e))

    print("\nDone.")
