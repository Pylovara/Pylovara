// Lib/mcs_operatoren.c — v3.0: Minimal, sicher, feed-basiert
#include "mcs_operatoren.h"
#include "mcs_feed.h"
#include "mcs_semantics.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

mcs_operator_t* mcs_operator_new(void) {
    return calloc(1, sizeof(mcs_operator_t));
}

void mcs_operator_free(mcs_operator_t* op) {
    if (!op) return;
    if (op->type == MCS_OP_WHEN_NOT) {
        mcs_free_protein(op->data.not.cond);
    }
    mcs_free_protein(op->then_branch);
    mcs_free_protein(op->else_branch);
    free(op);
}

int mcs_operator_set_type(mcs_operator_t* op, mcs_op_type_t type) {
    if (!op) return 0;
    op->type = type;
    return 1;
}

int mcs_operator_bind_condition(mcs_operator_t* op, mcs_protein_t* p) {
    if (!op || !p || op->type != MCS_OP_WHEN_NOT) return 0;
    op->data.not.cond = p;
    return 1;
}

int mcs_operator_bind_comparison(mcs_operator_t* op, int id_a, int id_b) {
    if (!op || id_a < 0 || id_b < 0) return 0;
    if (op->type != MCS_OP_WHEN_LT && op->type != MCS_OP_WHEN_GT) return 0;
    op->data.cmp.left_id = id_a;
    op->data.cmp.right_id = id_b;
    return 1;
}

int mcs_operator_bind_residue(mcs_operator_t* op, int feed_id) {
    if (!op || feed_id < 0) return 0;
    if (op->type != MCS_OP_DATA_RESIDUE) return 0;
    op->data.residue_id = feed_id;
    return 1;
}

int mcs_operator_set_branches(mcs_operator_t* op, mcs_protein_t* then, mcs_protein_t* elseb) {
    if (!op) return 0;
    op->then_branch = then;
    op->else_branch = elseb;
    return 1;
}

mcs_truth_t mcs_evaluate_operator(const mcs_operator_t* op) {
    if (!op) return MCS_ERROR;

    switch (op->type) {
        case MCS_OP_WHEN_NOT: {
            if (!op->data.not.cond) return MCS_ERROR;
            mcs_truth_t cond = mcs_evaluate_condition(op->data.not.cond);
            return (cond == MCS_FALSE) ? MCS_TRUE : (cond == MCS_TRUE ? MCS_FALSE : MCS_ERROR);
        }

        case MCS_OP_WHEN_LT:
        case MCS_OP_WHEN_GT: {
            const char* a_str = mcs_feed_get(op->data.cmp.left_id);
            const char* b_str = mcs_feed_get(op->data.cmp.right_id);
            if (!a_str || !b_str) return MCS_ERROR;

            double a = atof(a_str);
            double b = atof(b_str);

            if (op->type == MCS_OP_WHEN_LT) return (a < b) ? MCS_TRUE : MCS_FALSE;
            else                             return (a > b) ? MCS_TRUE : MCS_FALSE;
        }

        case MCS_OP_TRANS_ERROR:
        case MCS_OP_DATA_RESIDUE:
            return MCS_TRUE; // Annotationen → keine Auswertung nötig

        default:
            return MCS_ERROR;
    }
}
