#!/bin/bash
#Absoluter Ordnerpfad:                                               #
#Hyprland-Module/Pylovara-FileManager/KernModul/aliasloader.sh       #
#Pylovara Since 2025© https://github.com/Pylovara                    #
#https://github.com/Pylovara/Hyprland-Module/Pylovara-FileManager    #  

# Lädt automatisch alle ls*.sh-Skripte als Aliase, 
# z.B. ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/lsupdate.sh → update

for f in "$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager"/ls*.sh; do
  [ -e "$f" ] || continue
  name="$(basename "${f}" .sh | sed 's/^ls//')"
  alias "${name}"="${f}"
done
