#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include "debug.h"
#include "magic.h"

#include "cublib.h"
#include "tools.h"

/*
 * rotate
 */

Cub* Cub_rotate_XYZ(Cub* zis) {
  Cub_nopermut(zis);
  return zis;
}

Cub* Cub_rotate_XZY(Cub* zis) {
  int permut[CUB_MAXDIM + 1];

  Cub_check_dim(zis, 3);
  Cub_nopermut(zis);
  permut[0] = 0;
  permut[1] = 2;
  permut[2] = 1;
  permut[3] = 3;
  Cub_permut(zis, permut);
  return zis;
}

Cub* Cub_rotate_YXZ(Cub* zis) {
  int permut[CUB_MAXDIM + 1];

  Cub_check_dim(zis, 3);
  Cub_nopermut(zis);
  permut[0] = 1;
  permut[1] = 0;
  permut[2] = 2;
  permut[3] = 3;
  Cub_permut(zis, permut);
  return zis;
}

Cub* Cub_rotate_YZX(Cub* zis) {
  int permut[CUB_MAXDIM + 1];

  Cub_check_dim(zis, 3);
  Cub_nopermut(zis);
  permut[0] = 1;
  permut[1] = 2;
  permut[2] = 0;
  permut[3] = 3;
  Cub_permut(zis, permut);
  return zis;
}

Cub* Cub_rotate_ZXY(Cub* zis) {
  int permut[CUB_MAXDIM + 1];

  Cub_check_dim(zis, 3);
  Cub_nopermut(zis);
  permut[0] = 2;
  permut[1] = 0;
  permut[2] = 1;
  permut[3] = 3;
  Cub_permut(zis, permut);
  return zis;
}

Cub* Cub_rotate_ZYX(Cub* zis) {
  int permut[CUB_MAXDIM + 1];

  Cub_check_dim(zis, 3);
  Cub_nopermut(zis);
  permut[0] = 2;
  permut[1] = 1;
  permut[2] = 0;
  permut[3] = 3;
  Cub_permut(zis, permut);
  return zis;
}

struct {
  Cub* (*funk)(Cub*);
  char* name;
} Cub_faces_tab[] = {
  Cub_rotate_XYZ, "xyz",
  Cub_rotate_XZY, "xzy",
  Cub_rotate_YXZ, "yxz",
  Cub_rotate_YZX, "yzx",
  Cub_rotate_ZXY, "zxy",
  Cub_rotate_ZYX, "zyx",
};

/*
 * slice ortho
 */

Cub* Cub_faces_slice_ortho_to_files(Cub* zis, int slice, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int i;

  Cub_check_dim(zis, 3);

  verbose(1, __PRETTY_FUNCTION__ "...");
  for (i = 0; i < zis->dim << 1; ++i) {
    Cub_faces_tab[i].funk(zis);
    sprintf(buf, "%s-%s-%03d", fname, Cub_faces_tab[i].name, slice);
    Cub_slice_ortho_to_file(zis, slice, buf);
  }
  Cub_rotate_XYZ(zis);
  
  return zis;
}

Cub* Cub_slice_ortho_to_file(Cub* zis, int slice, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int fd;

  Cub_check_dim(zis, 3);
  strcpy(buf, fname);
  strcat(buf, ".pgm");
  fd = creat(buf, 0644);
  if (fd == -1) {
    error_creat(__PRETTY_FUNCTION__, buf);
    zis->error = 1;
    return zis;
  }

  plane = Cub_plane_new_from_volume(0, zis);
  Cub_slice_ortho(zis, plane, slice);

  Cub_write_pgm(plane, fd);
  Cub_delete(plane);
  close(fd);

  return zis;
}

Cub* Cub_slice_ortho(Cub* zis, Cub* plane, int slice) {
  int max;

  Cub_check_dim(zis, 3);
  Cub_check_dim(plane, 2);
  verbose(1, __PRETTY_FUNCTION__ "...");
  max = zis->size[1] - 1;
  Cub_cut_plane_m(zis, plane,
		0, 0, slice,
		max, 0, slice,
		0, max, slice,
		max, max, slice);
  return zis;
}

