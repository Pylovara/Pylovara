#ifndef MCS_KERNEL_CORE_H
#define MCS_KERNEL_CORE_H

#include <stdint.h>

// @kernel-nr: 01 - Datentypen
typedef __int128 b_inf;
typedef uint64_t b_64;

// @kernel-nr: 14 - ID-DNA-Logik
#define MASTER_DNA "þ7F3A-THOMAS-ZIMMERMANN-STUFE10"

// @kernel-nr: 99 - MCS-CMD-REGISTER
typedef enum {
    CMD_LÖSCHUNG,
    CMD_AUSFÜHRUNG,
    CMD_FEED,
    CMD_PURGE
} MCS_Befehl;

// Regel 2.1: Hardware-nahe Makros (Lichtkegel-Befehle)
#define ALU_TAKT_SYNC() do { __asm__ volatile ("pause" ::: "memory"); } while(0)
#define ALU_REINIGEN()  do { __asm__ volatile ("xor %%rax, %%rax" ::: "rax"); } while(0)

#endif
