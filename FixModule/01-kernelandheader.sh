#!/bin/bash
# 01-kernel-header-update.sh
# Findet laufenden Kernel und aktualisiert nur Kernel + Header

set -e

echo "🔍 Erkenne laufenden Kernel..."
KERNEL_VERSION=$(uname -r)
echo "➡️  Laufender Kernel: $KERNEL_VERSION"

# Kernel-Paket und Header ableiten
if [[ "$KERNEL_VERSION" == *"zen"* ]]; then
    KERNEL_PKG="linux-zen"
    HEADER_PKG="linux-zen-headers"
elif [[ "$KERNEL_VERSION" == *"lts"* ]]; then
    KERNEL_PKG="linux-lts"
    HEADER_PKG="linux-lts-headers"
elif [[ "$KERNEL_VERSION" == *"hardened"* ]]; then
    KERNEL_PKG="linux-hardened"
    HEADER_PKG="linux-hardened-headers"
elif [[ "$KERNEL_VERSION" == *"rt"* ]]; then
    KERNEL_PKG="linux-rt"
    HEADER_PKG="linux-rt-headers"
else
    KERNEL_PKG="linux"
    HEADER_PKG="linux-headers"
fi

echo "📦 Aktualisiere Kernel und Header: $KERNEL_PKG + $HEADER_PKG"

# System und genutzten Kernel + Header aktualisieren
sudo pacman -Syu --needed "$KERNEL_PKG" "$HEADER_PKG"

echo "✅ Kernel und Header sollten nun aktuell sein."

echo "🔄 Aktualisiere DKMS-Module (Treiber-Anpassungen)..."
sudo dkms autoinstall

echo ""
echo "🎯 WICHTIG: Kernel oder Module wurden aktualisiert."
echo "❗ Du musst jetzt neu starten, damit alle Treiber richtig geladen werden!"
sleep 240

# Benutzer fragen, ob sofort rebootet werden soll
read -p "🔁 Jetzt neu starten? (j/n): " antwort
case "$antwort" in
    j|J)
        echo "🔄 Starte neu..."
        sudo reboot
        ;;
    n|N)
        echo "⚠️ Bitte denke daran, manuell neu zu starten bevor du weitermachst!"
        exit 0
        ;;
    *)
        echo "❌ Ungültige Eingabe. Bitte manuell neu starten!"
        exit 1
        ;;
esac