/*
 * transparence ortho
 */

Cub* Cub_faces_transparence_ortho_to_files(Cub* zis, Cub* attenuate, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int i;

  Cub_check_dim(zis, 3);
  Cub_check_dim(attenuate, 1);
  Cub_check_side(zis, attenuate);

  verbose(1, __PRETTY_FUNCTION__ "...");
  for (i = 0; i < zis->dim << 1; ++i) {
    Cub_faces_tab[i].funk(zis);
    sprintf(buf, "%s-%s", fname, Cub_faces_tab[i].name);
    Cub_transparence_ortho_to_file(zis, attenuate, buf);
  }
  Cub_rotate_XYZ(zis);
  
  return zis;
}

Cub* Cub_transparence_ortho_to_file(Cub* zis, Cub* attenuate, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int fd;

  Cub_check_dim(zis, 3);
  Cub_check_dim(attenuate, 1);
  Cub_check_side(zis, attenuate);
  strcpy(buf, fname);
  strcat(buf, ".pgm");
  fd = creat(buf, 0644);
  if (fd == -1) {
    error_creat(__PRETTY_FUNCTION__, buf);
    zis->error = 1;
    return zis;
  }

  plane = Cub_plane_new_from_volume(0, zis);
  Cub_transparence_ortho(zis, plane, attenuate);

  Cub_write_pgm(plane, fd);
  Cub_delete(plane);
  close(fd);

  return zis;
}

Cub* Cub_transparence_ortho(Cub* zis, Cub* plane, Cub* attenuate) {
  int side;
  int x, y, z;

  Cub_check_dim(zis, 3);
  Cub_check_dim(plane, 2);
  Cub_check_dim(attenuate, 1);
  Cub_check_side(zis, plane);
  Cub_check_side(zis, attenuate);
  verbose(1, __PRETTY_FUNCTION__ "...");

  side = zis->size[1];
  for (x = 0; x < side; ++x) {
    for (y = 0; y < side; ++y) {
      int sum;

      sum = 0;
      for (z = 0; z < side; ++z) {
	int v, a;

	v = Cget3(zis, z, y, x);
	a = Cget1(attenuate, z);
	v = v > a ? v - a : v;
	sum += v;
      }
      Cset2(plane, x, y, sum >> zis->side);
    }
  }
  return zis;
}

Cub* Cub_faces_transparence_ortho_on_bits_to_files(Cub* zis, Cub* attenuate, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int i;

  Cub_check_dim(zis, 3);
  Cub_check_dim(attenuate, 1);
  Cub_check_side(zis, attenuate);

  verbose(1, __PRETTY_FUNCTION__ "...");
  for (i = 0; i < zis->dim << 1; ++i) {
    Cub_faces_tab[i].funk(zis);
    sprintf(buf, "%s-%s", fname, Cub_faces_tab[i].name);
    Cub_transparence_ortho_on_bits_to_file(zis, attenuate, buf);
  }
  Cub_rotate_XYZ(zis);
  
  return zis;
}

Cub* Cub_transparence_ortho_on_bits_to_file(Cub* zis, Cub* attenuate, char* fname) {
  char buf[BUFSIZ];
  Cub plane[8];
  int fd;
  int i;
  int nbits;

  nbits = 8;
  Cub_check_dim(zis, 3);
  Cub_check_dim(attenuate, 1);
  Cub_check_side(zis, attenuate);

  for (i = 0; i < nbits; ++i) {
    Cub_plane_new_from_volume(&plane[i], zis);
  }
  Cub_transparence_ortho_on_bits(zis, plane, attenuate);
  for (i = 0; i < nbits; ++i) {
    sprintf(buf, "%s-%d.pgm", fname, i);
    fd = creat(buf, 0644);
    if (fd == -1) {
      error_creat(__PRETTY_FUNCTION__, buf);
      zis->error = 1;
      return zis;
    }
    Cub_write_pgm(&plane[i], fd);
    Cub_delete(&plane[i]);
    close(fd);
  }
  return zis;
}

