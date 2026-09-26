#include "named.h"

extract0(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 1) << 7;
		*otab |= (*itab++ & 1) << 6;
		*otab |= (*itab++ & 1) << 5;
		*otab |= (*itab++ & 1) << 4;
		*otab |= (*itab++ & 1) << 3;
		*otab |= (*itab++ & 1) << 2;
		*otab |= (*itab++ & 1) << 1;
		*otab++ |= (*itab++ & 1) << 0;
	}
}

extract1(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 2) << 6;
		*otab |= (*itab++ & 2) << 5;
		*otab |= (*itab++ & 2) << 4;
		*otab |= (*itab++ & 2) << 3;
		*otab |= (*itab++ & 2) << 2;
		*otab |= (*itab++ & 2) << 1;
		*otab |= (*itab++ & 2) << 0;
		*otab++ |= (*itab++ & 2) >> 1;
	}
}

extract2(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 4) << 5;
		*otab |= (*itab++ & 4) << 4;
		*otab |= (*itab++ & 4) << 3;
		*otab |= (*itab++ & 4) << 2;
		*otab |= (*itab++ & 4) << 1;
		*otab |= (*itab++ & 4) << 0;
		*otab |= (*itab++ & 4) >> 1;
		*otab++ |= (*itab++ & 4) >> 2;
	}
}

extract3(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 8) << 4;
		*otab |= (*itab++ & 8) << 3;
		*otab |= (*itab++ & 8) << 2;
		*otab |= (*itab++ & 8) << 1;
		*otab |= (*itab++ & 8) << 0;
		*otab |= (*itab++ & 8) >> 1;
		*otab |= (*itab++ & 8) >> 2;
		*otab++ |= (*itab++ & 8) >> 3;
	}
}

extract4(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 16) << 3;
		*otab |= (*itab++ & 16) << 2;
		*otab |= (*itab++ & 16) << 1;
		*otab |= (*itab++ & 16) << 0;
		*otab |= (*itab++ & 16) >> 1;
		*otab |= (*itab++ & 16) >> 2;
		*otab |= (*itab++ & 16) >> 3;
		*otab++ |= (*itab++ & 16) >> 4;
	}
}

extract5(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 32) << 2;
		*otab |= (*itab++ & 32) << 1;
		*otab |= (*itab++ & 32) << 0;
		*otab |= (*itab++ & 32) >> 1;
		*otab |= (*itab++ & 32) >> 2;
		*otab |= (*itab++ & 32) >> 3;
		*otab |= (*itab++ & 32) >> 4;
		*otab++ |= (*itab++ & 32) >> 5;
	}
}

extract6(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 64) << 1;
		*otab |= (*itab++ & 64) << 0;
		*otab |= (*itab++ & 64) >> 1;
		*otab |= (*itab++ & 64) >> 2;
		*otab |= (*itab++ & 64) >> 3;
		*otab |= (*itab++ & 64) >> 4;
		*otab |= (*itab++ & 64) >> 5;
		*otab++ |= (*itab++ & 64) >> 6;
	}
}

extract7(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 128) << 0;
		*otab |= (*itab++ & 128) >> 1;
		*otab |= (*itab++ & 128) >> 2;
		*otab |= (*itab++ & 128) >> 3;
		*otab |= (*itab++ & 128) >> 4;
		*otab |= (*itab++ & 128) >> 5;
		*otab |= (*itab++ & 128) >> 6;
		*otab++ |= (*itab++ & 128) >> 7;
	}
}

rextract0(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 1) << 0;
		*otab |= (*itab++ & 1) << 1;
		*otab |= (*itab++ & 1) << 2;
		*otab |= (*itab++ & 1) << 3;
		*otab |= (*itab++ & 1) << 4;
		*otab |= (*itab++ & 1) << 5;
		*otab |= (*itab++ & 1) << 6;
		*otab++ |= (*itab++ & 1) << 7;
	}
}

