#include <malloc.h>
#include <assert.h>
#include <varargs.h>

#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "util/named.h"
#include "conex.h"

#define N_CONEX 64

void* Conex_tbl;

ConexType* ConexType_new(char* name, int cnt) {
    ConexType* zis;

    zis = (ConexType*)malloc(sizeof(ConexType));
    assert(zis);
    zis->magic = magic(CONEX_TYPE);
    zis->name = name;
    zis->cnt = cnt;
    return zis;
}

int cmd_ConexType_new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    ConexType* info;
    char* name;
    int cnt;

    void* ptr;
    char handle[64];

    if (ac < 2 || ac > 3) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", "name [cnt]", 0);
	return TCL_ERROR;
    }
    
    name = av[1];
    cnt = 0;
    if (ac == 3) {
	cnt = atoi(av[2]);
    }

    info = ConexType_new(name, cnt);

    Tcl_HandleAlloc(Conex_tbl, handle);
    ptr = Tcl_HandleXlate(interp, Conex_tbl, handle);
    assert(ptr);

    *(ConexType**)ptr = info;

    strcpy(interp->result, handle);
    return TCL_OK;
}

ConexVar* ConexVar_new(ConexType* type, int nbit) {
    ConexVar* zis;

    zis = (ConexVar*)malloc(sizeof(ConexVar));
    assert(zis);
    zis->magic = magic(CONEX_VAR);
    zis->type = type;
    zis->nbit = nbit;
    return zis;
}

int cmd_ConexVar_new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    ConexVar* var;
    ConexType* type;
    int nbit;

    void* ptr;
    char handle[64];

    if (ac <= 1) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", "ConexType [nbit]", 0);
	return TCL_ERROR;
    }
    
    type = *(ConexType**)Tcl_HandleXlate(interp, Conex_tbl, av[1]);
    if (!type) {
	return TCL_ERROR;
    }
    nbit = 0;
    if (ac >= 3) {
	nbit = atoi(av[2]);
    }

    var = ConexVar_new(type, nbit);

    Tcl_HandleAlloc(Conex_tbl, handle);
    ptr = Tcl_HandleXlate(interp, Conex_tbl, handle);
    assert(ptr);

    *(ConexVar**)ptr = var;

    strcpy(interp->result, handle);
    return TCL_OK;
}

bool ConexVar_match(ConexVar* a, ConexVar* b) {
    assert(a->magic == magic(CONEX_VAR) && b->magic == magic(CONEX_VAR));
    return !strcmp(a->type->name, b->type->name) && a->nbit == b->nbit;
}

ConexVal* ConexVal_new(ConexVar* var, int offset) {
    ConexVal* zis;

    zis = (ConexVal*)malloc(sizeof(ConexVal));
    assert(zis);
    zis->magic = magic(CONEX_VAL);
    zis->state = 0;
    zis->nbit = var->nbit;
    zis->nstate = 1 << zis->nbit;
    zis->maxval = zis->nstate - 1;
    zis->offset = offset;
    zis->mask = zis->maxval << zis->offset;
    return zis;
}

ConexVarList* ConexVarList_new(va_alist)
va_dcl {
    va_list ap;
    static ConexVar* varg[16];
    int cnt;

    va_start(ap);
    for (cnt = 0; (varg[cnt++] = va_arg(ap, ConexVar*)) != 0;);
    va_end(ap);
    assert(cnt < 16);

    return ConexVarList_new_1(varg, cnt - 1);
}

ConexVarList* ConexVarList_new_1(ConexVar** cv, int ac) {
    ConexVarList* zis;
    int i;

    zis = (ConexVarList*)malloc(sizeof(ConexVarList));
    assert(zis);
    zis->magic = magic(CONEX_VAR_LIST);
    zis->ptr = (ConexVar**)malloc(sizeof(ConexVar*) * ac);
    assert(zis->ptr);
    zis->cnt = ac;
    for (zis->narg = i = 0; i < ac; ++i) {
	zis->ptr[i] = cv[i];
	zis->narg += zis->ptr[i]->type->cnt;
    }
    return zis;
}

int cmd_ConexVarList_new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    ConexVar* cv[16];
    char handle[64];
    void* ptr;
    int i;

    assert(ac < 17);
    for (i = 1; i < ac; ++i) {
	cv[i - 1] = *(ConexVar**)Tcl_HandleXlate(interp, Conex_tbl, av[i]);
	if (!cv[i - 1]) {
	    return TCL_ERROR;
	}
    }

    Tcl_HandleAlloc(Conex_tbl, handle);
    ptr = Tcl_HandleXlate(interp, Conex_tbl, handle);
    assert(ptr);

    *(ConexVarList**)ptr = ConexVarList_new_1(cv, ac - 1);

    strcpy(interp->result, handle);
    return TCL_OK;
}

bool ConexVarList_match(ConexVarList* a, ConexVarList* b) {
    int i;

    assert(a->magic == magic(CONEX_VAR_LIST) && b->magic == magic(CONEX_VAR_LIST));
    if (a->cnt != b->cnt) {
	return false;
    }
    if (a->narg != b->narg) {
	return false;
    }
    for (i = 0; i < a->cnt; ++i) {
	if (!ConexVar_match(a->ptr[i], b->ptr[i])) {
	    return false;
	}
    }
    return true;
}

