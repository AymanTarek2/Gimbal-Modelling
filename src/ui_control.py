import tkinter as tk
from tkinter import ttk

# --- SHARED DATA CLASS ---
class SharedControl:
    def __init__(self):
        # --- COMMANDS (UI -> SIM) ---
        # ALL VALUES ARE LOCAL FRAME
        self.joints = [0.0, 0.0, 0.0]          # joint angles (rad)
        self.base_ori = [0.0, 0.0, 0.0]        # local roll, pitch, yaw (rad)
        self.base_pos = [0.0, 0.0, 0.0]        # local x, y, z (m)
        
        # --- MEASUREMENTS (SIM -> UI) ---
        self.meas_joints = [0.0, 0.0, 0.0]
        self.meas_base_ori = [0.0, 0.0, 0.0]
        self.meas_base_pos = [0.0, 0.0, 0.0]
        
        self.running = True


# --- UI FUNCTION ---
def run_ui(shared_data):
    root = tk.Tk()
    root.title("Gimbal Control Interface (LOCAL FRAME)")
    root.geometry("500x720")
    
    updaters = []

    # --- SLIDER HELPER ---
    def create_monitor_slider(parent, label_text, r_min, r_max, 
                              getter_cmd, setter_cmd, getter_meas):
        
        frame = ttk.Frame(parent)
        frame.pack(fill='x', padx=10, pady=5)
        
        info_label = ttk.Label(frame, text=label_text, font=("Consolas", 10))
        info_label.pack(anchor='w')
        
        def on_slider_change(val):
            setter_cmd(float(val))

        scale = ttk.Scale(
            frame, from_=r_min, to=r_max,
            orient='horizontal', command=on_slider_change
        )
        scale.set(getter_cmd())
        scale.pack(fill='x')

        # Click + drag jump support
        def handle_mouse(event):
            w = scale.winfo_width()
            if w <= 0:
                return
            x = max(0, min(event.x, w))
            ratio = x / w
            val = r_min + ratio * (r_max - r_min)
            scale.set(val)
            on_slider_change(val)
            return "break"

        scale.bind("<Button-1>", handle_mouse)
        scale.bind("<B1-Motion>", handle_mouse)

        def update_me():
            tgt = getter_cmd()
            cur = getter_meas()
            info_label.config(
                text=f"{label_text:<22} | Tgt: {tgt: >7.4f} | Cur: {cur: >7.4f}"
            )

        updaters.append(update_me)

    # --------------------------------------------------
    # JOINTS (LOCAL, JOINT SPACE)
    # --------------------------------------------------
    ttk.Label(root, text="--- Gimbal Joints (Rad, Local) ---",
              font=("Arial", 11, "bold")).pack(pady=(10, 0))

    create_monitor_slider(
        root, "Joint 1 (Yaw)",
        -3.14, 3.14,
        lambda: shared_data.joints[0],
        lambda v: shared_data.joints.__setitem__(0, v),
        lambda: shared_data.meas_joints[0]
    )

    create_monitor_slider(
        root, "Joint 2 (Pitch)",
        -3.14, 3.14,
        lambda: shared_data.joints[1],
        lambda v: shared_data.joints.__setitem__(1, v),
        lambda: shared_data.meas_joints[1]
    )

    create_monitor_slider(
        root, "Joint 3 (Roll)",
        -3.14, 3.14,
        lambda: shared_data.joints[2],
        lambda v: shared_data.joints.__setitem__(2, v),
        lambda: shared_data.meas_joints[2]
    )

    # --------------------------------------------------
    # BASE ORIENTATION (LOCAL BODY FRAME)
    # --------------------------------------------------
    ttk.Label(root, text="--- Base Orientation (Rad, LOCAL) ---",
              font=("Arial", 11, "bold")).pack(pady=(10, 0))

    create_monitor_slider(
        root, "Base Roll (local X)",
        -3.14, 3.14,
        lambda: shared_data.base_ori[0],
        lambda v: shared_data.base_ori.__setitem__(0, v),
        lambda: shared_data.meas_base_ori[0]
    )

    create_monitor_slider(
        root, "Base Pitch (local Y)",
        -3.14, 3.14,
        lambda: shared_data.base_ori[1],
        lambda v: shared_data.base_ori.__setitem__(1, v),
        lambda: shared_data.meas_base_ori[1]
    )

    create_monitor_slider(
        root, "Base Yaw (local Z)",
        -3.14, 3.14,
        lambda: shared_data.base_ori[2],
        lambda v: shared_data.base_ori.__setitem__(2, v),
        lambda: shared_data.meas_base_ori[2]
    )

    # --------------------------------------------------
    # BASE TRANSLATION (LOCAL BODY FRAME)
    # --------------------------------------------------
    ttk.Label(root, text="--- Base Translation (m, LOCAL FRAME) ---",
              font=("Arial", 11, "bold")).pack(pady=(10, 0))

    create_monitor_slider(
        root, "Forward (+X local)",
        -0.5, 0.5,
        lambda: shared_data.base_pos[0],
        lambda v: shared_data.base_pos.__setitem__(0, v),
        lambda: shared_data.meas_base_pos[0]
    )

    create_monitor_slider(
        root, "Left (+Y local)",
        -0.5, 0.5,
        lambda: shared_data.base_pos[1],
        lambda v: shared_data.base_pos.__setitem__(1, v),
        lambda: shared_data.meas_base_pos[1]
    )

    create_monitor_slider(
        root, "Up (+Z local)",
        -0.5, 0.5,
        lambda: shared_data.base_pos[2],
        lambda v: shared_data.base_pos.__setitem__(2, v),
        lambda: shared_data.meas_base_pos[2]
    )

    # --------------------------------------------------
    # MONITOR LOOP
    # --------------------------------------------------
    def monitor_loop():
        if not shared_data.running:
            return
        for u in updaters:
            u()
        root.after(50, monitor_loop)

    monitor_loop()

    def on_close():
        shared_data.running = False
        root.destroy()

    root.protocol("WM_DELETE_WINDOW", on_close)
    root.mainloop()
