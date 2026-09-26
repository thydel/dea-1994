#ifndef STR_H
#define STR_H

#define STR_VALIST(func) \
char* func(va_alist) \
va_dcl { \
    va_list ap; \
    extern char* func ## _(int, char**, int); \
    static char* varg[1024]; \
    int cnt; \
    int size; \
    int i; \
    va_start(ap); \
    for (cnt = 0; (varg[cnt++] = va_arg(ap, char *)) != 0;); \
    va_end(ap); \
    for (size = 0, i = 0; i < cnt - 1; ++i) { \
	size += strlen(varg[i]); \
    } \
    return func ## _(cnt - 1, varg, size); \
}

typedef struct {
    char** ptr;
    int cnt;
    int size;
} StrVect;

extern StrVect* StrVect_new();

extern char* alloc(int);
extern char* str(char*);
extern char* strn(char*, int);
/* extern char* len(); */
extern char* append();
extern int rem_nul(int, char**);

#endif
