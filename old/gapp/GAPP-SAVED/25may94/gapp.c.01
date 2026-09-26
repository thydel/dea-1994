#include <sys/types.h>
#include <sys/mman.h>

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#include "gappfields.h"

/*
 * standards neighboors pipeline
 *
 * 16 14 12 10  8  6  4  2  0
 *  8  7  6  5  4  3  2  1  0
 * NW _W SW _N _C _S NE _E SE
 *
 * gapp context layout
 *
 * externals                internals                     instructions
 * ------------------------ ----------------------------- -------------------
 * -------------------- --- -------------- -------------- -------------------
 *   21   20   19    18  17   16   15   14   13   12   11    9    6    3    0
 * ___W ___E ___S ___N _RAM __BW __CY __SM ___C __EW __NS RAMI __CI _EWI _NSI
 * ------------------- ---- -------------- -------------- ---- ---- ---- ----
 *                   4    1              3              3    2    3    3    3
 * ------------------------ ----------------------------- -------------------
 *                        5                             6                  11
 * --------------------------------------------------------------------------
 *                                                                         22
 *
 */

/* Instructions group */
#define GAPP_NSI_SIZE 3
#define GAPP_EWI_SIZE 3
#define GAPP_CI_SIZE 3
#define GAPP_RAMI_SIZE 2

/* Registers group */
/* general and alu input */
#define GAPP_NS_SIZE 1
#define GAPP_EW_SIZE 1
#define GAPP_C_SIZE 1
/* alu output */
#define GAPP_SM_SIZE 1
#define GAPP_CY_SIZE 1
#define GAPP_BW_SIZE 1

/* External bits group */
/* implement ram as neighboorood bit */
#define GAPP_RAM_SIZE 1
/* NS axe */
#define GAPP_N_SIZE 1
#define GAPP_S_SIZE 1
#define GAPP_NOS_SIZE 1
/* EW axe */
#define GAPP_E_SIZE 1
#define GAPP_W_SIZE 1
#define GAPP_EOW_SIZE 1

enum {
  GAPP_NSI, GAPP_EWI, GAPP_CI, GAPP_RAMI, /* instruction */
  GAPP_NS, GAPP_EW, GAPP_C,	/* registers */
  GAPP_SM, GAPP_CY, GAPP_BW,	/* alu output registers */
  GAPP_RAM,			/* external i/o */
  GAPP_N, GAPP_S, GAPP_E, GAPP_W, /* external inputs */
  GAPP_INPUTS
};

static int Gapp_input_sizes[] = {
  GAPP_NSI_SIZE, GAPP_EWI_SIZE, GAPP_CI_SIZE, GAPP_RAMI_SIZE,
  GAPP_NS_SIZE, GAPP_EW_SIZE, GAPP_C_SIZE,
  GAPP_SM_SIZE, GAPP_CY_SIZE, GAPP_BW_SIZE,
  GAPP_RAM_SIZE,
  GAPP_N_SIZE, GAPP_S_SIZE, GAPP_E_SIZE, GAPP_W_SIZE
};

static char* Gapp_input_names[] = {
  "NSI", "EWI", "CI", "RAMI",
  "NS", "EW", "C",
  "SM", "CY", "BW",
  "RAM",
  "N", "S", "E", "W"
};

enum {
  GAPP_NNS, GAPP_NEW, GAPP_NC,	/* registers */
  GAPP_NSM, GAPP_NCY, GAPP_NBW,	/* alu output registers */
  GAPP_NRAM,			/* external outputs */
  GAPP_OUTPUTS
};

static int Gapp_output_sizes[] = {
  GAPP_NS_SIZE, GAPP_EW_SIZE, GAPP_C_SIZE,
  GAPP_SM_SIZE, GAPP_CY_SIZE, GAPP_BW_SIZE,
  GAPP_RAM_SIZE
};

static char* Gapp_output_names[] = {
  "NNS", "NEW", "NC",
  "NSM", "NCY", "NBW",
  "NRAM",
};

