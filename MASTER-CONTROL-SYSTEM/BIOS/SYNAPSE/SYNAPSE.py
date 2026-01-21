# ==============================
# SYNAPSE – Übergangsregeln
# ==============================

import random

class Synapse:
    def __init__(self, mutation_rate):
        self.mutation_rate = mutation_rate

    def apply(self, state):
        """
        Primitive Regel:
        - wähle einen Zustand
        - verändere ihn leicht
        """
        if not state.values:
            return

        key = random.choice(list(state.values.keys()))
        delta = random.uniform(-1.0, 1.0)

        # Mutation
        if random.random() < self.mutation_rate:
            delta *= random.uniform(1.5, 3.0)

        state.update(key, delta)
