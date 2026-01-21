# =============================================================================
# @kernel-nr: SYNAPSE | ÜBERGANGSREGELN | INFO-ID = SYNAPSE-REGELN
# =============================================================================
# NAME     = SYNAPSE – Übergangsregeln
# FUNKTION = Mutation + Birth-Logik
# STATUS   = FREIGESCHALTET FÜR TEST
# =============================================================================

import random

class Synapse:
    def __init__(self, mutation_rate):
        self.mutation_rate = mutation_rate

    def apply(self, state):
        """
        MCS-Style Regel:
        - Wenn leer → Geburt eines Keys (INIT-V ähnlich)
        - Sonst → leichte Änderung, selten starke Mutation
        """
        if not state.values:
            # Geburt – sanfter Start wie INIT-V
            state.values["core_pulse"] = random.uniform(3.0, 7.0)
            return

        key = random.choice(list(state.values.keys()))
        delta = random.uniform(-0.8, 0.8)           # kleine normale Schritte
        if random.random() < self.mutation_rate:
            delta *= random.uniform(1.1, 1.8)       # milde Mutation – nicht 3x!
        state.update(key, delta)