#define GAPP_INS_SIZE (GAPP_NSI_SIZE + GAPP_EWI_SIZE + GAPP_CI_SIZE + GAPP_RAMI_SIZE)
#define GAPP_IREG_SIZE (GAPP_NS_SIZE + GAPP_EW_SIZE + GAPP_C_SIZE)
#define GAPP_OREG_SIZE (GAPP_SM_SIZE + GAPP_CY_SIZE + GAPP_BW_SIZE) 
#define GAPP_REG_SIZE (GAPP_IREG_SIZE + GAPP_OREG_SIZE)
#define GAPP_EXT_SIZE (GAPP_RAM_SIZE + GAPP_N_SIZE + GAPP_S_SIZE + GAPP_E_SIZE + GAPP_W_SIZE)

enum { GAPP_INS, GAPP_REG, GAPP_EXT, GAPP_IPARTS };

static int Gapp_iparts_sizes[] = {
  GAPP_INS_SIZE, GAPP_REG_SIZE, GAPP_EXT_SIZE, GAPP_IPARTS
};

static char* Gapp_iparts_names[] = { "INS", "REG", "EXT" };

/*
 * ALU
 */

static int Gapp_alu[] = {	/* SM CY BW */
  0,				/* 0  0  0 */
  5,				/* 1  0  1 */
  4,				/* 1  0  0 */
  2,				/* 0  1  0 */
  5,				/* 1  0  1 */
  3,				/* 0  1  1 */
  2,				/* 0  1  0 */
  7				/* 1  1  1 */
};

/*
 * BIT FIELDS
 */

typedef struct {
  int cnt;
  int size;
  char* prefix;
  struct {
    int pos;
    int size;
    int mask;
    char* name;
  }* fields;
  int* explode;
  int implode;
} Bit_Field;

Bit_Field* Bit_Field_new(Bit_Field* zis, char* prefix, char** names, int* sizes, int cnt) {
  int i, pos;

  if (!zis) {
    zis = (Bit_Field*)malloc(sizeof(Bit_Field));
    assert(zis);
  }
  zis->prefix = prefix;
  zis->cnt = cnt;
  zis->fields = (typeof(zis->fields))malloc(sizeof(*zis->fields) * cnt);
  zis->explode = (int*)malloc(sizeof(int*) * cnt);
  
  zis->size = pos = 0;
  for (i = 0; i < zis->cnt; ++i) {
    zis->fields[i].pos = pos;
    zis->fields[i].size = sizes[i];
    zis->fields[i].mask = ((1 << sizes[i]) - 1) << pos;
    zis->fields[i].name = names[i];
    pos += sizes[i];
    zis->size += sizes[i];
  }
  return zis;
}

inline int* Bit_Field_explode(Bit_Field* zis, int implode) {
  int i;

  zis->implode = implode;
  for (i = 0; i < zis->cnt; ++i) {
    zis->explode[i] = (zis->implode & zis->fields[i].mask) >> zis->fields[i].pos;
  }
  return zis->explode;
}

inline int Bit_Field_implode(Bit_Field* zis) {
  int i;
  
  zis->implode = 0;
  for (i = 0; i < zis->cnt; ++i) {
    zis->implode |= zis->explode[i] << zis->fields[i].pos;
  }
  return zis->implode;
}

void Bit_Field_mk_include(Bit_Field* zis, FILE* fp) {
  int i;

  for (i = 0; i < zis->cnt; ++i) {
    fprintf(fp, "#define %s_%s_POS %d\n",
	    zis->prefix, zis->fields[i].name, zis->fields[i].pos);
    fprintf(fp, "#define %s_%s_SIZE %d\n",
	    zis->prefix, zis->fields[i].name, zis->fields[i].size);
    fprintf(fp, "#define %s_%s_MASK 0%o\n",
	    zis->prefix, zis->fields[i].name, zis->fields[i].mask);
  }
}

/*
 * GAPP PE
 */

typedef struct {
  Bit_Field input;
  Bit_Field output;
  Bit_Field iparts;
  int* alu;
  int size;
  unsigned char* pe_tab;
/* void (**ctl_tab)(Gappsim*); */
  char** ctl_tab;
} Gapp;

void Gapp_mk_pe_table(Gapp* zis) {
  int i;

  for (i = 0; i < zis->size; ++i) {
    zis->pe_tab[i] = Gapp_next_state(zis, i);
    if ((i & (1 << 20) - 1) == 0 ) {
      fprintf(stderr, "%d ", i >> 20);
    }
  }
  fprintf(stderr, "\n");
}

