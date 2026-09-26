#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define DEBUG 0
#define debug(f, e) if(f && DEBUG) {e;}

#define MAGIC 42

/*          Y Z X */
#define DFL 0,0,0
#define DFR 0,0,1
#define DBL 0,1,0
#define DBR 0,1,1
#define TFL 1,0,0
#define TFR 1,0,1
#define TBL 1,1,0
#define TBR 1,1,1

#define POINTS_MAGIC (MAGIC + 1)
#define POINTS_MAXDIM 3
#define X 0			/* indice of dimension 1 coord */
#define Y 1
#define Z 2

typedef struct {
  int magic;
  int dim;
  int cnt;
  int size;
  int* coord;
} Points;

inline void Points_check(Points* zis) {
  assert(zis && zis->magic == POINTS_MAGIC && zis->dim <= POINTS_MAXDIM);
}

Points* Points_new(Points* zis, int dim, int cnt) {
  if (!zis) {
    zis = malloc(sizeof(Points));
    assert(zis);
  }
  zis->magic = POINTS_MAGIC;
  zis->dim = dim;
  zis->cnt = cnt;
  zis->size = sizeof(int) * zis->dim * zis->cnt;
  zis->coord = (int*) malloc(zis->size);
  assert(zis->coord);
  Points_check(zis);
  return zis;
}

void Points_delete(Points* zis) {
  Points_check(zis);
  free(zis->coord);
  free(zis);
  return;
}

FILE* Points_print(Points* zis, FILE* out) {
  int i, j;

  Points_check(zis);

  fprintf(out, "Points {\n");

  fprintf(out, "dim %d;\n", zis->dim);
  fprintf(out, "cnt %d;\n", zis->cnt);
  fprintf(out, "size %d;\n", zis->size);

  fprintf(out, "coord[] {\n");
  for (i = 0; i < zis->cnt; ++i) {
    for (j = 0; j < zis->dim; ++j) {
      fprintf(out, "%d, ", Points_get(zis, j, i));
    }
    fprintf(out, "\n");
  }
  fprintf(out, "}\n");

  fprintf(out, "}\n");

  return out;
}

inline int Points_get(Points* zis, int dim, int n) {
  return zis->coord[n * zis->dim + dim];
}

inline int PgetX(Points* zis, int n) {
  return Points_get(zis, X, n);
}

inline int PgetY(Points* zis, int n) {
  return Points_get(zis, Y, n);
}

inline int PgetZ(Points* zis, int n) {
  return Points_get(zis, Z, n);
}

inline int Points_set(Points* zis, int dim, int n, int v) {
  return zis->coord[n * zis->dim + dim] = v;
}

inline int PsetX(Points* zis, int n, int v) {
  return Points_set(zis, X, n, v);
}

inline int PsetY(Points* zis, int n, int v) {
  return Points_set(zis, Y, n, v);
}

inline int PsetZ(Points* zis, int n, int v) {
  return Points_set(zis, Z, n, v);
}

#define CUB_MAGIC (MAGIC + 2)
#define CUB_MAXDIM POINTS_MAXDIM
#define D1 0			/* indice of dimension 1 data */
#define D2 1
#define D3 2
#define D0 3

typedef struct {
  int magic;
  int dim;			/* number of dimension of cube */
  int lside;			/* log2 of side */
  int log[CUB_MAXDIM + 1];	/* log2 of side^1...MAXDIM */
  int size[CUB_MAXDIM];		/* size of side^1...MAXDIM */
  char* data[CUB_MAXDIM];	/* actual cube data with space for
				   cut thru backward in dimensions */
  int cnt;			/* for a zero dimension accumulation */
  float ratio;			/* for a zero dimension reduction */
} Cub;

inline void Cub_check(Cub* zis) {
  assert(zis && zis->magic == CUB_MAGIC && zis->dim <= CUB_MAXDIM);
}

#define _get1 data[D1][x]
#define _get2 data[D2][(x << zis->log[D1]) + y]
#define _get3 data[D3][(x << zis->log[D2]) + (y << zis->log[D1]) + (z << zis->log[D0])]

inline int Cget1(Cub* zis, int x) {
  return zis->_get1;
}

inline int Cget2(Cub* zis, int x, int y) {
  return zis->_get2;
}

inline int Cget3(Cub* zis, int x, int y, int z) {
  return zis->_get3;
}

inline int Cset1(Cub* zis, int x, int v) {
  return zis->_get1 = v;
}

inline int Cset2(Cub* zis, int x, int y, int v) {
  return zis->_get2 = v;
}

inline int Cset3(Cub* zis, int x, int y, int z, int v) {
  return zis->_get3 = v;
}

