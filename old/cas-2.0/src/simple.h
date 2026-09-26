typedef struct Simple2D {
    int magic;
    char* handle;
    char* name;
    int refcnt;
    struct Simple2D* self;

    Time2D* time;		/* space time */
    Func* func;			/* operation on space time */

} Simple2D;

extern Simple2D* Simple2D_alloc();
extern Simple2D* Simple2D_new(Simple2D*, Time2D*, Func*);
extern void Simple2D_delete(Simple2D*);
extern void Simple_init(Tcl_Interp*);
extern void* Simple_tbl;
