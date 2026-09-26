#include "conex/bind.h"

_9_sum()
{
    return C + N + NE + E + SE + S + SW + W + NW;
}

anneal()
{
    static int tab[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, };

    return tab[_9_sum()] | L << 1;
}

