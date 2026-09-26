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