Cub* Cub_new(Cub* zis, int dim, int lside) {
  int i;

  if (!zis) {
    zis = (Cub*) malloc(sizeof(Cub));
    assert(zis);
  }
  
  zis->magic = CUB_MAGIC;
  zis->dim = dim;
  zis->lside = lside;
  for (i = 0; i < zis->dim; ++i) {
    zis->log[i] = zis->lside * (i + 1);
    zis->size[i] = 1 << zis->log[i];
    zis->data[i] = malloc(zis->size[i]);
    assert(zis->data[i]);
  }
  zis->log[D0] = 0;

  Cub_check(zis);
  return zis;
}

Cub_permut(Cub* zis, int* p) {
  int i;
  int tmp[CUB_MAXDIM + 1];

  Cub_check(zis);
  for (i = 0; i < zis->dim + 1; ++i) {
    assert(p[i] < CUB_MAXDIM + 1);
    tmp[i] = zis->log[p[i]];
  }
  for (i = 0; i < zis->dim + 1; ++i) {
    zis->log[i] = tmp[i];
  }
}

Cub_nopermut(Cub* zis) {
  int i;

  Cub_check(zis);
  for (i = 0; i < zis->dim; ++i) {
    zis->log[i] = zis->lside * (i + 1);
  }
  zis->log[D0] = 0;
}

void Cub_zero_volume(Cub* zis) {
  int x, y, z;
  int side;

  Cub_check(zis);
  side = zis->size[D1];
  for (x = 0; x < side; ++x) {
    for (y = 0; y < side; ++y) {
      for (z = 0; z < side; ++z) {
	Cset3(zis, x, y, z, 0);
      }
    }
  }
}

void Cub_zero_plane(Cub* zis) {
  int x, y;
  int side;

  Cub_check(zis);
  side = zis->size[D1];
  for (x = 0; x < side; ++x) {
    for (y = 0; y < side; ++y) {
      Cset2(zis, x, y, 0);
    }
  }
}

void Cub_zero_line(Cub* zis) {
  int x;
  int side;

  Cub_check(zis);
  side = zis->size[D1];
  for (x = 0; x < side; ++x) {
    Cset1(zis, x, 0);
  }
}

inline char* Cub_point(Cub* zis, int n) {
  Cub_check(zis);
  return &zis->data[D1][n];
}

inline char* Cub_line(Cub* zis, int n) {
  Cub_check(zis);
  return &zis->data[D2][n << zis->log[D1]];
}

inline char* Cub_plane(Cub* zis, int n) {
  Cub_check(zis);
  return &zis->data[D3][n << zis->log[D2]];
}

Cub* Cub_read(Cub* zis, int fd) {
  int n;

  Cub_check(zis);
  n = read(fd, zis->data[zis->dim - 1], zis->size[zis->dim - 1]);
  assert(n == zis->size[zis->dim - 1]);
  return zis;
}

Cub* Cub_write(Cub* zis, int dim, int fd) {
  int n;

  Cub_check(zis);
  assert(dim < CUB_MAXDIM);
  n = write(fd, zis->data[dim], zis->size[dim]);
  assert(n == zis->size[dim]);
  return zis;
}

Cub* Cub_write_pgm(Cub* zis, int fd) {
  char buf[BUFSIZ];

  sprintf(buf, "P5\n%d %d\n%d\n", zis->size[D1], zis->size[D1], 255);
  write(fd, buf, strlen(buf));
  return Cub_write(zis, D2, fd);
}

FILE* Cub_print(Cub* zis, FILE* out) {
  int i;

  Cub_check(zis);

  fprintf(out, "Cub {\n");

  fprintf(out, "dim %d;\n", zis->dim);

  fprintf(out, "log[] {\n");
  for (i = 0; i < zis->dim + 1; ++i) {
    fprintf(out, "%d, ", zis->log[i]);
  }
  fprintf(out, "}\n");

  fprintf(out, "size[] {\n");
  for (i = 0; i < zis->dim; ++i) {
    fprintf(out, "%d, ", zis->size[i]);
  }
  fprintf(out, "}\n");

  fprintf(out, "}\n");

  return out;
}

/*
 * line3d was dervied from DigitalLine.c published as "Digital Line Drawing"
 * by Paul Heckbert from "Graphics Gems", Academic Press, 1990
 *
 * 3D modifications by Bob Pendleton. The original source code was in the public
 * domain, the author of the 3D version places his modifications in the
 * public domain as well.
 *
 * line3d uses Bresenham's algorithm to generate the 3 dimensional points on a
 * line from (x1, y1, z1) to (x2, y2, z2)
 *
 */

/* find maximum of a and b */
#define MAX(a,b) (((a)>(b))?(a):(b))