/*
   for r in 0 i o; do for w in 0 1; do for e in 0 1; do for s in 0 1; do for n in 0 1; do
   if [ $n = "1" -a $s = "1" ]; then echo -n "0, "; continue; fi;
   if [ $e = "1" -a $w = "1" ]; then echo -n "0, "; continue; fi;
   echo "Gappsim_Run_r${r}_w${w}_e${e}_s${s}_n${n},"; done; done; done; done; done;
*/
/* static void (*gapp_ctl[])(Gappsim*) = { */
static char* gapp_ctl[] = {
  "Gappsim_Run_r0_w0_e0_s0_n0",
  "Gappsim_Run_r0_w0_e0_s0_n1",
  "Gappsim_Run_r0_w0_e0_s1_n0",
  0, "Gappsim_Run_r0_w0_e1_s0_n0",
  "Gappsim_Run_r0_w0_e1_s0_n1",
  "Gappsim_Run_r0_w0_e1_s1_n0",
  0, "Gappsim_Run_r0_w1_e0_s0_n0",
  "Gappsim_Run_r0_w1_e0_s0_n1",
  "Gappsim_Run_r0_w1_e0_s1_n0",
  0, 0, 0, 0, 0, "Gappsim_Run_ri_w0_e0_s0_n0",
  "Gappsim_Run_ri_w0_e0_s0_n1",
  "Gappsim_Run_ri_w0_e0_s1_n0",
  0, "Gappsim_Run_ri_w0_e1_s0_n0",
  "Gappsim_Run_ri_w0_e1_s0_n1",
  "Gappsim_Run_ri_w0_e1_s1_n0",
  0, "Gappsim_Run_ri_w1_e0_s0_n0",
  "Gappsim_Run_ri_w1_e0_s0_n1",
  "Gappsim_Run_ri_w1_e0_s1_n0",
  0, 0, 0, 0, 0, "Gappsim_Run_ro_w0_e0_s0_n0",
  "Gappsim_Run_ro_w0_e0_s0_n1",
  "Gappsim_Run_ro_w0_e0_s1_n0",
  0, "Gappsim_Run_ro_w0_e1_s0_n0",
  "Gappsim_Run_ro_w0_e1_s0_n1",
  "Gappsim_Run_ro_w0_e1_s1_n0",
  0, "Gappsim_Run_ro_w1_e0_s0_n0",
  "Gappsim_Run_ro_w1_e0_s0_n1",
  "Gappsim_Run_ro_w1_e0_s1_n0",
  0, 0, 0, 0, 0
};

static int gapp_nsi[] = { 0, 16, 1, 2, 0, 0, 0 };
static int gapp_ewi[] = { 0, 16, 4, 8, 0, 0, 0 };
static int gapp_ci[] = { 0, 16, 0, 0, 0, 0, 0, 0 };
static int gapp_rami[] = { 0, 32, 0, 0 };

static char* gapp_nsi_names[] = {
 0, "ns=ram", "ns=n", "ns=s", "ns=ew", "ns=c", "ns=0", "ns=??"
};

static char* gapp_ewi_names[] = {
 0, "ew=ram", "ew=e", "ew=w", "ew=ns", "ew=c", "ew=0", "ew=??"
};

static char* gapp_ci_names[] = {
 0, "c=ram", "c=ns", "c=ew", "c=cy", "c=bw", "c=0", "c=1"
};

static char* gapp_rami_names[] = {
 0, "ram=cm", "ram=c", "ram=sm"
};

/*
 * warning
 * add a intruction bitfield to use instead of input
 */
void Gapp_mk_ctl_table(Gapp* zis) {
  int i, size;
  int insi, iewi, ici, irami;
  int nsi, ewi, ci, rami;
  
  size = 1 << GAPP_INS_SIZE;
  for (i = 0; i < size; ++i) {
    Bit_Field_explode(&zis->input, i);
    insi = zis->input.explode[GAPP_NSI];
    iewi = zis->input.explode[GAPP_EWI];
    ici = zis->input.explode[GAPP_CI];
    irami = zis->input.explode[GAPP_RAMI];
    if (insi == 7 || iewi == 7) {
      zis->ctl_tab[i] = "undefined";
    } else {
      nsi = gapp_nsi[insi];
      ewi =  gapp_ewi[iewi];
      ci = gapp_ci[ici];
      rami = gapp_rami[irami];

      if (nsi + ewi + ci >= 32 || nsi + ewi + ci + rami >= 48) {
	zis->ctl_tab[i] = "illegal";
      } else {
	zis->ctl_tab[i] = gapp_ctl[nsi + ewi + ci + rami];
      }
    }
    assert(zis->ctl_tab[i]);
  }
}

