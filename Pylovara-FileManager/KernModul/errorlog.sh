#!/bin/bash
# Absoluter Pfad:
# Hyprland-Module/Pylovara-FileManager/KernModul/errorlog.sh

log_dir="$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/ErrorLogs"
timestamp=$(date +"%Y-%m-%d_%H%M")
logfile="$log_dir/errorlog_${timestamp}.log"

mkdir -p "$log_dir"

error_message="$1"
affected_script="$2"

{
  echo "--------------------------------------"
  echo "Fehlerzeit: $(date)"
  echo "Fehlerbeschreibung: $error_message"
  echo "Betroffenes Skript: $affected_script"
  echo "--------------------------------------"
} >> "$logfile"

echo "[ FEHLER ] $error_message → Log: $logfile" >&2
