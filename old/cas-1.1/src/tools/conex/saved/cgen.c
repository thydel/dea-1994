#include <stdio.h>
#include <varargs.h>
#include <malloc.h>
#include <assert.h>

#include "str.h"
#include "cgen.h"

#define CHK(ac, size) assert(ac > 1 && ac < 64 && size > 2 && size < 4096)

SEQ(seq);
char* seq_(int ac, char** av, int size) {
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

SEQ(list);
char* list_(int ac, char** av, int size) {
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

SEQ(or);
char* or_(int ac, char** av, int size) {
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

char* eval(int e) {
    return strn(buf, sprintf(buf, "%d", e));
}

char* declare(char* id, char* args, char* local, char* body) {
    return strn(buf, sprintf(buf, "%s%s\n{\n%s\n%s}\n", id, args, local, body));
}

char* cmnt(char* c, char* s) {
    return append("/* ", c, " */\n", s, nil);
}

char* set(char* l, char* r) {
    return append(l, " = ", r, nil);
}

char* var(char* t, char* i) {
    return append(t, " ", i, nil);
}

char* ptr(char* t, char* i) {
    return append(t, "* ", i, nil);
}

char* rptr(char* t, char* i) {
    return append("register ", ptr(t, i), nil);
}

BINOP(add, +);
BINOP(and, &);
BINOP(sub, -);
BINOP(lshift, <<);
BINOP(rshift, >>);

char* array(char* l, char* r) {
    return append(l, "[", r, "]", nil);
}

char* next(char* s) {
    return append("*", s, "++", nil);
}

char* star(char* s) {
    return append("*", s, nil);
}

char* uminus(char* s) {
    return append("-", s, nil);
}

char* loop(char* cnt, char* index, char* str) {
    return strn(buf, sprintf(buf, "for (%s = %s; %s--;) {\n%s}\n", index, cnt, index, str));
}

char* cond(int test, char* true, char* false) {
    return test ? true : false;
}

char* field(char* l, char* r) {
    return append(l, "->", r, nil);
}
