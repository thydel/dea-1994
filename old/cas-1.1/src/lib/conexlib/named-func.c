#include "util/named.h"

#define gen(name) extern void name();
#include "named-func.txt"
#undef gen

#define gen(name) NAMED_P(name),

static Named named_space[] = {
#include "named-func.txt"
    NULL_NAMED
};

extern Named* named_func;

void conexlib_init() {
    named_func = Named_cat(named_func, named_space);
}
