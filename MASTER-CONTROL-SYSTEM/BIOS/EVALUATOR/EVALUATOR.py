# =============================================================================
# @mcs-nr: EVALUATOR | BEWERTUNG | INFO-ID = LAYOUT-SCORER-00.5
# =============================================================================
# NAME         = Evaluator – MCS-00.63 Layout-Bewertung
# VERSION      = 0.0.5
# AUTOR        = Thomas Zimmermann Stufe 10
# STAND         = 2026-01-21
# STATUS       = FREIGESCHALTET FÜR ECHTE SSoT 00.63 KEYWORDS
# BESCHREIBUNG = Belohnt nur echte MCS-Typen aus SSoT 00.63 + Symmetrie + stabile Kerne
# QUELLE       = PYLOVARA-SYSTEM-SSoT-00-63.pdf (öffentliche Teile)
# =============================================================================

class Evaluator:
    def score(self, state):
        """
        Erweiterte Layout-Bewertung – nur mit echten SSoT 00.63 Typen:
        - Leer = sehr schlecht
        - Zu viele / zu wenige Keys = Strafe
        - Energie-Distanz (Ziel = 12) = Strafe
        - Bonus für echte MCS-Typen (B1, B8, B16, B32, B64, B-INF, p-KEY, INIT-V, ...)
        - Bonus für core_pulse nahe 5 (wie INIT-V stabil)
        - Bonus für Symmetrie (pos/neg Balance)
        """
        if not state.values:
            return -10.0                    # Härtere Strafe für komplett leer

        total_abs = sum(abs(v) for v in state.values.values())
        num_keys = len(state.values)

        # =========================================================================
        # BASIS-STRAFEN – Chaos & Abweichung
        # =========================================================================
        size_penalty = max(0, num_keys - 15) * 1.2 + max(0, 5 - num_keys) * 2.0
        energy_target = 12.0                    # leicht höher wegen mehr möglicher Keys
        energy_distance = abs(total_abs - energy_target) * 1.0

        # =========================================================================
        # BONUS – ECHTE SSoT 00.63 MCS-TYPEN
        # =========================================================================
        bonus = 0.0

        # Offizielle MCS-Typen aus SSoT 00.63 (keine Erfindungen!)
        sso63_keywords = [
            "B1", "B8", "B16", "B32", "B64", "B-INF", "B-pA",
            "p-KEY", "INIT-V",
            "PROTEINE", "PROTONEN", "BOOT-LOGIK", "MIT-SYNC", "DNA-ID-GENERATOR"
        ]

        for kw in sso63_keywords:
            if kw in state.values:
                val = state.values[kw]
                # Bonus nur, wenn Wert plausibel (nicht extrem)
                if -10 < val < 20:
                    bonus += 2.5                    # starke Belohnung für echte Typen

        # Kern-Stabilität (wie INIT-V / START-PROTEIN)
        if "core_pulse" in state.values:
            if 4.0 < state.values["core_pulse"] < 6.0:
                bonus += 3.5                        # höherer Bonus für Kern

        # Key-Anzahl Bonus (5–12 = gute Ordnung für MCS-Struktur)
        if 5 <= num_keys <= 12:
            bonus += 1.8

        # Symmetrie-Bonus (Balance pos/neg Werte)
        pos_count = sum(1 for v in state.values.values() if v > 0)
        neg_count = sum(1 for v in state.values.values() if v < 0)
        symmetry_diff = abs(pos_count - neg_count)
        if symmetry_diff <= 2:
            bonus += 2.0

        # =========================================================================
        # GESAMT-SCORE – näher an 0 = besser
        # =========================================================================
        score = - (energy_distance + size_penalty) + bonus
        return score
