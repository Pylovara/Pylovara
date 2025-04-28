Hyprland-Module Beta Version

Pylovara Since 2025©
GitHub: Pylovara
Repo-URL: Hyprland-Module
Next Update in Work

PolyvaraFileManager wird mit einer eigenen erweiterten Suchfunktion ausgestattet:
Suche	Ordner	Datei	Funktion
suche	Download/	MeinPic.png	open (Browser / youpicopener)
suche	Musik/	drumandbase.mp3	open (VLC / Primärer Player)
suche	Home/	.zshrc	open (nano / vim / neovim / etc.)
suche	Download/	lesezeug.txt	open (cat / pdf / office / IDE / etc.)

Extra Funktionen:
Suche	Ordner	Datei	Funktion
suche	Download/	datei	cp (Linux Command, z.B. cp nach ~/dev/root/)

Die Funktionen werden nicht nur einfach gehalten, sondern als allgemeine Commands ausgeschmückt:
z.B. cat, cp, rm und viele mehr.
Die vereinfachten Commands basieren auf logischer Struktur für den allgemeinen Gebrauch.

Ziel:
Den Pylovara-FileManager später mit einem verbesserten Terminal + Framework zu kombinieren,
und so auf Kernel-Ebene zu integrieren.

    Geplanter Kernel-Name: Linux-plv

    Ausgelegt auf: Wine / PortProton.ru / Waydroid / KVM / Flatpak / Docker / Native Apps

    Fokus: Effizienz und Performance

Installation

git clone https://github.com/Pylovara/Hyprland-Module.git
cd Hyprland-Module
chmod +x setup.sh
chmod +x update.sh
./setup.sh

Manual Updater

cd Hyprland-Module
./update.sh

Kompatible Architekturen / Umgebungen

    Hyprland

    Hyprland-Starter ML4W (Website)

    JaKooLit Arch-Hyprland
    (Achtung: .zshrc muss aktualisiert werden! Source-Codes aus .zshrc_backend manuell in .zshrc einfügen.)

Hardcore updater.sh

Warum so extrem?

    Ich schreibe das Repo direkt im Browser – daher gibt es keine Git-Ordner oder lokale Commits.

    Dadurch erhält der User beim Download keine Git-Daten, sondern nur den Ordnerinhalt.

    Wenn der Ordner schon existiert, entstehen sonst Fehler.

Deshalb überschreibt updater.sh radikal alles!
Vorteile davon:

    Alte/falsche Daten werden vollständig ersetzt.

    Forks können sich nicht einfach am Original bedienen – sie müssen vieles manuell anpassen.

    Keine klassischen Releases, sondern nur den aktuellen Zustand (Arch-Style).

Kurz gesagt:
👉 Dieses Repo ist ein permanenter Rolling-Release!

    Hinweis:
    Zukünftig wird es zusätzlich einen yay-Ansatz geben.
