# ==============================
# K.K.I.S NULLPUNKT KONFIGURATION
# ==============================

# IDENTITÄT
KOGNITIVE_KUENSTLICHE_INTELLIGENZ_NAME = "SHIVABAAL"
KKIS_VERSION = "0.0.1"


# Pfade
SOURCE_INPUT_DIR  = "source/input"
SOURCE_OUTPUT_DIR = "source/output"
ACTIVE_SOURCE_LIST = "source/active.list"

# Lernparameter (primitive!)
STATE_DECAY = 0.01        # Vergessen
STATE_GAIN  = 0.05        # Verstärkung
MUTATION_RATE = 0.02      # Variation

# Sicherheitsgrenzen
MAX_STATE_SIZE = 10_000
ALLOW_SELF_MODIFICATION = False

# Logging
VERBOSE = True

# ZUSTANDSLOGIK
class Zustand:
    def __init__(self):
        self.values = {
            "core_stability": 5.0,     # Startwert nahe dem Optimum (10)
            "energy_reserve": 3.0,
            "mutation_pressure": 1.0
        }
        self.alter = 0

    def update(self, key, delta):   # statt aktualisieren
        self.values[key] = self.values.get(key, 0.0) + delta

    def abschwaechen(self, rate):
        for k in self.values:
            self.values[k] *= (1.0 - rate)

    def abbild(self):
        return dict(self.values)