ConexValList* ConexValList_new(ConexVarList *var_list) {
    ConexValList* zis;
    int index;
    int offset;
    int nbit;
    int i;
    int j;

    zis = (ConexValList*)malloc(sizeof(ConexValList));
    assert(zis);
    zis->magic = magic(CONEX_VAL_LIST);
    zis->cnt = var_list->narg;
    zis->ptr = (ConexVal**)malloc(sizeof(ConexVal**) * zis->cnt);
    assert(zis->ptr);
    for (index = offset = nbit = i = 0; i < var_list->cnt; ++i) {
	nbit += var_list->ptr[i]->nbit * var_list->ptr[i]->type->cnt;
	for (j = 0; j < var_list->ptr[i]->type->cnt; ++j, ++index) {
	    zis->ptr[index] = ConexVal_new(var_list->ptr[i], offset);
	    assert(zis->ptr[index]);
	    offset += zis->ptr[index]->nbit;
	}
    }
    zis->arg = (int*)malloc(sizeof(int) * zis->cnt);
    for (i = 0; i < zis->cnt; ++i) {
	zis->arg[i] = 0;
    }
    zis->index = 0;
    zis->nbit = nbit;
    zis->nstate = 1 << zis->nbit;
    return zis;
}

void ConexValList_incr(ConexValList* zis) {
    int i;

    assert(zis->index < zis->nstate);
    ++zis->index;
    for (i = 0; i < zis->cnt; ++i) {
	if (zis->ptr[i]->state < zis->ptr[i]->maxval) {
	    ++zis->ptr[i]->state;
	    return;
	}
	zis->ptr[i]->state = 0;
    }
}

void ConexValList_zero(ConexValList* zis) {
    int i;

    zis->index = 0;
    for (i = 0; i < zis->cnt; ++i) {
	zis->arg[i] = zis->ptr[i]->state = 0;
    }
}

void ConexValList_set_arg(ConexValList* zis) {
    int i;

    for (i = 0; i < zis->cnt; ++i) {
	zis->arg[i] = zis->ptr[i]->state;
    }
}

void ConexValList_get_arg(ConexValList* zis) {
    int i;

    for (i = 0; i < zis->cnt; ++i) {
	zis->ptr[i]->state = zis->arg[i];
    }
}

void ConexValList_implode(ConexValList* zis) {
    int i;

    zis->index = 0;
    for (i = 0; i < zis->cnt; ++i) {
	zis->index |= (zis->ptr[i]->state & zis->ptr[i]->maxval) << zis->ptr[i]->offset;
    }    
}

void ConexValList_explode(ConexValList* zis) {
    int i;

    for (i = 0; i < zis->cnt; ++i) {
	zis->ptr[i]->state = (zis->index & zis->ptr[i]->mask) >> zis->ptr[i]->offset;
    }    
}

ConexList* ConexList_new(ConexVarList* var_list) {
    ConexList* zis;

    zis = (ConexList*)malloc(sizeof(ConexList));
    assert(zis);
    zis->magic = magic(CONEX_LIST);
    zis->var = var_list;
    zis->val = ConexValList_new(var_list);
    assert(zis->val);
    return zis;
}

int cmd_ConexList_new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    ConexList* conex_list;
    ConexVarList* var_list;

    void* ptr;
    char handle[64];

    if (ac <= 1) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", "ConexVarList", 0);
	return TCL_ERROR;
    }
    
    var_list = *(ConexVarList**)Tcl_HandleXlate(interp, Conex_tbl, av[1]);
    if (!var_list) {
	return TCL_ERROR;
    }

    conex_list = ConexList_new(var_list);

    Tcl_HandleAlloc(Conex_tbl, handle);
    ptr = Tcl_HandleXlate(interp, Conex_tbl, handle);
    assert(ptr);

    *(ConexList**)ptr = conex_list;

    strcpy(interp->result, handle);
    return TCL_OK;
}

ConexSpec* ConexSpec_new(ConexList* in, ConexList* out, void (*apply)()) {
    ConexSpec* zis;

    assert(in && in->magic == magic(CONEX_LIST) &&
	   out && out->magic == magic(CONEX_LIST) &&
	   apply);
    zis = (ConexSpec*)malloc(sizeof(ConexSpec));
    assert(zis);
    zis->magic = magic(CONEX_SPEC);
    zis->in = in;
    zis->out = out;
    zis->apply = apply;
    return zis;
}

int cmd_ConexSpec_new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av) {
    extern Named* named_func;

    ConexSpec* conex_spec;
    ConexList* in;
    ConexList* out;
    void (*apply)();

    void* ptr;
    char handle[64];

    if (ac <= 3) {
	Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", "ConexList ConexList apply", 0);
	return TCL_ERROR;
    }
    
    in = *(ConexList**)Tcl_HandleXlate(interp, Conex_tbl, av[1]);
    if (!in) {
	return TCL_ERROR;
    }

    out = *(ConexList**)Tcl_HandleXlate(interp, Conex_tbl, av[2]);
    if (!out) {
	return TCL_ERROR;
    }

    apply = (void (*)())Named_get(named_func, av[3]);
    if (!apply) {
	Tcl_AppendResult(interp, av[0], ": ", av[3], " not found", 0);
	return TCL_ERROR;
    }

    conex_spec = ConexSpec_new(in, out, apply);

    Tcl_HandleAlloc(Conex_tbl, handle);
    ptr = Tcl_HandleXlate(interp, Conex_tbl, handle);
    assert(ptr);

    *(ConexSpec**)ptr = conex_spec;

    strcpy(interp->result, handle);
    return TCL_OK;
}

void Conex_init(Tcl_Interp *interp) {
    Conex_tbl = Tcl_HandleTblInit("Conex", sizeof(void*), N_CONEX);
    Tcl_CreateCommand(interp, "ConexType", cmd_ConexType_new,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "ConexVar", cmd_ConexVar_new,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "ConexVarList", cmd_ConexVarList_new,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "ConexList", cmd_ConexList_new,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "ConexSpec", cmd_ConexSpec_new,
		      (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);
}
