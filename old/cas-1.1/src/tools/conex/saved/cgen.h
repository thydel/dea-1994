#define BINOP(name, op) \
char* name(char* l, char* r) { \
    return append("(", l, " ", #op, " ", r, ")", nil); \
}

extern char* seq();
extern char* list();
extern char* or();
extern char* eval(int);
extern char* declare(char*, char*, char*, char*);
extern char* cmnt(char*, char*);
extern char* ptr(char*, char*);
extern char* var(char*, char*);
extern char* rptr(char*, char*);
extern char* set(char*, char*);
extern char* add(char*, char*);
extern char* and(char*, char*);
extern char* sub(char*, char*);
extern char* lshift(char*, char*);
extern char* rshift(char*, char*);
extern char* array(char*, char*);
extern char* next(char*);
extern char* star(char*);
extern char* uminus(char*);
extern char* loop(char*, char*, char*);
extern char* cond(int, char*, char*);
extern char* field(char*, char*);
