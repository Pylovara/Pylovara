Aliasloader.sh  : „Wenn du einmal im Wald bist, schau in jede Hütte.“
HeaderMaker.sh  : „bring mir ein Blatt und ich male die MonaLisa."
pylovara-env.sh : „Ein CEO muss mehr können als nur Nasekratzen."








###############################################################################################

Shell-Umgebung einbauen aliasreset.sh:
alias reset-pylovara="bash ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/aliasreset.sh"

trigger :

reset-pylovara
aliasloader.sh
aliaslist.sh

oder ich machs so modular  :

name : pylovara-tools.sh (oder RESET , wie auch immer) :

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


- Neue Steuerzentrale z. B. ~/.config/pylovara-env.sh:

# Quelle für Pylovara Tools
source "$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/pylovara-tools.sh"

# Alias setzen (nur beim Bedarf)
alias pylovara-reload='bash ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/pylovara-tools.sh'

2. In die .zshrc nur noch:

source ~/.config/pylovara-env.sh


trigger gesamt : pylovara-reload

###############################################################################################

aliaslist.sh anschluss .... eingabewort : aliases-pylovara

zshrc:
alias aliases-pylovara="bash ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/aliaslist.sh"


bashrc
[[ -f  ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/aliaslist.sh ]] && source ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/aliaslist.sh


###############################################################################################

aliasloader.sh Anschluss .... 

zshrc:
source ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/aliasloader.sh

bashrc:
[[ -f ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/aliasloader.sh ]] && source ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/aliasloader.sh


###############################################################################################

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


