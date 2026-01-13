import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider
from collections import defaultdict

# ===============================
# NUMERIC POINT EXTRACTION
# ===============================
def get_point_from_T(T_matrix, symbol_values):
    T_num = T_matrix.subs(symbol_values)
    T_np = np.array(T_num.tolist(), dtype=float)
    return T_np[0:3, 3] * 1000.0  # mm


# ===============================
# VISUALIZER
# ===============================
def start_visualizer(visual_frames, internal_map):
    # 1. Filter out unwanted origin frames entirely
    filtered_frames = [
        (name, T, chain) for name, T, chain in visual_frames 
        if name not in ["base_link_CoM", "Base_Origin"]
    ]

    all_symbols = sorted(
        list(set().union(*(T.free_symbols for _, T, _ in filtered_frames))),
        key=lambda s: s.name
    )

    fig, ax = plt.subplots(figsize=(14, 10))
    plt.subplots_adjust(left=0.3, bottom=0.15)

    sliders = [Slider(plt.axes([0.05, 0.1 + i * 0.035, 0.15, 0.025]), sym.name, 
               *((-1000, 1000) if any(n in sym.name for n in ['px', 'py', 'pz']) else (-np.pi, np.pi)), 
               valinit=0.0) for i, sym in enumerate(all_symbols)]

    # 2. Logic: Build connections based on the deepest available ancestor
    def build_chain_edges():
        edges = set()
        # Sort by chain length (deepest roots first)
        sorted_f = sorted(filtered_frames, key=lambda x: len(x[2]))
        
        for i, (child_name, _, child_chain) in enumerate(sorted_f):
            # Look backwards for the closest ancestor that exists in our list
            for j in range(i - 1, -1, -1):
                parent_name, _, parent_chain = sorted_f[j]
                # If parent_chain is a prefix of child_chain, this is the parent
                if child_chain[:len(parent_chain)] == parent_chain:
                    edges.add((parent_name, child_name))
                    break
        return edges

    edges = build_chain_edges()

    # ---------------------------------
    # UPDATE FUNCTION
    # ---------------------------------
    def update(val):
        ax.clear()
        vals = {sym: s.val for sym, s in zip(all_symbols, sliders)}

        # Compute positions
        pts = {n: get_point_from_T(T, vals) for n, T, _ in filtered_frames}

        # DRAW EDGES
        for a, b in edges:
            pa, pb = pts[a], pts[b]
            ax.annotate(
                '', xy=(pb[2], pb[1]), xytext=(pa[2], pa[1]),
                arrowprops=dict(arrowstyle='->', color='black', lw=1.5, shrinkA=0, shrinkB=0)
            )

        # DRAW NODES
        grouped = defaultdict(list)
        for name, p in pts.items():
            grouped[tuple(np.round(p, 6))].append(name)

        for (x, y, z), names in grouped.items():
            color = 'red' if "base_com" in names else 'blue'
            ax.scatter(z, y, s=50, c=color, zorder=5)
            label = "\n".join(names)
            # FIXED: Coordinate labels updated to three decimal places
            coord = f"({x:.3f}, {y:.3f}, {z:.3f})"
            ax.annotate(
                f"{label}\n{coord}", (z, y), xytext=(6, 6),
                textcoords='offset points', fontsize=7,
                bbox=dict(boxstyle="round,pad=0.2", fc="white", ec="black", alpha=0.9)
            )

        # AXES
        if pts:
            all_pts = np.array(list(pts.values()))
            zc, yc = all_pts[:, 2], all_pts[:, 1]
            span = max(zc.max() - zc.min(), yc.max() - yc.min())
            span = span if span > 10 else 100
            ax.set_xlim(zc.mean() - span, zc.mean() + span)
            ax.set_ylim(yc.mean() - span, yc.mean() + span)

        ax.set_aspect('equal')
        ax.set_xlabel('Global Z (mm)')
        ax.set_ylabel('Global Y (mm)')
        ax.set_title('ZY Projection: Rooted at base_com (3 Decimal Precision)')
        ax.grid(True, linestyle=':', alpha=0.5)
        fig.canvas.draw_idle()

    for s in sliders: s.on_changed(update)
    update(None)
    plt.show()