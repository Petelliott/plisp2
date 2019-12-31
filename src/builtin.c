#include <plisp/builtin.h>
#include <plisp/object.h>
#include <plisp/read.h>
#include <plisp/toplevel.h>
#include <assert.h>
#include <stdarg.h>

void plisp_init_builtin(void) {
    // gcc passes variadic args just like regular args, so this is
    // okayish. the C standard forbids casting form f(...) to f().
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

    plisp_define_builtin("+", plisp_builtin_plus);
    plisp_define_builtin("-", plisp_builtin_minus);

    plisp_define_builtin("cons", plisp_builtin_cons);
    plisp_define_builtin("car", plisp_builtin_car);
    plisp_define_builtin("cdr", plisp_builtin_cdr);

    plisp_define_builtin("reverse", plisp_builtin_reverse);
    plisp_define_builtin("list", plisp_builtin_list);

    plisp_define_builtin("not", plisp_builtin_not);
    plisp_define_builtin("null?", plisp_builtin_nullp);
    plisp_define_builtin("eq?", plisp_builtin_eq);

    #pragma GCC diagnostic pop
}

void plisp_define_builtin(const char *name, plisp_fn_t fun) {
    plisp_toplevel_define(
        plisp_intern(plisp_make_symbol(name)),
        plisp_make_closure(NULL, fun));
}

plisp_t plisp_builtin_plus(size_t nargs, plisp_t a, plisp_t b, ...) {
    assert(plisp_c_fixnump(a));
    assert(plisp_c_fixnump(b));
    assert(nargs >= 2);

    va_list vl;
    va_start(vl, b);

    plisp_t sum = a + b;

    for (size_t i = 2; i < nargs; ++i) {
        plisp_t arg = va_arg(vl, plisp_t);
        assert(plisp_c_fixnump(arg));
        sum += arg;
    }

    return sum;
}

plisp_t plisp_builtin_minus(size_t nargs, plisp_t a, plisp_t b, ...) {
    assert(plisp_c_fixnump(a));
    assert(plisp_c_fixnump(b));
    assert(nargs >= 2);

    va_list vl;
    va_start(vl, b);

    plisp_t sum = a - b;

    for (size_t i = 2; i < nargs; ++i) {
        plisp_t arg = va_arg(vl, plisp_t);
        assert(plisp_c_fixnump(arg));
        sum -= arg;
    }

    return sum;
}

plisp_t plisp_builtin_cons(size_t nargs, plisp_t car, plisp_t cdr) {
    assert(nargs == 2);
    return plisp_cons(car, cdr);
}

plisp_t plisp_builtin_car(size_t nargs, plisp_t cell) {
    assert(nargs == 1);
    return plisp_car(cell);
}

plisp_t plisp_builtin_cdr(size_t nargs, plisp_t cell) {
    assert(nargs == 1);
    return plisp_car(cell);
}

plisp_t plisp_builtin_reverse(size_t nargs, plisp_t lst, plisp_t onto) {
    assert(nargs == 1 || nargs == 2);

    if (plisp_c_nullp(lst)) {
        return onto;
    }

    if (nargs == 1) {
        onto = plisp_nil;
    }

    return plisp_builtin_reverse(2, plisp_cdr(lst),
                                 plisp_cons(plisp_car(lst), onto));
}

plisp_t plisp_builtin_list(size_t nargs, ...) {
    va_list vl;
    va_start(vl, nargs);

    plisp_t lst = plisp_nil;
    for (size_t i = 0; i < nargs; ++i) {
        lst = plisp_cons(va_arg(vl, plisp_t), lst);
    }

    return plisp_builtin_reverse(2, lst, plisp_nil);
}

plisp_t plisp_builtin_not(size_t nargs, plisp_t obj) {
    assert(nargs == 1);
    if (obj == plisp_make_bool(false)) {
        return plisp_make_bool(true);
    } else {
        return plisp_make_bool(false);
    }
}

plisp_t plisp_builtin_nullp(size_t nargs, plisp_t obj) {
    assert(nargs == 1);
    return plisp_make_bool(plisp_c_nullp(obj));
}

plisp_t plisp_builtin_eq(size_t nargs, plisp_t a, plisp_t b) {
    assert(nargs == 2);
    return plisp_make_bool(a == b);
}
