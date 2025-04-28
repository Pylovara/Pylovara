#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
echo "https://github.com/Pylovara/Hyprland-Module/"
echo "=== Netzwerk | Header Repair Autoinstaller ==="

# 1. Broadcom-Check (inkl. DKMS / AUR / wl-Modul)
if lspci | grep -i broadcom | grep -iq "network"; then
  echo "🔍 Broadcom WLAN erkannt – führe Treiber-Fix durch..."

  # DKMS + Header
  sudo pacman -Sy --needed dkms linux-zen-headers || sudo pacman -Sy --needed linux-headers

  # Paket neu installieren
  if pacman -Qs broadcom-wl | grep -q installed; then
    echo "⚠️  Entferne altes broadcom-wl Paket..."
    sudo pacman -Rns --noconfirm broadcom-wl
  fi

  # Neuinstallation via yay
  yay -S --noconfirm broadcom-wl-dkms

  # Alte Module raus, wl rein
  sudo rmmod b43 b43legacy bcm43xx bcma brcm80211 brcmfmac brcmsmac ssb tg3 wl 2>/dev/null
  sudo modprobe wl
  echo "✅ Broadcom-Treiber repariert."
fi

# 2. rfkill-Entsperrung
echo "🔓 Entsperre WLAN via rfkill..."
sudo rfkill unblock all

# 3. Standard-Netzwerktools checken/installieren
echo "🔧 Stelle sicher, dass iproute2, iw & NetworkManager da sind..."
sudo pacman -S --noconfirm iproute2 iw networkmanager

# 4. Dienste starten
echo "🔁 Aktiviere & starte NetworkManager..."
sudo systemctl enable NetworkManager --now

# 5. IP-Link zeigen zur Diagnose
echo "🌐 Aktive Netzwerkgeräte:"
ip link show | grep -Ei "^[0-9]+:|wl|en"

# 6. WLAN-Scan (wenn nmcli da)
if command -v nmcli >/dev/null 2>&1; then
  echo "📡 Verfügbare WLANs:"
  nmcli device wifi list
else
  echo "⚠️  'nmcli' nicht verfügbar – installiere mit: sudo pacman -S networkmanager"
fi

echo "✅ Netzwerk-Reparatur abgeschlossen."
