#!/bin/bash
# Absoluter Pfad:
# Hyprland-Module/Pylovara-FileManager/KernModul/aliaslist.sh
# Zeigt alle von Pylovara gesetzten Aliase an.

echo "---------------------------"
echo " Pylovara-Aliasübersicht"
echo "---------------------------"
compgen -a | grep -v '^_' | grep -v '^__' | sort
