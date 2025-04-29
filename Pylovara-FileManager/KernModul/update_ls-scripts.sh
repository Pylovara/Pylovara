#!/bin/bash
#Absoluter Ordnerpfad:                                               #
#Hyprland-Module/Pylovara-FileManager/KernModul/update_ls-scripts.sh #
#Pylovara Since 2025© https://github.com/Pylovara                    #
#https://github.com/Pylovara/Hyprland-Module/Pylovara-FileManager    #   

header_path="$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/HeaderMaker.sh"

for script in "$HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager"/Search/ls*.sh; do
  # Nicht den Header selbst bearbeiten
  [[ "$script" == *"HeaderMaker.sh" ]] && continue

  # Bestehenden Inhalt sichern (außer sie haben schon show_header)
  grep -q "show_header" "$script" && continue

  temp=$(mktemp)
  echo "#!/bin/bash" > "$temp"
  echo "source \"$header_path\"" >> "$temp"
  echo "cd \"$(dirname "$script")\" || exit 1" >> "$temp"
  echo "show_header" >> "$temp"
  tail -n +2 "$script" >> "$temp" # Restlicher Code 
  mv "$temp" "$script"
  chmod +x "$script"

  echo "→ aktualisiert: $(basename "$script")"
done
