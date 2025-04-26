#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
echo "https://github.com/Pylovara/Hyprland-Module/"
echo "===    Xorg/Wayland Monitor Repair ===      "

#Monitor-Reparatur

log_and_continue() {
  echo "⚠️ FEHLER: $1"
  echo "↪️  Debug-Ausgabe:"
  echo "----------------------------------"
  echo "$2"
  echo "----------------------------------"
}

# Prüfe, ob ein Monitor erkannt wurde
XRANDR_OUTPUT=$(xrandr --listmonitors 2>&1)
if ! xrandr --listmonitors &>/dev/null; then
  log_and_continue "Kein aktives Display erkannt." "$XRANDR_OUTPUT"
  echo "🔁 Versuche Neustart des Display-Servers..."

  # Wayland oder Xorg?
  if [ "$XDG_SESSION_TYPE" == "wayland" ]; then
    echo "🌀 Wayland erkannt – prüfe Hyprland socket..."
    if ! pgrep -x "Hyprland" &>/dev/null; then
      echo "⚠️  Hyprland läuft nicht – versuche Start mit Wayland env..."
      HYPR_START=$(dbus-run-session Hyprland 2>&1 &)
      sleep 3
      if ! pgrep -x "Hyprland" &>/dev/null; then
        log_and_continue "Hyprland konnte nicht gestartet werden." "$HYPR_START"
      else
        echo "✅ Hyprland erfolgreich gestartet."
      fi
    else
      echo "✅ Hyprland läuft bereits."
    fi
  else
    echo "📺 X11/Xorg erkannt – versuche Neustart von Xorg..."
    if [ -f ~/.xinitrc ]; then
      echo "🔁 Starte Xorg via startx..."
      STARTX_LOG=$(startx 2>&1)
      if [[ $? -ne 0 ]]; then
        log_and_continue "startx schlug fehl." "$STARTX_LOG"
      else
        echo "✅ Xorg erfolgreich gestartet."
      fi
    else
      echo "⚠️  Keine ~/.xinitrc gefunden. Erstelle Basisdatei..."
      echo 'exec startplasma-x11' > ~/.xinitrc
      chmod +x ~/.xinitrc
      STARTX_LOG=$(startx 2>&1)
      if [[ $? -ne 0 ]]; then
        log_and_continue "startx mit neuer xinitrc schlug fehl." "$STARTX_LOG"
      else
        echo "✅ Xorg erfolgreich gestartet (neu)."
      fi
    fi
  fi
else
  echo "✅ Monitor/Display erkannt: $XRANDR_OUTPUT"
fi

# GPU erkennen
echo "🔍 Erkenne aktive GPU:"
GPU_INFO=$(lspci | grep -E "VGA|3D")
if [[ -z "$GPU_INFO" ]]; then
  log_and_continue "Keine GPU gefunden." "$(lspci)"
else
  echo "$GPU_INFO"
fi

# Mesa- und DRM-Komponenten prüfen
echo "🔧 Prüfe Mesa & DRM..."
MESA_LIST=$(pacman -Qs mesa 2>&1)
DRM_MODULES=$(lsmod | grep drm)

if [[ -z "$MESA_LIST" ]]; then
  log_and_continue "Mesa-Pakete fehlen scheinbar." "$MESA_LIST"
else
  echo "$MESA_LIST"
fi

if [[ -z "$DRM_MODULES" ]]; then
  log_and_continue "Keine DRM-Module aktiv." "$(lsmod)"
else
  echo "$DRM_MODULES"
fi

# Reinstall bei Bedarf
read -p "🔄 Möchtest du Mesa & DRM-Komponenten neu installieren? [y/N] " reinstall
if [[ $reinstall =~ ^[Yy]$ ]]; then
  REINSTALL_LOG=$(sudo pacman -S --noconfirm mesa vulkan-icd-loader xf86-video-intel libdrm 2>&1)
  if [[ $? -ne 0 ]]; then
    log_and_continue "Fehler beim Reinstall von Mesa & DRM." "$REINSTALL_LOG"
  else
    echo "✅ Mesa + Treiber erfolgreich neu installiert."
  fi
fi

# Abschluss
echo "🏁 Xorg/Wayland-Reparatur abgeschlossen. Weiter mit dem nächsten Modul."
