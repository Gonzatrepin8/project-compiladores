#ifndef ASSEMBLY_CODE_H
#define ASSEMBLY_CODE_H

#include <stdio.h>
#include <string.h>

void generate_assembly(FILE *out);

void asm_write_header(FILE *out, const char *func_name);
void asm_write_footer(FILE *out);
void asm_write_mov(FILE *out, const char *dst, const char *src);
void asm_write_add(FILE *out, const char *dst, const char *src);
void asm_write_sub(FILE *out, const char *dst, const char *src);
void asm_write_mul(FILE *out, const char *dst, const char *src);
void asm_write_cmp(FILE *out, const char *a, const char *b);
void asm_write_label(FILE *out, const char *label);
void asm_write_jump(FILE *out, const char *label);
void asm_write_cond_jump(FILE *out, const char *cond, const char *label);

#endif
