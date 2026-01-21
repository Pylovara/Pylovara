# =============================================================================
# @kernel-nr: MAIN | STARTPUNKT | INFO-ID = MASTER-START-00.1
# =============================================================================
# NAME     = MAIN – Einstieg in den kognitiven Loop
# VERSION  = 0.0.1
# STATUS   = FREIGESCHALTET
# =============================================================================

from BIOS.LOOP.LOOP import CognitiveLoop

loop = CognitiveLoop()

for i in range(1000):
    score = loop.step()
    print(f"[{i}] score={score}")
