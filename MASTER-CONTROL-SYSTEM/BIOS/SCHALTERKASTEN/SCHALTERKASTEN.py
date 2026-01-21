# =============================================================================
# @kernel-nr: CONFIG | BIOS/SCHALTERKASTEN | INFO-ID = KKIS-NULLPUNKT-KONFIG
# =============================================================================
# NAME         = KKIS NULLPUNKT KONFIGURATION
# VERSION      = 0.0.2
# AUTOR        = Bandino Der Henker
# STAND         = 2026-01-21
# STATUS       = FREIGESCHALTET FÜR TEST
# =============================================================================

KOGNITIVE_KUENSTLICHE_INTELLIGENZ_NAME = "SHIVABAAL"
KKIS_VERSION = "0.0.2"

# =============================================================================
# Lernparameter – MCS-Style: kleine Werte = Kontrolle
# =============================================================================
STATE_DECAY      = 0.03      # Vergessen pro Step – stärker als vorher (0.01)
STATE_GAIN       = 0.05      # Verstärkung – bleibt erstmal
MUTATION_RATE    = 0.02      # Wahrscheinlichkeit für starke Änderung
MAX_STATE_SIZE   = 10000     # Sicherheitsgrenze Keys-Anzahl
ALLOW_SELF_MOD   = False     # Noch nicht erlaubt – später vielleicht

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
        # Wert ändern + kappen (verhindert Explosion)
        new_val = self.values.get(key, 0.0) + delta
        self.values[key] = max(-30.0, min(30.0, new_val))   # MCS-Sicherung

    def abschwaechen(self, rate):
        # Alle Werte altern lassen (Decay)
        for k in self.values:
            self.values[k] *= (1.0 - rate)

    def abbild(self):
        # Snapshot für Speichern
        return dict(self.values)

