Was pylo können muss:

    Akzeptiere absolute oder relative Pfade (auch /usr/include/-)
    Ignoriere das /- – und speichere den Pfad fixiert
    Dateiname extrahieren
    Wenn da noch was kommt (Befehl) → übergebe Datei an das Programm
    Pfadangabe absolut oder relativ möglich
    Kein cd, keine Shell-Umgebungsabhängigkeit
    Jeder Ort im System möglich – inklusive /usr, /etc, /boot
    Rest bleibt UNIX: cat, nano, xdg-open, hexdump, alles !

    Hyprland-Module/Pylovara-FileManager/
    ├── ExtraSystem/
    │   └── pylo.sh         ← das neue Tool
    ├── Search/             ← aliasbasierte Übersicht (ls*.sh)
    ├── KernModul/
    │   └── HeaderMaker.sh  ← Baum/Anzeige

    einbindung .bashrc oder .zshrc and source 

    alias pylo="bash ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/ExtraSystem/pylo.sh"

Warum Keine Logg ? Deshalb :

"Ein Admin erkennt man daran, dass sein Werkzeug weniger Fragen stellt als ein Praktikant."
