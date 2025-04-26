# Hyprland/Arch Linux Fix Modules
# Pylovara Since 2025© https://github.com/Pylovara
# https://github.com/Pylovara/Hyprland-Module/

This repository contains a set of Bash scripts designed to diagnose and fix common issues in Arch Linux systems, particularly those related to Hyprland, Xorg, networking, sound, and Broadcom Wi-Fi.

## Modules Overview

The scripts are organized into individual modules, each addressing a specific area of potential problems.

-   **`module.sh`**: The main script that orchestrates the execution of other fix modules in a predefined sequence.
-   **`netzwerk-fix.sh`**:  A comprehensive network repair script that handles Broadcom Wi-Fi, `rfkill` blocking, network tools installation, and service management.
-   **`broadcom-fix.sh`**: Specifically targets Broadcom Wi-Fi issues by installing drivers and resolving conflicts.
-   **`sound-fix.sh`**:  Focuses on troubleshooting PipeWire/ALSA sound problems, including service restarts, (re)installation, and volume settings.
-   **`xorg-fix.sh`**:  Aimed at fixing display/monitor issues in both Xorg and Wayland/Hyprland environments.
-   **`repair-all.sh`**:  A universal repair script that sequentially runs the relevant fix scripts based on system detection.

## Module Details

### `module.sh`

This is the primary entry point for applying multiple fixes. It executes the other scripts in the following order:

1.  **Network Fix**:  `netzwerk-fix.sh`
2.  **Broadcom Fix (Optional)**: `broadcom-fix.sh` (only if a Broadcom Wi-Fi adapter is detected)
3.  **Sound Fix**: `sound-fix.sh`
4.  **Xorg Fix**: `xorg-fix.sh`
5.  **Universal Repair**: `repair-all.sh`

### `netzwerk-fix.sh`

This script performs the following actions:

1.  **Broadcom Check/Fix**:
    * Detects Broadcom Wi-Fi adapters.
    * Installs DKMS and kernel headers.
    * Installs `broadcom-wl-dkms` from the AUR.
    * Removes conflicting kernel modules.
    * Loads the `wl` module.
2.  **`rfkill` Unblock**: Unblocks all devices using `rfkill`.
3.  **Network Tools**: Ensures `iproute2`, `iw`, and `networkmanager` are installed.
4.  **NetworkManager Service**: Enables and starts the `NetworkManager` service.
5.  **IP Link Information**: Displays active network interfaces.
6.  **Wi-Fi Scan**: Lists available Wi-Fi networks (if `nmcli` is available).

### `broadcom-fix.sh`

This script specifically addresses Broadcom Wi-Fi issues:

1.  **Device Detection**: Checks for a Broadcom Wi-Fi adapter.
2.  **DKMS and Headers**: Installs DKMS and kernel headers.
3.  **Package Management**: Removes any existing `broadcom-wl` packages and installs `broadcom-wl-dkms` from the AUR.
4.  **Module Handling**: Removes conflicting kernel modules and loads the `wl` module.
5.  **NetworkManager Restart**: Restarts NetworkManager.

### `sound-fix.sh`

This script troubleshoots sound-related problems:

1.  **PipeWire Check**: Checks if PipeWire is running and attempts to start it if it isn't.
2.  **PipeWire Installation**:  Reinstalls PipeWire and related packages if the service fails to start.
3.  **ALSA Check**: Ensures `alsa-utils` is installed.
4.  **Volume Adjustment**: Sets the master volume to 80%.
5.  **Sound Test**:  Performs a quick sound test.

### `xorg-fix.sh`

This script diagnoses and attempts to fix display/monitor issues:

1.  **Monitor Detection**: Checks if a monitor is detected using `xrandr`.
2.  **Display Server Restart**:  Attempts to restart the display server (Wayland/Hyprland or Xorg) if no monitor is detected.
    * For Wayland, it checks and restarts Hyprland.
    * For Xorg, it checks for and uses `~/.xinitrc` to start Xorg.
3.  **GPU Detection**:  Identifies the active GPU.
4.  **Mesa/DRM Check**:  Verifies the installation of Mesa and the presence of DRM modules.
5.  **Mesa/DRM Reinstallation (Optional)**:  Prompts the user to reinstall Mesa and related drivers.

### `repair-all.sh`

This script acts as a universal repair tool:

1.  **Broadcom Repair**:  Runs `broadcom-fix.sh` if a Broadcom adapter is detected.
2.  **Network Repair**:  Runs `netzwerk-fix.sh`.
3.  **Sound Repair**:  Runs `sound-fix.sh` if PipeWire is detected.
4.  **Xorg Repair**:  Runs `xorg-fix.sh` if no Xorg display is detected.
5.  **Status Checks**: Provides status messages for each repair step.

## Prerequisites

-   Arch Linux installed
-   `sudo` privileges
-   Internet connection (for package installation)
-   AUR helper (e.g., `yay`) for Broadcom driver installation

## Usage

1.  **Clone the repository:**

    ```bash
    git clone https://github.com/Pylovara/Hyprland-Module/FixModule.git
    cd ~/Pylovara/Hyprland-Module/FixModule
    chmod +x 00-module.sh
    ./00-module.sh
    ```

## Important Notes

-   **Broadcom Wi-Fi**: The Broadcom fix requires an AUR helper like `yay`. Ensure you have one installed.
-   **Xorg/Wayland**: The Xorg fix attempts to handle both X11 and Wayland (specifically Hyprland).
-   **Dependencies**:  The scripts install necessary packages (e.g., `iproute2`, `networkmanager`, `alsa-utils`, `mesa`).
-   **Caution**:  These scripts perform system-level changes. Use them with caution and understand the potential impact.

## Contributing

Feel free to contribute to this project by submitting issues or pull requests.