rextract1(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 2) >> 1;
		*otab |= (*itab++ & 2) << 0;
		*otab |= (*itab++ & 2) << 1;
		*otab |= (*itab++ & 2) << 2;
		*otab |= (*itab++ & 2) << 3;
		*otab |= (*itab++ & 2) << 4;
		*otab |= (*itab++ & 2) << 5;
		*otab++ |= (*itab++ & 2) << 6;
	}
}

rextract2(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 4) >> 2;
		*otab |= (*itab++ & 4) >> 1;
		*otab |= (*itab++ & 4) << 0;
		*otab |= (*itab++ & 4) << 1;
		*otab |= (*itab++ & 4) << 2;
		*otab |= (*itab++ & 4) << 3;
		*otab |= (*itab++ & 4) << 4;
		*otab++ |= (*itab++ & 4) << 5;
	}
}

rextract3(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 8) >> 3;
		*otab |= (*itab++ & 8) >> 2;
		*otab |= (*itab++ & 8) >> 1;
		*otab |= (*itab++ & 8) << 0;
		*otab |= (*itab++ & 8) << 1;
		*otab |= (*itab++ & 8) << 2;
		*otab |= (*itab++ & 8) << 3;
		*otab++ |= (*itab++ & 8) << 4;
	}
}

rextract4(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 16) >> 4;
		*otab |= (*itab++ & 16) >> 3;
		*otab |= (*itab++ & 16) >> 2;
		*otab |= (*itab++ & 16) >> 1;
		*otab |= (*itab++ & 16) << 0;
		*otab |= (*itab++ & 16) << 1;
		*otab |= (*itab++ & 16) << 2;
		*otab++ |= (*itab++ & 16) << 3;
	}
}

rextract5(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 32) >> 5;
		*otab |= (*itab++ & 32) >> 4;
		*otab |= (*itab++ & 32) >> 3;
		*otab |= (*itab++ & 32) >> 2;
		*otab |= (*itab++ & 32) >> 1;
		*otab |= (*itab++ & 32) << 0;
		*otab |= (*itab++ & 32) << 1;
		*otab++ |= (*itab++ & 32) << 2;
	}
}

rextract6(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 64) >> 6;
		*otab |= (*itab++ & 64) >> 5;
		*otab |= (*itab++ & 64) >> 4;
		*otab |= (*itab++ & 64) >> 3;
		*otab |= (*itab++ & 64) >> 2;
		*otab |= (*itab++ & 64) >> 1;
		*otab |= (*itab++ & 64) << 0;
		*otab++ |= (*itab++ & 64) << 1;
	}
}

rextract7(register unsigned char* itab, register unsigned char* otab, int size)
{
	register int i;

	for (i = size >> 3; i--;) {
		*otab = (*itab++ & 128) >> 7;
		*otab |= (*itab++ & 128) >> 6;
		*otab |= (*itab++ & 128) >> 5;
		*otab |= (*itab++ & 128) >> 4;
		*otab |= (*itab++ & 128) >> 3;
		*otab |= (*itab++ & 128) >> 2;
		*otab |= (*itab++ & 128) >> 1;
		*otab++ |= (*itab++ & 128) << 0;
	}
}

extract_all(unsigned char* itab, unsigned char* otab, int size)
{
    char* p;
    int s;

    p = otab;
    s = size >> 3;

    extract0(itab, p, size);
    p += s;
    extract1(itab, p, size);
    p += s;
    extract2(itab, p, size);
    p += s;
    extract3(itab, p, size);
    p += s;
    extract4(itab, p, size);
    p += s;
    extract5(itab, p, size);
    p += s;
    extract6(itab, p, size);
    p += s;
    extract7(itab, p, size);
    p += s;
}

