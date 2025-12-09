// Lib/mcs_runner.c — v3.0: minimal, sicher, skalierbar
#include "mcs_runner.h"
#include "mcs_feed.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int mcs_run_transaktion(mcs_transaktion_t* t) {
    if (!t || !t->is_valid) return MCS_ERR_SYNTAX;

    // 🔹 1. Bedingung prüfen (z.B. ° ['$terminal'])
    if (t->wahrheit == WAHR_WHEN_NOT && t->condition) {
        int cond_result = mcs_run_protein(t->condition);
        if (cond_result == 0) {
            // Bedingung erfüllt → THEN-Zweig
            if (t->proteine[0] && t->proteine[0]->then_branch) {
                return mcs_run_protein(t->proteine[0]->then_branch);
            }
        } else {
            // Bedingung NICHT erfüllt → ELSE-Zweig
            if (t->proteine[0] && t->proteine[0]->else_branch) {
                return mcs_run_protein(t->proteine[0]->else_branch);
            }
        }
    }

    // 🔹 2. Sequenzielle Ausführung aller Proteine
    for (int i = 0; i < t->protein_count; i++) {
        int res = mcs_run_protein(t->proteine[i]);
        if (res != MCS_OK) return res;
    }
    return MCS_OK;
}

int mcs_run_protein(mcs_protein_t* p) {
    if (!p) return MCS_ERR_SYNTAX;

    // 🔹 Fall: IF-Zweig (¶ ...)
    if (p->wahrheit == WAHR_IF && p->then_branch) {
        return mcs_run_protein(p->then_branch);
    }

    // 🔹 Fall: ELSE-Zweig (¶¶ ...)
    if (p->wahrheit == WAHR_ELSE && p->else_branch) {
        return mcs_run_protein(p->else_branch);
    }

    // 🔹 Fall: Normale Aktion (»[...]«)
    if (p->action) {
        return mcs_run_action(p->action);
    }
    return MCS_OK;
}

int mcs_run_action(mcs_action_t* a) {
    if (!a || !a->cmd) return MCS_ERR_SYNTAX;

    // 🔹 1. Blankernenner auswerten (nur $cmd, nicht Code!)
    if (a->blankernenner && a->blankernenner[0] == '$') {
        // Beispiel: $pgrep firefox → popen, Ergebnis in Feed speichern
        FILE* p = popen(a->blankernenner + 1, "r");
        if (p) {
            char buf[64];
            if (fgets(buf, sizeof(buf), p)) {
                // Entferne \n
                buf[strcspn(buf, "\n")] = 0;
                if (a->feed.id > 0) {
                    mcs_feed_set(a->feed.id, buf);
                }
            }
            pclose(p);
        }
    }

    // 🔹 2. Argumente auswerten
    if (a->arg.type == ARG_TIME && a->arg.value > 0) {
        sleep(a->arg.value);
    }

    // 🔹 3. System-Command ausführen (nur '...', nicht '' oder ’’!)
    if (a->arg1) {
        // Sicher: Nur wenn cmd = "exec", "run", etc.
        if (strcmp(a->cmd, "exec") == 0 || strcmp(a->cmd, "run") == 0) {
            char cmd[256];
            snprintf(cmd, sizeof(cmd), "%s %s", a->cmd, a->arg1);
            return system(cmd);
        }
    }

    return MCS_OK;
}
