Was pylo können muss:

    Akzeptiere absolute oder relative Pfade (auch /usr/include/-)
    Ignoriere das /- – und speichere den Pfad fixiert
    Dateiname extrahieren
    Wenn da noch was kommt (Befehl) → übergebe Datei an das Programm
    Pfadangabe absolut oder relativ möglich
    Kein cd, keine Shell-Umgebungsabhängigkeit
    Jeder Ort im System möglich – inklusive /usr, /etc, /boot
    Rest bleibt UNIX: cat, nano, xdg-open, hexdump, alles !

    Hyprland-Module/
    ├── Pylovara-FileManager/
    │   ├── ExtraSystem/
    │   │   ├── pylo.sh
    │   │   ├── pylohelp.sh      ← debug version
    │   ├── Logs/
    │   │   └── pylohelp.log     ← alle Logs der Developer-Version

        Normale Benutzung (ohne Loggen):

        pylo /usr/include/- ares_version.h cat

        Entwickler-Modus (mit Logging):

        pylohelp /usr/include/- ares_version.h cat




    einbindung .bashrc oder .zshrc and source 

    alias pylo="bash ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/ExtraSystem/pylo.sh"
    alias pylohelp="bash ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/ExtraSystem/pylohelp.sh"

Warum  ? Deshalb :

"Ein Admin erkennt man daran, dass sein Werkzeug weniger Fragen stellt als ein Praktikant."

Für Dev Level zwecke gibts ein pylohelp logger
