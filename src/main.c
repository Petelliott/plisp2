#include <plisp/object.h>
#include <plisp/read.h>
#include <plisp/write.h>
#include <plisp/compile.h>
#include <plisp/toplevel.h>
#include <plisp/builtin.h>
#include <plisp/gc.h>
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
    plisp_init_gc();
    plisp_init_reader();
    plisp_init_compiler(argv[0]);
    plisp_init_toplevel();
    plisp_init_builtin();

    if (argc > 1) {
        plisp_c_load(argv[1]);
    } else {

        plisp_t filesym = plisp_intern(plisp_make_symbol("%file"));
        plisp_toplevel_define(filesym, plisp_make_bool(false));
        while (1) {
            printf("> ");
            plisp_t obj = plisp_c_read(stdin);
            if (plisp_c_eofp(obj)) {
                putchar('\n');
                break;
            }
            obj = plisp_toplevel_eval(obj);
            if (obj != plisp_unspec) {
                plisp_c_write(stdout, obj);
                putchar('\n');
            }
        }
    }

    plisp_end_compiler();

    return 0;
}
