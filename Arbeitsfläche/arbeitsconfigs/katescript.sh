#!/bin/bash
# ============================================================
#  PYLOVARA-KATE-WRAPPER.SH
# ============================================================

# Pfad :
CONFIG_DIR="$HOME/Pylovara/Configs"
CONFIG_FILE="$CONFIG_DIR/pylovara-kate.cfg"

# Sicherstellen :
mkdir -p "$CONFIG_DIR"

# Kate starten mit der Config
# --new-instance = Unabhängiges Fenster
# --config = Lade DIESE Config (nicht die globale)
kate --new-instance --config "$CONFIG_FILE" "$@"
