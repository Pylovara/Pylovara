#!/bin/bash

echo "🚀 Starte Installation von Hyprland-Module..."

# Zielverzeichnis
TARGET="$HOME/.config/hypr"

# Prüfen, ob das Zielverzeichnis existiert
if [ ! -d "$TARGET" ]; then
    echo "⚠ Fehler: Zielverzeichnis $TARGET existiert nicht. Bitte stelle sicher, dass Hyprland korrekt eingerichtet ist."
    exit 1
fi

# Ordner kopieren
echo "📂 Kopiere kompletten Hyprland-Module Ordner nach $TARGET/Hyprland-Module..."
cp -r "$(pwd)" "$TARGET/Hyprland-Module"

echo "✨ Installation abgeschlossen! Das Modul befindet sich jetzt unter ~/.config/hypr/Hyprland-Module."