void Gapp_print_ctl_table(Gapp* zis) {
  int i, size, flag;
  char* nsi; char* ewi; char* ci; char* rami;

  size = 1 << GAPP_INS_SIZE;
  for (i = 0; i < size; ++i) {
    Bit_Field_explode(&zis->input, i);
    nsi = gapp_nsi_names[zis->input.explode[GAPP_NSI]];
    ewi = gapp_ewi_names[zis->input.explode[GAPP_EWI]];
    ci = gapp_ci_names[zis->input.explode[GAPP_CI]];
    rami = gapp_rami_names[zis->input.explode[GAPP_RAMI]];
    flag = 0;
    if (0) {
      if (nsi) { fprintf(stderr, "%s", nsi); ++flag; }
      if (ewi) { fprintf(stderr, "%s%s", flag ? "; " : "", ewi); ++flag; }
      if (ci) { fprintf(stderr, "%s%s", flag ? "; " : "", ci); ++flag; }
      if (rami) { fprintf(stderr, "%s%s", flag ? "; " : "", rami); ++flag; }
    } else {
      if (nsi) {
	fprintf(stderr, "%s", nsi);
	++flag;
      } else {
	fprintf(stderr, "\t");
      }
      if (ewi) {
	fprintf(stderr, "%s%s", flag ? ";\t" : "", ewi);
	++flag;
      } else {
	fprintf(stderr, "\t");
      }
      if (ci) {
	fprintf(stderr, "%s%s", flag ? ";\t" : "", ci);
	++flag;
      } else {
	fprintf(stderr, "\t");
      }
      if (rami) {
	fprintf(stderr, "%s%s", flag ? ";\t" : "", rami);
	++flag;
      } else {
	fprintf(stderr, "\t");
      }
    }
    fprintf(stderr, "\t%s\n", zis->ctl_tab[i]);
  }
}

Gapp* Gapp_new(Gapp* zis) {
  int maptab, fd, n;

  maptab = 0;
  if (!zis) {
    zis = (Gapp*)malloc(sizeof(Gapp));
    assert(zis);
  }
  Bit_Field_new(&zis->input, "GAPP", Gapp_input_names, Gapp_input_sizes, GAPP_INPUTS);
  Bit_Field_new(&zis->output,"GAPP", Gapp_output_names,  Gapp_output_sizes, GAPP_OUTPUTS);
  Bit_Field_new(&zis->iparts, "GAPP", Gapp_iparts_names, Gapp_iparts_sizes, GAPP_IPARTS);
  zis->alu = Gapp_alu;
  zis->size = 1 << zis->input.size;
  if (!maptab) {
    zis->pe_tab = malloc(zis->size);
  }
  assert(zis->pe_tab);
  fd = open("gapp.t", 0);
  if (fd == -1) {
    Gapp_mk_pe_table(zis);
    fd = creat("gapp.t", 0666);
    assert(fd);
    n = write(fd, zis->pe_tab, zis->size);
    assert(n == zis->size);
    close(fd);
  } else if (maptab) {
    zis->pe_tab = mmap(0, zis->size, PROT_READ, /* MAP_FILE */ 0, fd, 0);
    assert(zis->pe_tab != (unsigned char*)-1);
  } else {
    n = read(fd, zis->pe_tab, zis->size);
    assert(n == zis->size);
  }
/*  zis->ctl_tab = (typeof(*zis->ctl_tab))malloc(sizeof(typeof(*zis->ctl_tab))
					       * (1 << zis->iparts.fields[GAPP_INS].size)); */
  zis->ctl_tab = (char**)malloc(sizeof(char**) * (1 << GAPP_INS_SIZE));

  assert(zis->ctl_tab);
  Gapp_mk_ctl_table(zis);
  return zis;
}

