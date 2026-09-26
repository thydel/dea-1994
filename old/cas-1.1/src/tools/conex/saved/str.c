#include <varargs.h>
#include <malloc.h>
#include <assert.h>

#include "str.h"

char* nil = 0;
char* nul = "";

static char _buf[4096];
char* buf = &_buf[0];

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

SEQ(len);
int len_(int ac, char** av, int size) {
    return size;
}

SEQ(append);
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
