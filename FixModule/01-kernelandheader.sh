#!/bin/bash
# 01-kernel-header-update.sh
# Findet laufenden Kernel und aktualisiert Kernel + Header

set -e

echo "🔍 Erkenne laufenden Kernel..."
KERNEL_VERSION=$(uname -r)
echo "➡️  Laufender Kernel: $KERNEL_VERSION"

echo "📦 Suche passende Header-Pakete..."
# Kernel-Namen ableiten
if [[ "$KERNEL_VERSION" == *"zen"* ]]; then
    HEADER_PKG="linux-zen-headers"
elif [[ "$KERNEL_VERSION" == *"lts"* ]]; then
    HEADER_PKG="linux-lts-headers"
else
    HEADER_PKG="linux-headers"
fi

echo "🔧 Aktualisiere Kernel und Header zusammen..."
sudo pacman -Syu --needed linux linux-headers linux-zen linux-zen-headers linux-lts linux-lts-headers

echo "✅ Kernel und Header sollten nun aktuell sein."

echo "🔄 Aktualisiere DKMS-Module..."
sudo dkms autoinstall

echo "🎯 Fertig! Starte nun neu, falls Kernel oder Module aktualisiert wurden."
