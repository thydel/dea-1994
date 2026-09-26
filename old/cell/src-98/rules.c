#include <stdio.h>

#include "neighbor.h"
#include "named_func.h"

#define U 2
#define F 3

extern char* str_arg;
extern int num_arg;
extern int* num_arg_tab;

_4sum()
{
    return  N + E + S + W;
}

_5sum()
{
    return C + N + E + S + W;
}

_5parity()
{
    return C ^ N ^ E ^ S ^ W;
}

diamond()
{
    return C | N | E | S | W;
}

triangle()
{
    return C | N | E | W;
}

_5_maj()
{
    static int tab[] = { 0, 0, 0, 1, 1, 1, };

    return tab[_5sum()];
}

_8sum()
{
    return N + NE + E + SE + S + SW + W + NW;
}

_8sum_0()
{
    return N0 + NE0 + E0 + SE0 + S0 + SW0 + W0 + NW0;
}

_9_sum()
{
    return C + N + NE + E + SE + S + SW + W + NW;
}

_9_sum_0()
{
    return C0 + N0 + NE0 + E0 + SE0 + S0 + SW0 + W0 + NW0;
}

_9parity()
{
    return C ^ N ^ NE ^ E ^ SE ^ S ^ SW ^ W ^ NW;

}

ink()
{
    return C ? C : _8sum() == 3;
}

life()
{
    static int T[] = { 0, 1, -1, };
    static int tab[] = { 0, 0, U, 1, 0, 0, 0, 0, 0, };

    T[U] = C;
    return T[tab[_8sum()]];
}

anneal_flip()
{
    static int T[] = { 0, 1, -1, };
    static int tab[] = { 0, 0, 0, 0, U, 1, 1, 1, 1, };

    T[U] = !C;
    return T[tab[_8sum()]];
}

lifex()
{
    static int T[] = { 0, 1, -1, };
    static int tab[] = { 0, 0, U, 1, 0, 0, 0, 0, 0, };

    int old;
    int new;
    int tmp;
    int x1;
    int x2;

    old = C & 1;
    T[U] = old;
    new = T[tab[_8sum()]];
    tmp = L & 1;
    x1 = old ^ new;
    x2 = tmp ^ new;
    return new | old << 1 | x1 << 2 | x2 << 3;
}

life_2()
{
    static int T[] = { 0, 1, -1, };
    static int tab[] = { 0, 0, U, 1, 0, 0, 0, 0, 0, };

    int tmp;

    T[U] = C & 1;
    tmp = T[tab[_8sum()]];

    L = L ? --L : 0;

    if (tmp && !(C & 1)) {
	L = num_arg_tab[0];
    } else if (C & 1 && !tmp && L) {
	tmp = 1;
    }

    return tmp | L << 1;
}

life_1()
{
    static int T[] = { 0, 1, -1, };
    static int tab[] = { 0, 0, U, 1, 0, 0, 0, 0, 0, };

    T[U] = C;
    return T[tab[_8sum()]] | ((L << 2) | (C << 1));
}

not_life()
{
	int tmp;

	tmp = _8sum();
	return !life() && tmp && tmp != 8;
}

_1_out_of_8()
{
    return C ? 1 : _8sum() == 1;
}

_1_out_of_n()
{
    return C ? 1 : _8sum() == num_arg;
}

lichens()
{
    static int tab[] = { 0, 0, 0, 1, 0, 0, 0, 1, 1, };

    return tab[_8sum()] ? 1 : C;
}

lichens_with_death()
{
    static int T[] = { 0, 1, -1, };
    static tab[] = { U, U, U, 1, 0, U, U, 1, 1, };

    T[U] = C;
    return T[tab[_8sum()]];
}

totalistic()
{
	static int T[] = { 0, 1, -1, -1, };

	T[U] = C;
	T[F] = !C;
	return T[str_arg[_8sum()] - '0'];
}

totalistic_9()
{
	static int T[] = { 0, 1, -1, -1};

	T[U] = C;
	T[F] = !C;
	return T[str_arg[_9_sum()] - '0'] /* | C << 1 | (C ^ (L & 1)) << 2 */;
}

majority()
{
    static int tab[] = { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, };

    return tab[_9_sum()];
}

annealx()
{
    static int tab[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, };

    int old;
    int new;
    int tmp;
    int x1;
    int x2;

    old = C & 1;

    new = tab[_9_sum()];

    tmp = L & 1;
    x1 = old ^ new;
    x2 = tmp ^ new;
    return new | old << 1 | x1 << 2 | x2 << 3;
}

