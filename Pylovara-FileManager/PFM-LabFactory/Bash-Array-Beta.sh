#!/bin/bash
# Pylovara Since 2025© https://github.com/Pylovara #
# https://github.com/Pylovara/Hyprland-Module/Pylovara-FileManager
# Bash-Array-Beta WorkFlow

# Modulquelle
source ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/HeaderMaker.sh

# Liste aller Ordner, die im Hyprland-Umfeld (User, Gamer, Streamer) denkbar sind:
ordnerliste=(
  "$HOME/Bilder"
  "$HOME/Dokumente"
  "$HOME/Downloads"
  "$HOME/Musik"
  "$HOME/Videos"
  "$HOME/Öffentlich"
  "$HOME/Schreibtisch"

  "$HOME/.config/hypr"
  "$HOME/.config/hypr/hyprpaper"
  "$HOME/.config/hypr/hyprlock"
  "$HOME/.config/waybar"
  "$HOME/.config/wofi"
  "$HOME/.config/rofi"
  "$HOME/.config/kitty"
  "$HOME/.config/foot"
  "$HOME/.config/mako"
  "$HOME/.config/dunst"
  "$HOME/.config/swaylock"
  "$HOME/.config/swaync"
  "$HOME/.config/gtklock"
  "$HOME/.config/zsh"
  "$HOME/.config/bash"
  "$HOME/.config/fuzzel"
  "$HOME/.config/bemenu"
  "$HOME/.config/fastfetch"
  "$HOME/.config/ags"
  "$HOME/.config/eww"

  "$HOME/.config/obs-studio"
  "$HOME/.config/shotcut"
  "$HOME/.config/kdenlive"
  "$HOME/.config/vlc"
  "$HOME/.config/mpv"
  "$HOME/.config/audacity"

  "$HOME/.config/nvim"
  "$HOME/.config/codium"
  "$HOME/.config/helix"
  "$HOME/.config/emacs"

  "$HOME/.config/firefox"
  "$HOME/.config/brave"
  "$HOME/.config/librewolf"
  "$HOME/.config/thunderbird"

  "$HOME/.config/steam"
  "$HOME/.steam"
  "$HOME/Games"
)

# Durchlauf mit strenger Kontrolle
for ordner in "${ordnerliste[@]}"; do
  if [[ -d "$ordner" ]]; then
    cd "$ordner" || continue
    tree_output=true
    show_header
  fi
done
