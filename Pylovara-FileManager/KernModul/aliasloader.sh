#!/bin/bash
# Absoluter Pfad:
# Hyprland-Module/Pylovara-FileManager/KernModul/aliasloader.sh
# Lädt alle ls*.sh Skripte als Aliase.

for f in "$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/Search"/ls*.sh; do
  [ -e "$f" ] || continue
  name="$(basename "${f}" .sh | sed 's/^ls//')"
  if [[ -x "$f" ]]; then
    alias "${name}"="${f}"
  else
    echo "[ WARNUNG ] Datei nicht ausführbar: $f" >&2
  fi
done
