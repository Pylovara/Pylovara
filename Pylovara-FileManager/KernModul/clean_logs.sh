#!/bin/bash
# Absoluter Pfad:
# Hyprland-Module/Pylovara-FileManager/KernModul/clean_logs.sh
# automatische Log-Säuberung, sauber, robust, idiotensicher 

# Verzeichnis der Logs
log_dir="$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/ErrorLogs"

# Maximal erlaubte Tage, bevor gelöscht wird
max_age_days=7

# Prüfen ob das Log-Verzeichnis existiert
if [ ! -d "$log_dir" ]; then
  echo "[ WARNUNG ] Log-Verzeichnis existiert nicht: $log_dir" >&2
  exit 0
fi

# Alte Logdateien löschen
find "$log_dir" -type f -name "errorlog_*.log" -mtime +"$max_age_days" -print -delete

echo "[ OK ] Alte Logs älter als $max_age_days Tage gelöscht."