rextract_all(unsigned char* itab, unsigned char* otab, int size)
{
    char* p;
    int s;

    p = otab;
    s = size >> 3;

    rextract0(itab, p, size);
    p += s;
    rextract1(itab, p, size);
    p += s;
    rextract2(itab, p, size);
    p += s;
    rextract3(itab, p, size);
    p += s;
    rextract4(itab, p, size);
    p += s;
    rextract5(itab, p, size);
    p += s;
    rextract6(itab, p, size);
    p += s;
    rextract7(itab, p, size);
    p += s;
}

extract_all_1(unsigned char* itab, unsigned char* otab, int size, int revert)
{
    int i;
    int sz;
    int sz2, sz3, sz4, sz5,sz6, sz7;

    sz = size >> 3;
    sz2 = sz * 2;
    sz3 = sz * 3;
    sz4 = sz * 4;
    sz5 = sz * 5;
    sz6 = sz * 6;
    sz7 = sz * 7;

    for (i = 0; i < size; ++i) {
	int v;
	int low;
	int high;
	
	v = itab[i];
	low = revert ? ~i & 7 : i & 7;
	high = i >> 3;

	otab[high] |= (v & 1) << low;
	otab[sz + high] |= ((v & 1 << 1) >> 1) << low;
	otab[sz2 + high] |= ((v & 1 << 2) >> 2) << low;
	otab[sz3 + high] |= ((v & 1 << 3) >> 3) << low;
	otab[sz4 + high] |= ((v & 1 << 4) >> 4) << low;
	otab[sz5 + high] |= ((v & 1 << 5) >> 5) << low;
	otab[sz6 + high] |= ((v & 1 << 6) >> 6) << low;
	otab[sz7 + high] |= ((v & 1 << 7) >> 7) << low;
    }
}

extract0_zoom2(register unsigned char* itab, unsigned char* otab, int side)
{
    static unsigned char t0[] = { 0, 3 << 6, };
    static unsigned char t1[] = { 0, 3 << 4, };
    static unsigned char t2[] = { 0, 3 << 2, };
    static unsigned char t3[] = { 0, 3, };
	
    register unsigned char* p0;
    register unsigned char* p1;
    int i;
    int j;
    int k;

    k = side >> 2;
    p0 = otab;
    p1 = otab + k;

    for (i = side; i--;) {
	for (j = side >> 3; j--;) {
	    *p0 = t0[*itab++ & 1];
	    *p0 |= t1[*itab++ & 1];
	    *p0 |= t2[*itab++ & 1];
	    *p0 |= t3[*itab++ & 1];
	    *p1++ = *p0++;
	    *p0 = t0[*itab++ & 1];
	    *p0 |= t1[*itab++ & 1];
	    *p0 |= t2[*itab++ & 1];
	    *p0 |= t3[*itab++ & 1];
 	    *p1++ = *p0++;
	}
	p0 += k;
	p1 += k;
    }
}

int (*extract_tab[])(unsigned char*, unsigned char*, int) = {
    extract0,
    rextract0,
    extract1,
    rextract1,
    extract2,
    rextract2,
    extract3,
    rextract3,
    extract4,
    rextract4,
    extract5,
    rextract5,
    extract6,
    rextract6,
    extract7,
    rextract7,
    extract_all,
    rextract_all
    };

Named extract_named[] = {
    NAMED_P(extract0),
    NAMED_P(extract1),
    NAMED_P(extract2),
    NAMED_P(extract3),
    NAMED_P(extract4),
    NAMED_P(extract5),
    NAMED_P(extract6),
    NAMED_P(extract7),
    NAMED_P(rextract0),
    NAMED_P(rextract1),
    NAMED_P(rextract2),
    NAMED_P(rextract3),
    NAMED_P(rextract4),
    NAMED_P(rextract5),
    NAMED_P(rextract6),
    NAMED_P(rextract7),
    NAMED_P(extract_all),
    NAMED_P(extract_all_1),
    NAMED_P(rextract_all),
    NAMED_P(extract0_zoom2),
    NULL_NAMED
};

void extract_init() {
  extract_tab[0] = extract0;
}

