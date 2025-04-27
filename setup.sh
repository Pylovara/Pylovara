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

#### hier die .zshrc setup 

# Prüfen ob ~/.zshrc existiert
if [ ! -f "$HOME/.zshrc" ]; then
    echo "⚠ Fehler: Keine .zshrc gefunden. Dieses Setup ist nur für Systeme mit Hyprland und ZSH geeignet."
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
