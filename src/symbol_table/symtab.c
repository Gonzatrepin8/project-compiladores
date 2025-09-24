#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symtab.h"

SymTab *symtab_new(void) {
    SymTab *st = calloc(1, sizeof(SymTab));
    st->level = 0;
    st->is_function = false;
    return st;
}

void symtab_insert(SymTab *st, Info *info) {
    Symbol *s = calloc(1, sizeof(Symbol));
    struct SymTab *parent;
    s->info = info;
    s->next = st->head;
    st->head = s;
}

TypeInfo symtab_lookup(SymTab *st, const char *name) {
    for (SymTab *scope = st; scope != NULL; scope = scope->parent) {
        for (Symbol *s = scope->head; s != NULL; s = s->next) {
            if (strcmp(s->info->name, name) == 0) {
                return s->info->eval_type;
            }
        }
    }
    return TYPE_ERROR;
}

TypeInfo symtab_scope(SymTab *st, const char *name) {
    SymTab *scope = st;
    for (Symbol *s = scope->head; s != NULL; s = s->next) {
        if (strcmp(s->info->name, name) == 0) {
            return s->info->eval_type;
        }
    }
    return TYPE_ERROR;
}

void symtab_print(SymTab *st, FILE *stream) {
    if (!stream) return;

    SymTab *stack[128];
    int n = 0;
    for (SymTab *scope = st; scope != NULL && n < 128; scope = scope->parent) {
        stack[n++] = scope;
    }

    fprintf(stream, "=== Symbol Table ===\n");
    
    for (int i = n - 1; i >= 0; --i) {
        int level = (n - 1) - i;
        fprintf(stream, "Scope level %d:\n", level);
        Symbol *s = stack[i]->head;
        if (!s) {
            fprintf(stream, "  (empty)\n");
        }
        for (; s != NULL; s = s->next) {
            fprintf(stream, "  Name: %s, Type: %s, value: %d\n",
                   s->info->name ? s->info->name : "(null)",
                   type_to_string(s->info->eval_type),
                   (s->info->eval_type == TYPE_INT) ? s->info->ival : s->info->bval);
        }
    }
    fprintf(stream, "====================\n");
}


int symtab_get_value(SymTab *st, const char *name, int *found) {
    for (SymTab *scope = st; scope != NULL; scope = scope->parent) {
        for (Symbol *s = scope->head; s != NULL; s = s->next) {
            if (strcmp(s->info->name, name) == 0) {
                *found = 1;
                if (s->info->eval_type == TYPE_INT) {
                    return s->info->ival;
                } else if (s->info->eval_type == TYPE_BOOL) {
                    return s->info->bval;
                }
            }
        }
    }
    *found = 0;
    return 0;
}


void symtab_set_value(SymTab *st, const char *name, int value) {
    for (SymTab *scope = st; scope != NULL; scope = scope->parent) {
        for (Symbol *s = scope->head; s != NULL; s = s->next) {
            if (strcmp(s->info->name, name) == 0) {
                if (s->info->eval_type == TYPE_INT) {
                    s->info->ival = value;
                } else if (s->info->eval_type == TYPE_BOOL) {
                    s->info->bval = value;
                }
                return;
            }
        }
    }
    fprintf(stderr, "Error: assignment to undeclared variable '%s'\n", name);
}

void symtab_print_scope(SymTab *st) {
    printf("Scope level %d:\n", st->level);
    for (Symbol *s = st->head; s != NULL; s = s->next) {
        printf("  Name: %s, Type: %s\n",
               s->info->name,
               type_to_string(s->info->eval_type));
    }
}