inline void gapp_pe(int* a, int* i, int* o) {
  int nst[] = { i[GAPP_NS], i[GAPP_RAM], i[GAPP_N], i[GAPP_S], i[GAPP_EW], i[GAPP_C], 0 };
  int ewt[] = { i[GAPP_EW], i[GAPP_RAM], i[GAPP_E], i[GAPP_W], i[GAPP_NS], i[GAPP_C], 0 };
  int ct[] = { i[GAPP_C], i[GAPP_RAM], i[GAPP_NS], i[GAPP_EW], i[GAPP_CY], i[GAPP_BW], 0, 1 };
  int ramt[] = { i[GAPP_RAM], 0, i[GAPP_C], i[GAPP_SM] };
  int tmp = a[(i[GAPP_NS] << 2) | (i[GAPP_EW] << 1) | i[GAPP_C]];

  o[GAPP_NNS] = nst[i[GAPP_NSI]];
  o[GAPP_NEW] = ewt[i[GAPP_EWI]];
  o[GAPP_NC] = ct[i[GAPP_CI]];
  o[GAPP_NRAM] = ramt[i[GAPP_RAMI]];

  o[GAPP_NSM] = !!(tmp & 4);
  o[GAPP_NCY] = !!(tmp & 2);
  o[GAPP_NBW] = tmp & 1;
}

inline int Gapp_next_state(Gapp* zis, int input) {
  Bit_Field_explode(&zis->input, input);
  gapp_pe(zis->alu, zis->input.explode, zis->output.explode);
  return Bit_Field_implode(&zis->output);
}

/*
 * CAPP SIM
 */

typedef struct {
  int* north;
  int* south;
  int* east;
  int* west;
} Neighboor_VN;

typedef struct {
  int side;
  int size;
  Neighboor_VN first;
  Neighboor_VN mid;
  Neighboor_VN last;
} Neighboor_Offset;

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
  zis->first.west[0] = side;
  for (i = 1; i < side; ++i) {
    zis->first.west[i] = i - 1;
  }
  zis->mid.west = zis->last.west = zis->first.west;

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

typedef struct {
  Gapp gapp;
  int gen;
  Neighboor_Offset* neighboor_offset;
  Neighboor_Offset torus;
  unsigned char* past;
  unsigned char* futur;
  unsigned char* tmp;
  unsigned int* memory;
  unsigned char* plane;
  int side;
  int size;
} Gappsim;

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

void Gappsim_trace(Gappsim* zis, int input, int output, unsigned char* futur) {
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
	    "  ___W ___E ___S ___N _RAM __BW __CY __SM ___C __EW __NS RAMI __CI _EWI _NSI (%d times, gen %d, x %d y %d)\n",
	    cnt, zis->gen, (futur - zis->futur) / zis->side, (futur - zis->futur) % zis->side);
    fprintf(stderr,
	    "I %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d (%d)\n",
	    i[GAPP_W], i[GAPP_E], i[GAPP_S], i[GAPP_N], i[GAPP_RAM], i[GAPP_BW], i[GAPP_CY], i[GAPP_SM], i[GAPP_C], i[GAPP_EW], i[GAPP_NS],
	    i[GAPP_RAMI], i[GAPP_CI], i[GAPP_EWI], i[GAPP_NSI], oinput);
    Bit_Field_explode(&zis->gapp.output, ooutput);
    o = zis->gapp.output.explode;
    fprintf(stderr, "O                     %4d %4d %4d %4d %4d %4d %4d                     (%d)\n",
	    o[GAPP_NRAM], o[GAPP_NBW], o[GAPP_NCY], o[GAPP_NSM], o[GAPP_NC], o[GAPP_NEW], o[GAPP_NNS], ooutput);
    oinput = input;
    ooutput = output;
    cnt = 1;
  }
}

inline int get_ram(int* memory, int address) {
  return !!(memory[address >> 2] & (1 << (address & 31)));
}

inline void set_ram(int* memory, int address, int value) {
  *memory = value ?
    (memory[address >> 2] | (1 << (address & 31)))
      :(memory[address >> 2] & ~(1 << (address & 31)));
}

#define get_neighboors() \
  (!!(neighboors & 1024) | ((!!(neighboors & 64)) << 1) | \
    ((!!(neighboors & 8)) << 2) | ((!!(neighboors & 32768)) << 3))

#define GAPP_TRANSITION \
  index = instruction | ((local & 63) << 11) | (get_ram(memory, address) << 17) | (get_neighboors() << 18); \
  newstate = zis->gapp.pe_tab[index]; \
  Gappsim_trace(zis, index, newstate, futur); \
  set_ram(memory, address, !!(index & 0x20000)); \
  memory += 4;

