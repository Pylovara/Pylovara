#!/bin/bash
# Pylovara Since 2025© https://github.com/Pylovara #
echo "https://github.com/Pylovara/Hyprland-Module/"
echo "  === Start 00-module.sh Autorepair ===     "

# Scripte ausführbar machen
chmod +x 01-kernelandheader.sh
chmod +x 02-NetzwerkUniversall.sh
chmod +x 03-sound-fix.sh
chmod +x 04-xorg-fix.sh

# Wenn Marker-Datei existiert, weitermachen nach Reboot
if [ -f /tmp/continue_after_reboot ]; then
    echo "🛠️  Fortsetzung nach Reboot erkannt!"
    rm /tmp/continue_after_reboot
    ./02-NetzwerkUniversall.sh
    echo "[3/5] Sound-Fix wird gestartet..."
    ./03-sound-fix.sh
    echo "[4/5] Xorg-Fix wird gestartet..."
    ./04-xorg-fix.sh
    echo "[5/5] AllInOne komplett abgeschlossen."
    exit 0
fi

# 1. Kernel und Header Aktualisieren
echo "[1/5] Kernel und Header Fix wird gestartet..."
./01-kernelandheader.sh

# Falls hier weiter, normal weitermachen
./02-NetzwerkUniversall.sh
echo "[3/5] Sound-Fix wird gestartet..."
./03-sound-fix.sh
echo "[4/5] Xorg-Fix wird gestartet..."
./04-xorg-fix.sh
echo "[5/5] AllInOne komplett durchgelaufen."


