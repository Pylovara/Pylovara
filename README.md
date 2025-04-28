# Hyprland-Module Beta Version

# Pylovara Since 2025© https://github.com/Pylovara

URL: https://github.com/Pylovara/Hyprland-Module/

---

# Next Update in Work

PolyvaraFileManager: wird mit einer eigenen erweiterten Suchfunktion ausgestattet.

| suche | Ordner | Datei | Function |
|:-----|:-------|:------|:---------|
| suche | Download/- | MeinPic.png | open (Browser/youpicopner) |
| suche | Musik/- | drumandbase.mp3 | open (vlc/yourprimärer Player) |
| suche | Home/- | .zshrc | open (nano/vim/neovim/etc) |
| suche | Download/- | lesezeug.txt | open (cat/pdf/office/ide/etc) |

**extra:**

| suche | Ordner | Datei | Funktion |
|:-----|:-------|:------|:---------|
| suche | Download/- | datei | cp (linux command/all + to ~/dev/root/) |

---

Die Funktionen werden nicht nur einfach gehalten, sondern werden als allgemeine Commands ausgeschmückt, z.B.: `cat`, `cp`, `rm` and all.  
Die vereinfachten Commands werden auf Logik aufgebaut für den allgemeinen Gebrauch.

---

**Ziel:**  
Pylovara-FileManager später mit einem verbesserten Terminal mit Framework zu kombinieren und damit auf Kernel-Ebene einzuordnen.  
Es wird damit verbunden einen eigenen verbesserten Linux-Zen Kernel geben, der auf Effizienz ausgelegt sein wird.  
Der kommende Kernel wird sich **Linux-plv** nennen:  
Ausgelegt auf Wine / Portproton.ru / Waydroid / KVM / Flat / Docker / Native!

---

# Installation FileManager Modul

```bash
git clone https://github.com/Pylovara/Hyprland-Module.git
cd Hyprland-Module
chmod +x setup.sh
chmod +x update.sh
./setup.sh
```

---

# Manual Updater Repo Updater AllInOne

```bash
cd Hyprland-Module
./update.sh
```

---

# Kompaktibel ArchArchitectur 

- https://github.com/hyprwm/Hyprland
- https://github.com/mylinuxforwork/hyprland-starter (other: https://www.ml4w.com/)
- https://github.com/JaKooLit/Arch-Hyprland *(Achtung: `.zshrc` updaten! Source-Codes in `.zshrc` einfügen.)*

---

# Hardcore updater.sh !!!!!!!!!!!!!!!

Aus folgendem Grund:  
Ich schreibe das Repo per Hand und arbeite direkt im Browser, daher gibt es keine Git-Ordner-Daten oder Commits lokal.  
Dadurch bekommt der heruntergeladene User keine Git-Ordner-Daten, und wenn der Ordner bereits vorhanden ist, gibt es nur Fehlermeldungen.

---

**Warum Hardcore:**  
Ich muss oft Daten umschreiben oder verbessern, und viele Dateien sind zwar da, aber im Code falsch.  
Um das mittelfristig komplett zu eliminieren, muss der Updater die Daten radikal überschreiben.

Dadurch wird sichergestellt, dass es keine Forks geben kann, die sich am Original bedienen.  
Forks müssen viele manuelle Pfade umschreiben, um wirklich autark zu agieren.

---

**Philosophie:**  
Das Repo wird keine Versionen haben, sondern nur den **Ist-Zustand** – 
ein nie vorbeigehender, unfertiger Zustand, der immer mehr ausgebaut wird.  

**Komplett Arch-Philosophie pur.**

Das Repo ist damit ein **permanenter Rolling-Release**.

---

Zur Info:  
Später wird es dann auch einen `yay`-Ansatz geben!

