# ==============================
# MAIN – Startpunkt
# ==============================

from BIOS.LOOP.loop import CognitiveLoop

loop = CognitiveLoop()

for i in range(1000):
    score = loop.step()
    print(f"[{i}] score={score}")
