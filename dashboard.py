import tkinter as tk
from tkinter import scrolledtext
import subprocess
import threading
import os
import sys
import re
import time
from datetime import datetime

class ShauryaGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("SHAURYA v0.2.0 - LIVE INJECTOR")
        self.root.geometry("1260x760")
        self.root.configure(bg="#1e1e1e")

        self.exo_process = None
        self.shaurya_process = None
        self.exo_start_time = None
        self.shaurya_start_time = None

        self.total_messages = 0
        self.accepted_messages = 0
        self.rejected_messages = 0
        self.min_latency_us = "N/A"
        self.max_latency_us = "N/A"
        self.avg_latency_us = "N/A"
        self.p99_latency_us = "N/A"
        self.last_action = "N/A"

        self.trade_summary_pattern = re.compile(r"Processed\s+(\d+)\s+live\s+trades", re.IGNORECASE)
        self.total_messages_pattern = re.compile(r"Total\s+Messages\s*:\s*(\d+)", re.IGNORECASE)
        self.min_latency_pattern = re.compile(r"Min\s+Latency\s*:\s*([0-9]+(?:\.[0-9]+)?)\s*us", re.IGNORECASE)
        self.max_latency_pattern = re.compile(r"Max\s+Latency\s*:\s*([0-9]+(?:\.[0-9]+)?)\s*us", re.IGNORECASE)
        self.avg_latency_pattern = re.compile(r"Avg\s+Latency\s*:\s*([0-9]+(?:\.[0-9]+)?)\s*us", re.IGNORECASE)
        self.p99_latency_pattern = re.compile(r"99th\s+Percentile\s*:\s*([0-9]+(?:\.[0-9]+)?)\s*us", re.IGNORECASE)
        self.rejected_pattern = re.compile(r"FPGA:\s*BLOCKED|REJECTED|BLOCKED", re.IGNORECASE)
        self.accepted_pattern = re.compile(r"\[BUY\]|\[SELL\]|APPROVED|EXECUTED", re.IGNORECASE)

        self.verilog_modules = {
            "feature_engine.v": tk.StringVar(value="UNKNOWN"),
            "risk_firewall.v": tk.StringVar(value="UNKNOWN"),
            "rate_limiter.v": tk.StringVar(value="UNKNOWN"),
            "kill_switch.v": tk.StringVar(value="UNKNOWN"),
        }

        self.status_vars = {
            "Exchange": tk.StringVar(value="OFFLINE"),
            "Engine": tk.StringVar(value="OFFLINE"),
            "Uptime": tk.StringVar(value="00:00:00"),
            "Total Messages": tk.StringVar(value="0"),
            "Accepted": tk.StringVar(value="0"),
            "Rejected": tk.StringVar(value="0"),
            "Min Lat (us)": tk.StringVar(value="N/A"),
            "Max Lat (us)": tk.StringVar(value="N/A"),
            "Avg Lat (us)": tk.StringVar(value="N/A"),
            "P99 Lat (us)": tk.StringVar(value="N/A"),
            "Last Action": tk.StringVar(value="N/A"),
        }

        # --- CONTROL PANEL ---
        btn_frame = tk.Frame(root, bg="#1e1e1e")
        btn_frame.pack(pady=(14, 8))

        # Stock Input
        tk.Label(btn_frame, text="Stock Symbol:", bg="#1e1e1e", fg="white", font=("Consolas", 12, "bold")).grid(row=0, column=0, padx=5)
        self.symbol_entry = tk.Entry(btn_frame, font=("Consolas", 12, "bold"), width=8, bg="#2d2d2d", fg="#00ff00", insertbackground="white")
        self.symbol_entry.insert(0, "KLAC")
        self.symbol_entry.grid(row=0, column=1, padx=(0, 20))

        # Buttons
        self.btn_start_all = tk.Button(btn_frame, text="▶ START ALL (20s)", command=self.start_all,
                                       bg="#005f00", fg="white", font=("Consolas", 11, "bold"), width=18, relief=tk.FLAT)
        self.btn_start_all.grid(row=0, column=2, padx=8)

        self.btn_stop = tk.Button(btn_frame, text="■ STOP ALL", command=self.stop_all, 
                                  bg="#8b0000", fg="white", font=("Consolas", 11, "bold"), width=12, relief=tk.FLAT)
        self.btn_stop.grid(row=0, column=3, padx=8)

        self.btn_restart_engine = tk.Button(btn_frame, text="Restart Engine", command=self.restart_shaurya,
                                            bg="#5f4b00", fg="white", font=("Consolas", 11, "bold"), width=15, relief=tk.FLAT)
        self.btn_restart_engine.grid(row=0, column=4, padx=8)

        self.btn_clear_logs = tk.Button(btn_frame, text="Clear Logs", command=self.clear_logs,
                                        bg="#3d3d3d", fg="white", font=("Consolas", 11), width=12, relief=tk.FLAT)
        self.btn_clear_logs.grid(row=0, column=5, padx=8)

        self.btn_save_snapshot = tk.Button(btn_frame, text="Save Snapshot", command=self.save_snapshot,
                                           bg="#195f5f", fg="white", font=("Consolas", 11), width=14, relief=tk.FLAT)
        self.btn_save_snapshot.grid(row=0, column=6, padx=8)

        # --- METRICS PANEL ---
        panel_frame = tk.Frame(root, bg="#1e1e1e")
        panel_frame.pack(fill=tk.X, padx=15, pady=(0, 10))

        metrics_frame = tk.LabelFrame(panel_frame, text=" LIVE METRICS ", bg="#141414", fg="#ffd166",
                                      font=("Consolas", 10, "bold"), bd=1, relief=tk.FLAT)
        metrics_frame.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=(0, 6))

        metric_order = [
            "Exchange", "Engine", "Uptime", "Total Messages", "Accepted",
            "Rejected", "Min Lat (us)", "Max Lat (us)", "Avg Lat (us)", "P99 Lat (us)"
        ]
        for idx, key in enumerate(metric_order):
            row, col = divmod(idx, 5)
            metric_cell = tk.Frame(metrics_frame, bg="#141414")
            metric_cell.grid(row=row, column=col, sticky="w", padx=8, pady=4)
            tk.Label(metric_cell, text=f"{key}:", bg="#141414", fg="#a8dadc", font=("Consolas", 10, "bold")).pack(side=tk.LEFT)
            tk.Label(metric_cell, textvariable=self.status_vars[key], bg="#141414", fg="#f1fa8c", font=("Consolas", 10)).pack(side=tk.LEFT, padx=(5, 0))

        verilog_frame = tk.LabelFrame(panel_frame, text=" VERILOG SAFETY FABRIC ", bg="#141414", fg="#80ffdb",
                                      font=("Consolas", 10, "bold"), bd=1, relief=tk.FLAT)
        verilog_frame.pack(side=tk.RIGHT, fill=tk.X, expand=True, padx=(6, 0))

        self.verilog_labels = {}
        for idx, module_name in enumerate(self.verilog_modules):
            module_cell = tk.Frame(verilog_frame, bg="#141414")
            module_cell.grid(row=idx // 2, column=idx % 2, sticky="w", padx=10, pady=4)
            tk.Label(module_cell, text=module_name, bg="#141414", fg="#8ecae6", font=("Consolas", 10, "bold")).pack(side=tk.LEFT)
            status_label = tk.Label(module_cell, textvariable=self.verilog_modules[module_name], bg="#141414", fg="#ffd166", font=("Consolas", 10))
            status_label.pack(side=tk.LEFT, padx=(8, 0))
            self.verilog_labels[module_name] = status_label

        self.refresh_verilog_status()

        # --- LOG CONSOLES ---
        console_frame = tk.Frame(root, bg="#1e1e1e")
        console_frame.pack(fill=tk.BOTH, expand=True, padx=15, pady=10)

        exo_frame = tk.Frame(console_frame, bg="#1e1e1e")
        exo_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=(0, 5))
        tk.Label(exo_frame, text="REAL-TIME INJECTOR LOGS", bg="#1e1e1e", fg="#00ff00", font=("Consolas", 11, "bold")).pack(anchor="w")
        self.exo_text = scrolledtext.ScrolledText(exo_frame, bg="#0d0d0d", fg="#00ff00", font=("Consolas", 10), relief=tk.FLAT)
        self.exo_text.pack(fill=tk.BOTH, expand=True, pady=5)

        shaurya_frame = tk.Frame(console_frame, bg="#1e1e1e")
        shaurya_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=(5, 0))
        tk.Label(shaurya_frame, text="SHAURYA EXECUTION PLANE", bg="#1e1e1e", fg="#00ffff", font=("Consolas", 11, "bold")).pack(anchor="w")
        self.shaurya_text = scrolledtext.ScrolledText(shaurya_frame, bg="#0d0d0d", fg="#00ffff", font=("Consolas", 10), relief=tk.FLAT)
        self.shaurya_text.pack(fill=tk.BOTH, expand=True, pady=5)

        self.root.after(500, self.refresh_runtime_status)

    def append_text(self, text_widget, text):
        text_widget.insert(tk.END, text)
        text_widget.see(tk.END)

    def format_uptime(self, start_ts):
        if not start_ts:
            return "00:00:00"
        elapsed = max(0, int(time.time() - start_ts))
        hours = elapsed // 3600
        minutes = (elapsed % 3600) // 60
        seconds = elapsed % 60
        return f"{hours:02d}:{minutes:02d}:{seconds:02d}"

    def update_metric_labels(self):
        self.status_vars["Total Messages"].set(str(self.total_messages))
        self.status_vars["Accepted"].set(str(self.accepted_messages))
        self.status_vars["Rejected"].set(str(self.rejected_messages))
        self.status_vars["Min Lat (us)"].set(self.min_latency_us)
        self.status_vars["Max Lat (us)"].set(self.max_latency_us)
        self.status_vars["Avg Lat (us)"].set(self.avg_latency_us)
        self.status_vars["P99 Lat (us)"].set(self.p99_latency_us)
        self.status_vars["Last Action"].set(self.last_action)

    def handle_log_line(self, source, line):
        if source != "shaurya":
            return

        match = self.trade_summary_pattern.search(line)
        if match:
            parsed_count = int(match.group(1))
            self.total_messages = max(self.total_messages, parsed_count)

        match = self.total_messages_pattern.search(line)
        if match:
            self.total_messages = int(match.group(1))

        match = self.min_latency_pattern.search(line)
        if match:
            self.min_latency_us = match.group(1)

        match = self.max_latency_pattern.search(line)
        if match:
            self.max_latency_us = match.group(1)

        match = self.avg_latency_pattern.search(line)
        if match:
            self.avg_latency_us = match.group(1)

        match = self.p99_latency_pattern.search(line)
        if match:
            self.p99_latency_us = match.group(1)

        if "Price:" in line:
            self.total_messages += 1

        if self.rejected_pattern.search(line):
            self.rejected_messages += 1
            self.last_action = "REJECTED"
        elif self.accepted_pattern.search(line):
            self.accepted_messages += 1
            self.last_action = "EXECUTED"

        latency_match = re.search(r"Lat:\s*([0-9]+(?:\.[0-9]+)?)\s*us", line)
        if latency_match:
            self.avg_latency_us = latency_match.group(1)

        inferred_accepted = self.total_messages - self.rejected_messages
        if inferred_accepted > self.accepted_messages:
            self.accepted_messages = inferred_accepted

        self.update_metric_labels()

    def process_line(self, source, text_widget, decoded):
        self.append_text(text_widget, decoded)
        self.handle_log_line(source, decoded)
        # Print cleanly to terminal without double tags
        print(decoded, end="")

    def read_output(self, process, text_widget):
        source = "injector" if text_widget is self.exo_text else "shaurya"
        for line in iter(process.stdout.readline, b''):
            if line:
                decoded = line.decode('utf-8', errors='ignore')
                self.root.after(0, self.process_line, source, text_widget, decoded)
        process.stdout.close()

    def refresh_verilog_status(self):
        for module_name, module_status_var in self.verilog_modules.items():
            exists = os.path.exists(module_name)
            if exists:
                module_status_var.set("LOADED")
                self.verilog_labels[module_name].config(fg="#80ff72")
            else:
                module_status_var.set("MISSING")
                self.verilog_labels[module_name].config(fg="#ff6b6b")

    def refresh_runtime_status(self):
        exo_online = self.exo_process is not None and self.exo_process.poll() is None
        shaurya_online = self.shaurya_process is not None and self.shaurya_process.poll() is None

        self.status_vars["Exchange"].set("ONLINE" if exo_online else "OFFLINE")
        self.status_vars["Engine"].set("ONLINE" if shaurya_online else "OFFLINE")

        if shaurya_online:
            self.status_vars["Uptime"].set(self.format_uptime(self.shaurya_start_time))
        else:
            self.status_vars["Uptime"].set("00:00:00")

        if self.exo_process is not None and self.exo_process.poll() is not None:
            self.exo_process = None

        if self.shaurya_process is not None and self.shaurya_process.poll() is not None:
            self.shaurya_process = None

        self.update_metric_labels()
        self.root.after(500, self.refresh_runtime_status)

    def clear_logs(self):
        self.exo_text.delete("1.0", tk.END)
        self.shaurya_text.delete("1.0", tk.END)
        self.append_text(self.exo_text, "[SYSTEM] Exchange log cleared.\n")
        self.append_text(self.shaurya_text, "[SYSTEM] Engine log cleared.\n")

    def save_snapshot(self):
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        output_name = f"dashboard_snapshot_{timestamp}.txt"
        with open(output_name, "w", encoding="utf-8") as fh:
            fh.write("=== SHAURYA DASHBOARD SNAPSHOT ===\n")
            for key in ["Exchange", "Engine", "Uptime", "Total Messages", "Accepted", "Rejected", "Min Lat (us)", "Max Lat (us)", "Avg Lat (us)", "P99 Lat (us)", "Last Action"]:
                fh.write(f"{key}: {self.status_vars[key].get()}\n")
            fh.write("\n=== EXCHANGE LOG ===\n")
            fh.write(self.exo_text.get("1.0", tk.END))
            fh.write("\n=== SHAURYA LOG ===\n")
            fh.write(self.shaurya_text.get("1.0", tk.END))
        self.append_text(self.shaurya_text, f"[SYSTEM] Snapshot saved to {output_name}\n")

    def start_all(self):
        # 1. Start Injector Server first so it listens
        self.start_injector()
        # 2. Wait slightly to ensure port is open, then start engine
        self.root.after(500, self.start_shaurya)

    def stop_process(self, process):
        if not process:
            return
        if process.poll() is None:
            process.terminate()
            try:
                process.wait(timeout=2)
            except subprocess.TimeoutExpired:
                process.kill()

    def restart_shaurya(self):
        if self.shaurya_process:
            self.stop_process(self.shaurya_process)
            self.shaurya_process = None
            self.append_text(self.shaurya_text, "\n[SYSTEM] Engine restart requested.\n")
        self.start_shaurya()

    def start_injector(self):
        if not self.exo_process:
            symbol = self.symbol_entry.get().strip().upper()
            if not symbol:
                symbol = "MSFT"
            
            self.append_text(self.exo_text, f"[SYSTEM] Launching Real Stock Injector for {symbol} (20 Seconds)...\n")
            
            # Using -u flag to prevent log buffering
            cmd = [sys.executable, "-u", "real_stock_injector.py", "--symbol", symbol, "--iterations", "20"]
            self.exo_process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, creationflags=0x08000000)
            threading.Thread(target=self.read_output, args=(self.exo_process, self.exo_text), daemon=True).start()
            self.exo_start_time = time.time()

    def start_shaurya(self):
        if not self.shaurya_process:
            self.append_text(self.shaurya_text, "[SYSTEM] Booting LLVM Fused Shaurya Engine...\n")
            self.shaurya_process = subprocess.Popen(["bin\\Shaurya.exe"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, creationflags=0x08000000)
            threading.Thread(target=self.read_output, args=(self.shaurya_process, self.shaurya_text), daemon=True).start()
            self.shaurya_start_time = time.time()

    def stop_all(self):
        if self.exo_process:
            self.stop_process(self.exo_process)
            self.exo_process = None
            self.exo_start_time = None
            self.append_text(self.exo_text, "\n[SYSTEM] Injector Terminated.\n")
            
        if self.shaurya_process:
            self.stop_process(self.shaurya_process)
            self.shaurya_process = None
            self.shaurya_start_time = None
            self.append_text(self.shaurya_text, "\n[SYSTEM] Shaurya Engine Terminated.\n")

        self.status_vars["Exchange"].set("OFFLINE")
        self.status_vars["Engine"].set("OFFLINE")
        self.status_vars["Uptime"].set("00:00:00")

if __name__ == "__main__":
    if not os.path.exists("real_stock_injector.py") or not os.path.exists("bin\\Shaurya.exe"):
        print("CRITICAL ERROR: Could not find 'real_stock_injector.py' or 'bin\\Shaurya.exe'.")
        print("Please ensure you run this from the project root!")
    else:
        root = tk.Tk()
        app = ShauryaGUI(root)
        root.protocol("WM_DELETE_WINDOW", lambda: (app.stop_all(), root.destroy()))
        root.mainloop()