# ==============================
# EVALUATOR – Bewertung
# ==============================

class Evaluator:
    def score(self, state):
        """
        Primitive Bewertung:
        - Stabilität
        - Nicht-Explosion
        - Nicht-Leere
        """
        if not state.values:
            return -1.0

        total = sum(abs(v) for v in state.values.values())

        # Bevorzuge mittlere Ordnung
        return -abs(total - 10.0)
