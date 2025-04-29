#!/bin/bash

# Funktion zum Ausführen mit Passwortabfrage (wenn nötig)
sudo_cmd() {
  if [[ $EUID -ne 0 ]]; then
    echo "🔐 Benötige Root-Rechte, um '$*' auszuführen..."
    sudo "$@"
  else
    "$@"
  fi
}

echo "Starte Installation von Polyvara-FileManager Demo ..."

# Zielverzeichnis
TARGET="$HOME/.config/hypr"
MODULE_DIR="Hyprland-Module/Polyvara-FileManager"
INSTALL_PATH="$TARGET/$MODULE_DIR"

# Quellordner (absolute Pfadangabe)
SOURCE_DIR="$(dirname "$(realpath "$0")")/Polyvara-FileManager"

# Vorprüfungen
if [ ! -d "$TARGET" ]; then
  echo "⚠️ Fehler: Zielverzeichnis $TARGET existiert nicht. Bitte stelle sicher, dass Hyprland korrekt installiert ist."
  exit 1
fi

if [ ! -d "$SOURCE_DIR" ]; then
  echo "⚠️ Fehler: Quellordner Polyvara-FileManager nicht gefunden. Bitte führe dieses Script aus dem Root des Repos aus."
  exit 1
fi

# Installation
echo "📂 Kopiere Polyvara-FileManager nach $INSTALL_PATH..."
mkdir -p "$INSTALL_PATH"
cp -r "$SOURCE_DIR/"* "$INSTALL_PATH/"
chmod -R +x "$INSTALL_PATH/"*.sh

# .zshrc Anpassen
echo "⚙️  Bearbeite .zshrc..."

if [ ! -f "$HOME/.zshrc" ]; then
  echo "⚠️ Keine .zshrc gefunden. Dieses Setup ist nur für ZSH gedacht."
  exit 1
fi

if ! grep -q "Polyvara-FileManager/aliasloader.sh" "$HOME/.zshrc"; then
  cat << 'EOF' >> "$HOME/.zshrc"

# Polyvara-FileManager Setup
source ~/.config/hypr/Hyprland-Module/Polyvara-FileManager/aliasloader.sh

# Set-up icons for files/directories in terminal using lsd
alias ls='lsd'
alias tree='tree -a -L 2'

# Polyvara-FileManager Farben
export LS_COLORS="\
di=1;37:\
fi=0;37:\
ln=0;97:\
ex=1;97:\
*.sh=1;97:\
*.py=1;97:\
*.mp4=0;37:\
*.mkv=0;37:\
*.png=0;37:\
*.jpg=0;37:\
*.jpeg=0;37:\
*.zip=0;37:\
*.tar=0;37:\
*.gz=0;37:\
*.iso=0;37:"

EOF
  echo "✅ Polyvara-Einträge in .zshrc hinzugefügt."
else
  echo "ℹ️ Polyvara-Einträge bereits vorhanden. Überspringe."
fi

# tree installieren
echo "🌳 Installiere 'tree' falls nicht vorhanden..."
if ! command -v tree &> /dev/null; then
  sudo_cmd pacman -S --noconfirm tree
  if [ $? -eq 0 ]; then
    echo "✅ 'tree' erfolgreich installiert."
  else
    echo "❌ Fehler bei der Installation von 'tree'. Bitte manuell ausführen: sudo pacman -S tree"
  fi
else
  echo "✅ 'tree' ist bereits installiert."
fi

echo "Installation abgeschlossen!"
echo "👉 Bitte Terminal neu starten oder 'source ~/.zshrc' ausführen."
