#include "conex.h"

typedef struct {
    VN p0;
    VN p1;
} HistoIn;

typedef struct {
    Local p0;
    Local p1;
} HistoOut;

void VN2_histo(HistoIn* i, HistoOut* o) {
    int take;
    int give;
    int c0, n0, s0;
    int c1, n1, s1;

    c0 = i->p0.c;
    n0 = i->p0.n;
    s0 = i->p0.s;

    c1 = i->p1.c;
    n1 = i->p1.n;
    s1 = i->p1.s;

    take = !c0 & n0 & !(c1 & !n1);
    give = !s0 & c0 & !(s1 & !c1);
    if (take) o->p0 = n0;
    if (give) o->p0 = s0;
    o->p1 = c1;
}

#if 0
/* von-neumann-2 */
histo() {
    int take;
    int give;

    take = !C0 & N0 & !(C1 & !N1);
    give = !S0 & C0 & !(S1 & !C1);
    if (take) C0 = N0;
    if (give) C0 = S0;
    return C0 | C1 << 1;
}
#endif

