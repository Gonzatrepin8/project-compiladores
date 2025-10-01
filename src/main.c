#include <libgen.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "ast/ast.h"
#include "symbol_table/symtab.h"
#include "symbol_table/build_symtab.h"
#include "type_check/type_check.h"

extern int yylex(void);
extern void yyerror(const char *s);

extern int debug_mode;
extern bool semantic_error;
extern bool type_check_error;

extern FILE *yyin;
extern FILE *lexout;
FILE *semout;
FILE *sintout;
FILE *symout;
char lex_filename[256];
char sint_filename[256];
char sent_filename[256];
char sym_filename[256];

extern AST *root;

typedef enum {
    TARGET_FULL,
    TARGET_SCAN,
    TARGET_PARSE
} TargetStage;

TargetStage target_stage = TARGET_FULL;

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-debug] [-target scan|parse] <sourcefile>\n", argv[0]);
        return 1;
    }

    int argi = 1;
    while (argi < argc && argv[argi][0] == '-') {
        if (strcmp(argv[argi], "-debug") == 0) {
            debug_mode = 1;
            argi++;
        } else if (strcmp(argv[argi], "-target") == 0) {
            if (argi + 1 >= argc) {
                fprintf(stderr, "-target requires an argument (scan|parse)\n");
                return 1;
            }
            if (strcmp(argv[argi+1], "scan") == 0) {
                target_stage = TARGET_SCAN;
            } else if (strcmp(argv[argi+1], "parse") == 0) {
                target_stage = TARGET_PARSE;
            } else {
                fprintf(stderr, "Unknown target: %s (expected scan|parse)\n", argv[argi+1]);
                return 1;
            }
            argi += 2;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[argi]);
            return 1;
        }
    }

    if (argi >= argc) {
        fprintf(stderr, "No input file given.\n");
        return 1;
    }

    yyin = fopen(argv[argi], "r");
    if (!yyin) {
        perror("fopen");
        return 1;
    }

    const char *inputfile = argv[argi];

    struct stat st = {0};
    if (stat("output", &st) == -1) {
        if (mkdir("output", 0700) != 0) {
            perror("mkdir");
            return 1;
        }
    }

    char base[256];
    strncpy(base, basename((char *)inputfile), sizeof(base) - 1);
    base[sizeof(base) - 1] = '\0';

    char *dot = strrchr(base, '.');
    if (dot) *dot = '\0';

    snprintf(lex_filename, sizeof(lex_filename), "output/%s.lex", base);
    snprintf(sint_filename, sizeof(sint_filename), "output/%s.sint", base);
    snprintf(sent_filename, sizeof(sent_filename), "output/%s.sem", base);
    snprintf(sym_filename, sizeof(sym_filename), "output/%s.sym", base);

    lexout = fopen(lex_filename, "w");
    if (!lexout) { perror("fopen lex"); return 1; }
    if (target_stage >= TARGET_PARSE) {
        sintout = fopen(sint_filename, "w");
        if (!sintout) { perror("fopen sint"); return 1; }
    }
    if (target_stage == TARGET_FULL) {
        semout = fopen(sent_filename, "w");
        symout = fopen(sym_filename, "w");
        if (!semout || !symout) { perror("fopen sem"); return 1; }
    }

    int result = 0;

    if (target_stage == TARGET_SCAN) {
        while (yylex() != 0) { }
    } else {
        result = yyparse();
        if (target_stage >= TARGET_PARSE) {
            if (result == 0) {
                fprintf(sintout, "Parser: SUCCESS\n");
            } else {
                fprintf(sintout, "Parser: FAILED\n");
            }
        }

        if (target_stage == TARGET_FULL && result == 0) {
            if (root) {
                SymTab *global = symtab_new();
                TypeInfo res = build_symtab(root, global, symout);
                if (semantic_error) {
                    fprintf(stderr, "Falló la creación de la tabla de símbolos debido a un error semantico.\n");
                    return 1;
                }
                Info *main_info = symtab_lookup_info(global, "main");
                if (main_info == NULL) {
                    fprintf(stderr, "Error semántico: La función 'main' no está definida.\n");
                    semantic_error = true;
                } else if (!main_info->is_function) {
                    fprintf(stderr, "Error semántico: 'main' debe ser una función.\n");
                    semantic_error = true;
                } else if (main_info->params != NULL) {
                    fprintf(stderr, "Error semántico: La función 'main' no debe tener parámetros.\n");
                    semantic_error = true;
                }

                if (semantic_error) {
                    return 1;
                }

                symtab_print(global, symout);
                check_types(root);
                print_ast(root, 0, 1);
                if (type_check_error) {
                    fprintf(stderr, "Type check error.\n");
                    return 1;
                }
            }
        }
    }

    fclose(yyin);
    fclose(lexout);
    if (target_stage >= TARGET_PARSE) {
        fclose(sintout);
    }
    if (target_stage == TARGET_FULL) {
        fclose(semout);
        fclose(symout);
    }

    if (debug_mode) {
        FILE *f = fopen(lex_filename, "r");
        if (f) {
            printf("---- Lexer Output (%s) ----\n", lex_filename);
            char c;
            while ((c = fgetc(f)) != EOF) putchar(c);
            fclose(f);
        }

        if (target_stage >= TARGET_PARSE) {
            f = fopen(sint_filename, "r");
            if (f) {
                printf("---- Parser Output (%s) ----\n", sint_filename);
                char c;
                while ((c = fgetc(f)) != EOF) putchar(c);
                fclose(f);
            }
        }

        if (target_stage == TARGET_FULL) {
            f = fopen(sent_filename, "r");
            if(f) {
                printf("---- AST (%s) ----\n", sent_filename);
                char c;
                while((c = fgetc(f)) != EOF) putchar(c);
                fclose(f);
            }

            f = fopen(sym_filename, "r");
            if (f) {
                printf("---- Symbol Table (%s) ----\n", sym_filename);
                char c;
                while((c = fgetc(f)) != EOF) putchar(c);
                fclose(f);
            }
        }
        
    }

    if (semantic_error) {
        return 1;
    }

    return result;
}