/* absolute value of a */
#define ABS(a) (((a)<0) ? -(a) : (a))

/* take sign of a, either -1, 0, or 1 */
#define ZSGN(a) (((a)<0) ? -1 : (a)>0 ? 1 : 0)

#define generic_line3d(generic_point3d) {\
  int xd, yd, zd; \
  int x, y, z; \
  int ax, ay, az; \
  int sx, sy, sz; \
  int dx, dy, dz; \
 \
  dx = x2 - x1; \
  dy = y2 - y1; \
  dz = z2 - z1; \
 \
  ax = ABS(dx) << 1; \
  ay = ABS(dy) << 1; \
  az = ABS(dz) << 1; \
 \
  sx = ZSGN(dx); \
  sy = ZSGN(dy); \
  sz = ZSGN(dz); \
 \
  x = x1; \
  y = y1; \
  z = z1; \
 \
  if (ax >= MAX(ay, az)) {	/* x dominant */ \
    yd = ay - (ax >> 1); \
    zd = az - (ax >> 1); \
    for (;;) { \
      generic_point3d;		/* point3d(x, y, z) */ \
      if (x == x2) { \
	goto done; \
      } \
      if (yd >= 0) { \
	y += sy; \
	yd -= ax; \
      } \
      if (zd >= 0) { \
	z += sz; \
	zd -= ax; \
      } \
      x += sx; \
      yd += ay; \
      zd += az; \
    } \
  } else if (ay >= MAX(ax, az)) { /* y dominant */ \
    xd = ax - (ay >> 1); \
    zd = az - (ay >> 1); \
    for (;;) { \
      generic_point3d;		/* point3d(x, y, z) */ \
      if (y == y2) { \
	goto done; \
      } \
      if (xd >= 0) { \
	x += sx; \
	xd -= ay; \
      } \
      if (zd >= 0) { \
	z += sz; \
	zd -= ay; \
      } \
      y += sy; \
      xd += ax; \
      zd += az; \
    } \
  } else if (az >= MAX(ax, ay)) { /* z dominant */ \
    xd = ax - (az >> 1); \
    yd = ay - (az >> 1); \
    for (;;) { \
      generic_point3d;		/* point3d(x, y, z) */ \
      if (z == z2) { \
	goto done; \
      } \
      if (xd >= 0) { \
	x += sx; \
	xd -= az; \
      } \
      if (yd >= 0) { \
	y += sy; \
	yd -= az; \
      } \
      z += sz; \
      xd += ax; \
      yd += ay; \
    } \
  } \
  done: \
}

/*
 * cut a line thru a volume
 */
int Cub_cut_line(Cub* zis, char* line, int x1, int y1, int z1, int x2, int y2, int z2) {
  int index;
  
  index = 0;
  generic_line3d(line[index++] = Cget3(zis, x, y, z));
  return index;
}

/*
 * return a vector of points making the line
 */
int Cub_line_points(Cub* zis, Points* out, int x1, int y1, int z1, int x2, int y2, int z2) {
  int index;

  index = 0;
  generic_line3d((PsetX(out, index, x), PsetY(out, index, y), PsetZ(out, index++, z)));
  return index;
}

/*
 * sum a line thru a volume
 */
int Cub_sum_line(Cub* zis, int* sum, int x1, int y1, int z1, int x2, int y2, int z2) {
  int index;
  int tmp;

  index = 0;
  tmp = 0;
  generic_line3d(tmp += Cget3(zis, x, y, z));
  *sum = tmp;
  return index;
}

int Cub_cut_plane(Cub* zis,
	      int x1, int y1, int z1,
	      int x2, int y2, int z2,
	      int x3, int y3, int z3,
	      int x4, int y4, int z4) {
  Points* line1;
  Points* line2;
  int n1, n2;
  int side, offset;
  int i;

  side = zis->size[D1];
  line1 = Points_new(0, 3, side);
  line2 = Points_new(0, 3, side);
  n1 = Cub_line_points(zis, line1, x1, y1, z1, x2, y2, z2);
  debug(0, Points_print(line1, stderr));
  n2 = Cub_line_points(zis, line2, x3, y3, z3, x4, y4, z4);
  debug(0, Points_print(line2, stderr));
  assert(n1 == n2);
  offset = (side - n1) >> 1;
  for (i = 0; i < n1; ++i) {
    Cub_cut_line(zis, Cub_line(zis, i + offset),
		 PgetX(line1, i), PgetY(line1, i), PgetZ(line1, i),
		 PgetX(line2, i), PgetY(line2, i), PgetZ(line2, i));
  }
  Points_delete(line1);
  Points_delete(line2);
  return n1;
}

