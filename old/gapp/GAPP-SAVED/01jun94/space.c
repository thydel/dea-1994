#include <stdio.h>

#include "space.h"

void (*textract[])(unsigned char*, unsigned char*, int) = {
    rextract0,
    rextract1,
    rextract2,
    rextract3,
    rextract4,
    rextract5,
    rextract6,
    rextract7,
};

void zero(unsigned char* p, int lside) {
  int side = 1 << lside;
  int size = side * side;

  while (--size) {
    *p++ = 0;
  }
}

void single(unsigned char* p, int lside) {
  int side = 1 << lside;
  int size = side * side;

  p[((side >> 1) << lside) + (side >> 1)] |= 1;
}

void randomize(unsigned char* p, int lside) {
  int side = 1 << lside;
  int size = side * side;

  srand48(time(0) & getpid());
  while (--size) {
    *p++ |= (lrand48() >> 16) & 1;
  }
}

void bloc(unsigned char* p, int lside) {
  int side, size, center, bside, i, j;

  side = 1 << lside;
  size = side * side;
  center = side >> 1;
  bside = side >> 3;
  for (i = center - bside; i < center + bside; ++i) {
    for (j = center - bside; j < center + bside; ++j) {
      p[(i << lside) + j] |= 1;
    }
  }
}

void state2ascii(unsigned char* p, int lside, int mask, FILE* out) {
  int side, size, i, j;

  side = 1 << lside;
  size = side * side;
  for (i = 0; i < side; ++i) {
    for (j = 0; j < side; ++j) {
      int state = p[(i << lside) + j] & mask;
      fprintf(out, "%o%o ", (state & 070) >> 3, state & 7);
    }
    fprintf(out, "\n");
  }
  fflush(out);
}

void frame2ascii(unsigned int* p, int lside, int frame, FILE* out) {
  int side, size, i, j;

  side = 1 << lside;
  size = side * side;
  for (i = 0; i < side; ++i) {
    for (j = 0; j < side; ++j) {
      unsigned int state = p[(i << lside + 2) + (j << 2) + frame];
      fprintf(out, "%x%x%x%x%x%x%x%x ",
	      (state & (0xF << 28)) >> 28,
	      (state & (0xF << 24)) >> 24,
	      (state & (0xF << 20)) >> 20,
	      (state & (0xF << 16)) >> 16,
	      (state & (0xF << 12)) >> 12,
	      (state & (0xF << 8)) >> 8,
	      (state & (0xF << 4)) >> 4,
	      state & 0xF);
    }
    fprintf(out, "\n");
  }
  fflush(out);
}

void rextract0(unsigned char* itab, unsigned char* otab, int size) {
  int i;

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

void rextract1(unsigned char* itab, unsigned char* otab, int size) {
  int i;

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

void rextract2(unsigned char* itab, unsigned char* otab, int size) {
  int i;

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

void rextract3(unsigned char* itab, unsigned char* otab, int size) {
  int i;

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

void rextract4(unsigned char* itab, unsigned char* otab, int size) {
  int i;

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

void rextract5(unsigned char* itab, unsigned char* otab, int size) {
  int i;

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

void rextract6(unsigned char* itab, unsigned char* otab, int size) {
  int i;

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

void rextract7(unsigned char* itab, unsigned char* otab, int size) {
  int i;

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
