#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
echo "https://github.com/Pylovara/Hyprland-Module/"
echo "  === Start 00-module.sh Autorepair ===     "

# Setzt Netzwerk, Sound, Xorg & Broadcom-Fix wenn nötig.
chmod +x 02-NetzwerkUniversall.sh
chmod +x 03-sound-fix.sh
chmod +x 04-xorg-fix.sh


# 1. Netzwerktreiber & Basis setzen
echo "[1/6] Netzwerk-Fix wird gestartet..."
./02-NetzwerkUniversall.sh

# 2. Sound-Probleme fixen (z. B. kein Output, PipeWire zickt)
echo "[3/6] Sound-Fix wird gestartet..."
./03-sound-fix.sh

# 3. Xorg-Treiber (nur wenn man was mit X11 oder Nvidia etc. macht)
echo "[4/6] Xorg-Fix wird gestartet..."
./04-xorg-fix.sh

# 6. Fertigmeldung
echo "[6/6] AllInOne komplett durchgelaufen."
