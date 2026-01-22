# =============================================================================
# @kernel-nr: EVALUATOR | BEWERTUNG | INFO-ID = LAYOUT-SCORER-00.6
# =============================================================================
# NAME         = Evaluator – MCS-00.63 Layout-Bewertung mit Datei-Lesen
# VERSION      = 0.0.6
# AUTOR        = Thomas Zimmermann Stufe 10
# STAND         = 2026-01-22
# STATUS       = FREIGESCHALTET FÜR DATEI-LESEN
# BESCHREIBUNG = Liest Keywords aus LAYOUTS/MCS-KEYWORDS/keywords.info-notes
# =============================================================================

import os

class Evaluator:
    def __init__(self):
        # =========================================================================
        # INITIALISIERUNG – Keywords aus Datei laden
        # =========================================================================
        self.keyword_file = "../LAYOUTS/MCS-KEYWORDS/keywords.info-notes"  # Relativer Pfad zum Ordner
        self.sso63_keywords = self._lade_keywords()

    def _lade_keywords(self):
        # =========================================================================
        # LADEN – Keywords aus Datei sourcen (wie SSoT-Liste)
        # =========================================================================
        keywords = []
        if os.path.exists(self.keyword_file):
            with open(self.keyword_file, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line and not line.startswith('#'):  # Ignoriere Kommentare + Leere
                        keywords.append(line)
            print(f"[BOOT] {len(keywords)} Keywords aus {self.keyword_file} geladen")
        else:
            print(f"[WARN] Keyword-Datei {self.keyword_file} nicht gefunden → Standard-Liste verwenden")
            # Fallback auf harte Liste aus SSoT 00.63
            keywords = [
                "B1", "B8", "B16", "B32", "B64", "B-INF", "p-KEY", "INIT-V",
                "PROTEINE", "PROTONEN", "BOOT-LOGIK", "MIT-SYNC", "DNA-ID-GENERATOR", "Thomas Zimmermann", "ID-DNA-THOMAS-ZIMMERMANN-ÞÞZRB68"
            ]
        return keywords

    def score(self, state):
        """
        Erweiterte Layout-Bewertung – mit gelesenen Keywords:
        - Leer = sehr schlecht
        - Zu viele / zu wenige Keys = Strafe
        - Energie-Distanz (Ziel = 12) = Strafe
        - Bonus für gelesene MCS-Typen
        - Bonus für core_pulse nahe 5
        - Bonus für Symmetrie
        """
        if not state.values:
            return -10.0

        total_abs = sum(abs(v) for v in state.values.values())
        num_keys = len(state.values)

        size_penalty = max(0, num_keys - 15) * 1.2 + max(0, 5 - num_keys) * 2.0
        energy_target = 12.0
        energy_distance = abs(total_abs - energy_target) * 1.0

        bonus = 0.0

        # Bonus für gelesene Keywords
        for kw in self.sso63_keywords:
            if kw in state.values:
                val = state.values[kw]
                if -10 < val < 20:
                    bonus += 2.5

        if "core_pulse" in state.values:
            if 4.0 < state.values["core_pulse"] < 6.0:
                bonus += 3.5

        if 5 <= num_keys <= 12:
            bonus += 1.8

        pos_count = sum(1 for v in state.values.values() if v > 0)
        neg_count = sum(1 for v in state.values.values() if v < 0)
        symmetry_diff = abs(pos_count - neg_count)
        if symmetry_diff <= 2:
            bonus += 2.0

        score = - (energy_distance + size_penalty) + bonus
        return score
