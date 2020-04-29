#ifndef PLISP_READ_H
#define PLISP_READ_H

#include <plisp/object.h>
#include <stdio.h>

extern plisp_t plisp_eof;

bool plisp_c_eofp(plisp_t obj);

void plisp_init_reader(void);

plisp_t plisp_intern(plisp_t sym);
bool plisp_symbol_internedp(plisp_t sym);

plisp_t plisp_c_read(FILE *f);

#endif
