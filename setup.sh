#!/bin/bash

# Funktion zum Ausführen von Befehlen mit Passwortabfrage (wenn nötig)
sudo_cmd() {
  if [[ $EUID -ne 0 ]]; then
    echo "🔐 Benötige Root-Rechte, um '$1' auszuführen..."
    sudo "$@"
  else
    "$@"
  fi
}

echo "🚀 Starte Installation von Polyvara-FileManager..."

# Zielverzeichnis
TARGET="$HOME/.config/hypr"
MODULE_DIR="Hyprland-Module/Polyvara-FileManager"
INSTALL_PATH="$TARGET/$MODULE_DIR"

# Prüfen, ob das Zielverzeichnis existiert
if [ ! -d "$TARGET" ]; then
  echo "⚠ Fehler: Zielverzeichnis $TARGET existiert nicht. Bitte stelle sicher, dass Hyprland korrekt eingerichtet ist."
  exit 1
fi

# Prüfen, ob der Quellordner existiert
if [ ! -d "$(pwd)/Polyvara-FileManager" ]; then
  echo "⚠ Fehler: Quellordner Polyvara-FileManager nicht gefunden. Bitte führe das Skript aus dem Stammverzeichnis des Repositories aus."
  exit 1
fi

# Ordner kopieren
echo "📂 Kopiere den Polyvara-FileManager Ordner nach $INSTALL_PATH..."
cp -r "$(pwd)/Polyvara-FileManager" "$INSTALL_PATH"

# .sh-Skripte ausführbar machen
echo "🔨 Setze Ausführungsberechtigungen für .sh-Skripte..."
find "$INSTALL_PATH" -name "*.sh" -exec chmod +x {} \;

# .zshrc Setup
echo "⚙️  Konfiguriere .zshrc..."

# Prüfen ob ~/.zshrc existiert
if [ ! -f "$HOME/.zshrc" ]; then
  echo "⚠ Fehler: Keine .zshrc gefunden. Dieses Setup ist nur für Systeme mit ZSH geeignet."
  exit 1
fi

# Prüfen ob Polyvara-Loader schon eingebunden ist
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
  echo "✅ Polyvara-Einträge wurden in ~/.zshrc hinzugefügt."
else
  echo "ℹ️ Polyvara-Einträge sind bereits in ~/.zshrc vorhanden. Überspringe."
fi

# tree installieren
echo "🌳 Installiere 'tree'..."
sudo_cmd pacman -S --noconfirm tree
if [ $? -eq 0 ]; then
  echo "✅ 'tree' wurde erfolgreich installiert."
else
  echo "❌ Fehler bei der Installation von 'tree'. Bitte installiere es manuell: sudo pacman -S tree"
fi

echo "✨ Installation von Polyvara-FileManager abgeschlossen!"
echo "👉  Bitte starte dein Terminal neu oder führe 'source ~/.zshrc' aus, um die Änderungen zu aktivieren."
