#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara 
#https://github.com/Pylovara/Hyprland-Module/FunctionsModule

header_path="$HOME/.config/hypr/function/header.sh"

for script in "$HOME/.config/hypr/function"/ls*.sh; do
  # Nicht den Header selbst bearbeiten
  [[ "$script" == *"header.sh" ]] && continue

  # Bestehenden Inhalt sichern (außer sie haben schon show_header)
  grep -q "show_header" "$script" && continue

  temp=$(mktemp)
  echo "#!/bin/bash" > "$temp"
  echo "source \"$header_path\"" >> "$temp"
  echo "cd \"$(dirname "$script")\" || exit 1" >> "$temp"
  echo "show_header" >> "$temp"
  tail -n +2 "$script" >> "$temp" # Restlicher Code ohne Shebang
  mv "$temp" "$script"
  chmod +x "$script"

  echo "→ aktualisiert: $(basename "$script")"
done
