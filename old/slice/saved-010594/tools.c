#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include "debug.h"
#include "magic.h"

#include "cublib.h"

int Cub_volume_to_file(Cub* zis, char* fname) {
  char buf[BUFSIZ];
  int fd;

  sprintf(buf, "%s-%dx3.raw", fname, zis->size[D1]);
  fd = creat(buf, 0644);
  if (fd == -1) {
    error_creat(__PRETTY_FUNCTION__, buf);
    return 0;
  }
  Cub_write(zis, D3, fd);
  close(fd);
}

void Cub_slice_ortho(Cub* zis, int slice) {
  int side;
  int max;

  side = zis->size[D1];
  max = side - 1;

  Cub_cut_plane(zis,
		0, 0, slice,
		max, 0, slice,
		0, max, slice,
		max, max, slice);
}

int Cub_slice_ortho_to_file(Cub* zis, int slice, char* fname) {
  int fd;

  char buf[BUFSIZ];
  strcpy(buf, fname);
  strcat(buf, ".pgm");

  fd = creat(buf, 0644);
  if (fd == -1) {
    error_creat(__PRETTY_FUNCTION__, buf);
    return 0;
  }

  Cub_slice_ortho(zis, slice);

  Cub_write_pgm(zis, fd);
  close(fd);

  return 1;
}

int Cub_slice_thru_diagonale_to_file(Cub* zis, char* fname) {
  char buf[BUFSIZ];
  int side;
  int max;
  int i;
  int fd;

  side = zis->size[D1];
  max = side - 1;

  Cub_zero_plane(zis);

  sprintf(buf, "%s-%dx3.raw", fname, zis->size[D1]);

  fd = creat(buf, 0644);
  if (fd == -1) {
    error_creat(__PRETTY_FUNCTION__, buf);
    return 0;
  }

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
  return 1;
}

void Cub_faces(Cub* zis, char* fname) {
  char buf[BUFSIZ];
  int dbg;

  dbg = 0;

  Cub_zero_plane(zis);
  Cub_rotate_XYZ(zis);
  debug(dbg, Cub_print(zis, stderr));
  sprintf(buf, "%s-xyz-0", fname);
  Cub_slice_ortho_to_file(zis, 0, buf);

  Cub_zero_plane(zis);
  Cub_rotate_XZY(zis);
  debug(dbg, Cub_print(zis, stderr));
  sprintf(buf, "%s-xzy-0", fname);
  Cub_slice_ortho_to_file(zis, 0, buf);

  Cub_zero_plane(zis);
  Cub_rotate_YXZ(zis);
  debug(dbg, Cub_print(zis, stderr));
  sprintf(buf, "%s-yxz-0", fname);
  Cub_slice_ortho_to_file(zis, 0, buf);

  Cub_zero_plane(zis);
  Cub_rotate_YZX(zis);
  debug(dbg, Cub_print(zis, stderr));
  sprintf(buf, "%s-yzx-0", fname);
  Cub_slice_ortho_to_file(zis, 0, buf);

  Cub_zero_plane(zis);
  Cub_rotate_ZXY(zis);
  debug(dbg, Cub_print(zis, stderr));
  sprintf(buf, "%s-zxy-0", fname);
  Cub_slice_ortho_to_file(zis, 0, buf);

  Cub_zero_plane(zis);
  Cub_rotate_ZYX(zis);
  debug(dbg, Cub_print(zis, stderr));
  sprintf(buf, "%s-zyx-0", fname);
  Cub_slice_ortho_to_file(zis, 0, buf);

  Cub_zero_plane(zis);
  Cub_rotate_XYZ(zis);
  debug(dbg, Cub_print(zis, stderr));
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

