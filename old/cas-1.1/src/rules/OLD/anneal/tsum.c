#include "conex/bind.h"

tsum() /* moore-t-8 */
{
    int tmp;
    int mask;
    int match;
    int delta;

    mask = 3;
    match = 0;
    delta = -1;

    tmp = (SUM + C) / 9;
    tmp = tmp & mask == match ? tmp : tmp + delta;

    return tmp;
}
