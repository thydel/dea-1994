#include "conex.h"
#include "lib.h"

life(Moore* i, Local* o) {
    Local sum;

    Moore_sum8(i, &sum);
    if (sum == 2) {
	*o = i->c;
    } else if (sum == 3) {
	*o = 1;
    } else {
	*o = 0;
    }
}

