// include/mcs_transaktion.h — v3.0, mit Wahrheiten-Unterstützung
#ifndef MCS_TRANS_H
#define MCS_TRANS_H

#include "mcs_token.h"
#include "mcs_protein.h"   // ← Protein kennt jetzt IF/ELSE

typedef struct {
    mcs_token_t trans_start;
    mcs_token_t trans_end;

    // 🔹 NEU: Bedingungen auf Transaktionsebene
    mcs_wahrheit_t wahrheit;      // z.B. WAHR_WHEN_NOT
    mcs_protein_t* condition;      // z.B. ['$terminal']

    // 🔹 Proteine in Reihenfolge — jetzt mit Verzweigungen!
    mcs_protein_t** proteine;     // dynamisches Array
    int protein_count;

    int is_valid;
} mcs_transaktion_t;

mcs_transaktion_t* mcs_parse_transaktion(const char* input);
void mcs_free_transaktion(mcs_transaktion_t* t);

#endif
