#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
echo "https://github.com/Pylovara/Hyprland-Module/"
echo "  === Universal Arch Reparatur-Skript ===   "

# Funktion für Fehlerausgabe, ohne Abbruch
check_status() {
  if [ $? -ne 0 ]; then
    echo "❌ Fehler bei: $1"
  else
    echo "✅ OK: $1"
  fi
}

# Broadcom WLAN-Check
if lspci | grep -i broadcom &>/dev/null; then
  echo "🔍 Broadcom WLAN erkannt – Starte Reparatur..."
  ./broadcom-fix.sh
  check_status "Broadcom WLAN Reparatur"
fi

# Netzwerk-Check
echo "🔧 Starte Netzwerk-Reparatur..."
./netzwerk-fix.sh
check_status "Netzwerk Reparatur"

# Sound-Check
if pactl info &>/dev/null; then
  echo "🔊 PipeWire Sound-Check..."
  ./sound-fix.sh
  check_status "Sound-Fix"
else
  echo "⚠️  Kein PipeWire erkannt oder nicht gestartet"
fi

# Xorg-Check
if ! xrandr --listmonitors &>/dev/null; then
  echo "🖥️ Kein Xorg-Display erkannt – Starte Xorg-Reparatur..."
  ./xorg-fix.sh
  check_status "Xorg-Fix"
else
  echo "✅ Xorg-Display aktiv"
fi

echo "🏁 Reparatur abgeschlossen. System sollte jetzt bereit sein."
