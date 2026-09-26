typedef struct {
    StateFrame past;
    StateFrame futur;
} SpaceSimple2D;

typedef struct {
    StateVect past;
    StateVect futur;
} SpaceSimple1D;

typedef struct {
    SpaceSimple2D* space;
    Conex* conex;
    Func* func;
    void (*step
} RunSimple2D;


#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <varargs.h>

#include "tcl.h"
#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "util/named.h"
#include "util/str.h"
#include "frame/frame.h"

print(StateVect* sv) {
    int i;

    for (i = 0; i < sv->size; ++i) {
	printf("%d ", sv->ptr[i]);
    }
    printf("\n");
}

bind_loop(StateVect* in, StateVect* out, int cnt) {
    int i;

    if (cnt == in->size) {
	print(out);
	return;
    }
    for (i = 0; i < in->ptr[cnt]; ++i) {
	out->ptr[cnt] = i;
	gen(in, out, cnt + 1);
    }
}

bind_loop(Func* func, int cnt) {
    int i;

    if (cnt == func->in->cnt) {
	func->func(func->in->ptr, func->out->ptr, func->arg);
	func->tab->ptr[mk_index(func->cnt, func->in] = 
	return;
    }
    for (i = 0; i < in->ptr[cnt]; ++i) {
	out->ptr[cnt] = i;
	gen(in, out, cnt + 1);
    }
}

char* bind(Func* func) {
    if (!func->tab) {
	func->tab = SV_new(func->ispec->size);
    }
    for (index = var = 0; var < func->ispec->cnt; ++var) {
	for (dim = 0; dim < func->ispec->ptr[var]->info->cnt ; ++dim, ++index) {
	    func->size[index] = func->ispec->ptr[var]->size;
	}
    }
    bind_loop(func);
}

char* cmd_name;

main() {
    StateVect* in;
    StateVect* out;
    int i;

    in = SV_new(4);
    out = SV_new(4);

    for (i = 0; i < in->size - 1; ++i) {
	in->ptr[i] = 2;
    }
    in->ptr[i] = 8;
    gen(in, out, 0);
}

