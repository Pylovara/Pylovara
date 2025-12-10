// Lib/mcs_runner.c — v3.0 MVP: nur Ausführung, kein Parsing!
#include "mcs_runner.h"
#include "mcs_feed.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int mcs_run_transaktion(mcs_transaktion_t* t) {
    if (!t || !t->is_valid) return MCS_ERR_SYNTAX;

    // 🔹 Bedingung prüfen (° [...])
    if (t->wahrheit == WAHR_WHEN_NOT && t->condition) {
        int cond_ok = (mcs_run_protein(t->condition) == MCS_OK);
        if (!cond_ok && t->proteine[0] && t->proteine[0]->then_branch) {
            return mcs_run_protein(t->proteine[0]->then_branch);
        }
        if (cond_ok && t->proteine[0] && t->proteine[0]->else_branch) {
            return mcs_run_protein(t->proteine[0]->else_branch);
        }
    }

    // 🔹 Alle Proteine ausführen
    for (int i = 0; i < t->protein_count; i++) {
        if (t->proteine[i]) {
            int res = mcs_run_protein(t->proteine[i]);
            if (res != MCS_OK) return res;
        }
    }
    return MCS_OK;
}

int mcs_run_protein(mcs_protein_t* p) {
    if (!p) return MCS_ERR_SYNTAX;

    // 🔹 IF-Zweig (¶)
    if (p->wahrheit == WAHR_IF && p->then_branch) {
        return mcs_run_protein(p->then_branch);
    }
    // 🔹 ELSE-Zweig (¶¶)
    if (p->wahrheit == WAHR_ELSE && p->else_branch) {
        return mcs_run_protein(p->else_branch);
    }
    // 🔹 Normale Aktion
    if (p->action) {
        return mcs_run_action(p->action);
    }
    return MCS_OK;
}

int mcs_run_action(mcs_action_t* a) {
    if (!a) return MCS_ERR_SYNTAX;
    if (!a->cmd) {
        fprintf(stderr, "[DEBUG] cmd is NULL\n");
        return MCS_ERR_SYNTAX;
    }

    printf("[DEBUG] cmd='%s', blankernenner='%s', feed.id=%d, arg.type=%d, arg.value=%.2f\n",
           a->cmd ? a->cmd : "(null)",
           a->blankernenner ? a->blankernenner : "(null)",
           a->feed.id,
           a->arg.type,
           a->arg.value);

    // 🔹 1. Blankernenner: $cmd → popen + Feed
    if (a->blankernenner && a->blankernenner[0] == '$') {
        FILE* p = popen(a->blankernenner + 1, "r");
        if (p) {
            char buf[64] = {0};
            if (fgets(buf, sizeof(buf), p)) {
                buf[strcspn(buf, "\n")] = 0;
                if (a->feed.id > 0) {
                    mcs_feed_set(a->feed.id, buf);
                }
            }
            pclose(p);
        }
    }

    // 🔹 2. Argumente: Zeitsteuerung (ARG_TIME)
    if (a->arg.type == ARG_TIME && a->arg.value > 0) {
        sleep(a->arg.value);  // später: `usleep` + `mcs_resolve_value`
    }

    // 🔹 3. System-Command (nur für 'exec', 'run')
    if (a->arg1 &&
        (strcmp(a->cmd, "exec") == 0 || strcmp(a->cmd, "run") == 0)) {
        char cmd[256];
    snprintf(cmd, sizeof(cmd), "%s %s", a->cmd, a->arg1);
    return system(cmd);
        }

        return MCS_OK;
}
