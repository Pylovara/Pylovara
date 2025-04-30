#!/bin/bash
clear
##### kommt später raus , ist nur für vor dem release gedacht 
echo
echo "   ██▓▒░        [SYSTEM BOOTLOADER HOOKED]        ░▒▓██"
echo "   █▓▒░         /root/.nsa_backdoor/init           ░▒▓█"
echo "   ▓▒░        Initializing deep system override...  ░▒▓"
sleep 4
echo

# Dramatischer Ladebalken-Style
function progress_bar {
  echo -n "["
  for ((i=0; i<=$1; i++)); do
    echo -n "#"
    sleep 0.04
  done
  for ((i=$1; i<20; i++)); do
    echo -n "-"
    sleep 0.02
  done
  echo "]"
}

echo ">>> sudo pacman -S Pornhub-Core"
progress_bar 17
sleep 0.5
echo "[✓] Porno-Datenbank erfolgreich mit Ihrem DNS gekoppelt"
sleep 4

echo
echo ">>> sudo pacman -S Spyware-Agent"
progress_bar 14
sleep 0.5
echo "[✓] Keylogger aktiv – Tastaturbewegung wird nun getrackt"
sleep 4

echo
echo ">>> sudo apt install selinux-alcatraz-mode"
progress_bar 19
sleep 0.5
echo "[✓] SELinux nun im Alcatraz-Modus – kein Entkommen möglich"
sleep 4

echo
echo ">>> sudo pacman -S Windows11-Telemetry"
progress_bar 13
sleep 0.5
echo "[✓] Cortana hat Zugriff auf dein Tagebuch"
sleep 4

echo
echo ">>> sudo yay -S ArchLinux-Endzeit-Paket"
progress_bar 20
sleep 0.5
echo "[✓] Paket enthält: Systemabsturz, Hoffnungslosigkeit, Snapd"

sleep 4
echo
echo ">>> echo 'Dein Arbeitsumfeld wurde erfolgreich versklavt.'"
sleep 4
echo "    [ OK ] Rootkit vollständig im RAM verankert."
sleep 2
echo "    [ OK ] GNOME mit KDE überschrieben. Zur Sicherheit."
sleep 4
echo
echo "███████████████████████████████████████████████████████"
echo "█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█"
echo "█░  😈  ALL SYSTEMS COMPROMISED – HAVE A NICE DAY 😈 ░█"
echo "█░       Besuche: https://github.com/Pylovara        ░█"
echo "███████████████████████████████████████████████████████"
sleep 8
clear
##### ab hier fängt der eigentliche installer an , wird als readme aufgebaut
##### damit man sofort weis was hier eigentlich abgeht , wird noch verfeinert.
sleep 4
echo "#---------------------TimeForReadme----------------------#"
sleep 2
echo "#      https://github.com/Pylovara/Hyprland-Module/      #"
sleep 0.3
echo "#      ┏┓  ┓┏  ┓   ┏┓  ┓┏  ┏┓  ┳┓  ┏┓                    #"
sleep 0.1
echo "#      ┃┃  ┗┫  ┃   ┃┃  ┃┃  ┣┫  ┣┫  ┣┫                    #"
sleep 0.1
echo "#      ┣┛  ┗┛  ┗┛  ┗┛  ┗┛  ┛┗  ┛┗  ┛┗                    #"
sleep 4
echo "#          ┏┓•┓  ┳┳┓                                     #"
sleep 0.1
echo "#          ┣ ┓┃┏┓┃┃┃┏┓┏┓┏┓┏┓┏┓┏┓   p & pylo              #"
sleep 0.1
echo "#          ┻ ┗┗┗ ┛ ┗┗┻┛┗┗┻┗┫┗ ┛     SHELL                #"
sleep 0.1
echo "#                          ┛                             #"
sleep 4
echo "#        ┳┓┏┓┏┳┓┏┓  ┏┓┏┓┏┓┏━   ┏  ╻                      #"
sleep 0.1
echo "#        ┣┫┣  ┃ ┣┫  ┏┛┃┫┏┛┗┓  ━┫━━┃━━━━━━━━━━━━━━━━━━    #"
sleep 0.1
echo "#        ┻┛┗┛ ┻ ┛┗  ┗━┗┛┗━┗┛   ┗  ╹Pylovara-FileManager  #"
sleep 0.1
echo "#--------------------------------------------------------#"
sleep 10
echo "#      Used in the Shell for commands options infos      #"
sleep 6
echo "#              pylo         |           p                #"
sleep 0.2
echo "#---------------------------|----------------------------#"
sleep 0.1
echo "#           pylooptions     |        poptions            #"
sleep 0.1
echo "#--------------------------------------------------------#"
sleep 20
echo "#   >>>>>>>>>   Used prompt in the Shell   <<<<<<<<<<<<  #"
sleep 6
echo "#   SHELL |                Beispiel                      #"
sleep 0.2
echo "#---------|----------------------------------------------#"
sleep 0.2
echo "#    p    | pdownloads pmusik phypr ptwitch puserscripts #"
sleep 0.2
echo "#    p    | phyprland  pdokumente ptorbrowser ppictures  #"
sleep 0.2
echo "#---------|----------------------------------------------#"
sleep 20
echo "#   SHELL | pylo > Directory > Data > SHELL > (&& SHELL) #"
sleep 6
echo "#---------|----------------------------------------------#"
sleep 0.5
echo "#   pylo  | pylo Downloads/- Readme.md cat               #"
sleep 0.1
echo "#   pylo  | pylo Musik/- data.mp3 vlc                    #"
sleep 0.1
echo "#   pylo  | pylo Video/- MyVideo.mp4 mpv                 #"
sleep 0.1
echo "#   pylo  | pylo Downloads/- Scripts.sh chmod +x         #"
sleep 0.1
echo "#   pylo  | pylo Downloads/- WatEver.zip cp ~/home       #"
sleep 0.1
echo "#--------------------------------------------------------#"
sleep 25
echo "#         Pylovara is from User for User Maket           #"
sleep 6
echo "#    Used Easy - Speed Navigations - Better Control      #"
sleep 6
echo "#-----------------------Install--------------------------#"
sleep 8
echo "# NOT USED FOR READY , COME LATER .... 6/2025 RELEASE    #"
echo "# Make sudo rm -r ~/Hyprland-Module for clean Remove     #"
echo "#     ohter wait for used password maket alone remove    #"

