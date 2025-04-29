#!/bin/bash
# Absoluter Pfad:
# Hyprland-Module/Pylovara-FileManager/KernModul/aliasloader.sh
# Lädt alle lsp*.sh Skripte aus Unterordnern als Aliase.

SEARCH_DIR="$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/Search"

find "$SEARCH_DIR" -type f -name 'lsp*.sh' | while read -r f; do
  name="$(basename "$f" .sh | sed 's/^lsp//;s/.sh$//')"
  if [[ -x "$f" ]]; then
    alias "$name"="$f"
  else
    echo "[ WARNUNG ] Datei nicht ausführbar: $f" >&2
  fi
done
