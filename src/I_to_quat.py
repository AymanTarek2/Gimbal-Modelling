import numpy as np
import sympy as sp
from scipy.spatial.transform import Rotation as R

def get_clean_mujoco_inertial(I_sympy):
    # 1. Convert to NumPy
    I_np = np.array(I_sympy.tolist(), dtype=float)
    
    # 2. Eigen-decomposition
    evals, evecs = np.linalg.eigh(I_np)
    
    # 3. Map eigenvalues to [X, Y, Z] to prevent swapping
    # np.argmax(np.abs(evecs), axis=0) finds which original axis 
    # each eigenvector is most aligned with.
    order = np.argmax(np.abs(evecs), axis=0)
    sorted_indices = np.argsort(order)
    
    evals = evals[sorted_indices]
    evecs = evecs[:, sorted_indices]

    # 4. FIX: Ensure eigenvectors point in the "positive" original direction
    # This prevents the 180-degree flips (like the one you saw)
    for i in range(3):
        if evecs[i, i] < 0:
            evecs[:, i] *= -1
            
    # 5. Ensure a Right-Handed System (det must be +1)
    if np.linalg.det(evecs) < 0:
        evecs[:, 2] *= -1
        
    # 6. Convert to MuJoCo Quaternion (w, x, y, z)
    r = R.from_matrix(evecs)
    quat_xyzw = r.as_quat()
    
    # Reorder to wxyz
    quat_wxyz = [quat_xyzw[3], quat_xyzw[0], quat_xyzw[1], quat_xyzw[2]]
    
    return evals, quat_wxyz

# --- Test with your Matrix ---
scale = 1e-9
I = sp.Matrix([[28901.95, 0.0, 0.0],[0.0, 53236.19, 0.0],[0.0, 0.0, 28901.95]]) * scale

diaginertia, quat = get_clean_mujoco_inertial(I)

print(f'diaginertia="{" ".join(f"{x:.12f}" for x in diaginertia)}"')
print(f'quat="{" ".join(f"{x:.12f}" for x in quat)}"')