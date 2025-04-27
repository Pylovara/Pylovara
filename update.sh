#!/bin/bash

# Verzeichnisse definieren
TARGET="$HOME/.config/hypr/Hyprland-Module/Polyvara-FileManager"
SOURCE_DIR="$(dirname "$(realpath "$0")")/Polyvara-FileManager"

# Prüfen, ob das Zielverzeichnis existiert
if [ ! -d "$TARGET" ]; then
  echo "⚠ Fehler: Zielverzeichnis existiert nicht. Bitte führe setup.sh zuerst aus."
  exit 1
fi

# Warnung: Alle Dateien werden überschrieben
echo "⚠ WARNUNG: Alle Dateien im Zielverzeichnis werden überschrieben!"

# Dateien hart kopieren und alte Dateien ersetzen
echo "🔄 Überschreibe Dateien im Polyvara-FileManager..."

# Lösche alle bestehenden Dateien im Zielordner
rm -rf "$TARGET/*"

# Kopiere alle Dateien aus dem Quellordner ins Zielverzeichnis
cp -r "$SOURCE_DIR/." "$TARGET/"

# Setze Ausführungsberechtigungen für alle Skripte
find "$TARGET" -name "*.sh" -exec chmod +x {} \;

echo "✅ Polyvara-FileManager wurde erfolgreich aktualisiert und überschrieben!"
