// mcs_register.h
#ifndef MCS_REGISTER_H
#define MCS_REGISTER_H

#include <stdint.h>

// Hardware-nahe Makros (Präfix ALU laut Regel 2.1)
static inline void ALU_REINIGEN() {
    // Hier wird der Sentiator-Befehl 'ſ' physisch umgesetzt
    // Löscht die Register der virtuellen MCS-Maschine
    __asm__ volatile ("" : : : "memory");
}

// Die Wahrheiten-Struktur für das Register
typedef struct {
    uint8_t stufe;    // þ1 bis þ10
    char dna_key[16]; // þ7F3A...
} MCS_IDENTITAET;

// Funktion zum Mappen der Feeds (1) auf Hardware
void mcs_register_eintrag_erstellen(int feed_id, const char* wert);

#endif
