Der Polyvara FileManager fungiert als eigenständiges , hochmodulares und 100% selbst erweiterbares Filesystem 
das sich an den grundprinzipien einer Shell orientiert und daten explizit in einer baum struktur auslesen kann.

Zur Info : ausführbare datennamen werden grundsätzlich mit einem s gesucht beispiel : s + vlc = ordner - svlc = ordnergesamt

das prinzip des MODULES beruht auf sichbare strukturen und ist in der kern funktion ein schnellsuch tool .....

Der Polyvara File Manager wird im späteren verlauf mit einer Erweiterbaren datensuche ausgestattet die das suchen und ausführen
kombiniert und sich etwas anders anfühlen wird als eine normale terminal eingabe , dies steht aber noch in der entwicklung und
ist noch nicht vollständig bestimmt und befindet sich zurzeit noch nicht im Polyvara-FileManager ....

Dieses Modult wird ständig geupdatet , je nach dem was mir selbst in die finger gerät , ordner die noch nicht existieren 
werden bei einer Issue gerne berücksichtig in der bearbeitung vorgezogen und vollständig omplenetiert 

Die selbstständige update funktion existiert derzeit noch nicht vollständig daher sollte man Manual in das Repo schauen um 
die neuesten erweiterungen zu bekommen ..... 


wie wird es Implementiert nach dem runterladen ?

zur zeit wurde noch kein script geschrieben das alle daten ausführbar macht und den Polyvara ordner in Hyprland in 
den richtigen Ordner rein Läd ..... der Richtige Ordner zur zeit für Polyvara wäre der /home/User/.config/hypr/ ordner.

Der Polyvara-FileManager ist so Konzipiert das er lediglich Gesourced werden muss , da wir zu anfang mit Hyprland und .zshrc
arbeiten ist es also die .zshrc die sich auch im User Ordner befindet , wo auch die allgemeine .bashrc existiert 


# If you come from bash you might have to change your $PATH.
# export PATH=$HOME/bin:/usr/local/bin:$PATH

#Source Polyvara-FileManager :
source ~/.config/hypr/Polyvara-FileManager/aliasloader.sh #<------ HerzStück

# Set-up icons for files/directories in terminal using lsd
alias ls='lsd'
alias l='ls -l'
alias la='ls -a'
alias lla='ls -la'
alias tree='tree -a -L 2' # <----- sudo pacman -S tree und das als alias setzen .

# Polyvara-FileManager Colors (individualisierbar)
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

Weitere Informationen findet ihr zum Projekt im :

- Arbeitsblatt.txt
https://github.com/Pylovara/Hyprland-Module/blob/main/Polyvara-FileManager/arbeitsblatt.txt

Vorhandene Implementierungen hier :
- Polyvara-FileManager/Polyvara-FileManager-Course.txt
https://github.com/Pylovara/Hyprland-Module/blob/main/Polyvara-FileManager/Polyvara-FileManager-Course.txt
