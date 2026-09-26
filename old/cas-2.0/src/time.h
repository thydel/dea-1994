typedef struct Time2D {
    int magic;
    char* handle;
    char* name;
    int refcnt;
    struct Time2D* self;

    /* private */
    Space2D** ptr;		/* vector of space used as a ??? */
    int cnt;			/* cnt of allocated spaces */

    Space2D* zero;		/* empty space for past whan at BOT */
    Space2D* acu;		/* the futur of a function on a space */

    int point;			/* current space time point index */
    int mark;
    int time;			/* absolute time index */
    
    /* public */
    Space2D* past;
    Space2D* present;		/* for direct cmd access */
    Space2D* futur;

    /* stats */
    CntVect* sum;		/* collect the sum of each space */
} Time2D;

extern Time2D* Time2D_alloc();
extern Time2D* Time2D_new(Time2D*, Space2D*, int);
extern void Time2D_delete(Time2D*);
extern void Time_init(Tcl_Interp*);
extern void* Time_tbl;