#define GAPP_LINE \
  local = *center; \
  neighboors = (north[zis->side - 1] & 3) << 16 | (center[zis->side - 1] & 3) << 14 | (south[zis->side - 1] & 3) << 12; \
  neighboors |= (*north++ & 3) << 10 | (*center++ & 3) << 8 | (*south++ & 3) << 6; \
  neighboors |= (*north++ & 3) << 4 | (*center++ & 3) << 2 | (*south++ & 3); \
  GAPP_TRANSITION; \
  *futur++ = newstate; \
  for (i = count; i--;) { \
    local = *center; \
    neighboors = (neighboors << 6) & 0x0003ffff | (*north++ & 3) << 4 | (*center++ & 3) << 2 | (*south++ & 3); \
    GAPP_TRANSITION; \
    *futur++ = newstate; \
  } \
  local = *center; \
  neighboors = (neighboors << 6) & 0x0003ffff | (north[-zis->side] & 3) << 4 | (center[-zis->side] & 3) << 2 | (south[-zis->side] & 3); \
  GAPP_TRANSITION; \
  *futur++ = newstate;

Gappsim_run(Gappsim* zis, int instruction, int address) {
  unsigned char* tmp;
  int count, i, j;
  unsigned char* futur;
  int *memory;
  unsigned char* north;
  unsigned char* center;
  unsigned char* south;
  int local, neighboors, index, newstate;

  futur = zis->futur;
  memory = zis->memory;
  count = zis->side - 2;

  north = zis->past + zis->size - zis->side;
  center = zis->past;
  south = center + zis->side;
  GAPP_LINE;
  north = zis->past;
  center = north + zis->side;
  south = center + zis->side;
  for (j = count; j--;) {
    GAPP_LINE;
  }
  north = zis->past + zis->size - (zis->side << 1);
  center = north + zis->side;
  south = zis->past;
  GAPP_LINE;

  tmp = zis->past; zis->past = zis->futur; zis->futur = tmp;
  ++zis->gen;
}

void Gappsim_run_internal(Gappsim* zis, int instruction) {
  unsigned char* p;
  unsigned char* t;
  int n, i;

  p = zis->past;
  n = zis->size >> 3;
  t = zis->gapp.pe_tab;
  for (i = 0; i < n;) {
    p[i] = t[instruction | (p[i++] << GAPP_REG_POS)];
    p[i] = t[instruction | (p[i++] << GAPP_REG_POS)];
    p[i] = t[instruction | (p[i++] << GAPP_REG_POS)];
    p[i] = t[instruction | (p[i++] << GAPP_REG_POS)];
    p[i] = t[instruction | (p[i++] << GAPP_REG_POS)];
    p[i] = t[instruction | (p[i++] << GAPP_REG_POS)];
    p[i] = t[instruction | (p[i++] << GAPP_REG_POS)];
    p[i] = t[instruction | (p[i++] << GAPP_REG_POS)];
  }
}

void Gappsim_run_i_n(Gappsim* zis, int op) {
  unsigned char* p;
  unsigned char* f;
  unsigned char* t;
  int n, m, i, j;
  int* d;

  p = zis->past; f = zis->futur;
  t = zis->gapp.pe_tab;
  d = zis->neighboor_offset->first.north;
  n = zis->side;
  for (i = 0; i < n; ++i) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((p[d[i]] & GAPP_N_MASK) << GAPP_N_POS)];
  }
  d = zis->neighboor_offset->mid.north;
  m = zis->side - 2;
  for (j = 0; j < m; ++j) {
    p += n;
    for (i = 0; i < n; ++i) {
      f[i] = t[op | (p[i] << GAPP_REG_POS) | ((p[d[i]] & GAPP_N_MASK) << GAPP_N_POS)];
    }
  }
  d = zis->neighboor_offset->last.north;
  for (i = 0; i < n; ++i) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((p[d[i]] & GAPP_N_MASK) << GAPP_N_POS)];
  }
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->gen;
}

#define NS_RAM 1
#define NS_N 2
#define NS_S 3
#define NS_EW 4
#define NS_C 5
#define NS_0 6

#define EW_RAM (1 << 3)
#define EW_E (2 << 3)
#define EW_W (3 << 3)
#define EW_NS (4 << 3)
#define EW_C (5 << 3)
#define EW_0 (6 << 3)

