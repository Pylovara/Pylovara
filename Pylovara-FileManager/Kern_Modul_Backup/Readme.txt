# Dev Level KernModule Manual 
# Notfallplan bei Komplett-Crash

Schritt                             | Vorteil
Backup-Ordner KernModul_Backup      | Immer frische Kopie griffbereit
Restore-Skript                      | 1-Klick-Wiederherstellung bei Problemen

Info:
Ruhig bleiben Fehler passieren, Recovery läuft

---

#!/bin/bash
# AbsuluterPfad
# Hyprland-Module/Pylovara-FileManager/restore_kernmodule.sh:
# Stellt alle KernModule aus dem Backup wieder her

echo "⏳ Wiederherstellung läuft..."

cp ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul_Backup/*.sh ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/

chmod +x ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/*.sh

echo "[ OK ] Kernmodule erfolgreich wiederhergestellt."

---

Direct :

bash ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/restore_kernmodule.sh