void Cub_transparence(Cub* zis) {
  int x, y, z;
  int sum;
  int tmp;
  int side;
  int i;
  int fd;

  side = zis->size[D1];

  for (x = 0; x < side; ++x) {
    for (y = 0; y < side; ++y) {
      sum = 0;
      tmp = 0;
      for (z = 0; z < side; ++z) {
	tmp += z;
	sum += Cget3(zis, z, y, x) - z;
      }
      Cset2(zis, x, y, (sum - tmp) / 256);
    }
  }

  fd = creat("out/sum-a.pgm", 0644);
  Cub_write_pgm(zis, fd);
  close(fd);

  for (x = 0; x < side; ++x) {
    for (y = 0; y < side; ++y) {
      sum = 0;
      tmp = 0;
      for (z = 0; z < side; ++z) {
	tmp += z;
	sum += Cget3(zis, z, y, x) + z;
      }
      Cset2(zis, x, y, (sum - tmp) / 256);
    }
  }

  fd = creat("out/sum-b.pgm", 0644);
  Cub_write_pgm(zis, fd);
  close(fd);

  for (i = 0; i < 8; ++i) {
    char buf[64];

    for (x = 0; x < side; ++x) {
      for (y = 0; y < side; ++y) {
	sum = 0;
	for (z = 0; z < side; ++z) {
	  sum += !!(Cget3(zis, x, y, z) & (1 << i));
	}
	Cset2(zis, x, y, sum);
      }
    }

    sprintf(buf, "out/sum-a%d.pgm", i);
    fd = creat(buf, 0644);
    Cub_write_pgm(zis, fd);
    close(fd);
  }

  for (i = 0; i < 8; ++i) {
    char buf[64];

    for (x = 0; x < side; ++x) {
      for (y = 0; y < side; ++y) {
	sum = 0;
	for (z = 0; z < side; ++z) {
	  sum += (!!(Cget3(zis, x, y, z) & (1 << i))) * z;
	}
	Cset2(zis, x, y, sum / z * z);
      }
    }

    sprintf(buf, "out/sum-b%d.pgm", i);
    fd = creat(buf, 0644);
    Cub_write_pgm(zis, fd);
    close(fd);
  }
}

void Cub_fill(Cub* zis) {
  int x, y, z;
  int side;

  side = zis->size[D1];
  for (x = 0; x < side; ++x) {
    for (y = 0; y < side; ++y) {
      for (z = 0; z < side; ++z) {
	Cset3(zis, x, y, z, x / 1.2 + y / 1.4 + z / 1.6);
      }
    }
  }
}

void Cub_test(Cub* zis) {
  int side;
  int max;
  int i;
  int fd;
  int permut[CUB_MAXDIM + 1];

  debug(0, Cub_print(zis, stderr));
  Cub_read(zis, 0);
  side = zis->size[D1];
  max = side - 1;

  fd = creat("out/bot.pgm", 0644);
  Cub_cut_plane(zis,
		0, 0, 0,
		max, 0, 0,
		0, max, 0,
		max, max, 0);
  Cub_write_pgm(zis, fd);
  close(fd);

  fd = creat("out/bot1.pgm", 0644);

  permut[D2] = D0;
  permut[D1] = D1;
  permut[D0] = D2;
  permut[D3] = D3;
  debug(1, Cub_print(zis, stderr));
  Cub_permut(zis, permut);
  debug(1, Cub_print(zis, stderr));
  Cub_cut_plane(zis,
		0, 0, 0,
		max, 0, 0,
		0, max, 0,
		max, max, 0);
  Cub_write_pgm(zis, fd);

  close(fd);

  Cub_zero_plane(zis);
  fd = creat("out/diag.raw", 0644);
  for (i = 0; i < side; ++i) {
    Cub_cut_plane(zis,
		  i, 0, 0,
		  0, 0, i,
		  i, max, 0,
		  0, max, i);
    Cub_write(zis, D2, fd);
  }
  for (i = 0; i < side; ++i) {
    Cub_cut_plane(zis,
		  max, 0, i,
		  i, 0, max,
		  max, max, i,
		  i, max, max);
    Cub_write(zis, D2, fd);
  }
  close(fd);

  Cub_zero_plane(zis);
  Cub_transparence(zis);

  Cub_fill(zis);

  fd = creat("out/fill.raw", 0644);
  Cub_write(zis, D3, fd);
  close(fd);

  Cub_nopermut(zis);
  debug(0, Cub_print(zis, stderr));
}

int main(int ac, char **av) {
  Cub* cub;

  cub = Cub_new(0, 3, 7);
  Cub_test(cub);
  return 0;
}
