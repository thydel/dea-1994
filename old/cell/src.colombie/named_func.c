#include "named_func.h"

int (*Named_Func_get(Named_Func* tab, char* name))()
{
    int i;

    for (i = 0; tab[i].name; ++i) {
	if (!strcmp(name, tab[i].name)) {
	    return tab[i].func;
	}
    }
    return 0;
}

