# =============================================================================
# @mcs-nr: SYNAPSE | ÜBERGANGSREGELN | INFO-ID = SYNAPSE-REGELN-00.3
# =============================================================================
# NAME         = SYNAPSE – Übergangsregeln mit starkem MCS-Seeding
# VERSION      = 0.0.3
# AUTOR        = Thomas Zimmermann Stufe 10
# STAND         = 2026-01-22
# STATUS       = FREIGESCHALTET FÜR STARKES KEYWORD-SEEDING
# =============================================================================

import random

class Synapse:
    def __init__(self, mutation_rate):
        self.mutation_rate = mutation_rate
        # Echte + deine erweiterte Liste (aus SSoT 00.63 + eigene Identifikatoren)
        self.preferred_keys = [
            "B1", "B8", "B16", "B32", "B64", "B-INF", "p-KEY", "INIT-V",
            "PROTEINE", "PROTONEN", "BOOT-LOGIK", "MIT-SYNC", "BOXIS", "WAHRHEITEN",
            "ARGUMENTE", "SENTIATOREN", "FEEDS", "MCS-CMD-REGISTER", "IDENTIFIKATION",
            "DATENTYPEN", "kernel lex", "DATEITYPEN", "/Pylovara/Handbuch/KernelNotes/",
            "Thomas Zimmermann", "ID-DNA-THOMAS-ZIMMERMANN-ÞÞZRB68"
        ]

    def apply(self, state):
        if not state.values:
            # Geburt – 85% Chance auf echtes Keyword (starkes Seeding)
            if random.random() < 0.85:
                key = random.choice(self.preferred_keys)
                state.values[key] = random.uniform(2.0, 7.0)  # plausibler Bereich
            else:
                state.values["core_pulse"] = random.uniform(3.0, 7.0)
            return

        key = random.choice(list(state.values.keys()))
        delta = random.uniform(-0.5, 0.5)           # noch sanfter (vorher -0.6 bis 0.6)
        if random.random() < self.mutation_rate:
            delta *= random.uniform(1.05, 1.35)     # sehr milde Mutation
            # 20% Chance, ein neues echtes Keyword hinzuzufügen (max 18 Keys)
            if random.random() < 0.20 and len(state.values) < 18:
                new_key = random.choice(self.preferred_keys)
                if new_key not in state.values:
                    state.values[new_key] = random.uniform(1.0, 5.0)
        state.update(key, delta)
