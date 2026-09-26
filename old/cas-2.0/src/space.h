typedef struct Space2D {
    int magic;
    char* handle;
    char* name;
    int refcnt;
    struct Space2D* self;

    char* msg;
    StateFrame* state;
    PlaneFrame* plane;
    int time;
    int nstate;

    /* stats */
    int sum;
    CntVect* histogram;
    CntFrame* time_sum;
} Space2D;

extern Space2D* Space2D_new(Space2D*, int, int, int);
extern void Space2D_delete(Space2D*);

extern void Space_init(Tcl_Interp*);
extern void* Space_tbl;
