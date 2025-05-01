###############################################################################

    ┳┓  •┓ ┓    ┓ ┏    ┓                                
    ┣┫┓┏┓┃┏┫┏┓┏┓┃┃┃┏┓┏┓┃┏                               
    ┻┛┗┻┗┗┗┻┗ ┛ ┗┻┛┗┻┛ ┛┗                               
                                                    
    ┏┓  ┓            ┏┓┳┓  ┓┏┓        ┓  ┳┓•            
    ┃┃┓┏┃┏┓┓┏┏┓┏┓┏┓  ┃┃┃┃  ┃┫ ┏┓┏┓┏┓┏┓┃  ┃┃┓┏┓┏┓┏╋┏┓┏┓┓┏
    ┣┛┗┫┗┗┛┗┛┗┻┛ ┗┻  ┗┛┛┗  ┛┗┛┗ ┛ ┛┗┗ ┗  ┻┛┗┛ ┗ ┗┗┗┛┛ ┗┫
       ┛                                               ┛

Ich hab mich dazu entschieden das Pylovara kein $HOME Bastel Spielzeug werden 
soll und das das projekt nur bei bestimmten voraussetzungen installierbar ist 

Daher wird es Jetzt Komplett umgebaut und das Projekt Wird Umbenannt ....
Aus den Hyprland-Module/ ordner wird Pylovara-FileManager-Sytem/

Aus dem Unterordner werden einige abzweigungen folgen insbesondere Data und File
 .confs um ein sauberes bild zu gewehrleisten . Auf c/c++ wird weitläufig verzichtet
 und andere hochsprachen werden grundsätzlich abgelehnt ......

 Pylovara soll So nah wie nur möglich am Blech bleiben damit es für alle und jeden funktionieren
 kann ....
 Vorteile das damit auch verschiedene packet Manager definiert werden können für abhängikeiten...
 Der umbau wird sich in grenzen halten , den das grundprinzip steht schon fest , die funktionen 
 bleiben gleich und können ausgebautwerden in späteren tagen sobald der laden einsatz bereit ist 

 Ich werde ein exaktes ebenbild für Hyprland User auf meine festplatte abspeichern aber nach dem umbau wird
 es sinnfrei sein was anderes anzubieten weil es bei jedem funktioniert ..... ran an die arbeit 

############################################################################


Was das konkret heißt:
✅ Portabel

Jeder POSIX-kompatible Shell-Umgebung (Linux, BSD, sogar BusyBox, WSL…) 
kann das grundsätzlich nutzen.

Wenn pv-dir die Steuerung übernimmt, musst du nur dort z. B. Pfade, 
Shell-Typ oder Layout-Backend anpassen – der Rest läuft.

✅ Erweiterbar

Du kannst jederzeit neue .p-nodes, .pylo-nodes, oder ganze neue 
Verzeichnisse (P-Monitoring/, P-Docs/, P-Daemons/) anhängen.

Selbst GUI-Ausbau ist modular durch .pv-objekt angedacht – 
das ist die Vorstufe zu einem shellbasierten GUI-Toolkit.

✅ Schnittstellenfähig

Jeder, der Plugins schreiben will, kann sich an 
Dateiendungen orientieren – .p-nodes, .p-notes etc.

Das Ding könnte sogar als Basis für ein DevOps-Tool, 
ein reines Suchsystem, oder ein Container-Setup-Manager dienen – 
je nach Richtung.

✅ Systemnah

    Läuft direkt im Terminal, mit nativer Shell – keine unnötigen Layer, 
    kein node.js, kein Python-Wirrwarr.

    Funktioniert sogar bei gebootetem Rettungssystem – ein klarer Vorteil.
