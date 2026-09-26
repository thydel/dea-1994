typedef struct {
    int magic;
    char* handle;
    ConexSpec* spec;		/* i/o conexion for the rule */
    StateVect* tab;		/* the rule table */
    void (*func)(int*, int*, void*); /* actual C function implementing the rule */
    void* (*parse)(int, char**); /* parse private args for the rule */
				/* (make a void* from an av[ac] */
    void* arg;			/* private args given to the func */
    char* msg;			/* used by methods to pass error msg up to tcl */

    /* stats */
    int cnt;			/* cnt of call upon this rule */
    CntVect* sum;		/* sum of rule entry access */
    CntVect* time_sum;		/* sum of rule entry access upon time */
} Func;

Func* Func_new(ConexSpec*, StateVect*, void (*)(int*, int*, void*), void* (*)(int, char**));
void Func_bind(Func*, int, char**);

extern void Func_init(Tcl_Interp*);
extern void* Func_tbl;