annealxx()
{
    static int tab[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, };

    int old1;
    int new;
    int old2;
    int x1;
    int x2;

    old1 = C & 1;

    new = tab[_9_sum()];

    old2 = L & 1;
    x1 = old1 ^ new;
    x2 = old2 ^ new;
    return new | old1 << 1 | x1 << 2 | x2 << 3;
}

anneal()
{
    static int tab[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, };

    return tab[_9_sum()];
}


stir()
{
    return E & S ^ W ^ N ^ C;
}

t_sum() /* moore-t-8 */
{
    int tmp;
    int n;
    int mask;
    int match;
    int delta;

    n = num_arg_tab[0];
    mask = num_arg_tab[1];
    match = num_arg_tab[2];
    delta = num_arg_tab[3];
    
    switch (n) {

      case 0: {
	  tmp = (SUM + C) / 9;
	  break;
      }

      case 1: {
	  tmp = (SUM + C) >> 3;
	  break;
      }
	
      case 2: {
	  tmp = (SUM + C);
	  tmp = tmp < 256 ? tmp : tmp >> 1;
	  tmp = tmp < 256 ? tmp : tmp >> 1;
	  tmp = tmp < 256 ? tmp : tmp >> 1;
	  break;
      }

/*
  try 3, 0, -1
*/
      case 3: {
	  tmp = (SUM + C) / 9;
	  tmp = tmp & mask == match ? tmp : tmp + delta;
	  break;
      }

      case 30: {
	  tmp = (SUM + C) / 9;
	  if (!tmp) break;
	  tmp = tmp & mask == match ? tmp : tmp + delta;
	  break;
      }

      case 31: {
	  tmp = (SUM + C) / 9;
	  tmp = tmp & mask != match ? tmp : tmp + delta;
	  break;
      }

      case 4: {
	  tmp = (SUM + C) >> 3;
	  tmp = tmp & mask == match ? tmp : tmp + delta;
	  break;
      }
	
      case 5: {
	  tmp = (SUM + C);
	  tmp = tmp < 256 ? tmp : tmp >> 1;
	  tmp = tmp < 256 ? tmp : tmp >> 1;
	  tmp = tmp < 256 ? tmp : tmp >> 1;
	  tmp = tmp & mask == match ? tmp : tmp + delta;
	  break;
      }

      case 6: {
	  tmp = (SUM + C) / 9;
	  if (tmp <= num_arg_tab[1]) {
	      tmp -= num_arg_tab[2];
	  } else {
	      tmp += num_arg_tab[3];
	  }
	  break;
      }

      case 7: {
	  if (!C && SUM) {
	      tmp = SUM - num_arg_tab[1];
	  } else {
	      tmp = C;
	  }
	  break;
      }

      case 8: {
	  tmp = SUM;
	  break;
      }

      case 100: {
	  
	  
	  /* anneal */
	  static int tab[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, };
	  
	  tmp = tab[(C & 1) + (SUM > 9 ? 0 : SUM)];
	  break;
      }
	
      case 101: {
	  /* life */
	  static int T[] = { 0, 1, -1, };
	  static int tab[] = { 0, 0, U, 1, 0, 0, 0, 0, 0, };
	  
	  T[U] = C & 1;
	  tmp = T[tab[SUM > 8 ? 0 : SUM]];
	  break;
      }

      case 200: {
	  tmp = SUM / 9;
	  if (C >= num_arg_tab[1] && tmp >= num_arg_tab[2] && tmp <= num_arg_tab[3]) {
	      tmp = C + num_arg_tab[4];
	  } else {
	      tmp = C - num_arg_tab[4];
	  }
	  break;

      }

      default: {
	  abort();
      }
    }

    return tmp;
}

rand_anneal() /* von-neumann-2 */
{
    static int tab[] = { 0, 0, 0, 1, 1, 1, };
    int sum;
    int stir;
    int rand;

    sum = C0 + N0 + E0 + S0 + W0;
    stir = E1 & S1 ^ W1 ^ N1 ^ C1;
    rand = C1 & N1 & S1 & W1 & E1;
    tab[2] = rand;
    tab[3] = rand ^ 1;
    return tab[sum] | stir << 1;
}

