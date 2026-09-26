#include <stdio.h>

main()
{
    gen_extract(stdout);
    return 0;
}


gen_extract(FILE* stream)
{
    gen_extract1(stream, "", 0);
    gen_extract1(stream, "r", 1);
}

#define MAXBIT 7

char* spin(int src, int dst) {
    return ((MAXBIT - src) - dst >= 0 ? "<<" : ">>");
}

int offset(int src, int dst, int flag) {
    return abs((MAXBIT - src) - dst);
}

gen_extract1(FILE* stream, char* prefix, int flag)
{
    int src;
    int dst;

    for (src = 0; src < 8 ; ++src) {
	fprintf(stream, "%sextract%d(register unsigned char* itab, register unsigned char* otab, int size)\n",
		prefix, src);
	fprintf(stream, "%s", "{\n");
	fprintf(stream, "%s", "\tregister int i;\n");
	fprintf(stream, "%s", "\n");
	fprintf(stream, "%s", "\tfor (i = size >> 3; i--;) {\n");
    {
	dst = flag ? 7 : 0;
	fprintf(stream, "\t\t*otab = (*itab++ & %d) %s %d;\n",
		1 << src, spin(src, dst), offset(src, dst, flag));
	if (flag) {
	    for (dst = 6; dst > 0; --dst) {
		fprintf(stream, "\t\t*otab |= (*itab++ & %d) %s %d;\n",
			1 << src, spin(src, dst), offset(src, dst, flag));
	    }
	} else {
	    for (dst = 1; dst < MAXBIT; ++dst) {
		fprintf(stream, "\t\t*otab |= (*itab++ & %d) %s %d;\n",
			1 << src, spin(src, dst), offset(src, dst, flag));
	    }
	}
	fprintf(stream, "\t\t*otab++ |= (*itab++ & %d) %s %d;\n",
		1 << src, spin(src, dst), offset(src, dst, flag));
    }
	fprintf(stream, "%s", "\t}\n");
	fprintf(stream, "%s", "}\n");
	fprintf(stream, "%s", "\n");
    }
}

