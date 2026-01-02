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

#endif
