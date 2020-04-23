#ifndef PLISP_BUILTIN_H
#define PLISP_BUILTIN_H

#include <plisp/object.h>

void plisp_init_builtin(void);

void plisp_define_builtin(const char *name, plisp_fn_t fun);

plisp_t plisp_builtin_plus(plisp_t *clos, size_t nargs, plisp_t a, plisp_t b, ...);
plisp_t plisp_builtin_minus(plisp_t *clos, size_t nargs, plisp_t a, plisp_t b, ...);

plisp_t plisp_builtin_cons(plisp_t *clos, size_t nargs, plisp_t car, plisp_t cdr);
plisp_t plisp_builtin_car(plisp_t *clos, size_t nargs, plisp_t cell);
plisp_t plisp_builtin_cdr(plisp_t *clos, size_t nargs, plisp_t cell);

plisp_t plisp_c_reverse(plisp_t lst);
plisp_t plisp_builtin_reverse(plisp_t *clos, size_t nargs, plisp_t lst, plisp_t onto);
plisp_t plisp_builtin_list(plisp_t *clos, size_t nargs, ...);

plisp_t plisp_builtin_not(plisp_t *clos, size_t nargs, plisp_t obj);
plisp_t plisp_builtin_nullp(plisp_t *clos, size_t nargs, plisp_t obj);
plisp_t plisp_builtin_eq(plisp_t *clos, size_t nargs, plisp_t a, plisp_t b);
plisp_t plisp_builtin_lt(plisp_t *clos, size_t nargs, plisp_t a, plisp_t b);

size_t plisp_c_length(plisp_t lst);
plisp_t plisp_builtin_length(plisp_t *clos, size_t nargs, plisp_t lst);

plisp_t plisp_builtin_display(plisp_t *clos, size_t nargs, plisp_t obj);
plisp_t plisp_builtin_write(plisp_t *clos, size_t nargs, plisp_t obj);
plisp_t plisp_builtin_println(plisp_t *clos, size_t nargs, ...);
plisp_t plisp_builtin_newline(plisp_t *clos, size_t nargs);

plisp_t plisp_builtin_collect_garbage(plisp_t *clos, size_t nargs);
plisp_t plisp_builtin_object_addr(plisp_t *clos, size_t nargs, plisp_t obj);

plisp_t plisp_builtin_vector(plisp_t *clos, size_t nargs, ...);
plisp_t plisp_builtin_make_vector(plisp_t *clos, size_t nargs,
                                  plisp_t len, plisp_t init);

#endif
