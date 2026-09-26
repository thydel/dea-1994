#include "extract.h"
#include "extract_tab.h"

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