_9_rand_anneal() /* moore-2 */
{
    static int tab0[] = { 0, 0, 0, 0, -1, -1, 1, 1, 1, 1, };
    static int tab1[] = { 0, 0, 0, -1, -1, -1, -1, 1, 1, 1, };
    static int tab2[] = { 0, 0, 0, 1, -1, -1, 0, 1, 1, 1, };
    static int tab3[] = { 0, 0, 0, -1, 1, 0, -1, 1, 1, 1, };
    static int tab4[] = { 0, 0, -1, -1, 1, 0, -1, -1, 1, 1, };
    int* tab;
    int sum;
    int stir;
    int rand;

    sum = C0 + N0 + E0 + S0 + W0 + NE0 + SE0 + NW0 + SW0;
    stir = E1 & S1 ^ W1 ^ N1 ^ C1;
    rand = C1 & N1 & S1 & W1 & E1;
    switch (num_arg) {
      case 0:
	tab = tab0;
	tab[4] = rand;
	tab[5] = rand ^ 1;
	break;
      case 1:
	tab = tab1;
	tab[3] = rand;
	tab[4] = rand;
	tab[5] = rand ^ 1;
	tab[6] = rand ^ 1;
	break;
      case 2:
	tab = tab2;
	tab[4] = rand;
	tab[5] = rand ^ 1;
	break;
      case 3:
	tab = tab3;
	tab[3] = rand;
	tab[6] = rand ^ 1;
	break;
      case 4:
	tab = tab3;
	tab[2] = rand;
	tab[3] = rand;
	tab[6] = rand ^ 1;
	tab[7] = rand ^ 1;
	break;
    }
    return tab[sum] | stir << 1;
}

