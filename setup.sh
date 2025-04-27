#!/bin/bash

echo "🚀 Starte Installation des Hyprland-Module Pakets..."

# Zielverzeichnis definieren
TARGET="$HOME/.config"

# Prüfen, ob wir im richtigen Verzeichnis sind
if [ ! -d "./CleanUPModule" ] || [ ! -d "./FixModule" ] || [ ! -d "./Polyvara-FileManager" ]; then
    echo "⚠ Fehler: Bitte setup.sh im Hyprland-Module-Ordner ausführen!"
    exit 1
fi

# Ordnerliste
MODULES=("CleanUPModule" "FixModule" "Polyvara-FileManager")

# Module kopieren
for module in "${MODULES[@]}"; do
    echo "📂 Kopiere $module nach $TARGET/$module..."
    mkdir -p "$TARGET/$module"
    cp -r "$module/"* "$TARGET/$module/"
done

echo "✨ Installation abgeschlossen! Die Module befinden sich jetzt in deinem ~/.config Verzeichnis."
