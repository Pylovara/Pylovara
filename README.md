############################################################################################

Pylovara-FileManager-System = Modular | SystemSteuerung | ZuckunftsTechnik | Rolling-Release

Daten Typen am beispiel * für andere kennungen :

----
IN WORKING
*.*-nodes             |
*.*-notes             |
*.*-conf              |
*.*-pv.conf           |
*.*-wiki-nodes        |
*.*-wiki.notes        |
*.*-nano-nodes        |
*.*-nano-notes        |
*.*-micro-nodes       |
*.*-micro-notes       |
*.*-needles-input     |
*.*-needles-output    |

----
NEXT STEP 
*.*-audio-nodes
*.*-audio-notes
*.*-gpu-nodes
*.*-gpu-notes
*.*-input-nodes
*.*-input-notes
*.*-camera-nodes
*.*-camera-notes
*.*-cpu-nodes
*.*-cpu-notes
*.*-mouse-nodes
*.*-mouse-notes
*.*-usb-nodes
*.*-ubs-notes

############################################################################################


Ich hab mich dazu entschieden das Pylovara kein $HOME Bastel Spielzeug werden 
soll und das das projekt eben nicht , nur bei bestimmten voraussetzungen installierbar bleibt

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
############################=-INWORK-=######################################

# *-nodes - *-notes system wird auf späterer sicht verfeinert , der  boden wird Mutter und Kind
# Komponenten darstellen .... danach wirds richtig finetuning *.-nano - *.-micro - *.-needles

# *.wiki.nodes - *.wiki.notes werden standartrisiert als direkter Projekt baum Überblick eingeführt,
# dadurch ermöglich es sich per direkt update funktion aus dem github repo die baustellenveränderungen
# wie auch daten veränderungen anzeigt , innerhalb der shell . Gut ansteuerbar mit allen Vim User oder
# nano wie cat user ..... der filemanager wird jedoch direkt mit dem repo verknüpft und alle updates
# erfolgen über git an der quelle (rolling-release) . Das abstellen von repo updates wird in zuckunft
# natürlich per note abstimmbar bleiben oder in der zentral Directory wo alle .pv-conf und .nonf rumliegen

WICHTIGER Schritt : Einen installer vorbereiten der nach dem der installer ausgeführt wird per sudo rechten
den gesamten ordner eins zu eins in das grundverzeichnis zero legt ..... von dort aus die ganzen datentypen 
aktivieren und einen bind garantieren der von der zentral Directory aus ,direkt in die gerade benutze umgebung
ob bash oder zsh , beides auf anhieb kompaktibel ....

Da alles auf bash basieren wird sollten alle bash basierten betriebsystemen in der lage sein per tty zugriff 
vor einem desktop schon per tty in der lage sein git zu installieren und das repo an zu zapfen git clone 

Es sollte auch problemlos mit FreeBSD kompaktibel sein oder mit Windows oder Darwin(macOS) zu harmonieren ....
Pylovara wird auf längerer sicht das bessere system bieten das den besten filemanager für ein gescheites 

- Bios - Gnu -Darwin -NT -Unix -Linux bootloader setup .... portabel .... besser ....
- Selbt ArchUser werden auf längerer sicht in Pylovara-FileManager-System rein installieren
- weil ihnen der umfang und die neue flexibilität schmackhafter scheint als Normal ....
- das system wäre durch *.*-notes in der lage auf jeder treiber komponente einen manualen schalt steuer
- einzustellen ..... 
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
