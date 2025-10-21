#include "assembly_gen.h"
#include "../three_address/three_address.h"

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct VarMap {
    char *name;
    int   offset;    
    struct VarMap *next;
} VarMap;

static VarMap *var_map_head = NULL;
static int current_stack_size = 0;

static void free_var_map(void) {
    VarMap *cur = var_map_head;
    while (cur) {
        VarMap *tmp = cur;
        cur = cur->next;
        free(tmp->name);
        free(tmp);
    }
    var_map_head = NULL;
    current_stack_size = 0;
}

static int ensure_offset(const char *name, FILE *out) {
    if (!name) return 0;

    for (VarMap *v = var_map_head; v; v = v->next) {
        if (strcmp(v->name, name) == 0) return v->offset;
    }
    VarMap *n = (VarMap*)calloc(1, sizeof(VarMap));
    n->name   = strdup(name);
    current_stack_size += 8;
    n->offset = current_stack_size;
    n->next   = var_map_head;
    var_map_head = n;

    fprintf(out, "    sub     rsp, 8\n");
    return n->offset;
}

static int is_int_literal(const char *s) {
    if (!s || !*s) return 0;
    if (*s == '-') ++s;
    if (!*s) return 0;
    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        ++s;
    }
    return 1;
}

static void load_i32_to_eax(FILE *out, const char *op) {
    if (is_int_literal(op)) {
        fprintf(out, "    mov     eax, %s\n", op);
    } else {
        int off = ensure_offset(op, out);
        fprintf(out, "    mov     eax, DWORD PTR [rbp-%d]\n", off);
    }
}

static void load_i32_to_ecx(FILE *out, const char *op) {
    if (is_int_literal(op)) {
        fprintf(out, "    mov     ecx, %s\n", op);
    } else {
        int off = ensure_offset(op, out);
        fprintf(out, "    mov     ecx, DWORD PTR [rbp-%d]\n", off);
    }
}

static void store_eax_to(FILE *out, const char *dst) {
    int off = ensure_offset(dst, out);
    fprintf(out, "    mov     DWORD PTR [rbp-%d], eax\n", off);
}

void asm_write_header(FILE *out, const char *func_name) {
    if (!func_name) func_name = "func";
    if (strcmp(func_name, "main") == 0) {
        fprintf(out, "    .globl  main\n");
        fprintf(out, "main:\n");
    } else {
        fprintf(out, "    .globl  %s\n", func_name);
        fprintf(out, "%s:\n", func_name);
    }
    fprintf(out, "    push    rbp\n");
    fprintf(out, "    mov     rbp, rsp\n");
}

void asm_write_footer(FILE *out) {
    fprintf(out, "    mov     rsp, rbp\n");
    fprintf(out, "    pop     rbp\n");
    fprintf(out, "    ret\n");
}

void asm_write_mov(FILE *out, const char *dst, const char *src) {
    load_i32_to_eax(out, src);
    store_eax_to(out, dst);
}

void asm_write_add(FILE *out, const char *dst, const char *rhs) {
    load_i32_to_ecx(out, rhs);
    fprintf(out, "    add     eax, ecx\n");
    store_eax_to(out, dst);
}

void asm_write_sub(FILE *out, const char *dst, const char *rhs) {
    load_i32_to_ecx(out, rhs);
    fprintf(out, "    sub     eax, ecx\n");
    store_eax_to(out, dst);
}

void asm_write_mul(FILE *out, const char *dst, const char *rhs) {
    load_i32_to_ecx(out, rhs);
    fprintf(out, "    imul    eax, ecx\n");
    store_eax_to(out, dst);
}

void asm_write_cmp(FILE *out, const char *a, const char *b) {
    load_i32_to_eax(out, a);
    load_i32_to_ecx(out, b);
    fprintf(out, "    cmp     eax, ecx\n");
}

void asm_write_label(FILE *out, const char *label) {
    fprintf(out, "%s:\n", label);
}

void asm_write_jump(FILE *out, const char *label) {
    fprintf(out, "    jmp     %s\n", label);
}

void asm_write_cond_jump(FILE *out, const char *cond, const char *label) {
    fprintf(out, "    j%s      %s\n", cond, label);
}

#define MAX_PARAMS 32
static char *pending_params[MAX_PARAMS];
static int   pending_count = 0;

static void params_reset(void) {
    for (int i = 0; i < pending_count; ++i) {
        pending_params[i] = NULL;
    }
    pending_count = 0;
}

static void params_push(const char *arg) {
    if (pending_count < MAX_PARAMS) {
        pending_params[pending_count++] = (char*)arg;
    }
}

static void move_arg_to_reg(FILE *out, int idx, const char *arg) {
    static const char *areg[] = { "edi", "esi", "edx", "ecx", "r8d", "r9d" };
    if (idx < 6) {
        if (is_int_literal(arg)) {
            fprintf(out, "    mov     %s, %s\n", areg[idx], arg);
        } else {
            int off = ensure_offset(arg, out);
            fprintf(out, "    mov     %s, DWORD PTR [rbp-%d]\n", areg[idx], off);
        }
    } else {
        if (is_int_literal(arg)) {
            fprintf(out, "    mov     eax, %s\n", arg);
            fprintf(out, "    push    rax\n");
        } else {
            int off = ensure_offset(arg, out);
            fprintf(out, "    mov     eax, DWORD PTR [rbp-%d]\n", off);
            fprintf(out, "    push    rax\n");
        }
    }
}

