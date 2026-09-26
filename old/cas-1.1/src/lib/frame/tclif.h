#define DATA_DCL(name) \
    Tcl_CreateCommand(interp, #name, cmd_ ## name ## _new, (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);

#define CMD_DCL(name) \
    Tcl_CreateCommand(interp, #name, cmd_ ## name, (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);

#define DATA_DEF(name) \
int cmd_ ## name ## _new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av)

#define CMD_DEF(name) \
int cmd_ ## name(ClientData notUsed, Tcl_Interp* interp, int ac, char** av)

#define BAD_ARG(msg) Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", msg, 0)

#define CHECK(n, msg) \
    if (ac != n + 1) { \
	BAD_ARG(msg); \
	return TCL_ERROR; \
    }

#define CREAT(type) \
    Tcl_HandleAlloc(type ## _tbl, buf); \
    ptr[0] = Tcl_HandleXlate(interp, type ## _tbl, buf); \
    assert(ptr[0]);

#define EXTRACT(type, n) \
{ \
    ptr[n] = Tcl_HandleXlate(interp, type ## _tbl, av[n]); \
    if (!ptr[n]) return TCL_ERROR; \
}

#define DATA_DONE \
{ \
    strcpy(interp->result, buf); \
    return TCL_OK; \
}

#define CMD_DONE \
{ \
      return TCL_OK; \
}

#define ARG_TYPE(t, n) *(t**)ptr[n]

#define CntType(n) atoi(av[n])
#define StrType(n) av[n]
