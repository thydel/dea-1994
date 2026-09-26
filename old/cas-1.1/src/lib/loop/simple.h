typedef struct {
    int magic;
    Func* func;
    StateFrame* past;
    StateFrame* futur;
    void (*step)(StateVect*, StateFrame*, StateFrame*);
    int cnt;
} Simple;

extern Simple* Simple_new(Func*, StateFrame*, StateFrame*);

extern void Simple_init(Tcl_Interp*);
extern void* Simple_tbl;
