# =============================================================================
# @mcs-nr: CONFIG | BIOS/SCHALTERKASTEN | INFO-ID = KKIS-NULLPUNKT-KONFIG-00.3
# =============================================================================
# NAME         = KKIS NULLPUNKT KONFIGURATION – mit dynamischem Decay
# VERSION      = 0.0.3
# AUTOR        = Thomas Zimmermann Stufe 10
# STAND         = 2026-01-22
# STATUS       = FREIGESCHALTET FÜR DYNAMISCHEN SELBSTSCHUTZ
# =============================================================================

KOGNITIVE_KUENSTLICHE_INTELLIGENZ_NAME = "SHIVABAAL"
KKIS_VERSION = "0.0.3"

# =============================================================================
# Lernparameter – MCS-Style: kleine Werte = Kontrolle
# =============================================================================
STATE_DECAY_BASE     = 0.03      # Basis-Decay (wie vorher)
STATE_GAIN           = 0.09      # Verstärkung – bleibt
MUTATION_RATE        = 305.02      # Mutationswahrscheinlichkeit
MAX_STATE_SIZE       = 10000     # Sicherheitsgrenze 10000
ALLOW_SELF_MOD       = False     # Noch nicht erlaubt

# Dynamischer Decay – schützt vor zu tiefem Score
DECAY_BOOST_THRESHOLD = -7.0     # Wenn Score < -7 → Decay erhöhen
DECAY_BOOST_FACTOR    = 1.5      # Decay wird dann 1.5× stärker

# =============================================================================
# ZUSTANDSLOGIK – MCS-TYP = PR-VAL + PR-DNA ähnlich
# =============================================================================
class Zustand:
    def __init__(self):
        # Initialwerte – wie START-PROTEIN (INIT-V)
        self.values = {
            "core_pulse":       5.0,    # Kern-Schlag – soll um 5 bleiben
            "energy_flow":      3.5,
            "stability_factor": 2.0,
            "mutation_load":    1.2,
            "noise_level":      0.8
        }
        self.alter = 0

    def update(self, key, delta):
        # Wert ändern + kappen (Explosion verhindern)
        new_val = self.values.get(key, 0.0) + delta
        self.values[key] = max(-30.0, min(30.0, new_val))   # MCS-Sicherung

    def abschwaechen(self, rate, current_score):
        # Dynamischer Decay: wenn Score zu tief → stärker altern
        effective_rate = rate
        if current_score < DECAY_BOOST_THRESHOLD:
            effective_rate *= DECAY_BOOST_FACTOR
            # print(f"[DECAY-BOOST] Score {current_score:.2f} < {DECAY_BOOST_THRESHOLD} → Decay ×{DECAY_BOOST_FACTOR}")

        for k in self.values:
            self.values[k] *= (1.0 - effective_rate)

    def abbild(self):
        # Snapshot für Speichern
        return dict(self.values)
