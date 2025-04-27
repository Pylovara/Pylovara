#!/bin/bash
#Pylovara Since 2025© https://github.com/Pylovara #
#https://github.com/Pylovara/Hyprland-Module/CleanUPModule

cleansystem() {
    echo "🧹 Starting system cleanup..."
    # Pre-fetch sudo password
    sudo -v
    # Clear pacman cache
    sudo pacman -Sc --noconfirm 2>/dev/null &&
    echo "✔ Pacman cache cleaned" || echo "⚠ Pacman cache clean failed (ignored)"
    # Clear yay cache
    yay -Sc --noconfirm 2>/dev/null &&
    echo "✔ Yay cache cleaned" || echo "⚠ Yay cache clean failed (ignored)"
    # Remove orphaned packages
    sudo pacman -Rns $(pacman -Qtdq 2>/dev/null) 2>/dev/null &&
    echo "✔ Orphaned packages removed" || echo "⚠ No orphaned packages found"
    # Vacuum old journal logs
    sudo journalctl --vacuum-time=2weeks 2>/dev/null &&
    echo "✔ Logs older than 2 weeks removed"
    # Clear /tmp
    rm -rf /tmp/* 2>/dev/null && echo "✔ /tmp folder cleaned"
    echo "✨ System cleanup complete!"
}

clearram() {
    echo "🧠 Optimizing RAM..."
    sudo sync && sudo sysctl -w vm.drop_caches=3 &&
    echo "✔ RAM cache cleared"
    free -h | grep Mem && echo "Current RAM status"
}

recordsession() {
    if [ -z "$1" ]; then
        echo "Please provide a filename! Example: recordsession terminal.txt"
        return 1
    fi
    script ~/Downloads/"$1"
}