Cub* Cub_transparence_ortho_on_bits(Cub* zis, Cub* plane, Cub* attenuate) {
  int sum[8];
  int x, y, z;
  int side;
  int i;
  int nbits;

  Cub_check_dim(zis, 3);
  verbose(1, __PRETTY_FUNCTION__ "...");
  nbits = 8;
  for (i = 0; i < nbits; ++i) {
    Cub_check_dim(&plane[i], 2);
    Cub_check_side(zis, &plane[i]);
  }
  side = zis->size[1];
  for (x = 0; x < side; ++x) {
    for (y = 0; y < side; ++y) {
      for (i = 0; i < nbits; ++i) {
	sum[i] = 0;
      }
      for (z = 0; z < side; ++z) {
	for (i = 0; i < nbits; ++i) {
	  int v, a;

	  v = !!(Cget3(zis, x, y, z) & (1 << i));
	  a = Cget1(attenuate, z);
	  v = v ? 255 - a : 0;
	  sum[i] += v;
	}
      }
      for (i = 0; i < nbits; ++i) {
	Cset2(&plane[i], x, y, sum[i] >> zis->side);
      }
    }
  }
  return zis;
}

/*
 * diagonale
 */

Cub* Cub_slice_thru_diagonale_to_file(Cub* zis, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int side;
  int max;
  int fd;
  int i;

  Cub_check(zis);
  verbose(1, __PRETTY_FUNCTION__ "...");
  side = zis->size[1];
  max = side - 1;

  plane = Cub_plane_new_from_volume(0, zis);

  sprintf(buf, "%s-%dx3.raw", fname, zis->size[1]);
  fd = creat(buf, 0644);
  if (fd == -1) {
    error_creat(__PRETTY_FUNCTION__, buf);
    zis->error = 1;
    return zis;
  }

  for (i = 0; i < side; i += 2) {
    Cub_cut_plane(zis, plane,
		  i, 0, 0,
		  0, 0, i,
		  i, max, 0,
		  0, max, i);
    Cub_write(plane, fd);
  }
  for (i = 0; i < side; i += 2) {
    Cub_cut_plane(zis, plane,
		  max, 0, i,
		  i, 0, max,
		  max, max, i,
		  i, max, max);
    Cub_write(plane, fd);
  }

  close(fd);
  return zis;
}

Cub* Cub_slice_thru_2diagonale_to_file(Cub* zis, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int side;
  int max;
  int fd;
  int i;

  Cub_check(zis);
  verbose(1, __PRETTY_FUNCTION__ "...");
  side = zis->size[1];
  max = side - 1;

  plane = Cub_plane_new_from_volume(0, zis);
  Cub_zero(plane);

  sprintf(buf, "%s-%dx3.raw", fname, zis->size[1]);
  fd = creat(buf, 0644);
  if (fd == -1) {
    error_creat(__PRETTY_FUNCTION__, buf);
    zis->error = 1;
    return zis;
  }

  for (i = 0; i < side; i += 3) {
    Cub_cut_plane(zis, plane,
		  i, 0, 0,
		  0, 0, i,
		  0, i, 0,
		  0, i, 0);
    Cub_write(plane, fd);
    Cub_zero(plane);
  }
  for (i = 0; i < side; i += 3) {
    Cub_cut_plane(zis, plane,
		  max, 0, i,
		  i, 0, max,
		  i, max, 0,
		  0, max, i);
    Cub_write(plane, fd);
    Cub_zero(plane);
  }
  for (i = 0; i < side; i += 3) {
    Cub_cut_plane(zis, plane,
		  max, i, max,
		  max, i, max,
		  max, max, i,
		  i, max, max);
    Cub_write(plane, fd);
    Cub_zero(plane);
  }

  close(fd);
  return zis;
}

/*
 * relative
 */

