#!/bin/bash
# AbsoluterPfad: 
# Hyprland-Module/Pylovara-FileManager/ExtraSystem/pylo.sh
# Pylovara universal fixer & forwarder

# Eingabe prüfen
if [[ -z "$1" || ! "$1" =~ /- ]]; then
    echo "[ ERROR ] Kein gültiger Ordner mit /- angegeben."
    exit 1
fi

# Fixierten Pfad setzen
fixed_path="${1%/-}"  # "/usr/include/-" → "/usr/include"
shift  # Rest der Argumente verschieben

# Pfad validieren
if [ ! -d "$fixed_path" ]; then
    echo "[ ERROR ] Ordner existiert nicht: $fixed_path"
    exit 1
fi

# Datei extrahieren
file="$1"
shift

if [ -z "$file" ]; then
    echo "[ INFO ] Nur Pfad fixiert: $fixed_path"
    exit 0
fi

# Datei-Pfad zusammensetzen
full_path="$fixed_path/$file"

# Datei prüfen
if [ ! -f "$full_path" ]; then
    echo "[ ERROR ] Datei nicht gefunden: $full_path"
    exit 1
fi

# Wenn noch Argumente → Befehl ausführen
if [ $# -gt 0 ]; then
    echo "[ OK ] Führe aus: $* $full_path"
    "$@" "$full_path"
else
    echo "[ OK ] Datei gefunden: $full_path"
fi
