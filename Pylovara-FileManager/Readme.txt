pakete :

sudo pacman -S tree bc find <--- nicht vergessen beim ./install.sh (vorsichtshalber)

Weisheit : 
"Erst denken, dann skripten — denn wer blind hackt, hackt doppelt!"
"Wer seine Struktur nicht versteht, hat sie nicht verdient."

Arbeitsverzeichnis (Root) ist:
~/.config/hypr/Hyprland-Module/Pylovara-FileManager/

    ExtraSearch → erstmal egal
    ExtraSystem → erstmal egal
    KernModul → da liegen die Grundfunktionen wie aliasloader.sh
    Search → hier liegen die ls.sh*-Skripte, die der Benutzer später per Alias aufrufen kann

Fakt                 | Erklärung
Alias                | Führt externes Skript aus, neues Environment.
source in zshrc      | Hilft nur den Aliassen, nicht den Skripten selbst.
source im Skript     | Unbedingt nötig, damit Funktionen wie show_header bekannt sind.
update_ls-scripts.sh | Saubere Pflichtarbeit: überall source HeaderMaker.sh vorne rein, wenn fehlt.
Resultat             | Stabiles, modulares System. Kein wildes Durcheinander.


Dateien KernModule   | Funktion
aliasloader.sh       | Lädt alle gültigen Skripte als Aliase
HeaderMaker.sh       | Erstellt den hübschen Header + optionalen Baum
update_ls-scripts.sh | Baut Skripte sauber um und hängt Fehlerprüfungen an
errorlog.sh          | Protokolliert jeden aufgetretenen Fehler







