#include <varargs.h>
#include <malloc.h>
#include <assert.h>

#include "str.h"

StrVect* StrVect_new(va_alist)
va_dcl {
    va_list ap;
    StrVect* zis;
    static char* varg[1024];
    int cnt;
    int size;
    int i;

    va_start(ap);
    for (cnt = 0; (varg[cnt++] = va_arg(ap, char *)) != 0;);
    va_end(ap);

    for (size = 0, i = 0; i < cnt - 1; ++i) {
	size += strlen(varg[i]);
    }

    zis = (StrVect*)alloc(sizeof(StrVect));
    zis->ptr = (char**)(sizeof(char*) * cnt);
    zis->cnt = cnt - 1;
    zis->size = size;
    for (i = 0; i < cnt; ++i) {
	zis->ptr[i] = varg[i];
    }

    return zis;
}

char* alloc(int size) {
    char* ret;

    ret = malloc(size);
    assert(ret);
    *ret = 0;
    return ret;
}

char* str(char* s) {
    return strcpy(alloc(strlen(s) + 1), s);
}

char* strn(char* s, int n) {
    return strcpy(alloc(n + 1), s);
}

/*
STR_VALIST(len);
int len_(int ac, char** av, int size) {
    return size;
}
*/

STR_VALIST(append);
char* append_(int ac, char** av, int size) {
    char* ret;
    int i;

    ret = alloc(size + 1);
    for (i = 0; i < ac; ++i) {
	strcat(ret, av[i]);
    }
    return ret;
}

int rem_nul(int ac, char** av) {
    char** tmp;
    int i;
    int cnt;

    tmp = malloc(ac * sizeof(char*));
    assert(tmp);
    for (i = 0, cnt = 0; i < ac; ++i) {
	if (*av[i]) {
	    tmp[cnt++] = av[i];
	}
    }
    for (i = 0; i < cnt; ++i) {
	av[i] = tmp[i];
    }
    av[i] = 0;
    free(tmp);
    return cnt;
}
