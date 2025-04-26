#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
echo "https://github.com/Pylovara/Hyprland-Module/"
echo "=== Broadcom WLAN Autoinstaller ==="

# Prüfen, ob Broadcom WLAN vorhanden ist
if ! lspci | grep -i broadcom | grep -iq "network"; then
  echo "❌ Kein Broadcom WLAN-Gerät gefunden. Abbruch."
  exit 1
fi

echo "✅ Broadcom WLAN erkannt"

# Installiere DKMS & Kernel-Header (Zen oder Standard)
echo "✅ Installiere DKMS & Header (zen)"
sudo pacman -Sy --needed dkms linux-zen-headers || sudo pacman -Sy --needed linux-headers

# Entferne altes Paket, wenn nötig
if pacman -Qs broadcom-wl | grep -q installed; then
  echo "⚠️  Entferne altes broadcom-wl Paket..."
  sudo pacman -Rns --noconfirm broadcom-wl
fi

# Installiere broadcom-wl-dkms aus dem AUR
echo "✅ Installiere broadcom-wl-dkms aus dem AUR"
yay -S --noconfirm broadcom-wl-dkms

# Entferne mögliche Konfliktmodule
echo "⚙️ Entlade alte WLAN-Module..."
sudo rmmod b43 b43legacy bcm43xx bcma brcm80211 brcmfmac brcmsmac ssb tg3 wl 2>/dev/null

# Lade das neue Modul
echo "⚙️ Lade Modul wl..."
sudo modprobe wl

# Netzwerkdienst neustarten (wenn NetworkManager läuft)
if systemctl is-active --quiet NetworkManager; then
  echo "🔁 Starte NetworkManager neu..."
  sudo systemctl restart NetworkManager
fi

echo "✅ Broadcom WLAN-Treiber installiert & aktiviert."
