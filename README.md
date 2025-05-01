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
 















#
#
#
#
#
#
#


################################################################################

OLD Directory Readme


# Hyprland-Module Beta Version

Pylovara Since 2025© 
URL: https://github.com/Pylovara/Hyprland-Module/

---
Good question. Technically... it doesn’t.
But aesthetically – absolutely.

The Pylovara installer is designed for people who live in the terminal. 
People who compile in their sleep. People who consider /bin/bash a place of worship. 
If that’s you, you deserve an installation process that feels like a good old BBS 
prank meets Mr. Robot.

This absurd "pre-install phase" is just a boot-sequence parody for entertainment. 
No real spyware, porn databases, or Alcatraz-level SELinux settings are being 
installed (unless you already did that yourself – in which case: we salute you).

So relax, laugh, and enjoy the ride.
Once the joke is over, the real setup begins – fast, functional, and exactly 
what you'd expect from a FileManager built for terminal pros.

the 6-2025 installer ist the install but not for release , you can but not more ^^.
---



# ArbeitsProzess

---
# Next Update 

Kitty-freundliche für leichtgewichtiges Pylovara-Menüsystem :

    whiptail - für grundlegende Menüs (Yes/No, Listen, Multi-Auswahl).

    fzf      - für alles, was durchsucht/ausgewählt werden soll.

    gum      - optional & Stylisch einbauen, läuft Gut auch in Standart Kitty .

# Fast Fertig wird dann verfeinert :

PylovaraFileManager: wird mit einer eigenen erweiterten Suchfunktion ausgestattet (nicht im polyvara sondern pylovara.

| suche | Ordner | Datei | Function |
|:-----|:-------|:------|:---------|
| pylo | Download/- | MeinPic.png | shell |
| pylo | Musik/- | drumandbase.mp3 | shell |
| pylo | Home/- | .zshrc | shell |
| pylo | Download/- | lesezeug.txt | shell |

**extra:**

| suche | Ordner | Datei | Funktion |
|:-----|:-------|:------|:---------|
| pylo | Download/- | datei | cp (linux command/all + to ~/dev/root/) |

---

Die Funktionen werden nicht nur einfach gehalten, sondern werden als allgemeine Commands ausgeschmückt, z.B.: `cat`, `cp`, `rm` and all.  
Die vereinfachten Commands werden auf Logik aufgebaut für den allgemeinen Gebrauch.

---

**Ziel(LongTime):**  
Pylovara-FileManager später mit Framework zu kombinieren und damit auf Kernel-Ebene einzuordnen.  
Es wird damit verbunden einen eigenen verbesserten Linux-Zen Kernel geben, der auf Effizienz ausgelegt sein wird.  

---

# Download + Installation FileManager Modul   Demo Light Stable Version  RohIdea (polyvara is not pylovara) 

```bash
git clone https://github.com/Pylovara/Hyprland-Module.git
cd Hyprland-Module
chmod +x demosetup.sh
./demosetup.sh
```

# Kompaktibel ArchArchitectur in ErstenSchritt

- https://github.com/hyprwm/Hyprland
- https://github.com/mylinuxforwork/hyprland-starter (other: https://www.ml4w.com/)
- https://github.com/JaKooLit/Arch-Hyprland *(Achtung: `.zshrc` updaten! Source-Codes in `.zshrc` einfügen.)*

---

**Philosophie:**  
Das Repo wird keine Versionen haben, sondern nur den **Ist-Zustand** – 
ein nie vorbeigehender, unfertiger Zustand, der immer mehr ausgebaut wird.  

**Komplett Arch-Philosophie pur.**

Das Repo ist damit ein **permanenter Rolling-Release**ohne versions nummer.

Versionen werden in User Hände gelegt die sich die Arbeit machen das Repo 
irgendwo hochzuladen als Versionierung , hier selbst wird es das nicht geben.

---

Zur Info:  
Später wird es dann auch einen `yay`-Ansatz geben!

---

Dummer Spruch :

"Manchmal ist ein Update wie ein Ölwechsel – Pflicht, damit die Karre wieder rennt!" 🛠️🏎️
- Arch haut Kernel-Updates raus wie andere Leute WhatsApp-Nachrichten...
Rolling Release heißt hier echt: "Wart mal 'ne Woche nicht — und dein System ist Mittelalter!"
