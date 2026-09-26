#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include "debug.h"
#include "magic.h"

#include "cublib.h"

/*
 * Points
 */

static inline void Points_check(Points* zis) {
  assert(zis && zis->magic == POINTS_MAGIC && zis->dim <= POINTS_MAXDIM);
}

static inline int Points_get(Points* zis, int dim, int n) {
  return zis->coord[n * zis->dim + dim];
}

static inline int PgetX(Points* zis, int n) { return Points_get(zis, X, n); }
static inline int PgetY(Points* zis, int n) { return Points_get(zis, Y, n); }
static inline int PgetZ(Points* zis, int n) { return Points_get(zis, Z, n); }

static inline int Points_set(Points* zis, int dim, int n, int v) {
  return zis->coord[n * zis->dim + dim] = v;
}

static inline int PsetX(Points* zis, int n, int v) { return Points_set(zis, X, n, v); }
static inline int PsetY(Points* zis, int n, int v) { return Points_set(zis, Y, n, v); }
static inline int PsetZ(Points* zis, int n, int v) { return Points_set(zis, Z, n, v); }

Points* Points_new(Points* zis, int dim, int cnt) {
  if (!zis) {
    zis = malloc(sizeof(Points));
    assert(zis);
    zis->free_flag = 1;
  }
  zis->free_flag = 0;
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

/*
 * Cub
 */

Cub* Cub_check(Cub* zis) {
  assert(zis && zis->magic == CUB_MAGIC && zis->dim >= 0 && zis->dim <= CUB_MAXDIM);
  return zis;
}

Cub* Cub_check3(Cub* zis, int x, int y, int z) {
  assert(x >= 0 && x < zis->size[1]);
  assert(y >= 0 && y < zis->size[1]);
  assert(z >= 0 && z < zis->size[1]);
  return zis;
}

Cub* Cub_check_dim(Cub* zis, int dim) {
  Cub_check(zis);
  assert(zis->dim == dim);
  return zis;
}

Cub* Cub_check_side(Cub* zis, Cub* cub) {
  assert(zis->side == cub->side);
  return zis;
}

#define _mod(n) (n + zis->size[1] & zis->mask)

#define _get1 data[x]
#define _get2 data[(x << zis->log[0]) + (y << zis->log[1])]
#define _get2m data[(_mod(x) << zis->log[0]) + (_mod(y) << zis->log[1])]
#define _get3 data[(x << zis->log[0]) + (y << zis->log[1]) + (z << zis->log[2])]
#define _get3m data[(_mod(x) << zis->log[0]) + (_mod(y) << zis->log[1]) + (_mod(z) << zis->log[2])]

#define _trace3(x, y, z) { debug(1, fprintf(stderr, "%d %d %d\n", x, y, z)); }

inline int Cget1(Cub* zis, int x) { return zis->_get1; }
inline int Cget2(Cub* zis, int x, int y) { return zis->_get2; }
inline int Cget3(Cub* zis, int x, int y, int z) { return zis->_get3; }
inline int Cget3m(Cub* zis, int x, int y, int z) { return zis->_get3m; }
inline int Cset1(Cub* zis, int x, int v) { return zis->_get1 = v; }
inline int Cset2(Cub* zis, int x, int y, int v) { return zis->_get2 = v; }
inline int Cset2m(Cub* zis, int x, int y, int v) { return zis->_get2m = v; }
inline int Cset3(Cub* zis, int x, int y, int z, int v) { return zis->_get3 = v; }

inline char* Cub_point(Cub* zis, int n) {
  Cub_check(zis);
  return &zis->data[n << zis->log[0]];
}

inline char* Cub_line(Cub* zis, int n) {
  Cub_check(zis);
  return &zis->data[n << zis->log[1]];
}

inline char* Cub_plane(Cub* zis, int n) {
  Cub_check(zis);
  return &zis->data[n << zis->log[2]];
}

Cub* Cub_new(Cub* zis, int dim, int side, int elt) {
  int i;

  if (!zis) {
    zis = (Cub*) malloc(sizeof(Cub));
    assert(zis);
    zis->free_flag = 1;
  } else {
    zis->free_flag = 0;
  }
  zis->magic = CUB_MAGIC;
  zis->dim = dim;
  zis->side = side;
  zis->mask = (1 << side) - 1;
  zis->elt = elt;
  zis->log[0] = elt;
  zis->size[0] = 1 << zis->log[0];
  for (i = 1; i <= zis->dim; ++i) {
    zis->log[i] = zis->side * i;
    zis->size[i] = 1 << zis->log[i];
  }
  zis->data = malloc(zis->size[dim]);
  assert(zis->data);
  Cub_check(zis);
  return zis;
}

Cub* Cub_volume_new(Cub* zis, int side, int elt) {
  return Cub_new(zis, 3, side, elt);
}

Cub* Cub_plane_new(Cub* zis, int side, int elt) {
  return Cub_new(zis, 2, side, elt);
}

Cub* Cub_line_new(Cub* zis, int side, int elt) {
  return Cub_new(zis, 1, side, elt);
}

Cub* Cub_plane_new_from_volume(Cub* zis, Cub* volume) {
  return Cub_plane_new(zis, volume->side, volume->elt);
}

Cub* Cub_line_new_from_volume(Cub* zis, Cub* volume) {
  return Cub_line_new(zis, volume->side, volume->elt);
}

void Cub_delete(Cub* zis) {
  Cub_check(zis);
  free(zis->data);
  if (zis->free_flag) {
    free(zis);
  }
}

FILE* Cub_print(Cub* zis, FILE* out) {
  int i;

  Cub_check(zis);

  fprintf(out, "Cub {\n");

  fprintf(out, "dim %d;\n", zis->dim);
  fprintf(out, "elt %d;\n", zis->elt);

  fprintf(out, "log[] {\n");
  for (i = 0; i <= zis->dim; ++i) {
    fprintf(out, "%d, ", zis->log[i]);
  }
  fprintf(out, "}\n");

  fprintf(out, "size[] {\n");
  for (i = 0; i <= zis->dim; ++i) {
    fprintf(out, "%d, ", zis->size[i]);
  }
  fprintf(out, "}\n");

  fprintf(out, "}\n");

  return out;
}

Cub* Cub_permut(Cub* zis, int* p) {
  int i;
  int tmp[CUB_MAXDIM + 1];

  Cub_check(zis);
  for (i = 0; i <= zis->dim; ++i) {
    assert(p[i] <= CUB_MAXDIM);
    tmp[i] = zis->log[p[i]];
  }
  for (i = 0; i <= zis->dim; ++i) {
    zis->log[i] = tmp[i];
  }
  return zis;
}

Cub* Cub_nopermut(Cub* zis) {
  int i;

  Cub_check(zis);
  zis->log[0] = zis->elt;
  zis->size[0] = 1 << zis->log[0];
  for (i = 1; i <= zis->dim; ++i) {
    zis->log[i] = zis->side * i;
    zis->size[i] = 1 << zis->log[i];
  }
  return zis;
}

Cub* Cub_line_ramp(Cub* zis) {
  int i;

  Cub_check_dim(zis, 1);
  for (i = 0; i < zis->size[1]; ++i) {
    Cset1(zis, i, i);
  }
  return zis;
}

Cub* Cub_zero(Cub* zis) {
    Cub_check(zis);
    memset(zis->data, 0, zis->size[zis->dim]);
}

Cub* Cub_read(Cub* zis, int fd) {
  int n;

  Cub_check(zis);
  verbose(1, __PRETTY_FUNCTION__ "...");
  n = read(fd, zis->data, zis->size[zis->dim]);
  assert(n == zis->size[zis->dim]);
  return zis;
}

Cub* Cub_write(Cub* zis, int fd) {
  int n;

  Cub_check(zis);
  verbose(1, __PRETTY_FUNCTION__ "...");
  n = write(fd, zis->data, zis->size[zis->dim]);
  assert(n == zis->size[zis->dim]);
  return zis;
}

Cub* Cub_write_pgm(Cub* zis, int fd) {
  char buf[BUFSIZ];
  
  Cub_check(zis);
  switch(zis->dim) {
  case 1:
    sprintf(buf, "P5\n%d %d\n%d\n", 1, zis->size[1], 255);
    break;
  case 2:
    sprintf(buf, "P5\n%d %d\n%d\n", zis->size[1], zis->size[1], 255);
    break;
  case 3:
    sprintf(buf, "P5\n%d %d\n%d\n", zis->size[1], zis->size[2], 255);
    break;
  default:
    assert(0);
  }
  write(fd, buf, strlen(buf));
  return Cub_write(zis, fd);
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

  debug(0, fprintf(stderr, "%d %d %d %d %d %d\n", x1, y1, z1, x2, y2, z2));
  index = 0;
  generic_line3d(line[index++] = Cget3(zis, x, y, z));
  return index;
}

int Cub_cut_line_m(Cub* zis, char* line, int x1, int y1, int z1, int x2, int y2, int z2) {
  int index;

  debug(0, fprintf(stderr, "%d %d %d %d %d %d\n", x1, y1, z1, x2, y2, z2));
  index = 0;
  generic_line3d(line[index++] = Cget3m(zis, x, y, z));
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

inline int line3d_count(int x1, int y1, int z1, int x2, int y2, int z2) {
  return MAX(ABS(x2 - x1), MAX(ABS(y2 - y1), ABS(z2 - z1)));
}

int Cub_cut_plane(Cub* zis, Cub* plane,
	      int x1, int y1, int z1,
	      int x2, int y2, int z2,
	      int x3, int y3, int z3,
	      int x4, int y4, int z4) {
  Points* line1;
  Points* line2;
  int n1, n2;
  int side, offset;
  int i;

  Cub_check(zis);
  Cub_check(plane);
  assert(zis->dim == 3 && plane->dim == 2);
  side = zis->size[1];
  line1 = Points_new(0, 3, side);
  line2 = Points_new(0, 3, side);
  n1 = Cub_line_points(zis, line1, x1, y1, z1, x3, y3, z3);
  debug(0, Points_print(line1, stderr));
  n2 = Cub_line_points(zis, line2, x2, y2, z2, x4, y4, z4);
  debug(0, Points_print(line2, stderr));
  assert(n1 == n2);
  offset = (side - n1) >> 1;
  for (i = 0; i < n1; ++i) {
    x1 = PgetX(line1, i);
    y1 = PgetY(line1, i);
    z1 = PgetZ(line1, i);
    x2 = PgetX(line2, i);
    y2 = PgetY(line2, i);
    z2 = PgetZ(line2, i);
    n2 = line3d_count(x1, y1, z1, x2, y2, z2);
    Cub_cut_line(zis, Cub_line(plane, i + offset) + ((side - n2) >> 1),
		 x1, y1, z1, x2, y2, z2);
  }
  Points_delete(line1);
  Points_delete(line2);
  return n1;
}

int Cub_cut_plane_m(Cub* zis, Cub* plane,
	      int x1, int y1, int z1,
	      int x2, int y2, int z2,
	      int x3, int y3, int z3,
	      int x4, int y4, int z4) {
  Points* line1;
  Points* line2;
  int n1, n2;
  int side, offset;
  int i;

  Cub_check_dim(zis, 3);
  Cub_check_dim(plane, 2);
  side = zis->size[1];
  line1 = Points_new(0, 3, side);
  line2 = Points_new(0, 3, side);
  n1 = Cub_line_points(zis, line1, x1, y1, z1, x3, y3, z3);
  debug(0, Points_print(line1, stderr));
  n2 = Cub_line_points(zis, line2, x2, y2, z2, x4, y4, z4);
  debug(0, Points_print(line2, stderr));
  assert(n1 == n2);
  offset = (side - n1) >> 1;
  for (i = 0; i < n1; ++i) {
    x1 = PgetX(line1, i);
    y1 = PgetY(line1, i);
    z1 = PgetZ(line1, i);
    x2 = PgetX(line2, i);
    y2 = PgetY(line2, i);
    z2 = PgetZ(line2, i);
    n2 = line3d_count(x1, y1, z1, x2, y2, z2);
    Cub_cut_line_m(zis, Cub_line(plane, i + offset) + ((side - n2) >> 1),
		 x1, y1, z1, x2, y2, z2);
  }
  Points_delete(line1);
  Points_delete(line2);
  return n1;
}

Cub* Cub_plane_relative(Cub* zis, Cub* plane) {
  int i;
  int side;
  int half;

  Cub_check_dim(zis, 3);
  Cub_check_dim(plane, 2);
  side = zis->size[1];
  half = side >> 1;
  for (i = 0; i < half; ++i) {
    Cub_cut_perimeter(zis, plane, half, half - i, half, i);
  }
  return zis;
}

Cub* Cub_plane_relative_move(Cub* zis, Cub* plane) {
  int i;
  int side;
  int half;

  Cub_check_dim(zis, 3);
  Cub_check_dim(plane, 2);
  side = zis->size[1];
  half = side >> 1;
  for (i = 0; i < half; ++i) {
if (1) {
    Cub_cut_perimeter_move(zis, plane,
		      half + (i >> 1), half - i, half + (i >> 1),
		      half, half, half,
		      i);
  } else {
    Cub_cut_perimeter_move(zis, plane,
		      half + (i >> 1), side - i, half + (i >> 1),
		      half, half, half,
		      i);
  }
  }
  return zis;
}

Cub* Cub_cut_perimeter(Cub* zis, Cub* plane, int x, int y, int z, int n) {
  int i;

  Cub_check_dim(zis, 3);
  Cub_check_dim(plane, 2);
  for (i = z-n; i <= z+n; ++i) { Cset2m(plane, x-n, i, Cget3m(zis, x-n, y, i)); }
  for (i = z-n; i <= z+n; ++i) { Cset2m(plane, x+n, i, Cget3m(zis, x+n, y, i)); }
  for (i = x-n; i <= x+n; ++i) { Cset2m(plane, i, z-n, Cget3m(zis, i, y, z-n)); }
  for (i = x-n; i <= x+n; ++i) { Cset2m(plane, i, z+n, Cget3m(zis, i, y, z+n)); }
  return zis;
}

Cub* Cub_cut_perimeter_move(Cub* zis, Cub* plane,
		       int x1, int y1, int z1,
		       int x2, int y2, int z2,
		       int n) {
  int i;

  Cub_check_dim(zis, 3);
  Cub_check_dim(plane, 2);
  for (i=0; i<(n<<1); ++i) { Cset2m(plane, x2-n, (z2-n)+i, Cget3m(zis, x1-n, y1, (z1-n)+i)); }
  for (i=0; i<(n<<1); ++i) { Cset2m(plane, x2+n, (z2-n)+i, Cget3m(zis, x1+n, y1, (z1-n)+i)); }
  for (i=0; i<(n<<1); ++i) { Cset2m(plane, (x2-n)+i, z2-n, Cget3m(zis, (x1-n)+i, y1, z1-n)); }
  for (i=0; i<(n<<1); ++i) { Cset2m(plane, (x2-n)+i, z2+n, Cget3m(zis, (x1-n)+i, y1, z1+n)); }
  return zis;
}
