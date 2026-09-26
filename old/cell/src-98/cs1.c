#include <stdio.h>

#define getval() getchar()
#define putval(v) putchar(v)

main(ac, av)
char *av[];
{
	foo(atoi(av[1]), atoi(av[2]));
	putchar('\n');
}

foo(sizin, sizout)
register int sizin, sizout;
{
	register int loop = sizout;
	register int inside = sizout;
	register int wanted = sizin;
	register int valin = getval();
	register int valout = 0;

	while (loop) {
		if (wanted > inside) {
			valout += valin * inside;
			valin = getval();
			wanted -= inside;
			inside = sizout;
		} else {
			putval((valout + valin * wanted) / sizin);
			valout = 0;
			inside -= wanted;
			wanted = sizin;
			--loop;
		}
	}
}
