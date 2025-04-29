#!/bin/bash
# Hyprland-Module/Pylovara-FileManager/KernModul/log_size_guard.sh
# Log größer als 1,2MB wird automatisch gelöscht
# bei extremen Problemen puffer erhöhen !!!!

log_dir="$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/ErrorLogs"
size_limit_kb=1228  # ca. 1,2MB

deleted_logs=0

# Prüfen, ob Log-Ordner existiert
[ -d "$log_dir" ] || exit 0

for logfile in "$log_dir"/*.log; do
  [ -e "$logfile" ] || break

  # Hole Dateigröße in KB
  filesize_kb=$(du -k "$logfile" | cut -f1)

  if [ "$filesize_kb" -gt "$size_limit_kb" ]; then
    rm -f "$logfile"
    ((deleted_logs++))
    echo "[ OK ] Großes Log gelöscht: $(basename "$logfile")"
  fi
done

if [ "$deleted_logs" -eq 0 ]; then
  echo "[ OK ] Keine Logs über 1,2MB gefunden."
else
  echo "[ INFO ] $deleted_logs große Logs entfernt."
fi
