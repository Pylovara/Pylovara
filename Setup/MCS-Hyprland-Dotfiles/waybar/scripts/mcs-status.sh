#!/bin/bash
# Quelle : /Pylovara/Setup/MCS-Hyprland-Dotfiles/waybar/scripts/mcs-status.sh
# Pylovara MCS-Status Check für Waybar

# Prüft, ob das MCS-Core-Verzeichnis als Proxy für 'Active' existiert
if [ -d "/Pylovara/System/Desktop/Protein" ]; then
    STATUS_TEXT="MCS 2.2 Ready"
    CSS_CLASS="mcs-active"
    TOOLTIP="MCS ist geladen und bereit. Klick für System-DNA via Protein Handler."
else
    STATUS_TEXT="Pylovara Offline"
    CSS_CLASS="mcs-inactive"
    TOOLTIP="Kritischer Fehler: Pylovara Core nicht gefunden."
fi

# Ausgabe des JSON für Waybar
cat << EOF
{
  "text": "$STATUS_TEXT",
  "tooltip": "$TOOLTIP",
  "class": "$CSS_CLASS"
}
EOF
