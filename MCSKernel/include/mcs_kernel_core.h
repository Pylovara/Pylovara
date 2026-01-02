#ifndef MCS_KERNEL_CORE_H
#define MCS_KERNEL_CORE_H

#include <stdint.h>

// @kernel-nr: 01 - Datentypen (b-inf, b-þa etc.)
typedef __int128 b_inf; // Für unendliche Bit-Tiefe simuliert
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

// Regel 2.1: Hardware-nahe Makros
#define ALU_TAKT_SYNC() __asm__ volatile ("pause" ::: "memory")
#define ALU_REINIGEN()  __asm__ volatile ("xor %%rax, %%rax" ::: "rax") // Der ſ-Befehl auf CPU-Ebene

#endif
