# Polyvara FileManager

Der Polyvara FileManager ist ein eigenständiges, hochmodulares und vollständig selbst erweiterbares Dateisystem, das sich an den Grundprinzipien einer Shell orientiert und Daten explizit in einer Baumstruktur auslesen kann.

## Funktionsweise

Die Suche nach ausführbaren Dateinamen erfolgt nach einem bestimmten Muster:

* `p + vlc`  sucht nach dem Ordner "vlc". (p = polyvara)
* `-pvlc` sucht nach dem gesamten Inhalt des Ordners "vlc".
* dies gilt nur bei kritischen syntax problemen | desktop | kernel | ausführbare exe/rpm/tz/dmg/flat/snap etc..

Das Prinzip des MODULES basiert auf sichtbaren Strukturen und dient in seiner Kernfunktion als Schnellsuchwerkzeug.

## Zukünftige Entwicklung

Der Polyvara File Manager wird in Zukunft mit einer erweiterbaren Datensuchfunktion ausgestattet, die Suchen und Ausführen kombiniert. Diese Funktion wird sich von einer herkömmlichen Terminaleingabe unterscheiden. Die Entwicklung dieser Funktion ist jedoch noch nicht abgeschlossen und ist derzeit nicht im Polyvara-FileManager enthalten.

## Updates

Dieses Modul wird regelmäßig aktualisiert, basierend auf meinen aktuellen Anforderungen. Fehlende Ordner werden bei einer Issue-Meldung priorisiert und zeitnah implementiert.

Die automatische Update-Funktion ist derzeit noch nicht vollständig implementiert. Bitte überprüfen Sie das Repository regelmäßig manuell, um die neuesten Erweiterungen zu erhalten.

## Implementierung

### Installation

Derzeit ist noch kein Skript vorhanden, das alle Daten ausführbar macht und den Polyvara-Ordner automatisch in den richtigen Hyprland-Ordner verschiebt. Der empfohlene Speicherort für den Polyvara-FileManager ist `/home/User/.config/hypr/`.

### Integration

Der Polyvara-FileManager ist für die Verwendung durch Sourcing konzipiert. In einer Hyprland-Umgebung mit zsh wird er typischerweise in die `.zshrc`-Datei im Benutzerverzeichnis integriert (dort, wo sich auch die `.bashrc` befindet).

```bash
# If you come from bash you might have to change your $PATH.
# export PATH=$HOME/bin:/usr/local/bin:$PATH

# Source Polyvara-FileManager (Hauptdatei):
source ~/.config/hypr/aliasloader.sh  # <------ Herzstück

# Set-up icons for files/directories in terminal using lsd
alias ls='lsd'
alias l='ls -l'
alias la='ls -a'
alias lla='ls -la'
alias tree='tree -a -L 2'  # <----- sudo pacman -S tree und das als alias setzen.

# Polyvara-FileManager Farben (anpassbar)
export LS_COLORS="\
di=1;37:\
fi=0;37:\
ln=0;97:\
ex=1;97:\
*.sh=1;97:\
*.py=1;97:\
*.mp4=0;37:\
*.mkv=0;37:\
*.png=0;37:\
*.jpg=0;37:\
*.jpeg=0;37:\
*.zip=0;37:\
*.tar=0;37:\
*.gz=0;37:\
*.iso=0;37:"
