#include "local.h"
#include "magic.h"

#include "conex/bind.h"
#include "frame/frame.h"
#include "conex/conex.h"

extern int a[];
extern int na;

_8sum()
{
    return N + NE + E + SE + S + SW + W + NW;
}

_8sum0()
{
    return (N & 1) + (NE & 1) + (E & 1) + (SE & 1) + (S & 1) + (SW & 1) + (W & 1) + (NW & 1);
}

_9sum0()
{
    return (C & 1) + (N & 1) + (NE & 1) + (E & 1) + (SE & 1) + (S & 1) + (SW & 1) + (W & 1) + (NW & 1);
}

anneal()
{
    static int tab[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, };

    return tab[_9sum0()];
}

#define U 2

life()
{
    static int T[] = { 0, 1, -1, };
    static int tab[] = { 0, 0, U, 1, 0, 0, 0, 0, 0, };

    T[U] = C & 1;
    return T[tab[_8sum0()]];
}

life1()
{
    static int T[] = { 0, 1, -1, };
    static int tab[] = { 0, 0, U, 1, 0, 0, 0, 0, 0, };

    int tmp;

    T[U] = C & 1;
    tmp = T[tab[_8sum0()]];

    L = L ? --L : 0;

    if (tmp && !(C & 1)) {
	L = na ? a[0] : 0;
    } else if (C & 1 && !tmp && L) {
	tmp = 1;
    }

    return tmp | L << 1;
}

tube_worm() /* moore-1+2 */
{
    /* set plane 0, 1 et timers only to random */

    /* try looking only frame n/(4 + timer) */

    /* try with timer = 5 */
    static int alarm_tab0[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, };

    /* try with timer = 2, 3, 4 or 5 */
    static int alarm_tab1[] = { 0, 0, 1, 1, 1, 1, 1, 1, 1, };

    /* try with timer = 3, 4 or 5 */
    static int alarm_tab2[] = { 0, 0, 0, 1, 1, 1, 1, 1, 1, };
    
    /* try with timer = 1, 2 (size >= 256), 3, 4 or 5 */
    static int alarm_tab3[] = { 0, 0, 1, 0, 1, 1, 1, 1, 1, };

    static int* alarm_tab[] = { alarm_tab0, alarm_tab1, alarm_tab2, alarm_tab3, };
    static int timer_tab[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, };

    int iworm;
    int oworm;
    int ialarm;
    int oalarm;
    int itimer;
    int otimer;
    int alarm;
    int timer;
    int ret;
    int view;

    alarm = a[0];
    timer = a[1];

    if (!alarm && ! timer) {
	alarm = 2;
	timer = 3;
    }

    iworm = C;
    ialarm = L & 1;
    itimer = (L & 7 << 1) >> 1;
    
    oworm = !itimer;
    oalarm = alarm_tab[alarm][_8sum()];
    otimer = iworm & ialarm ? timer : timer_tab[itimer];

    ret = oworm | oalarm << 1 | otimer << 2;
    view = (oworm | oalarm) | (oworm & oalarm) << 1 | (oworm ^ oalarm) << 2;

    return ret /* | view << 5 */;
}

extern Conex moore_1_conex;
extern Conex moore_1_7_conex;

#if 0
Conex* conex = &moore_1_7_conex;
int (*func)() = tube_worm;
#endif

#if 0
Conex* conex = &moore_1_conex;
int (*func)() = life;
#endif

#if 0
Conex* conex = &moore_1_7_conex;
int (*func)() = life1;
#endif

#if 1
Conex* conex = &moore_1_conex;
int (*func)() = anneal;
#endif

