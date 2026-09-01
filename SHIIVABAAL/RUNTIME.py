#!/usr/bin/env python3
import os
import sys
import time
import subprocess
import signal

PID_FILE = "training.pid"
LOG_FILE = "training.log"
PYTHON_CMD = "python3"
SCRIPT_TO_RUN = "MAIN.py"
INTERVAL = 1

def start():
    if os.path.exists(PID_FILE):
        print(f"Training läuft bereits (PID in {PID_FILE}).")
        return

    print(f"Starte Training Runtime (Intervall: {INTERVAL}s)...")
    
    # Simple background loop
    try:
        # We use a double fork or just a simple detached process logic
        # For this environment, we'll keep it simple: run a loop that spawns the script
        pid = os.fork()
        if pid > 0:
            # Parent process: write PID and exit
            with open(PID_FILE, "w") as f:
                f.write(str(pid))
            print(f"Training im Hintergrund gestartet. PID: {pid}")
            return
    except OSError as e:
        print(f"Fork fehlgeschlagen: {e}")
        return

    # Child process: The actual loop
    # Redirect output to log file
    with open(LOG_FILE, "a") as log:
        log.write(f"\n--- TRAINING START: {time.ctime()} ---\n")
        while True:
            try:
                log.write(f"[{time.ctime()}] Triggere {SCRIPT_TO_RUN}...\n")
                log.flush()
                # Run the main script
                subprocess.run([PYTHON_CMD, SCRIPT_TO_RUN], stdout=log, stderr=log)
                time.sleep(INTERVAL)
            except Exception as e:
                log.write(f"Fehler im Loop: {e}\n")
                log.flush()
                time.sleep(INTERVAL)

def stop():
    if not os.path.exists(PID_FILE):
        print("Kein aktives Training gefunden.")
        return

    with open(PID_FILE, "r") as f:
        pid = int(f.read().strip())

    print(f"Stoppe Training (PID: {pid})...")
    try:
        os.kill(pid, signal.SIGTERM)
        os.remove(PID_FILE)
        print("Training erfolgreich beendet.")
    except ProcessLookupError:
        print("Prozess existiert nicht mehr. PID-File entfernt.")
        os.remove(PID_FILE)
    except Exception as e:
        print(f"Fehler beim Stoppen: {e}")

def status():
    if os.path.exists(PID_FILE):
        with open(PID_FILE, "r") as f:
            pid = f.read().strip()
        print(f"TRAINING LÄUFT (PID: {pid})")
        # Show last 5 lines of log
        if os.path.exists(LOG_FILE):
            print("\nLetzte Log-Einträge:")
            os.system(f"tail -n 5 {LOG_FILE}")
    else:
        print("TRAINING GESTOPPT")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 RUNTIME.py [start|stop|status]")
        sys.exit(1)

    cmd = sys.argv[1].lower()
    if cmd == "start":
        start()
    elif cmd == "stop":
        stop()
    elif cmd == "status":
        status()
    else:
        print(f"Unbekannter Befehl: {cmd}")
        print("Usage: python3 RUNTIME.py [start|stop|status]")
