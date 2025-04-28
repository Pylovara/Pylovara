#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
echo "https://github.com/Pylovara/Hyprland-Module/"
echo "  === Start 00-module.sh Autorepair ===     "

# Setzt Netzwerk, Sound, Xorg & Broadcom-Fix wenn nötig.

# 1. Netzwerktreiber & Basis setzen
echo "[1/6] Netzwerk-Fix wird gestartet..."
chmod +x 02-broadcom-fix.sh
./01-netzwerk-fix.sh

# 2. Broadcom optional (falls vorhanden – manuell checken)
echo "[2/6] Broadcom-Fix (optional)..."
chmod +x 03-sound-fix.sh
./02-broadcom-fix.sh

# 3. Sound-Probleme fixen (z. B. kein Output, PipeWire zickt)
echo "[3/6] Sound-Fix wird gestartet..."
chmod +x 04-xorg-fix.sh
./03-sound-fix.sh

# 4. Xorg-Treiber (nur wenn man was mit X11 oder Nvidia etc. macht)
echo "[4/6] Xorg-Fix wird gestartet..."
chmod +x 05-repair-all.sh
./04-xorg-fix.sh

# 5. Reparatur-Skript für Notfälle oder Cleanup
echo "[5/6] Reparatur läuft..."
./05-repair-all.sh

# 6. Fertigmeldung
echo "[6/6] Module.sh komplett durchgelaufen."
