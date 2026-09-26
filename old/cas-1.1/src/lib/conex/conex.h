typedef struct {
    int magic;
    char* name;			/* unique id */
    int cnt;			/* multiplicateur for ConexVar */
} ConexType;

extern ConexType* ConexType_new(char*, int);

typedef struct {
    int magic;
    ConexType* type;		/* type of var (moore, local ...) */
    int nbit;			/* number of bits hold by the var */
} ConexVar;

extern ConexVar* ConexVar_new(ConexType*, int);
extern bool ConexVar_match(ConexVar*, ConexVar*);

typedef struct {
    int magic;
    int state;			/* actual value */
    int nbit;			/* number of bits hold by the val */
    int nstate;			/* pow(2, nbit) */
    int maxval;			/* nstate - 1 */
    int offset;			/* offset in the bit string for this val */
    int mask;			/* maxval << offset */
} ConexVal;

extern ConexVal* ConexVal_new(ConexVar*, int);

typedef struct {
    int magic;
    int cnt;
    ConexVar** ptr;
    int narg;			/* sum of ConexVar multiplicator (ConexType.cnt) */
} ConexVarList;

extern ConexVarList* ConexVarList_new();
extern ConexVarList* ConexVarList_new_1(ConexVar**, int);
extern bool ConexVarList_match(ConexVarList*, ConexVarList*);

typedef struct {
    int magic;
    int cnt;
    ConexVal** ptr;
    int* arg;			/* func arg form */
    int index;			/* table index form */
    int nbit;			/* sum of bits hold by the list */
    int nstate;			/* pow(2, nbit) */
} ConexValList;

extern ConexValList* ConexValList_new(ConexVarList*);
extern void ConexValList_incr(ConexValList*);
extern void ConexValList_zero(ConexValList*);
extern void ConexValList_implode(ConexValList*);
extern void ConexValList_explode(ConexValList*);
extern void ConexValList_set_arg(ConexValList*);
extern void ConexValList_get_arg(ConexValList*);

typedef struct {
    int magic;
    ConexVarList *var;
    ConexValList *val;
} ConexList;

extern ConexList* ConexList_new(ConexVarList*);

typedef struct {
    int magic;
    ConexList* in;
    ConexList* out;
    void (*apply)();
} ConexSpec;

extern ConexSpec* ConexSpec_new(ConexList*, ConexList*, void (*)());

extern void Conex_init(Tcl_Interp*);
extern void* Conex_tbl;
