typedef struct {
    char* name;
    int (*func)();
} Named_Func;

int (*Named_Func_get(Named_Func*, char*))();
