#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
echo "https://github.com/Pylovara/Hyprland-Module/"
echo "    === Sound Repair | PipeWire/ALSA  ===   "

# Prüfen, ob PipeWire läuft
if ! systemctl --user is-active pipewire &>/dev/null; then
  echo "⚠️  PipeWire läuft nicht – versuche zu starten..."
  systemctl --user start pipewire pipewire-pulse wireplumber
  sleep 1
fi

# Wenn PipeWire noch immer nicht aktiv ist, dann neu installieren
if ! systemctl --user is-active pipewire &>/dev/null; then
  echo "🛠️ PipeWire wird (re)installiert..."
  sudo pacman -Sy --noconfirm pipewire pipewire-alsa pipewire-pulse wireplumber
  systemctl --user daemon-reexec
  systemctl --user restart pipewire pipewire-pulse wireplumber
fi

# Sicherstellen, dass ALSA da ist
echo "🔧 Stelle sicher, dass ALSA funktioniert..."
sudo pacman -S --noconfirm alsa-utils

# Volume aufdrehen
echo "🔊 Setze Master-Volume auf 80%"
amixer sset Master 80% unmute &>/dev/null || pactl set-sink-volume @DEFAULT_SINK@ 80%

# Testton abspielen
echo "🔉 Führe Soundtest durch..."
speaker-test -t wav -l 1 &>/dev/null &
sleep 2
pkill speaker-test

echo "✅ Sound-Modul abgeschlossen."
