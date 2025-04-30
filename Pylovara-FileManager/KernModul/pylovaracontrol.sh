#!/bin/bash
# Pylovara Toolkit – aliasreset, aliasloader und aliaslist zentral ausführen

# Pfade (wenn nötig anpassen)
modul_dir="$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul"

echo "============================"
echo " Pylovara Alias-Werkzeuge"
echo "============================"

# 1. Aliase entfernen
echo -e "\n[1] Entferne alte Aliase:"
bash "$modul_dir/aliasreset.sh"

# 2. Neue Aliase setzen
echo -e "\n[2] Lade neue Aliase:"
bash "$modul_dir/aliasloader.sh"

# 3. Liste anzeigen
echo -e "\n[3] Aktive Aliase:"
bash "$modul_dir/aliaslist.sh"

echo -e "\n[✓] Pylovara-Werkzeuge abgeschlossen."