histo() /* von-neumann-2 */
{
    int take;
    int give;

    take = !C0 & N0 & !(C1 & !N1);
    give = !S0 & C0 & !(S1 & !C1);
    if (take) C0 = N0;
    if (give) C0 = S0;
    return C0 | C1 << 1;
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

    alarm = num_arg_tab[0];
    timer = num_arg_tab[1];

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

fox_rabbit() /* von-neumann-2+6 */
{
    int ifox;
    int ofox;
    int irabbit;
    int orabbit;
    int ifox_life;
    int ofox_life;
    int irabbit_life;
    int orabbit_life;

    int fox_sum;
    int rabbit_sum;

    ifox = C0;
    irabbit = C1;
    ifox_life = L & 3;
    irabbit_life = (L & 3 << 2) >> 2;

    fox_sum = W0 + N0 + S0 + E0;
    rabbit_sum = W1 + N1 + S1 + E1;

    ofox = ifox;
    orabbit = irabbit;

    if (ifox && irabbit) {
	orabbit = 0;
    }
    
    if (ifox) {
	ofox_life = ifox_life - 1;
	if (ofox_life > 0) {
	    ofox = 1;
	} else {
	    ofox = 0;
	}
    } 
    
    if (irabbit && !ifox) {
	orabbit_life = irabbit_life - 1;
	if (orabbit_life > 0) {
	    orabbit = 1;
	} else {
	    orabbit = 0;
	}
    }
    
    if (!ifox && fox_sum >= 2 && rabbit_sum >= 1) {
	ofox = 1;
	ofox_life = 3;
    }

    if (!irabbit && rabbit_sum >= 2) {
	orabbit = 1;
	orabbit_life = 3;
    }

    return ofox | orabbit << 1 | (ofox_life & 3) << 2 | (orabbit_life & 3) << 4 |
	(ofox & orabbit) << 6 | (ofox | orabbit) << 7;
}

fox_rabbit_1() /* von-neumann-2+6 */
{
    int ifox;
    int ofox;
    int irabbit;
    int orabbit;
    int ifox_life;
    int ofox_life;
    int irabbit_life;
    int orabbit_life;

    int fox_sum;
    int rabbit_sum;

    ifox = C0;
    irabbit = C1;
    ifox_life = L & 7;
    irabbit_life = (L & 7 << 3) >> 3;

    fox_sum = W0 + N0 + S0 + E0;
    rabbit_sum = W1 + N1 + S1 + E1;

    ofox = ifox;
    orabbit = irabbit;

    if (ifox && irabbit) {
	ofox_life = ifox_life - 1;
	if (ofox_life > 0) {
	    ofox = 1;
	} else {
	    ofox = 0;
	}
	orabbit = 0;
    }
    
    if (ifox && !irabbit) {
	ofox_life = ifox_life - 3;
	if (ofox_life > 0) {
	    ofox = 1;
	} else {
	    ofox = 0;
	}
    } 
    
    if (irabbit && !ifox) {
	orabbit_life = irabbit_life - 1;
	if (orabbit_life > 0) {
	    orabbit = 1;
	} else {
	    orabbit = 0;
	}
    }
    
    if (!ifox && fox_sum == 2 && rabbit_sum >= 1) {
	ofox = 1;
	ofox_life = 7;
    }

    if (!irabbit && (rabbit_sum >= 2 || rabbit_sum <= 3)) {
	orabbit = 1;
	orabbit_life = 2;
    }

    return ofox | orabbit << 1 | (ofox_life & 7) << 2 | (orabbit_life & 7) << 5;
}

fox_rabbit_2() /* von-neumann-2+6 */
{
    int ifox;
    int ofox;
    int irabbit;
    int orabbit;
    int ifox_life;
    int ofox_life;
    int irabbit_life;
    int orabbit_life;

    int fox_sum;
    int rabbit_sum;

    ifox = C0;
    irabbit = C1;
    ifox_life = L & 7;
    irabbit_life = (L & 7 << 3) >> 3;

    fox_sum = W0 + N0 + S0 + E0;
    rabbit_sum = W1 + N1 + S1 + E1;

    ofox = ifox;
    orabbit = irabbit;

    if (ifox && irabbit) {
	if (fox_sum > rabbit_sum) {
	    ofox_life = ifox_life - 1;
	    if (ofox_life > 0) {
		ofox = 1;
	    } else {
		ofox = 0;
	    }
	    orabbit = 0;
	} else if (fox_sum < rabbit_sum) {
	    orabbit_life = irabbit_life - 1;
	    if (orabbit_life > 0) {
		orabbit = 1;
	    } else {
		orabbit = 0;
	    }
	    ofox = 0;
	}
    }
    
    if (ifox && !irabbit) {
	ofox_life = ifox_life - 2;
	if (ofox_life > 0) {
	    ofox = 1;
	} else {
	    ofox = 0;
	}
    } 
    
    if (irabbit && !ifox) {
	orabbit_life = irabbit_life - 2;
	if (orabbit_life > 0) {
	    orabbit = 1;
	} else {
	    orabbit = 0;
	}
    }
    
    if (!ifox && fox_sum == 2 /* && rabbit_sum <= 1 */) {
	ofox = 1;
	ofox_life = 7;
    }

    if (!irabbit && rabbit_sum >= 2 && fox_sum >= 1) {
	orabbit = 1;
	orabbit_life = 3;
    }

    return ofox | orabbit << 1 | (ofox_life & 7) << 2 | (orabbit_life & 7) << 5;
}

_2_species() /* moore-1+7 */
{
    static int tab_one[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, };
    static int tab_two[] = { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, };

    int istep;
    int ostep;
    int ione;
    int oone;
    int itwo;
    int otwo;

    int one_sum;
    int two_sum;

    istep = (L & 1 << 6) >> 6;
    if (istep) {
	ione = C;
	itwo = L & 1;

	one_sum = _9_sum();
	two_sum = (L & 15 << 1) >> 1;

	oone = tab_two[one_sum];
	otwo = tab_one[two_sum];

	ostep = 0;

	return otwo | oone << 1 | ostep << 7 | one_sum << 2;
    } else {
	itwo = C;
	ione = L & 1;

	two_sum = _9_sum();
	one_sum = (L & 15 << 1) >> 1;

	oone = tab_one[two_sum];
	otwo = tab_two[one_sum];

	ostep = 1;

	return oone | otwo << 1 | ostep << 7 | two_sum << 2;
    }
}

_2_species_1() /* moore-1+7 */
{
    static int tab_one[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, };
    static int tab_two[] = { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, };

    int istep;
    int ostep;
    int ifirst;
    int ofirst;
    int ione;
    int oone;
    int itwo;
    int otwo;

    int one_sum;
    int two_sum;

    istep = (L & 1 << 6) >> 6;
    ifirst = (L & 1 << 5) >> 5;
    if (istep) {
	ione = C;
	itwo = L & 1;
	one_sum = _9_sum();
	two_sum = (L & 15 << 1) >> 1;
    } else {
	itwo = C;
	ione = L & 1;
	two_sum = _9_sum();
	one_sum = (L & 15 << 1) >> 1;
    }

    ofirst = 1;
    if (!ifirst) {
	oone = ione;
	otwo = itwo;
	goto out;
    }

    if (ione && itwo) {
	if (one_sum > two_sum) {
	    oone = 1;
	    otwo = 0;
	} else if (one_sum < two_sum) {
	    oone = 0;
	    otwo = 1;
	} else {
	    oone = ione;
	    otwo = itwo;
	}
    }
    if (!ione) {
	if (one_sum == 3) {
	    oone = 1;
	}
    }
    if (!itwo) {
	if (two_sum == 3) {
	    otwo = 1;
	}
    }

  out:
    if (istep) {
	ostep = 0;
	return otwo | oone << 1 | ostep << 7 | ofirst << 6 | one_sum << 2;
    } else {
	ostep = 1;
	return oone | otwo << 1 | ostep << 7 | ofirst << 6 | two_sum << 2;
    }
}

altern() /* moore-1+7 */
{
    static int tab_one[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, };
    static int tab_two[] = { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, };

    int istep;
    int ostep;
    int iv;
    int ov;

    int sum;

    istep = (L & 1 << 6) >> 6;
    iv = C;

    sum = _9_sum();
    if (istep) {
	ov = tab_one[sum];
	ostep = 0;
    } else {
	ov = tab_two[sum];
	ostep = 1;
    }
    return ov | ostep << 7;
}

altern_3() /* moore-1+7 */
{
    static int tab_one[] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, };
    static int tab_two[] = { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, };
    static int tab_three[] = { 0, 0, 1, 1, 0, 0, 0 , 1, 0, 0, };

    int istep;
    int ostep;
    int iv;
    int ov;

    int sum;

    istep = (L & 3 << 5) >> 5;
    iv = C;

    sum = _9_sum();
    switch (istep) {
      case 0:
	ov = tab_one[sum];
	ostep = 1;
	break;
      case 1:
	ov = tab_two[sum];
	ostep = 2;
	break;
      case 2:
	ov = tab_three[sum];
	ostep = 0;
	break;
    }
    return ov | ostep << 6;
}

