#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#include "bit-field.h"
#include "gapp-defs.h"
#include "gapp-arch.h"
#include "gapp-pe.h"
#include "gapp-sim.h"

Neighboor_Offset* Neighboor_Offset_new(Neighboor_Offset* zis, int side) {
  int size;
  int i;

  if (!zis) {
    zis = (Neighboor_Offset*)malloc(sizeof(Neighboor_Offset));
    assert(zis);
  }
  zis->side = side;
  size = zis->size = side * side;

  zis->first.north = (int*)malloc(side * sizeof(int));
  assert(zis->first.north);
  zis->mid.north = (int*)malloc(side * sizeof(int));
  assert(zis->mid.north);
  for (i = 0; i < side; ++i) {
    zis->first.north[i] = ((size - side) + i);
    zis->mid.north[i] = -side + i;
  }
  zis->last.north = zis->mid.north;

  zis->first.south = (int*)malloc(side * sizeof(int));
  assert(zis->first.south);
  zis->last.south = (int*)malloc(side * sizeof(int));
  assert(zis->last.south);
  for (i = 0; i < side; ++i) {
    zis->first.south[i] = side + i;
    zis->last.south[i] = -(size - side) + i;
  }
  zis->mid.south = zis->first.south;

  zis->first.east = (int*)malloc(side * sizeof(int));
  assert(zis->first.east);
  for (i = 0; i < side - 1; ++i) {
    zis->first.east[i] = i + 1;
  }
  zis->first.east[side - 1] = 0;
  zis->mid.east = zis->last.east= zis->first.east;

  zis->first.west = (int*)malloc(side * sizeof(int));
  assert(zis->first.west);
  zis->first.west[0] = side - 1;
  for (i = 1; i < side; ++i) {
    zis->first.west[i] = i - 1;
  }
  zis->mid.west = zis->last.west = zis->first.west;

  zis->north.first = zis->first.north;
  zis->north.mid = zis->mid.north;
  zis->north.last = zis->last.north;
  zis->south.first = zis->first.south;
  zis->south.mid = zis->mid.south;
  zis->south.last = zis->last.south;
  zis->east.first = zis->first.east;
  zis->east.mid = zis->mid.east;
  zis->east.last = zis->last.east;
  zis->west.first = zis->first.west;
  zis->west.mid = zis->mid.west;
  zis->west.last = zis->last.west;

  return zis;
}

void Neighboor_Offset_print(Neighboor_Offset* zis) {
  int i;
  fprintf(stderr, "%d %d\n", zis->side, zis->side);
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->first.north[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->mid.north[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->last.north[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->first.south[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->mid.south[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->last.south[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->first.east[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->mid.east[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->last.east[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->first.west[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->mid.west[i]);
  }
  fprintf(stderr, "\n");
  for (i = 0; i < zis->side; ++i) {
    fprintf(stderr, "%d ", zis->last.west[i]);
  }
  fprintf(stderr, "\n");
}

Gappsim* Gappsim_new(Gappsim* zis, int side) {
  if (!zis) {
    zis = (Gappsim*)malloc(sizeof(Gappsim)); assert(zis);
  }
  Gapp_new(&zis->gapp);
  zis->side = side;
  zis->size = side * side;
  zis->gen = 0;
  zis->past = malloc(zis->size); assert(zis->past); memset(zis->past, 0, zis->size);
  zis->futur = malloc(zis->size); assert(zis->futur); memset(zis->futur, 0, zis->size);
  zis->memory = (int*)malloc(zis->size * (4 * sizeof(int))); assert(zis->memory);
  memset(zis->memory, 0, zis->size * (4 * sizeof(int)));
  zis->plane = malloc(zis->size >> 3); assert(zis->plane);
  memset(zis->plane, 0, zis->size >> 3);
  Neighboor_Offset_new(&zis->torus, side);
  zis->neighboor_offset = &zis->torus;
  return zis;
}

Gappsim_extract(Gappsim* zis, int plane) { extern int
  (*textract[])(unsigned char*, unsigned char*, int);

  textract[plane](zis->past, zis->plane, zis->size);
}

void Gappsim_trace(Gappsim* zis, int input, int output, int index) {
  static int oinput, ooutput, cnt = 1;
  int* i;
  int* o;

  if (input == oinput) {
    assert(output == ooutput);
    ++cnt;
    return;
  } else {
    Bit_Field_explode(&zis->gapp.input, oinput);
    i = zis->gapp.input.explode;
    fprintf(stderr,
	    "  _EOW _NOS _RAM __BW __CY __SM ___C __EW __NS RAMI __CI _EWI _NSI (%d times, gen %d, x %d y %d)\n",
	    cnt, zis->gen, index / zis->side, index % zis->side);
    fprintf(stderr,
	    "I %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d (%d)\n",
	    i[GAPP_EOW], i[GAPP_NOS], i[GAPP_RAM],
	    i[GAPP_BW], i[GAPP_CY], i[GAPP_SM],
	    i[GAPP_C], i[GAPP_EW], i[GAPP_NS],
	    i[GAPP_RAMI], i[GAPP_CI], i[GAPP_EWI], i[GAPP_NSI], oinput);
    Bit_Field_explode(&zis->gapp.output, ooutput);
    o = zis->gapp.output.explode;
    fprintf(stderr, "O           %4d %4d %4d %4d %4d %4d %4d                     (%d)\n",
	    o[GAPP_NRAM], o[GAPP_NBW], o[GAPP_NCY], o[GAPP_NSM], o[GAPP_NC], o[GAPP_NEW], o[GAPP_NNS], ooutput);
    oinput = input;
    ooutput = output;
    cnt = 1;
  }
}

