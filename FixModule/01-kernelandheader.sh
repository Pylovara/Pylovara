#!/bin/bash
# 01-kernelandheader.sh
# Aktualisiert Kernel & Header, rekonstruiert ALLE DKMS-Module sauber.

set -e

echo "🔍 Erkenne laufenden Kernel..."
KERNEL_VERSION=$(uname -r)
echo "➡️  Laufender Kernel: $KERNEL_VERSION"

# Kernel-Paket und Header bestimmen
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
sudo pacman -Syu --needed "$KERNEL_PKG" "$HEADER_PKG"

echo "✅ Kernel und Header aktualisiert."

# Jetzt ALLE DKMS-Module neu bauen (nicht nur einfach dkms autoinstall!)
if [ -d /var/lib/dkms ]; then
    echo "🔧 Neubaue ALLE installierten DKMS-Module..."
    for module in /var/lib/dkms/*; do
        if [ -d "$module" ]; then
            modname=$(basename "$module")
            echo "➡️  Baue $modname neu..."
            sudo dkms install -m "$modname" -v $(ls "$module" | head -n 1) || {
                echo "⚠️  Fehler beim DKMS-Rebuild für $modname"
            }
        fi
    done
else
    echo "ℹ️ Keine DKMS-Module installiert."
fi

echo ""
echo "🎯 Hinweis: Wenn Kernel oder Module aktualisiert wurden, ist ein Neustart notwendig!"
sleep 3

# Benutzer fragen, ob neu gestartet werden soll
read -p "🔁 Jetzt neu starten? (j/n): " antwort
case "$antwort" in
    j|J)
        echo "🛠️  Marker setzen für Fortsetzung nach Reboot..."
        touch /tmp/continue_after_reboot
        sleep 3
        echo "🔄 Neustart in 5 Sekunden..."
        sleep 5
        sudo reboot
        ;;
    n|N)
        echo "⚠️  Bitte denke daran, manuell neu zu starten bevor du weitermachst!"
        exit 0
        ;;
    *)
        echo "❌ Ungültige Eingabe. Manuell neustarten!"
        exit 1
        ;;
esac
