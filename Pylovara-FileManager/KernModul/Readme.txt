



















#########################################################################################################################

# Dev Level 

FOR Delevoper Only maket in : 
Hyprland-Module/Pylovara-FileManager/KernModul/daily_maintenance.sh

#!/bin/bash
# Hyprland-Module/Pylovara-FileManager/KernModul/daily_maintenance.sh
# NUR für Entwickler! Nicht automatisch aktiv!

echo -e "\e[38;5;45m╭────────── DAILY MAINTENANCE START ──────────╮\e[0m"

# 1. Update alle ls-Skripte
echo -e "\e[38;5;117m→ Updating ls*.sh scripts...\e[0m"
/bin/bash "$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/update_ls-scripts.sh"

# 2. Alte Logs löschen
echo -e "\e[38;5;117m→ Cleaning old logs...\e[0m"
/bin/bash "$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/clean_logs.sh"

# 3. Große Logs löschen
echo -e "\e[38;5;117m→ Checking oversized logs...\e[0m"
/bin/bash "$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/log_size_guard.sh"

echo -e "\e[38;5;45m╰────────── DAILY MAINTENANCE DONE ───────────╯\e[0m"

#########################################################################################################################

this in bashrc ohter zshrc :

alias maintenance='/bin/bash $HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/daily_maintenance.sh'


Easy Used in Terminal command

maintenance

to info :
Es wird nichts automatisch gestartet, nur manuell .
Keine Fehlerunterbrechung: Jeder Schritt läuft durch, auch wenn einer fehlschlägt.
Alle Ausgaben sind farblich und übersichtlich, wie bei einem alten Wartungslauf.


