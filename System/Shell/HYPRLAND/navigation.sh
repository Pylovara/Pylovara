#!/bin/bash
# Keybinds von Hyprland, formatiert sie und zeigt sie in Wofi an

# Genutzt wird hyprctl, um die Keybinds zu holen. 
# Per awk-Kommando ( lesbar ).

KEYBINDS=$(hyprctl keybinds | awk '
    /^bind/ {
        # String 
        mods = $2
        key = $3
        dispatcher = $4
        arg = $5
        
        # Ein paar Dispatcher-Namen für die Übersicht
        if (dispatcher == "exec") dispatcher = "Starte"
        if (dispatcher == "movefocus") dispatcher = "Fokus"
        if (dispatcher == "movewindow") dispatcher = "Verschieben"
        
        printf "<b>SUPER + %s</b>  →  %s %s\n", key, dispatcher, arg
    }
')

# Genutzt wird : Wofi - Text!
echo -e "$KEYBINDS" | wofi --show dmenu \
    --prompt "HYPRLAND | PYLOVARA | NAVIGATION" \
    --width 800 \
    --height 600 \
    --location center \
    --no-actions \
    --no-mouse \
    --allow-markup