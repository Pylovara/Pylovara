// Lib/mcs_runner.c — v3.0 FINAL: mit Semantik-Integration, Parallel Run & Transport
// info : linear gedacht
#include "mcs_runner.h"
#include "mcs_feed.h"
#include "mcs_semantics.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int mcs_run_transaktion(mcs_transaktion_t* t) {
    if (!t || !t->is_valid) return MCS_ERR_SYNTAX;

    // 🔹 1. Transaktions-Bedingung (z.B. ° ['$terminal'])
    if (t->wahrheit != WAHR_NONE && t->condition) {
        mcs_semantic_op_t op = mcs_wahrheit_to_semantic(t->wahrheit);
        mcs_truth_t cond = mcs_evaluate_condition(t->condition);

        switch (op) {
            case SEMANTIC_WHEN_NOT:  // °
                if (cond == MCS_FALSE && t->protein_count > 0 && t->proteine && t->proteine[0] && t->proteine[0]->then_branch) {
                    return mcs_run_protein(t->proteine[0]->then_branch);
                }
                if (cond == MCS_TRUE && t->protein_count > 0 && t->proteine && t->proteine[0] && t->proteine[0]->else_branch) {
                    return mcs_run_protein(t->proteine[0]->else_branch);
                }
                break;
            default: break;
        }
    }

    // 🔹 2. Alle Proteine sequenziell ausführen — mit Wahrheits-Dispatch
    for (int i = 0; i < t->protein_count; i++) {
        mcs_protein_t* p = t->proteine && i < t->protein_count ? t->proteine[i] : NULL;
        if (!p) continue;

        if (p->wahrheit != WAHR_NONE) {
            mcs_semantic_op_t op = mcs_wahrheit_to_semantic(p->wahrheit);

            switch (op) {
                case SEMANTIC_IF: {
                    if (p->then_branch) mcs_run_protein(p->then_branch);
                    break;
                }
                case SEMANTIC_ELSE: {
                    if (p->else_branch) mcs_run_protein(p->else_branch);
                    break;
                }
                case SEMANTIC_PARALLEL_TRANSPORT: {  // ;;
                    if (p->action) mcs_run_action(p->action);  // synchron (MVP), sicher
                    break;
                }
                case SEMANTIC_PARALLEL: {  // ¶=
                    if (p->action) {
                        pid_t pid = fork();
                        if (pid == 0) {
                            // Kindprozess: ausführen & exit
                            mcs_run_action(p->action);
                            exit(0);
                        } else if (pid > 0) {
                            printf("[PARALLEL] Gestartet: PID %d\n", (int)pid);
                            // Elternprozess: NICHT warten → linear, nicht-blockierend
                        } else {
                            fprintf(stderr, "[ERROR] fork() fehlgeschlagen\n");
                        }
                    }
                    break;
                }
                default:
                    mcs_run_protein(p);
            }
        } else {
            mcs_run_protein(p);
        }
    }

    return MCS_OK;
}

int mcs_run_protein(mcs_protein_t* p) {
    if (!p) return MCS_ERR_SYNTAX;

    if (p->wahrheit == WAHR_IF && p->then_branch) {
        return mcs_run_protein(p->then_branch);
    }
    if (p->wahrheit == WAHR_ELSE && p->else_branch) {
        return mcs_run_protein(p->else_branch);
    }
    if (p->action) {
        return mcs_run_action(p->action);
    }
    return MCS_OK;
}

int mcs_run_action(mcs_action_t* a) {
    if (!a || !a->cmd) {
        fprintf(stderr, "[RUN] Action NULL\n");
        return MCS_ERR_SYNTAX;
    }

    printf("[RUN] cmd='%s', blank='%s', feed.id=%d, arg.type=%d, arg.value=%.2f\n",
           a->cmd, a->blankernenner ?: "(null)", a->feed.id, a->arg.type, a->arg.value);

    // 🔹 Blankernenner → Feed
    if (a->blankernenner && a->blankernenner[0] == '$' && a->feed.id > 0) {
        FILE* p = popen(a->blankernenner + 1, "r");
        if (p) {
            char buf[64] = {0};
            if (fgets(buf, sizeof(buf), p)) {
                buf[strcspn(buf, "\n")] = 0;
                mcs_feed_set(a->feed.id, buf, a->blankernenner);
                printf("[FEED] (%d) = '%s'\n", a->feed.id, buf);
            }
            pclose(p);
        }
    }

    // 🔹 ARG_TIME
    if (a->arg.type == ARG_TIME && a->arg.value > 0) {
        sleep((unsigned int)a->arg.value);
    }

    // 🔹 System-Command
    if (a->cmd && (strcmp(a->cmd, "exec") == 0 || strcmp(a->cmd, "run") == 0)) {
        const char* feed_val = a->feed.id > 0 ? mcs_feed_get(a->feed.id) : NULL;
        char cmd[256];
        if (a->blankernenner && feed_val) {
            snprintf(cmd, sizeof(cmd), "%s %s", a->cmd, feed_val);
        } else if (a->arg1) {
            snprintf(cmd, sizeof(cmd), "%s %s", a->cmd, a->arg1);
        } else {
            snprintf(cmd, sizeof(cmd), "%s", a->cmd);
        }
        printf("[EXEC] %s\n", cmd);
        return system(cmd);
    }

    return MCS_OK;
}
