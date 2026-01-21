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
