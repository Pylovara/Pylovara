#!/bin/bash
# Pylovara Since 2025© https://github.com/Pylovara

echo "🔧 https://github.com/Pylovara/Hyprland-Module/"
echo "=== Universeller WLAN & Netzwerk Reparatur Modus ==="

# Grundlegende Tools sicherstellen
sudo pacman -Sy --needed pciutils usbutils net-tools wireless_tools rfkill networkmanager

# Prüfen auf blockierte Geräte (sehr häufige Fehlerquelle)
echo "⚙️ Überprüfe RFKill..."
sudo rfkill unblock all

# Geräte scannen
echo "🔍 Suche PCI/USB Netzwerkkarten..."
lspci | grep -Ei "network|wireless"
lsusb | grep -Ei "network|wireless"

# Broadcom spezifisch erkennen
if lspci | grep -i broadcom | grep -iq "network"; then
    echo "✅ Broadcom WLAN erkannt"
    
    # Kernel Header sichern
    echo "🔧 Installiere DKMS & Kernel-Header (Zen oder Standard)"
    sudo pacman -Sy --needed dkms linux-zen-headers || sudo pacman -Sy --needed linux-headers
    
    # Altes broadcom-wl Paket entfernen
    if pacman -Qs broadcom-wl | grep -q installed; then
        echo "⚠️ Entferne altes broadcom-wl Paket..."
        sudo pacman -Rns --noconfirm broadcom-wl
    fi

    # Prüfen ob yay vorhanden
    if ! command -v yay &> /dev/null; then
        echo "❌ Yay nicht gefunden. Bitte yay installieren!"
        exit 1
    fi

    echo "✅ Installiere broadcom-wl-dkms aus dem AUR..."
    yay -S --noconfirm broadcom-wl-dkms
    echo "⚙️ Lade Modul wl..."
    sudo modprobe wl
else
    echo "ℹ️ Kein Broadcom erkannt. Suche allgemeine WLAN-Treiber..."
    echo "Versuche generische Module zu laden: iwlwifi, ath9k, rt2800pci..."
    sudo modprobe iwlwifi
    sudo modprobe ath9k
    sudo modprobe rt2800pci
fi

# Netzwerkdienste neu starten
if systemctl is-active --quiet NetworkManager; then
    echo "🔁 Starte NetworkManager neu..."
    sudo systemctl restart NetworkManager
else
    echo "⚠️ NetworkManager läuft nicht. Starte Dienst..."
    sudo systemctl enable --now NetworkManager
fi

# Warten kurz, dann Geräte anzeigen
sleep 2
echo "🔎 Aktuelle Netzwerkinterfaces:"
ip link

# Verbindungstest
if ip link | grep -q "wlan"; then
    echo "✅ WLAN-Interface erkannt. Reparatur erfolgreich!"
else
    echo "❌ Kein WLAN-Interface gefunden. Manuelles Eingreifen nötig."
fi

echo "🎯 Reparatur abgeschlossen."
