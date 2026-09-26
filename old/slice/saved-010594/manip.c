#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include "debug.h"
#include "magic.h"

#include "cublib.h"

void Cub_fill(Cub* zis) {
  int x, y, z;
  int side;

  side = zis->size[D1];
  for (x = 0; x < side; ++x) {
    for (y = 0; y < side; ++y) {
      for (z = 0; z < side; ++z) {
	Cset3(zis, x, y, z, x / 3 + y / 3 + z / 3);
      }
    }
  }
}

void Cub_rotate_XYZ(Cub* zis) {
  Cub_nopermut(zis);
}

void Cub_rotate_XZY(Cub* zis) {
  int permut[CUB_MAXDIM + 1];

  Cub_nopermut(zis);

  permut[D0] = D0;
  permut[D1] = D2;
  permut[D2] = D1;
  permut[D3] = D3;

  Cub_permut(zis, permut);
}

void Cub_rotate_YXZ(Cub* zis) {
  int permut[CUB_MAXDIM + 1];

  Cub_nopermut(zis);

  permut[D0] = D1;
  permut[D1] = D0;
  permut[D2] = D2;
  permut[D3] = D3;

  Cub_permut(zis, permut);
}

void Cub_rotate_YZX(Cub* zis) {
  int permut[CUB_MAXDIM + 1];

  Cub_nopermut(zis);

  permut[D0] = D1;
  permut[D1] = D2;
  permut[D2] = D0;
  permut[D3] = D3;

  Cub_permut(zis, permut);
}

void Cub_rotate_ZXY(Cub* zis) {
  int permut[CUB_MAXDIM + 1];

  Cub_nopermut(zis);

  permut[D0] = D2;
  permut[D1] = D0;
  permut[D2] = D1;
  permut[D3] = D3;

  Cub_permut(zis, permut);
}

/**/
void Cub_rotate_ZYX(Cub* zis) {
  int permut[CUB_MAXDIM + 1];

  Cub_nopermut(zis);

  permut[D0] = D2;
  permut[D1] = D1;
  permut[D2] = D0;
  permut[D3] = D3;

  Cub_permut(zis, permut);
}
