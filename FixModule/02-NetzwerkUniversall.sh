#!/bin/bash
# /02-NetzwerkUniversall.sh
# Pylovara Since 2025© https://github.com/Pylovara
# Universeller Netzwerk- und WLAN-Installer für ALLE Plattformen

set -e

echo "🔧 https://github.com/Pylovara/Hyprland-Module/"
echo "=== Universeller WLAN & Netzwerk Reparatur Modus ==="

# Tools sicherstellen
echo "🔍 Installiere benötigte Basis-Tools..."
sudo pacman -Sy --needed pciutils usbutils net-tools wireless_tools rfkill networkmanager

# Entblocken aller Funkgeräte
echo "⚙️ Entblocke alle Funkgeräte..."
sudo rfkill unblock all

# Geräteliste anzeigen
echo "🔍 Scanne PCI- und USB-Geräte nach Netzwerkkarten..."
lspci | grep -Ei "network|wireless" || echo "Keine PCI-Netzwerkkarten gefunden."
lsusb | grep -Ei "network|wireless" || echo "Keine USB-Netzwerkkarten gefunden."

# Wichtige Kernel-Module in der Reihenfolge laden
declare -a modules=("iwlwifi" "ath9k" "ath10k_pci" "rt2800pci" "rtw88_pci" "rtl8723de" "rtl8188eu" "brcmfmac" "b43" "asix" "ax88179_178a" "cdc_ether")

echo "🔧 Versuche passende Kernel-Module zu laden..."
for module in "${modules[@]}"; do
    if sudo modprobe "$module" 2>/dev/null; then
        echo "✅ Modul geladen: $module"
    else
        echo "❌ Modul nicht gefunden oder nicht geladen: $module"
    fi
done

# Spezialfall: Broadcom - auf AUR Paket (broadcom-wl-dkms) setzen
if lspci | grep -i broadcom | grep -iq "network"; then
    echo "🛰️ Broadcom WLAN erkannt."
    
    # Prüfen ob DKMS-Variante installiert ist
    if ! pacman -Qs broadcom-wl-dkms > /dev/null; then
        echo "🛠️ Installiere broadcom-wl-dkms aus dem AUR..."
        if ! command -v yay &>/dev/null; then
            echo "❗ Fehler: yay nicht gefunden. Bitte yay installieren!"
            exit 1
        fi
        yay -S --noconfirm broadcom-wl-dkms
    fi

    echo "🔃 Rebuild broadcom-wl mit DKMS..."
    sudo dkms install broadcom-wl/$(dkms status broadcom-wl | awk '{print $2}')
    
    echo "🔧 Lade Modul wl..."
    sudo modprobe wl
fi

# Spezialfall: Realtek RTL8xxxu Chips (sehr oft in Laptops)
if lsusb | grep -i "Realtek" | grep -iq "802.11"; then
    echo "🛰️ Realtek USB WLAN erkannt."
    
    if ! pacman -Qs rtl8821cu-dkms-git > /dev/null; then
        echo "🛠️ Installiere rtl8821cu-dkms-git (Realtek USB Treiber)..."
        yay -S --noconfirm rtl8821cu-dkms-git
    fi

    echo "🔃 Rebuild Realtek USB WLAN Modul mit DKMS..."
    sudo dkms install rtl8821cu/$(dkms status rtl8821cu | awk '{print $2}')
    
    sudo modprobe 8821cu
fi

# Netzwerkdienste neu starten
echo "🔁 (Re)Starte NetworkManager..."
sudo systemctl enable --now NetworkManager
sudo systemctl restart NetworkManager

# Warten und Netzwerke checken
sleep 2
echo "🔎 Überprüfe Netzwerkinterfaces:"
ip link

# Verbindungstest
if ip link | grep -q "wlan"; then
    echo "✅ WLAN-Interface erkannt. Alles bereit!"
else
    echo "⚠️ Kein WLAN-Interface gefunden. Eventuell manuelle Nacharbeit nötig."
fi

echo "🎯 Netzwerk-Reparatur abgeschlossen."
