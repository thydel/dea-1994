#include <stdio.h>
#include <varargs.h>
#include <malloc.h>
#include <assert.h>

#include "str.h"
#include "cgen.h"

char* nil = 0;
char* nul = "";

static char _buf[4096];
char* buf = &_buf[0];

char* eval(int e) {
    return strn(buf, sprintf(buf, "%d", e));
}

char* cond(int test, char* true, char* false) {
    return test ? true : false;
}

#define CHK(ac, size) assert(ac > 1 && ac < 64 && size > 2 && size < 4096)

SEQ(Cseq);
char* Cseq_(int ac, char** av, int size) {
    char* ret;
    char* sep;
    int i;
    
    CHK(ac, size);
    ac = rem_nul(ac, av);
    sep = ";\n";
    ret = alloc(size + ac * strlen(sep) + 1);
    for (i = 0; i < ac; ++i) {
	strcat(ret, append(av[i], sep, nil));

    }
    return ret;
}

SEQ(Clist);
char* Clist_(int ac, char** av, int size) {
    char* ret;
    char* sep;
    int i;

    CHK(ac, size);
    ac = rem_nul(ac, av);
    sep = ", ";
    ret = alloc(size + (ac - 1) * strlen(sep) + 1);
    for (i = 0; i < ac - 1; ++i) {
	strcat(ret, append(av[i], sep, nil));
    }
    return append("(", ret, av[i], ")", nil);
}

SEQ(Cor);
char* Cor_(int ac, char** av, int size) {
    char* ret;
    char* sep;
    int i;

    CHK(ac, size);
    ac = rem_nul(ac, av);
    sep = " | ";
    ret = alloc(size + (ac - 1) * strlen(sep) + 1);
    for (i = 0; i < ac - 1; ++i) {
	strcat(ret, append(av[i], sep, nil));
    }
    return append("(", ret, av[i], ")", nil);
}

char* Cdeclare(char* id, char* args, char* local, char* body) {
    return strn(buf, sprintf(buf, "%s%s\n{\n%s\n%s}\n", id, args, local, body));
}

char* Ccmnt(char* c, char* s) {
    return append("/* ", c, " */\n", s, nil);
}

char* Cset(char* l, char* r) {
    return append(l, " = ", r, nil);
}

char* Cvar(char* t, char* i) {
    return append(t, " ", i, nil);
}

char* Cptr(char* t, char* i) {
    return append(t, "* ", i, nil);
}

char* Crptr(char* t, char* i) {
    return append("register ", Cptr(t, i), nil);
}

BINOP(Cadd, +);
BINOP(Cand, &);
BINOP(Csub, -);
BINOP(Clshift, <<);
BINOP(Crshift, >>);

char* Carray(char* l, char* r) {
    return append(l, "[", r, "]", nil);
}

char* Cnext(char* s) {
    return append("*", s, "++", nil);
}

char* Cstar(char* s) {
    return append("*", s, nil);
}

char* Cuminus(char* s) {
    return append("-", s, nil);
}

char* Cloop(char* cnt, char* index, char* str) {
    return strn(buf, sprintf(buf, "for (%s = %s; %s--;) {\n%s}\n", index, cnt, index, str));
}

char* Cfield(char* l, char* r) {
    return append(l, "->", r, nil);
}