Cub* Cub_plane_relative_to_files(Cub* zis, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int i;

  Cub_check_dim(zis, 3);

  verbose(1, __PRETTY_FUNCTION__ "...");
  for (i = 0; i < zis->dim << 1; ++i) {
    Cub_faces_tab[i].funk(zis);
    sprintf(buf, "%s-%s", fname, Cub_faces_tab[i].name);
    Cub_plane_relative_to_file(zis, buf);
  }
  Cub_rotate_XYZ(zis);
  
  return zis;
}

Cub* Cub_plane_relative_to_file(Cub* zis, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int fd;

  Cub_check_dim(zis, 3);
  strcpy(buf, fname);
  strcat(buf, ".pgm");
  fd = creat(buf, 0644);
  if (fd == -1) {
    error_creat(__PRETTY_FUNCTION__, buf);
    zis->error = 1;
    return zis;
  }

  if (0) {
    plane = Cub_plane_new(0, 8, 0);
  } else {
    plane = Cub_plane_new_from_volume(0, zis);
  }
  Cub_zero(plane);
  Cub_plane_relative(zis, plane);

  Cub_write_pgm(plane, fd);
  Cub_delete(plane);
  close(fd);

  return zis;
}

Cub* Cub_plane_relative_move_to_files(Cub* zis, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int i;

  Cub_check_dim(zis, 3);

  verbose(1, __PRETTY_FUNCTION__ "...");
  for (i = 0; i < zis->dim << 1; ++i) {
    Cub_faces_tab[i].funk(zis);
    sprintf(buf, "%s-%s", fname, Cub_faces_tab[i].name);
    Cub_plane_relative_move_to_file(zis, buf);
  }
  Cub_rotate_XYZ(zis);
  
  return zis;
}

Cub* Cub_plane_relative_move_to_file(Cub* zis, char* fname) {
  Cub* plane;
  char buf[BUFSIZ];
  int fd;

  Cub_check_dim(zis, 3);
  strcpy(buf, fname);
  strcat(buf, ".pgm");
  fd = creat(buf, 0644);
  if (fd == -1) {
    error_creat(__PRETTY_FUNCTION__, buf);
    zis->error = 1;
    return zis;
  }

  if (0) {
    plane = Cub_plane_new(0, 8, 0);
  } else {
    plane = Cub_plane_new_from_volume(0, zis);
  }
  Cub_zero(plane);
  Cub_plane_relative_move(zis, plane);

  Cub_write_pgm(plane, fd);
  Cub_delete(plane);
  close(fd);

  return zis;
}

/*
 * volume
 */

Cub* Cub_volume_to_file(Cub* zis, char* fname) {
  char buf[BUFSIZ];
  int fd;

  Cub_check_dim(zis, 3);
  sprintf(buf, "%s-%dx3.raw", fname, zis->size[1]);
  fd = creat(buf, 0644);
  if (fd == -1) {
    error_creat(__PRETTY_FUNCTION__, buf);
    zis->error = 1;
    return zis;
  }
  Cub_write(zis, fd);
  close(fd);
  return zis;
}

Cub* Cub_fill_(Cub* zis) {
  int x, y, z;
  int side;

  verbose(1, __PRETTY_FUNCTION__ "...");
  side = zis->size[1];
  for (x = 0; x < side; ++x) {
    for (y = 0; y < side; ++y) {
      for (z = 0; z < side; ++z) {
	Cset3(zis, x, y, z, x / 3 + y / 3 + z / 3);
      }
    }
  }
  return zis;
}

Cub* Cub_fill(Cub* zis) {
  int x, y, z;
  int side;

  verbose(1, __PRETTY_FUNCTION__ "...");
  Cub_zero(zis);
  side = zis->size[1] >> 2;
  for (x = 0; x < side; ++x) {
    for (y = 0; y < side; ++y) {
      for (z = 0; z < side; ++z) {
	Cset3(zis, x, y, z, x + y + z);
      }
    }
  }
  return zis;
}

