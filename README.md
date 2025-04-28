# Hyprland-Module Beta Version

#Pylovara Since 2025© https://github.com/Pylovara #
url : https://github.com/Pylovara/Hyprland-Module/

-----------------------------------------------------------------------------------

# Next Update

PolyvaraFileManager : wird mit einer eigenen erweiterten Suchfunktion ausgestattet .

suche  Ordner     Datei      Fucntion

suche Download/- MeinPic.png open

die funktionen werden nicht nur einfach gehalten sondern werden als allgemein commands ausgeschmückt z.b : cat, cp , rm and all 
die vereinfachten command werden auf logik aufgebaut für den allgemein gebrauch .

ziel : Pylovara-FileManager später mit einem verbessertem Terminal mit Framework zu kombinieren und damit auf Kernel ebene einzuordnen.
       Es wird damit verbunden einen eigenen verbesserten Linux-Zen Kernel geben der auf Effizienz ausgelegt sein wird .
       Der Kommende Kernel wird sich Linux-plv nennen : ausgelegt auf Wine/Portproton.ru/Waydroid/KVM/Flat/Docker/Native !

-------------------------------------------------------------------

### Installation 
```bash
git clone https://github.com/Pylovara/Hyprland-Module.git
cd Hyprland-Module
chmod +x setup.sh
chmod +x update.sh
./setup.sh
```

### Manual Updater
```bash
cd Hyprland-Module
./update.sh
```
------------------------------------------------------------------
# Kompaktibel
- https://github.com/hyprwm/Hyprland
- https://github.com/mylinuxforwork/hyprland-starter ohter https://www.ml4w.com/ 
- https://github.com/JaKooLit/Arch-Hyprland # but you must by .zshrc update .zshrc_backend the source codes copie in .zshrc make !! 
------------------------------------------------------------------
Hardcore updater.sh !!!!!!!!!!!!!!!

Aus folgendem Grund:
Ich schreibe das Repo per Hand und arbeite direkt im Browser, daher gibt es keine Git-Ordner-Daten oder Commits lokal. Dadurch bekommt der heruntergeladene User keine Git-Ordner-Daten, und wenn der Ordner bereits vorhanden ist, gibt es nur Fehlermeldungen.

Aus diesem Grund wird der updater.sh **HARDCORE** alles überschreiben.

Was auch sinnvoll ist, weil:
Ich muss oft Daten umschreiben oder verbessern, und viele Dateien sind zwar da, aber im Code falsch. Um das mittelfristig komplett zu eliminieren, muss der Updater die Daten radikal überschreiben.

Dadurch wird auch sichergestellt, dass es keine Forks geben kann, die sich am Original bedienen. Forks müssen viele manuelle Pfade umschreiben, um wirklich autark zu agieren.

Das Repo wird keine Versionen haben, sondern nur den **Ist-Zustand** – ein nie vorbeigehender, unfertiger Zustand, der immer mehr ausgebaut wird. **Komplett Arch-Philosophie pur**.

Das Repo ist damit ein **permanenter Rolling-Release**.

zur info : Später wird es dann auch einen yay ansatz geben
