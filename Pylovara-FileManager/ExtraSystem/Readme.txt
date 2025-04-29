Ziel (in alter Admin-Sprache):

    pylo wird ein universelles Kommando.

    Es soll:

        Ordner erkennen, Dateien erkennen, eigenständig den Pfad fixieren.

        Wenn ein Ordner eingegeben wird (mit /–), soll pylo intern wissen, dass es aus diesem Ordner heraus weiterarbeiten soll, OHNE reinzuwechseln (cd unnötig).

        Dateinamen und Folgebefehle (z.B. vlc) sollen ganz normal der Shell übergeben werden, nachdem pylo den richtigen Ort kennt.

    Der erste Bindestrich - nach dem Ordner zeigt an: Hier fixieren!

    Danach sollen normale Kommandos möglich bleiben: Dateiname + Befehl.

    ExtraSystem/ wird der technische Ort sein, wo die „Magie“ von pylo wohnt.

Übersetzt in Aufgaben:
Bereich	Funktion
pylo	universelle Eingabe
Downloads/-	Ordnerpfad wird fixiert, aber nicht gewechselt
Dateiname	Datei innerhalb dieses Ordners suchen
Programm	(optional) diese Datei direkt mit Programm öffnen (z.B. vlc, nano, cat)
ExtraSystem/	Hier liegt das pylo-„Hirn“ (Such- und Verarbeitungslogik)


Was pylo tun muss (ganz klassisch gedacht):

    Erkennen:

        Wurde ein Ordner angegeben mit /-?

        Wenn ja: Pfad merken.

    Nachfolge erkennen:

        Kommt danach ein Dateiname?

        Kommt danach ein Befehl?

    Aktion ausführen:

        Wenn nur Dateiname: nur Pfad + Dateiname anzeigen oder prüfen.

        Wenn Dateiname + Befehl: Datei direkt an das Programm übergeben.

    Robust sein:

        Fehlerbehandlung: Existiert Ordner? Existiert Datei?

        Schöne Ausgabe: [ OK ], [ ERROR ] etc.

Beispiel für den pylo Ablauf
Eingabe:

pylo Musik/- drums.mp3 vlc

Ablauf:

    Erkennt Musik/ als existierenden Ordner (über find oder statische Pfade, Home als Basis).

    Erkennt drums.mp3 in diesem Ordner.

    Übergibt die Datei an vlc:

vlc /home/username/Musik/drums.mp3

→ Ohne dass du je ein cd machen musst!
(und ohne dass der Benutzer sich Gedanken macht, wo er gerade "steht") Strukturvorschlag:
Datei	Funktion
ExtraSystem/pylo.sh	Hauptprogramm, prüft und verarbeitet Eingaben
ExtraSystem/pylo_helper.sh	Helferfunktionen wie "Existiert Ordner?", "Existiert Datei?", "Schöne Ausgabe"
(optional später)	Erweiterungen wie Vorschläge, Autovervollständigung
