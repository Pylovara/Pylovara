#!/bin/bash

# Polyvara Update-Skript

POLYVARA_DIR="$HOME/.config/hypr/Hyprland-Module/Polyvara"

if [ -d "$POLYVARA_DIR" ]; then
    echo "Polyvara-Ordner gefunden. Aktualisiere..."
    cd "$POLYVARA_DIR" || exit 1
    git pull
    echo "✅ Polyvara ist jetzt auf dem neuesten Stand."
else
    echo "❌ Polyvara wurde nicht gefunden unter $POLYVARA_DIR"
    echo "Bitte führe setup.sh erneut aus oder prüfe die Installation."
fi