void generate_assembly(FILE *out) {
    fprintf(out, "    .text\n");

    TAC *n = tac_head;
    int in_function = 0;

    params_reset();
    free_var_map();

    while (n) {
        switch (n->op) {
        case TAC_DEFUNC: {
            params_reset();
            free_var_map();
            asm_write_header(out, n->target);
            in_function = 1;
        } break;

        case TAC_ENDFUNC: {
            asm_write_footer(out);
            in_function = 0;
            params_reset();
            free_var_map();
        } break;

        case TAC_EXTERN: {
        } break;

        case TAC_LABEL: {
            asm_write_label(out, n->target);
        } break;

        case TAC_GOTO: {
            asm_write_jump(out, n->target);
        } break;

        case TAC_IFZ: {
            load_i32_to_eax(out, n->arg1);
            fprintf(out, "    test    eax, eax\n");
            fprintf(out, "    je      %s\n", n->target);
        } break;

        case TAC_ASSIGN: {
            asm_write_mov(out, n->target, n->arg1);
        } break;

        case TAC_SUM: {
            load_i32_to_eax(out, n->arg1);
            asm_write_add(out, n->target, n->arg2);
        } break;

        case TAC_MINUS: {
            load_i32_to_eax(out, n->arg1);
            asm_write_sub(out, n->target, n->arg2);
        } break;

        case TAC_MUL: {
            load_i32_to_eax(out, n->arg1);
            asm_write_mul(out, n->target, n->arg2);
        } break;

        case TAC_DIV: {
            load_i32_to_eax(out, n->arg1);
            load_i32_to_ecx(out, n->arg2);
            fprintf(out, "    cdq\n");              
            fprintf(out, "    idiv    ecx\n");      
            store_eax_to(out, n->target);
        } break;

        case TAC_MOD: {
            load_i32_to_eax(out, n->arg1);
            load_i32_to_ecx(out, n->arg2);
            fprintf(out, "    cdq\n");
            fprintf(out, "    idiv    ecx\n");
            fprintf(out, "    mov     eax, edx\n");
            store_eax_to(out, n->target);
        } break;

        case TAC_LESS: {
            asm_write_cmp(out, n->arg1, n->arg2);
            fprintf(out, "    setl    al\n");
            fprintf(out, "    movzx   eax, al\n");
            store_eax_to(out, n->target);
        } break;

        case TAC_GREATER: {
            asm_write_cmp(out, n->arg1, n->arg2);
            fprintf(out, "    setg    al\n");
            fprintf(out, "    movzx   eax, al\n");
            store_eax_to(out, n->target);
        } break;

        case TAC_EQ: {
            asm_write_cmp(out, n->arg1, n->arg2);
            fprintf(out, "    sete    al\n");
            fprintf(out, "    movzx   eax, al\n");
            store_eax_to(out, n->target);
        } break;

        case TAC_NEG: {
            load_i32_to_eax(out, n->arg1);
            fprintf(out, "    neg     eax\n");
            store_eax_to(out, n->target);
        } break;

        case TAC_NOT: {
            load_i32_to_eax(out, n->arg1);
            fprintf(out, "    test    eax, eax\n");
            fprintf(out, "    sete    al\n");
            fprintf(out, "    movzx   eax, al\n");
            store_eax_to(out, n->target);
        } break;

        case TAC_AND: {
            load_i32_to_eax(out, n->arg1);
            fprintf(out, "    cmp     eax, 0\n");
            fprintf(out, "    setne   al\n");
            fprintf(out, "    movzx   eax, al\n");

            load_i32_to_ecx(out, n->arg2);
            fprintf(out, "    cmp     ecx, 0\n");
            fprintf(out, "    setne   cl\n");
            fprintf(out, "    movzx   ecx, cl\n");

            fprintf(out, "    and     eax, ecx\n");
            store_eax_to(out, n->target);
        } break;

        case TAC_OR: {
            load_i32_to_eax(out, n->arg1);
            fprintf(out, "    cmp     eax, 0\n");
            fprintf(out, "    setne   al\n");
            fprintf(out, "    movzx   eax, al\n"); 

            load_i32_to_ecx(out, n->arg2);
            fprintf(out, "    cmp     ecx, 0\n");
            fprintf(out, "    setne   cl\n");
            fprintf(out, "    movzx   ecx, cl\n");

            fprintf(out, "    or      eax, ecx\n");
            store_eax_to(out, n->target);
        } break;

        case TAC_PARAM: {
            params_push(n->arg1);
        } break;

        case TAC_CALL: {
            int expected = 0;
            if (n->arg2) expected = atoi(n->arg2);

            for (int i = 0; i < pending_count; ++i) {
                move_arg_to_reg(out, i, pending_params[i]);
            }


            fprintf(out, "    call    %s\n", n->arg1 ? n->arg1 : "unknown_func");

            if (pending_count > 6) {
                int extra = (pending_count - 6) * 8;
                fprintf(out, "    add     rsp, %d\n", extra);
            }

            if (n->target && *n->target) {
                store_eax_to(out, n->target);
            }

            params_reset();
        } break;

        case TAC_RETURN: {
            if (n->arg1) {
                load_i32_to_eax(out, n->arg1);
            }
            asm_write_footer(out);
        } break;

        case TAC_WHILE: {
            asm_write_label(out, n->target);
        } break;

        default: {
            fprintf(out, "    # [WARN] op no soportado id=%d\n", (int)n->op);
        } break;
        }

        n = n->next;
    }

    if (in_function) {
        asm_write_footer(out);
        free_var_map();
        params_reset();
    }
}