#define C_RAM (1 << 6)
#define C_NS (2 << 6)
#define C_EW (3 << 6)
#define C_CY (4 << 6)
#define C_BW (5 << 6)
#define C_0 (6 << 6)
#define C_1 (7 << 6)

#define RAM_C (2 << 9)
#define RAM_SM (3 << 9)

#define RA(I, A) Gappsim_run(gappsim, I, A)
#define R(I) Gappsim_run(gappsim, I, 0)
#define E(P) Gappsim_extract(gappsim, P); write(1, gappsim->plane, gappsim->size >> 3)
#define S() if (0) { fprintf(stderr, "? "); getchar(); }

int main(int ac, char** av) {
  Gappsim* gappsim;
  int cnt;
  int lside;
  int side;
  int plane;

  cnt = 100;
  lside = 3;
  plane = 1;

  side = 1 << lside;
  gappsim = Gappsim_new(0, side);
  if (0) {
    Neighboor_Offset_print(gappsim->neighboor_offset);
  }
  if (1) {
    FILE* fp;

    fp = fopen("gappfields.h", "w");
    assert(fp);
    fprintf(fp, "%s%s generated defs, dont edit %s%s\n", "/", "*", "*", "/");
    Bit_Field_mk_include(&gappsim->gapp.iparts, fp);
    Bit_Field_mk_include(&gappsim->gapp.input, fp);
    Bit_Field_mk_include(&gappsim->gapp.output, fp);
    close(fp);
  }
  if (1) {
    Gapp_print_ctl_table(&gappsim->gapp);
  }
  return 0;
  if (1) {
    int i = ((side >> 1) << lside) + (side >> 1);
    gappsim->past[i] = 3;
    fprintf(stderr, "%d %d\n", i / side, i % side);
  } else if (0) {
    *gappsim->past = 1;
  } else {
    randomize(gappsim->past, gappsim->size);
  }

  E(0); S();
  while(cnt > 0) {
    if (0) {
      R(NS_N); E(1); S();
    }
    if (1) {
      R(EW_W); E(0); S();
    }
    if (0) {
      R(EW_NS); S();
      R(NS_EW); S();
    }
    if (1) {
      cnt -= 1;
    }
  }
  return 0;
}

randomize(unsigned char* p, int size) {
  srand48(time(0) & getpid());
  while (--size) {
    *p++ = (lrand48() >> 16) & 1;
  }
}

rextract0(unsigned char* itab, unsigned char* otab, int size) {
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

rextract1(unsigned char* itab, unsigned char* otab, int size) {
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

rextract2(unsigned char* itab, unsigned char* otab, int size) {
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

rextract3(unsigned char* itab, unsigned char* otab, int size) {
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

rextract4(unsigned char* itab, unsigned char* otab, int size) {
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

rextract5(unsigned char* itab, unsigned char* otab, int size) {
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

rextract6(unsigned char* itab, unsigned char* otab, int size) {
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

rextract7(unsigned char* itab, unsigned char* otab, int size) {
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

int (*textract[])(unsigned char*, unsigned char*, int) = {
    rextract0,
    rextract1,
    rextract2,
    rextract3,
    rextract4,
    rextract5,
    rextract6,
    rextract7,
};

#if 0
void gapp_pe(
     /* alu */
     int* alu,
     /* in */
     int cmi, int nsi, int ewi, int ci, int rami, /* 13 */
     int cm, int ns, int ew, int c, /* 4 */
     int sm, int cy, int bw, /* 3 */
     int cms, int n, int s, int e, int w, int ram, /* 6 */
     /* out */
     int* ncm, int* nns, int* new, int* nc, /* 4 */
     int* nsm, int* ncy, int* nbw, /* 3 */
     int* nram /* 1 */
     ) {

  int cmt[] = { cm, ram, cms, 0 };
  int nst[] = { ns, ram, n, s, ew, c, 0 };
  int ewt[] = { ew, ram, e, w, ns, c, 0 };
  int ct[] = { c, ram, ns, ew, cy, bw, 0, 1 };
  int ramt[] = { ram, cm, c, sm };
  int tmp = alu[(ns << 2) | (ew << 1) | c];

  *ncm = cmt[cmi];
  *nns = nst[nsi];
  *new = ewt[ewi];
  *nc = ct[ci];
  *nram = ramt[rami];
	      
  *nsm = !!(tmp & 4);
  *ncy = !!(tmp & 2);
  *nbw = tmp & 1;
}
#endif