#if 0

rule tube-worm(moore worm:1, alarm:1, timer:2)
{
    worm = !timer;
    alarm = { 0 0 1 1 1 1 1 1 1 }[8-sum(worm)];
    timer = worm && alarm ? 3 : { 0 0 1 2 }[timer];
}

rule stir(von-neumann atom:1)
{
    atom = W(atom) & N(atom) ^ C(atom) ^ S(atom) ^ E(atom);
}

rule stir(von-neumann:1)
{
    C = W & N ^ C ^ S ^ E;
}

rule rand(von-neumann:1)
{
    C = W & N & C & S & E;
}

rule not-rand(von-neumann:1)
{
    C = rand(this) ^ 1;
}

rule rand-anneal(von-neumann atom:1, von-neuman random:1)
{
    random = stir(random);
    anneal = { 0 0 rand(random) not-random(random) 1 1 }[5-sum(atom)];
}

rand-annel(Von_Neumann atom, Von_Neumann heat)
{
    heat = stir(heat);
    anneal = table(0, 0, rand(heat), not_rand(heat), 1, 1)[5_sum(atom)];
}

#endif

north_west() { return NW; }
west() { return W; }
south_west() { return SW; }
north() { return N; }
center() { return C; }
south() { return S; }
north_est() { return NE; }
est() { return E; }
south_est() { return SE; }

/* moore-1+7 */
xxx()
{
    int n;
    int tmp1;
    int tmp2;

    n = num_arg_tab[0];
    switch(n) {
      case 0:
	return _8sum() + L >> 1;
      case 1:
	return _8sum() + L & 7;
      case 2:
	tmp1 = _8sum();
	tmp2 = L << 1 | C;
	tmp1 += tmp2;
	tmp1 >> 1;
	return tmp1 & 255;
      default:
	return 0;
    }
}


Named_Func rules_names[] = {
    "north-west", north_west,
    "west", west,
    "south-west", south_west,
    "north", north,
    "center", center,
    "south", south,
    "north-est", north_est,
    "est", est,
    "south-est", south_est,
    "5-parity", _5parity,
    "diamond", diamond,
    "triangle", triangle,
    "5-maj", _5_maj,
    "9-parity", _9parity,
    "ink", ink,
    "life", life,
    "life-1", life_1,
    "lifex", lifex,
    "life-2", life_2,
    "not-life", not_life,
    "1-out-of-8", _1_out_of_8,
    "1-out-of-n", _1_out_of_n,
    "lichens", lichens,
    "lichens-with-death", lichens_with_death,
    "totalistic", totalistic,
    "totalistic-9", totalistic_9,
    "majority", majority,
    "anneal", anneal,
    "anneal-flip", anneal_flip,
    "annealx", annealx,
    "stir", stir,
    "rand-anneal", rand_anneal,
    "9-rand-anneal", _9_rand_anneal,
    "histo", histo,
    "tube-worm", tube_worm,
    "fox-rabbit", fox_rabbit,
    "fox-rabbit-1", fox_rabbit_1,
    "fox-rabbit-2", fox_rabbit_2,
    "2-species", _2_species,
    "2-species-1", _2_species_1,
    "altern", altern,
    "altern-3", altern_3,
    "t-sum", t_sum,
    "xxx", xxx,
    0, 0,
};

