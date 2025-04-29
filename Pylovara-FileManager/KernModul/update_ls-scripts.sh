#!/bin/bash
# Absoluter Ordnerpfad:
# Hyprland-Module/Pylovara-FileManager/KernModul/update_ls-scripts.sh
# Errorlogs : Hyprland-Module/Pylovara-FileManager/KernModul/ErrorLogs

header_path="$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/HeaderMaker.sh"
error_log_dir="$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/ErrorLogs"
mkdir -p "$error_log_dir" # Falls ErrorLogs Ordner fehlt
timestamp=$(date "+%Y-%m-%d_%H-%M-%S")
error_log_file="$error_log_dir/errorlog_update_$timestamp.log"

log_error() {
  echo "[$(date '+%Y-%m-%d %H:%M:%S')] FEHLER: $1" >> "$error_log_file"
}

for script in "$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager"/Search/ls*.sh; do
  [[ "$script" == *"HeaderMaker.sh" ]] && continue

  if grep -q "show_header" "$script"; then
    echo "→ übersprungen (bereits aktualisiert): $(basename "$script")"
    continue
  fi

  temp=$(mktemp)
  {
    echo "#!/bin/bash"
    echo "source \"$header_path\""
    echo "cd \"$(dirname "$script")\" || { echo 'Fehler: Pfad ungültig'; exit 1; }"
    echo "show_header"
  } > "$temp"

  # Versuche alten Inhalt ab Zeile 2 anhängen
  if tail -n +2 "$script" >> "$temp"; then
    if mv "$temp" "$script"; then
      chmod +x "$script"
      echo "→ aktualisiert: $(basename "$script")"
    else
      log_error "Konnte Datei nicht überschreiben: $script"
      rm -f "$temp"
      continue
    fi
  else
    log_error "Konnte alten Inhalt nicht lesen: $script"
    rm -f "$temp"
    continue
  fi
done

# Wenn Fehler aufgetreten sind, kurze Abschlussmeldung
if [ -s "$error_log_file" ]; then
  echo "[ WARNUNG ] Fehler beim Aktualisieren! Details in: $error_log_file"
else
  rm -f "$error_log_file" # Leere Logs gleich entsorgen
fi
