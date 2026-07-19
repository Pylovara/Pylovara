# =============================================================================
# @mcs-nr: SYNAPSE | ÜBERGANGSREGELN | INFO-ID = SYNAPSE-REGELN-00.3
# =============================================================================
# NAME         = SYNAPSE – Übergangsregeln mit starkem MCS-Seeding
# VERSION      = 0.0.5
# AUTOR        = Thomas Zimmermann Stufe 10
# STAND         = 2026-03-23
# STATUS       = FREIGESCHALTET FÜR STARKES KEYWORD-SEEDING
# =============================================================================

import random
import BIOS.SCHALTERKASTEN.SCHALTERKASTEN as config

class Synapse:
    def __init__(self, mutation_rate):
        self.mutation_rate = mutation_rate

        self.preferred_keys = [
            "B1", "B8", "B16", "B32", "B64", "B-INF", "Þ", "INIT-V",
            "PROTEIN", "PROTON", "BOOT-LOGIK", "MIT-SYNC", "BOXIS", "REX",
            "ARGUMENT", "SENTIATOREN", "FEEDS", "MCS-CMD", "IDENTIFIKATION",
            "DATENTYPEN", "kernel lex", "DATEITYPEN", "/Pylovara/Handbuch/KernelNotes/",
            "Thomas Zimmermann", "ID-DNA", "THOMAS-ZIMMERMANN", "ÞÞZRB68","[", "}",
            "]", "¶", "{", "|", "¤", "↓", "↑", "!", "°", "Ø", "¥", "Ŧ", "$", "§", "MASK", 
            "TRANK", "POIK", "POOK", "REXK", "SENTK", "ARGK", "RETK", "MCCK", "DIK", "DAK",
            "FEEK", "WARK", "NAVK", "IDENK", "VATK", "HERZK", "KKIK", "MCCK", "ShiVara",
            "/Pylovara/MASTER-CONTROL-SYSTEM/LAYOUTS/MCS-KEYWORDS/priorities.info-notes"
        ]

        # Integration der registrierten Lernprogramme
        if hasattr(config, "LERNPROGRAMM_PFADE"):
            self._parse_lernprogramme(config.LERNPROGRAMM_PFADE)

    def _parse_lernprogramme(self, pfade):
        import os
        for pfad in pfade:
            if os.path.exists(pfad):
                try:
                    with open(pfad, 'r', encoding='utf-8') as f:
                        for line in f:
                            line = line.strip()
                            if not line or line.startswith('#'):
                                continue
                            if "§" in line:
                                parts = line.split("§")
                                if len(parts) > 1:
                                    subparts = parts[1].strip().split()
                                    if subparts:
                                        symbol = subparts[0]
                                        if symbol and symbol not in self.preferred_keys:
                                            self.preferred_keys.append(symbol)
                except Exception as e:
                    print(f"[WARN] Fehler beim Zugriff auf {pfad}: {e}")

    def apply(self, state):
        if not state.values:
            # Geburt – 85% Chance auf echtes Keyword (starkes Seeding)
            if random.random() < 0.85:
                key = random.choice(self.preferred_keys)
                state.values[key] = random.uniform(2.0, 8.0)  # plausibler Bereich
            else:
                state.values["core_pulse"] = random.uniform(3.0, 9.0)
            return

        key = random.choice(list(state.values.keys()))
        delta = random.uniform(-0.9, 0.9)           # noch sanfter (vorher -0.6 bis 0.6)
        if random.random() < self.mutation_rate:
            delta *= random.uniform(6.04, 16.33)     # sehr milde Mutation
            # 20% Chance, ein neues echtes Keyword hinzuzufügen (max 300 Keys)
            if random.random() < 0.40 and len(state.values) < 300:
                new_key = random.choice(self.preferred_keys)
                if new_key not in state.values:
                    state.values[new_key] = random.uniform(1.3, 5.1)
        state.update(key, delta)
