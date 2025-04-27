#!/bin/bash

# Polyvara Update-Skript für alle Module im Hyprland-Module Ordner

HYPRLAND_MODULE_DIR="$HOME/.config/hypr/Hyprland-Module"

if [ -d "$HYPRLAND_MODULE_DIR" ]; then
    echo "Hyprland-Module Ordner gefunden. Aktualisiere Module..."
    
    # Für jedes Unterverzeichnis im Hyprland-Module Ordner, der als Git-Repository erkannt wird
    for module in "$HYPRLAND_MODULE_DIR"/*/; do
        if [ -d "$module/.git" ]; then
            echo "Aktualisiere: $(basename "$module")..."
            cd "$module" || exit 1
            git pull
            echo "✅ $(basename "$module") ist jetzt auf dem neuesten Stand."
        else
            echo "⚠️ Kein Git-Repository gefunden in: $(basename "$module")"
        fi
    done
else
    echo "❌ Hyprland-Module wurde nicht gefunden unter $HYPRLAND_MODULE_DIR"
    echo "Bitte führe setup.sh erneut aus oder prüfe die Installation."
fi
