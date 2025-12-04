// include/mcs_protein.h
#ifndef MCS_PROTEIN_H
#define MCS_PROTEIN_H

#include "mcs_action.h"     // Aktion enthält cmd, arg1, feed, blankernenner, arg
#include "mcs_proton.h"     // optional
#include "mcs_warp.h"       // optional

// Protein = Aktion + optional Proton/Warp
typedef struct {
    mcs_action_t* action;   // »[...]«
    mcs_proton_t* proton;   // {Name|¨Wert¨}
    mcs_warp_t*   warp;     // ølang|codeø
} mcs_protein_t;

mcs_protein_t* mcs_parse_protein(const char* input);
void mcs_free_protein(mcs_protein_t* p);

#endif
