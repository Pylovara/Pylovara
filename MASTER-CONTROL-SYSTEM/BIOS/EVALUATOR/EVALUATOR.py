# =============================================================================
# @kernel-nr: EVALUATOR | BEWERTUNG | INFO-ID = LAYOUT-SCORER
# =============================================================================
# NAME     = Evaluator – Layout-Bewertung
# FUNKTION = Stabilität + Ordnung + Bonus für MCS-ähnliche Struktur
# STATUS   = FREIGESCHALTET FÜR TEST
# =============================================================================

class Evaluator:
    def score(self, state):
        """
        Primitive Layout-Bewertung im MCS-Stil:
        - Leer = sehr schlecht
        - Zu viele / zu wenige Keys = Strafe
        - Abstand zu idealer Energie (10) = Strafe
        - Bonus für "core_pulse" im guten Bereich
        - Bonus für 4–10 Keys (Ordnung)
        """
        if not state.values:
            return -8.0                     # Härtere Strafe für leer

        total_abs = sum(abs(v) for v in state.values.values())
        num_keys = len(state.values)

        # Strafe für Chaos / Leere
        size_penalty = max(0, num_keys - 12) * 1.5 + max(0, 4 - num_keys) * 2.0

        # Energie-Distanz (Ziel = 10)
        energy_distance = abs(total_abs - 10.0) * 1.2

        # Bonus – MCS-Layout-ähnlich
        bonus = 0.0
        if "core_pulse" in state.values:
            if 4.0 < state.values["core_pulse"] < 6.0:
                bonus += 2.5                    # Kern stabil → gut!
        if 4 <= num_keys <= 10:
            bonus += 1.0                        # Gute Anzahl Keys

        # Gesamt: negativ = schlecht, näher an 0 = besser
        return - (energy_distance + size_penalty) + bonus
