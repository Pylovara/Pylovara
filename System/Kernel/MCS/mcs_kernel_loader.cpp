// =================================================================
// MCS 2.7 KERNEL LOADER (C++ NATIVE IMPLEMENTATION)
// ZWECK: Liest die MCS 2.7 Syntax und routet den Befehl im Blanker Nenner
//        an das korrekte Zielsystem (SYSTEM, HYPRLAND, BASH).
// =================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

// Definierte MCS-Symbole (V2.7)
namespace MCS_SYMBOLS {
    const std::string TRANSAKTION_START       = "¢!";
    const std::string TRANSAKTION_ENDE        = "!¢";
    const std::string AKTION_START            = "»";
    const std::string AKTION_ENDE             = "«";
    // Die folgenden Symbole dienen der Syntax-Definition, der Inhalt wird jedoch im Blanker Nenner gekapselt.
    const std::string PROTEIN_ANFANG          = "[";
    const std::string PROTEIN_ENDE            = "]";
    const std::string PROTON_ANFANG           = "{";
    const std::string PROTON_ENDE             = "}";
    const std::string BLANKER_NENNER_CMD_START = "¨";
    const std::string BLANKER_NENNER_CMD_ENDE   = "¨"; // Korrigiert: Groß- und Kleinschreibung war entscheidend.
    const std::string TRENNBEFEHL             = "|";
    const std::string MCS_HYPR_CMD_START      = "’"; // Hyprland Composer Befehl Start
    const std::string MCS_HYPR_CMD_END        = "’"; // Hyprland Composer Befehl Ende

    // Standard Befehle innerhalb des Blanker Nenners
    const std::string BASH_CMD_START          = "¨"; // Shell Befehl Start
    const std::string BASH_CMD_END            = "¨"; // Shell Befehl Ende
    const std::string HYPR_CMD_START          = "’"; // Hyprland Befehl Start
    const std::string HYPR_CMD_END            = "’"; // Hyprland Befehl Ende
    const std::string SYSTEM_CMD_START        = "’"; // System / Kernel Befehl Start (Fehler: War ' vorhin)
    const std::string SYSTEM_CMD_END          = "’"; // System / Kernel Befehl Ende (Fehler: War ' vorhin)

    // Weitere Hilfssymbole
    const std::string KOMMENTAR               = "#";
}

/**
 * @brief Extrahiert den Kommando-Typ und den Inhalt aus einer MCS-Aktionszeile.
 *
 * Die Funktion sucht nach der Struktur: »['TYPE'|¨INHALT¨]«
 *
 * @param action_line Die zu parsenden MCS-Zeile.
 * @param command_type Der extrahierte Kommando-Typ (z.B. BASH_CMD).
 * @param command_content Der extrahierte Kommando-Inhalt.
 * @return true, wenn das Parsen erfolgreich war, false sonst.
 */
bool parse_mcs_action(const std::string& action_line, std::string& command_type, std::string& command_content) {
    using namespace MCS_SYMBOLS;

    // Suche nach dem Anfang der Aktion: »['
    size_t start_type = action_line.find(AKTION_START + PROTEIN_ANFANG);
    if (start_type == std::string::npos) return false;
    start_type += (AKTION_START + PROTEIN_ANFANG).length();

    // Suche nach dem Ende des Typs: '
    size_t end_type = action_line.find("'", start_type);
    if (end_type == std::string::npos) return false;

    // Extrahiere den Kommando-Typ (z.B. BASH_CMD)
    command_type = action_line.substr(start_type, end_type - start_type);

    // Springe hinter: '|¨
    size_t start_content = action_line.find(TRENNBEFEHL + BLANKER_NENNER_CMD_START, end_type);
    if (start_content == std::string::npos) return false;
    start_content += (TRENNBEFEHL + BLANKER_NENNER_CMD_START).length();

    // Suche nach dem Ende des Inhalts: ¨]«
    size_t end_content = action_line.find(BLANKER_NENNER_CMD_ENDE + PROTEIN_ENDE + AKTION_ENDE, start_content);
    if (end_content == std::string::npos) return false;

    // Extrahiere den Kommando-Inhalt
    command_content = action_line.substr(start_content, end_content - start_content);

    return true;
}

/**
 * @brief Simuliert die Kernel-Verarbeitung basierend auf dem MCS-Aktionstyp.
 *
 * @param type Der MCS-Aktionstyp (z.B. BASH_CMD, HYPR_CMD, SYSTEM_CMD).
 * @param content Der Inhalt des Befehls (Payload).
 */
void execute_mcs_action(const std::string& type, const std::string& content) {
    if (type == "BASH_CMD") {
        std::cout << "[KERNEL_ROUTE: BASH] Ausführen: " << content << std::endl;
        // In einem echten System würde hier 'system(content.c_str());' oder
        // ein popen() Aufruf zur Shell-Ausführung stehen.
    } else if (type == "HYPR_CMD") {
        std::cout << "[KERNEL_ROUTE: HYPR] Senden an Compositor: " << content << std::endl;
        // In einem echten System würde hier eine IPC-Kommunikation
        // (z.B. Socket) zum Hyprland Compositor erfolgen.
    } else if (type == "SYSTEM_CMD") {
        std::cout << "[KERNEL_ROUTE: SYSTEM] Kernel-Aktion ausgelöst: " << content << std::endl;
        // Hier würden interne, privilegierte Kernel-Funktionen aufgerufen.
    } else {
        std::cerr << "[KERNEL_ERROR] Unbekannter MCS-Typ gefunden: " << type << std::endl;
    }
}


