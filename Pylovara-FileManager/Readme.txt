pakete :

sudo pacman -S tree bc find crontab <--- nicht vergessen beim ./install.sh (vorsichtshalber)

Weisheit : 
"Erst denken, dann skripten — denn wer blind hackt, hackt doppelt!"
"Wer seine Struktur nicht versteht, hat sie nicht verdient."

Arbeitsverzeichnis (Root) ist:
~/.config/hypr/Hyprland-Module/Pylovara-FileManager/

    ExtraSearch → erstmal egal
    ExtraSystem → erstmal egal
    KernModul → da liegen die Grundfunktionen wie aliasloader.sh
    Search → hier liegen die ls.sh*-Skripte, die der Benutzer später per Alias aufrufen kann

Dateien KernModule   | Funktion
aliasloader.sh       | Lädt alle gültigen Skripte als Aliase
HeaderMaker.sh       | Erstellt den hübschen Header + optionalen Baum
update_ls-scripts.sh | Baut Skripte sauber um und hängt Fehlerprüfungen an
errorlog.sh          | Protokolliert jeden aufgetretenen Fehler + Status + Anzahl
clean_logs.sh        | Automatische Log-Säuberung, sauber, robust, idiotensicher , 7 Tage .
log_size_guard.sh    |	Löscht Logs automatisch, wenn sie >1,2MB groß werden.
Resultat             | Stabiles, modulares System. Kein wildes Durcheinander.


JedenTag Reinigen (idee):

crontab -e
0 3 * * * /bin/bash $HOME/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/clean_logs.sh >/dev/null 2>&1





