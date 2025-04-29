#!/bin/bash
# Absoluter Pfad:
# Hyprland-Module/Pylovara-FileManager/KernModul/aliasreset.sh
# Entfernt alle Aliase, die mit lsp beginnen – gedacht für Pylovara-Modul-Aliase.

echo "------------------------------"
echo " Entferne lsp*-Aliase (Reset)"
echo "------------------------------"

for a in $(compgen -a); do
  if [[ $a == lsp* ]]; then
    unalias "$a" && echo "[-] entfernt: $a"
  fi
done
