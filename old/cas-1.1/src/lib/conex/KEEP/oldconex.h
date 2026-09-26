typedef struct {
    int magic;
    ConexSpec* spec;
    void (*run)();
    void (*bind)();
} Conex;

extern Conex* Conex_new(ConexSpec*, void (*)(), void (*)());

extern void Conex_init(Tcl_Interp*);
extern void* Conex_tbl;
