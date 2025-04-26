#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
#https://github.com/Pylovara/Hyprland-Module/Polyvara-FileManager

# Farben definieren – übersichtlicher
declare -A COLORS=(
  [NC]="\e[0m"
  [YELLOW]="\e[38;5;226m"
  [RED]="\e[38;5;196m"
  [PINK]="\e[38;5;201m"
  [BLUE]="\e[38;5;93m"
  [WHITE]="\e[38;5;15m"
  [LIGHT]="\e[38;5;250m"
)
RANDOM_COLOR="\e[38;5;$((196 + RANDOM % 35))m"

show_header() {
  volume_raw=$(du -sh . | cut -f1)
  current_path=$(pwd)

  # 📦 Farbwahl je nach Größe (lesbarer)
  case $volume_raw in
    *K)
      size_num=${volume_raw%K}; size_num=$(echo "$size_num" | sed 's/,/./')
      if [ "$(echo "$size_num < 100" | bc)" -eq 1 ]; then
        color="$RANDOM_COLOR"
      else color="$YELLOW"; fi ;;
    *M)
      size_num=${volume_raw%M}; size_num=$(echo "$size_num" | sed 's/,/./')
      if [ "$(echo "$size_num < 100" | bc)" -eq 1 ]; then
        color="$RED"
      else color="$PINK"; fi ;;
    *G) color="$BLUE" ;;
    *) color="$WHITE" ;;
  esac

  # 📂 Letzte Datei suchen
  last_file=$(find . -maxdepth 1 -type f -printf "%A@ %p\n" 2>/dev/null | sort -n | tail -1 | cut -d' ' -f2-)
  [ -z "$last_file" ] && last_file=$(find . -maxdepth 1 -type f -printf "%T@ %p\n" 2>/dev/null | sort -n | tail -1 | cut -d' ' -f2-)
  last_file=$(basename "$last_file")
  center_line=$(printf "%-60s" "last handling 📂|> $last_file")

  # 📢 Ausgabe mit Farbschema
  echo -e "${color}╭── Volume: $volume_raw | Pfad: $current_path ${NC}"
  echo -e "${color}│|Polyvara-FileManager|$center_line${NC}"
  echo -e "${color}╰──────────────────────────────────────────────────────────${NC}"

  # 📁 Falls Baumstruktur erwünscht
  if [ "$tree_output" = true ]; then print_tree; fi
}

print_tree() {
  find . -maxdepth 2 -type d \( ! -name '.*' \) -printf "%P/\n" -o -type f -printf "  %P\n" \
  | sed 's|^\./||' \
  | awk '
    BEGIN {FS="/"}
    NF==1 {print "📄 " $0}
    NF==2 && $2=="" {print "📁 " $1}
    NF==2 && $2!="" {print "  └── 📄 " $2 " (" $1 ")"}'
}
