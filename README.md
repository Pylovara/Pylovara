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

Pylovara-FileManager-System/ 
|
|- P-Search/ ---- .p-notes	-------- Trigger- und Notizdateien für das p-Modul (z. B. für ptree)
|
|-----------P-Module---------------
||- P-Module/ ---- .p-nodes	-------- 
||#Kernmodule von p (also Shell-Knoten mit Logik)
||
||-P-Module/HeaderMaker.p-nodes
||# Pylovara-FileManager-System/P-Module/HeaderMaker.p-nodes
||# Ast/Tree Ausgabe Only show-header Optional
||
||-P-Module/aliaslist.p-nodes
||# Pylovara-FileManager-System/P-Module/aliaslist.p-nodes
||# Only Watching - P-Search - p-notes
||
||-P-Module/aliasloader.p-nodes
||# Pylovara-FileManager-System/P-Search/aliasloader.p-nodes
||# load all lsp*.sh Skripte aus Unterordnern als Aliase.
||
||-P-Module/clean_logs.p-nodes
||# Pylovara-FileManager-System/P-Module/clean_logs.p-nodes
||# automatische Log-Säuberung, sauber, robust, idiotensicher
||
||-P-Module/errorlog.p-nodes
||# Pylovara-FileManager-System/P-Module/errorlog.p-nodes
||# Error Logger - CleanSimpel - Port P-Error
||
||-P-Module/log_size_guard.p-nodes
||# Log größer als 1,2MB wird automatisch gelöscht 
||# bei extremen Problemen puffer erhöhen - Extrem please Buffer Higher !!!!
||
||-P-Module/pylovaracontrol.p-nodes
||# Pylovara-FileManager-System/P-Module/pylovaracontrol.p-nodes
||# Pylovara Toolkit – aliasreset, aliasloader und aliaslist zentral ausführen - One Clicker
||
||-P-Module/update_ls-scripts.p-nodes
||# Pylovara-FileManager-System/P-Module/update_ls-scripts.p-nodes
||# Errorlogs : Pylovara-FileManager/P-Error
||
||-P-Module/Arbeitsblatt.txt
||# Pylovara-FileManager-System/P-Module/Arbeitsblatt.txt
||# Ast - Entwurf - PModule/ - .p-nodes
||---------------------------------
|
|-P-Error/  ---- .p-logs	-------- Logausgaben aus p
|-Pylo-Search/ - .pylo-notes ----- Alternative Suchdatenbank für Pylo-kompatible Shell-Kommandos
|
||----------Pylo-Module------------
||-Pylo.Module/ - .pylo-nodes ----- 
||# .pylo-nodes: Kernmodule für pylo-Features
||
||-Pylo-Module/pylo.pylo-nodes
||# /Pylovara-FileManager-System/Pylo-Module/pylo.pylo-nodes
||# .pylo-nodes: Kernmodule für pylo-Features
||# universal fixer & forwarder
||
||-Pylo-Module/pylohelp.pylo-nodes
||# /Pylovara-FileManager-System/Pylo-Module/pylohelp.pylo-nodes
||# .pylo-nodes: Kernmodule für pylo-Features
||# Pylovara Universal fixer with Debug Logger
||
||-Pylo-Module/pylooptions.txt
||# Pylovara-FileManager-System/Pylo-Module/pylooptions.txt
||# .pylo-nodes: Kernmodule für pylo-Features
||# Control - Steuerung - Navigation - Read
||
||-Pylo-Module/Arbeitsblatt.txt
||# Ast - Entwurf - Pylo-Module/ - .pylo-nodes
||---------------------------------
|
|- Pylo-Error/ -- .pylo -logs ----- Logausgaben aus pylo
|- PLVA-Layouts - .pv-objekt	 ----- Visuelle Layoutdateien, z. B. für Kitty-GUI, Menüs, etc.
|- Pylovara-DirectoryManager.pv-dir - Steuerzentrale für Pfade, Konfiguration und zentrale Verwaltung Ordner 

Pylovara-FileManager-System/
│
├─ P-Search/                → .p-notes: Trigger/Notizen für "p" (Tree/Navigator)
├─ P-Module/                → .p-nodes: Kernmodule von "p" (Modul-Logik)
├─ P-Error/                 → .p-logs: Logausgaben aus "p"
│
├─ Pylo-Search/             → .pylo-notes: Datenbank für alternative SHELL-Kommandos
├─ Pylo.Module/             → .pylo-nodes: Kernmodule für pylo-Features
├─ Pylo-Error/              → .pylo-logs: Logausgaben aus "pylo"
│
├─ PLVA-Layouts/            → .pv-objekt: GUI-Elemente & visuelle Layouts (Kitty etc.)
└─ Pylovara-DirectoryManager.pv-dir/ → Zentrale für Pfade, Konfig, Routing, Shell-RC-Sourcing

 Stärken der Struktur:

    Modular: Klare Trennung nach Verantwortlichkeiten (p, pylo, layouts, dir-manager)

    Erweiterbar: später einfach P-Tools/, P-Monitoring/, P-Docs/ usw. anhängen.

    Verständlich: Sogar ein fremder Entwickler oder Nutzer kapiert auf Anhieb, was was ist.

    Portabel: Mit pv-dir als zentrale Routing-Instanz kann man später leicht anpassen/umschreiben , stichwort : porttabel.
