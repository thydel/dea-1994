#define STR(name) static char* name = #name

#define CVAR(name) static int name = #name

#define BINOP(name, op) \
char* name(char* l, char* r) { \
    return append("(", l, " ", #op, " ", r, ")", nil); \
}

extern char* eval(int);
extern char* cond(int, char*, char*);

extern char* Cseq();
extern char* Clist();
extern char* Cor();
extern char* Cdeclare(char*, char*, char*, char*);
extern char* Ccmnt(char*, char*);
extern char* Cptr(char*, char*);
extern char* Cvar(char*, char*);
extern char* Crptr(char*, char*);
extern char* Cset(char*, char*);
extern char* Cadd(char*, char*);
extern char* Cand(char*, char*);
extern char* Csub(char*, char*);
extern char* Clshift(char*, char*);
extern char* Crshift(char*, char*);
extern char* Carray(char*, char*);
extern char* Cnext(char*);
extern char* Cstar(char*);
extern char* Cuminus(char*);
extern char* Cloop(char*, char*, char*);
extern char* Cfield(char*, char*);

extern char* nil;
extern char* nul;
extern char* buf;