/**
 * @brief Lädt und parst eine MCS-Datei zeilenweise.
 *
 * @param filename Der Pfad zur MCS-Datei.
 */
void load_and_parse_mcs(const std::string& filename) {
    using namespace MCS_SYMBOLS;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[KERNEL_ERROR] Fehler: Konnte Datei '" << filename << "' nicht öffnen." << std::endl;
        return;
    }

    std::cout << "--- MCS 2.7 LOADER START: Parsing '" << filename << "' ---" << std::endl;
    std::string line;
    bool in_transaction = false;

    while (std::getline(file, line)) {
        // Entferne führende/nachfolgende Leerzeichen
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

        // Überspringe Kommentare und leere Zeilen
        if (line.empty() || line.rfind(KOMMENTAR, 0) == 0) continue;

        if (line.rfind(TRANSAKTION_START, 0) == 0) {
            in_transaction = true;
            std::cout << "[MCS_TRANS_START] Transaktion begonnen." << std::endl;
            continue;
        }

        if (line.rfind(TRANSAKTION_ENDE, 0) == 0) {
            in_transaction = false;
            std::cout << "[MCS_TRANS_END] Transaktion abgeschlossen." << std::endl;
            continue;
        }

        if (in_transaction && line.rfind(AKTION_START, 0) == 0) {
            std::string type, content;
            if (parse_mcs_action(line, type, content)) {
                execute_mcs_action(type, content);
            } else {
                std::cerr << "[KERNEL_ERROR] Syntax-Fehler in MCS-Aktion: " << line << std::endl;
            }
        }
    }
    std::cout << "--- MCS 2.7 LOADER END: Parsing abgeschlossen ---" << std::endl;
    file.close();
}

/**
 * @brief Erstellt eine simulierte MCS-Datei für den Testbetrieb.
 *
 * @param filename Der Name der zu erstellenden Datei.
 */
void create_simulation_file(const std::string& filename) {
    using namespace MCS_SYMBOLS;
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "[SETUP_ERROR] Konnte Simulationsdatei nicht erstellen." << std::endl;
        return;
    }

    file << KOMMENTAR << " Simuliertes Pylovara Start-Skript für Testzwecke" << std::endl;
    file << KOMMENTAR << " Diese Datei wird geladen durch: mcs_loader " << filename << std::endl;
    file << "\n";

    // 1. BASH_CMD (Shell-Befehl)
    file << KOMMENTAR << " Shell-Befehl (BASH_CMD)" << std::endl;
    file << TRANSAKTION_START << std::endl;
    file << "»['BASH_CMD'|" << BLANKER_NENNER_CMD_START << "$HOME/.config/hypr/initial-boot.sh" << BLANKER_NENNER_CMD_ENDE << "]«" << std::endl;
    file << TRANSAKTION_ENDE << std::endl;

    // 2. HYPR_CMD (Tastenbindung/HPTCTL)
    file << "\n" << KOMMENTAR << " Hyprland Composer Befehl (HYPR_CMD)" << std::endl;
    file << TRANSAKTION_START << std::endl;
    file << "»['HYPR_CMD'|" << BLANKER_NENNER_CMD_START << "bind=ALT, RETURN, exec, alacritty" << BLANKER_NENNER_CMD_ENDE << "]«" << std::endl;
    file << "»['HYPR_CMD'|" << BLANKER_NENNER_CMD_START << "monitor=,preferred,auto,1" << BLANKER_NENNER_CMD_ENDE << "]«" << std::endl;
    file << TRANSAKTION_ENDE << std::endl;

    // 3. SYSTEM_CMD (Tiefe Kernel-Aktion, hier Dateizugriff)
    file << "\n" << KOMMENTAR << " Linux Kernel Befehl (SYSTEM_CMD)" << std::endl;
    file << TRANSAKTION_START << std::endl;
    file << "»['SYSTEM_CMD'|" << BLANKER_NENNER_CMD_START << "vfs_read_permissions, /dev/input/event0" << BLANKER_NENNER_CMD_ENDE << "]«" << std::endl;
    file << TRANSAKTION_ENDE << std::endl;

    file.close();
    std::cout << "[SETUP_INFO] Simulationsdatei '" << filename << "' erstellt." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Nutzung: " << argv[0] << " <mcs_datei>" << std::endl;
        std::cerr << "Oder: " << argv[0] << " --create-sim" << std::endl;
        return 1;
    }

    std::string arg = argv[1];

    if (arg == "--create-sim") {
        create_simulation_file("hyprland.mcs");
    } else {
        load_and_parse_mcs(arg);
    }

    return 0;
}
