#include <malloc.h>
#include <assert.h>

#include "named.h"

Named null_named = { 0, 0 };

void* Named_get(Named* tab, char* name) {
    int i;

    for (i = 0; tab[i].name; ++i) {
	if (!strcmp(name, tab[i].name)) {
	    return tab[i].ptr;
	}
    }
    return 0;
}

int Named_len(Named* named) {
    int n;

    for (n = 0; named[n].name; ++n) {
	;
    }
    return n;
}

Named* Named_cat(Named* t1, Named* t2) {
    Named* named;
    int i;
    int l1;
    int l2;

    l1 = Named_len(t1);
    l2 = Named_len(t2);
    named = (Named*)malloc((l1 + l2 + 1) * sizeof(Named));
    assert(named);
    for (i = 0; i < l1; ++i) {
	named[i] = t1[i];
    }
    for (i = 0; i < l2; ++i) {
	named[l1 + i] = t2[i];
    }
    named[l1 + l2].name = 0;
    return named;
}
