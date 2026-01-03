#ifndef MCS_REGISTER_H
#define MCS_REGISTER_H

#include <stdint.h>

#define MAX_REGISTERS 256

typedef struct {
    int besetzt;
    char wert[1024];
    long numerisch;
} MCSRegister;

extern MCSRegister reg_bank[MAX_REGISTERS];

// --- PROTOTYPEN FÜR DAS GEDÄCHTNIS ---
void mcs_register_init(void);
void mcs_register_setze(int id, const char* wert);
char* mcs_register_hole(int id);
long mcs_register_hole_num(int id);

// In /Pylovara/MCSKernel/Logic/mcs_register.h

// ... bestehende Definitionen ...
long mcs_register_extrahiere_protein(int reg_nr);
void ALU_REGISTER_BINDEN(int reg_nr, long wert);
int ALU_AIMS_HANDSHAKE(long protein_signatur);

#endif
