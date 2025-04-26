#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
#https://github.com/Pylovara/Hyprland-Module/Polyvara-FileManager

# Lädt automatisch alle ls*.sh-Skripte als Aliase, z.B. ~/.config/hypr/Polyvara-FileManager/lsupdate.sh → update

for f in ~/.config/hypr/function/ls*.sh; do
  name=$(basename "$f" .sh | sed 's/^ls//')
  alias "$name"="$f"
done
