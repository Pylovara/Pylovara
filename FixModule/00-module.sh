#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
echo "https://github.com/Pylovara/Hyprland-Module/"
echo "  === Start 00-module.sh Autorepair ===     "

# Scripte ausführbar machen .
chmod +x 01-kernelandheader.sh
chmod +x 02-NetzwerkUniversall.sh
chmod +x 03-sound-fix.sh
chmod +x 04-xorg-fix.sh

# 1. Kernel und Header Aktualisieren
echo "[1/5] Netzwerk-Fix wird gestartet..."
./01-kernelandheader.sh

# 2. Netzwerktreiber & Basis setzen
echo "[2/5] Netzwerk-Fix wird gestartet..."
./02-NetzwerkUniversall.sh

# 3. Sound-Probleme fixen (z. B. kein Output, PipeWire zickt)
echo "[3/5] Sound-Fix wird gestartet..."
./03-sound-fix.sh

# 4. Xorg-Treiber (nur wenn man was mit X11 oder Nvidia etc. macht)
echo "[4/5] Xorg-Fix wird gestartet..."
./04-xorg-fix.sh

# 5. Fertigmeldung
echo "[5/5] AllInOne komplett durchgelaufen."

