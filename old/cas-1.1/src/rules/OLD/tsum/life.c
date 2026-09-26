#include "conex/bind.h"

_8sum()
{
    return N + NE + E + SE + S + SW + W + NW;
}

#define U 2

life()
{
    static int T[] = { 0, 1, -1, };
    static int tab[] = { 0, 0, U, 1, 0, 0, 0, 0, 0, };

    T[U] = C;
    return T[tab[_8sum()]];
}