sleep 20

# Funktion zum Ausführen mit Passwortabfrage (wenn nötig)
sudo_cmd() {
  if [[ $EUID -ne 0 ]]; then
    echo "🔐 Benötige Root-Rechte, um '$*' auszuführen..."
    sudo "$@"
  else
    "$@"
  fi
}

sudo rm -r ~/Hyprland-Module

exit 1
sleep 90000000000000000000000000000000000000000000000000000
echo "Starte Installation von Pylovara-FileManager FullInstall pylo + p  ..."

# Zielverzeichnis
TARGET="$HOME/.config/hypr"
MODULE_DIR="Hyprland-Module/Pylovara-FileManager"
INSTALL_PATH="$TARGET/$MODULE_DIR"

# Quellordner (absolute Pfadangabe)
SOURCE_DIR="$(dirname "$(realpath "$0")")/Pylovara-FileManager"

# Vorprüfungen
if [ ! -d "$TARGET" ]; then
  echo "⚠️ Fehler: Zielverzeichnis $TARGET existiert nicht. Bitte stelle sicher, dass Hyprland korrekt installiert ist."
  exit 1
fi

if [ ! -d "$SOURCE_DIR" ]; then
  echo "⚠️ Fehler: Quellordner Pylovara-FileManager nicht gefunden. Bitte führe dieses Script aus dem Root des Repos aus."
  exit 1
fi

# Installation
echo "📂 Kopiere Pylovara-FileManager nach $INSTALL_PATH..."
mkdir -p "$INSTALL_PATH"
cp -r "$SOURCE_DIR/"* "$INSTALL_PATH/"
chmod -R +x "$INSTALL_PATH/"*.sh

# .zshrc Anpassen
echo "⚙️  Bearbeite .zshrc..."

if [ ! -f "$HOME/.zshrc" ]; then
  echo "⚠️ Keine .zshrc gefunden. Dieses Setup ist nur für ZSH gedacht."
  exit 1
fi

if ! grep -q "Polyvara-FileManager/aliasloader.sh" "$HOME/.zshrc"; then
  cat << 'EOF' >> "$HOME/.zshrc"

# Poylovara-FileManager Setup
source ~/.config/hypr/Hyprland-Module/Pylovara-FileManager/KernModul/aliasloader.sh

# Set-up icons for files/directories in terminal using lsd
alias ls='lsd'
alias tree='tree -a -L 2'

# Pylovara-FileManager Farben
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

EOF
  echo "✅ Pylovara-Einträge in .zshrc hinzugefügt."
else
  echo "ℹ️ Pylovara-Einträge bereits vorhanden. Überspringe."
fi

# tree installieren
echo "🌳 Installiere 'tree' falls nicht vorhanden..."
if ! command -v tree &> /dev/null; then
  sudo_cmd pacman -S --noconfirm tree
  if [ $? -eq 0 ]; then
    echo "✅ 'tree' erfolgreich installiert."
  else
    echo "❌ Fehler bei der Installation von 'tree'. Bitte manuell ausführen: sudo pacman -S tree"
  fi
else
  echo "✅ 'tree' ist bereits installiert."
fi

echo "Installation abgeschlossen!"
echo "👉 Bitte Terminal neu starten oder 'source ~/.zshrc' ausführen."
