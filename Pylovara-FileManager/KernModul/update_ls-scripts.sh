#!/bin/bash
# Absoluter Pfad:
# Hyprland-Module/Pylovara-FileManager/KernModul/update_ls-scripts.sh
# Errorlogs : Hyprland-Module/Pylovara-FileManager/KernModul/ErrorLogs

header_path="$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/HeaderMaker.sh"
errorlog_script="$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/errorlog.sh"

mkdir -p "$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/ErrorLogs"

for script in "$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/Search"/ls*.sh; do
  [[ "$script" == *"HeaderMaker.sh" ]] && continue

  grep -q "show_header" "$script"
  if [ $? -eq 0 ]; then
    echo "[ INFO ] Überspringe: $(basename "$script") (bereits show_header enthalten)"
    continue
  fi

  temp=$(mktemp)
  {
    echo "#!/bin/bash"
    echo "source \"$header_path\""
    echo "cd \"$(dirname "$script")\" || { source \"$errorlog_script\" \"Fehler beim Wechsel in Verzeichnis\" \"$script\"; exit 1; }"
    echo "tree_output=true"
    echo "show_header || { source \"$errorlog_script\" \"Fehler beim Anzeigen des Headers\" \"$script\"; exit 1; }"
  } > "$temp"
  tail -n +2 "$script" >> "$temp"
  mv "$temp" "$script"
  chmod +x "$script"

  echo "[ OK ] Aktualisiert: $(basename "$script")"
done
