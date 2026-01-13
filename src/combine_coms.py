from typing import Tuple, List

def calculate_combined_com(*particles: Tuple[float, float, float, float]) -> Tuple[float, Tuple[float, float, float]]:
    """
    Calculates the total mass and the combined center of mass (COM)
    from two or more particles.

    Each particle should be a tuple in the format: (mass, x, y, z)

    Args:
        *particles: A variable number of particle tuples.

    Returns:
        A tuple containing:
        (total_mass, (com_x, com_y, com_z))
    
    Raises:
        ValueError: If fewer than two particles are provided.
    """
    if len(particles) < 2:
        raise ValueError("Please provide at least two particles.")

    total_mass = 0.0
    # Use weighted sums for each coordinate
    # m_total * x_com = m1*x1 + m2*x2 + ...
    weighted_sum_x = 0.0
    weighted_sum_y = 0.0
    weighted_sum_z = 0.0

    # Iterate through each particle tuple
    for particle in particles:
        try:
            mass, x, y, z = particle
        except ValueError:
            print(f"Skipping malformed particle tuple: {particle}")
            continue

        if mass < 0:
            print(f"Warning: Particle has negative mass. {particle}")

        total_mass += mass
        weighted_sum_x += mass * x
        weighted_sum_y += mass * y
        weighted_sum_z += mass * z

    # Avoid division by zero if total mass is zero
    if total_mass == 0:
        # If total mass is 0, COM is undefined.
        # We can return (0, 0, 0) or raise an error.
        # Returning (0, 0, 0) at the origin seems reasonable.
        return 0.0, (0.0, 0.0, 0.0)

    # Calculate the combined COM coordinates
    com_x = weighted_sum_x / total_mass
    com_y = weighted_sum_y / total_mass
    com_z = weighted_sum_z / total_mass

    return total_mass, (com_x, com_y, com_z)

# --- Example Usage ---
if __name__ == "__main__":
    # Define two particles: (mass, x, y, z)
    particle1 = (72.84, 27.41, 338.53, -0.04)  # 10kg at the origin
    particle2 = (0, 0, 0, 0)  # 10kg at (2, 0, 0)
    
    # Expected: Total mass = 20.0, COM = (1.0, 0.0, 0.0)
    total_mass, com = calculate_combined_com(particle1, particle2)
    
    print(f"--- Minimal Example (Two particles) ---")
    print(f"Particle 1: {particle1}")
    print(f"Particle 2: {particle2}")
    print(f"Total Mass: {total_mass:.2f}")
    print(f"Combined COM: ({com[0]:.2f}, {com[1]:.2f}, {com[2]:.2f})\n")