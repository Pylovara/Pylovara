// mcsc.c
// Minimal MCS -> ASM marker emitter
// Usage: ./mcsc input.mcs out.mcs.asm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void emit_db(FILE *f, const char *label, const char *text) {
    fprintf(f, "    ; %s marker\n", label);
    fprintf(f, "    db \"%s\",0\n", text);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s input.mcs out.mcs.asm\n", argv[0]);
        return 1;
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];

    FILE *in = fopen(infile, "r");
    if (!in) { perror("open input"); return 2; }

    FILE *out = fopen(outfile, "w");
    if (!out) { perror("open output"); fclose(in); return 3; }

    fprintf(out, "BITS 64\nSECTION .rodata\nglobal mcs_meta_start\nmcs_meta_start:\n");

    char *line = NULL;
    size_t n = 0;
    ssize_t len;

    // We'll emit a marker each time we encounter a token.
    // Mapping:
    //   "¢!" -> TRANS_START
    //   "!¢" -> TRANS_END
    //   "»"  -> ACT_START
    //   "«"  -> ACT_END
    //   "["  -> PROT_START
    //   "]"  -> PROT_END
    //   "{"  -> PROP_START
    //   "}"  -> PROP_END

    while ((len = getline(&line, &n, in)) != -1) {
        for (ssize_t i = 0; i < len; ++i) {
            unsigned char c = line[i];

            // detect two-char tokens first: ¢! and !¢
            if (c == 0xC2 || c == 0xC3 || c >= 0x80) {
                // UTF-8 handling for multi-byte symbols: naive approach - check substrings
                // We'll search for the known sequences in the rest of the line instead.
                // Check substrings:
                if (strstr(line + i, "¢!") == line + i) {
                    emit_db(out, "TRANS_START", "MCS_TRANS_START");
                    i += strlen("¢!") - 1;
                    continue;
                }
                if (strstr(line + i, "!¢") == line + i) {
                    emit_db(out, "TRANS_END", "MCS_TRANS_END");
                    i += strlen("!¢") - 1;
                    continue;
                }
                // if not our multi-byte tokens, skip one byte (avoid infinite loop)
                continue;
            }

            // ASCII tokens:
            switch (c) {
                case '[':
                    emit_db(out, "PROTEIN_START", "MCS_PROT[");
                    break;
                case ']':
                    emit_db(out, "PROTEIN_END", "MCS_PROT]");
                    break;
                case '{':
                    emit_db(out, "PROTON_START", "MCS_PROP{");
                    break;
                case '}':
                    emit_db(out, "PROTON_END", "MCS_PROP}");
                    break;
                case '>': // fallback if user uses > < for actions
                    emit_db(out, "ACTION_MARK", "MCS_ACTION>");
                    break;
                case '<':
                    emit_db(out, "ACTION_MARK", "MCS_ACTION<");
                    break;
                case '»': // if terminal encodes this as single char (rare)
                    emit_db(out, "ACTION_START", "MCS_ACT>");
                    break;
                case '«':
                    emit_db(out, "ACTION_END", "MCS_ACT<");
                    break;
                default:
                    break;
            }
        }

        // also search the whole line for the UTF-8 multi-byte symbols explicitly
        if (strstr(line, "»") != NULL) emit_db(out, "ACTION_START", "MCS_ACT>");
        if (strstr(line, "«") != NULL) emit_db(out, "ACTION_END", "MCS_ACT<");
        if (strstr(line, "¢!") != NULL) emit_db(out, "TRANS_START", "MCS_TRANS_START");
        if (strstr(line, "!¢") != NULL) emit_db(out, "TRANS_END", "MCS_TRANS_END");
    }

    free(line);
    fclose(in);

    // text section: minimal runnable code (exit syscall)
    fprintf(out, "\nSECTION .text\nglobal _start\n_start:\n    mov rax, 60\n    mov rdi, 0\n    syscall\n");

    fclose(out);

    printf("Wrote ASM: %s\n", outfile);
    return 0;
}
