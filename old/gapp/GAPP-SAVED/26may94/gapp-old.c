#include <sys/types.h>
#include <sys/mman.h>

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <getopt.h>

#include "gappfields.h"

/*
 * gapp context layout
 *
 * externals      internals                     instructions
 * -------------- ----------------------------- -------------------
 * ---------- --- -------------- -------------- -------------------
 *   19   18   17   16   15   14   13   12   11    9    6    3    0
 * _EOW _NOS _RAM __BW __CY __SM ___C __EW __NS RAMI __CI _EWI _NSI
 * --------- ---- -------------- -------------- ---- ---- ---- ----
 *         2    1              3              3    2    3    3    3
 * -------------- ----------------------------- -------------------
 *              3                             6                  11
 * ----------------------------------------------------------------
 *                                                               19
 *
 */

typedef struct {
  char* name;
  int size;
} Bit_Field_Spec;

static Bit_Field_Spec gapp_input_spec[] = {
  "NSI", 3, "EWI", 3, "CI", 3, "RAMI", 2, /* Instructions group */
				/* Registers group */
  "NS", 1, "EW", 1, "C", 1,	/* communication and alu input */
  "SM", 1, "CY", 1, "BW", 1,	/* alu output */
				/* External bits group */
  "RAM", 1,			/* implement ram as neighboorood bit */
  "NOS", 1, "EOW", 1,		/* NS and EW axe */
  0, 0
};

static Bit_Field_Spec gapp_output_spec[] = {
  "NNS", 1, "NEW", 1, "NC", 1,
  "NSM", 1, "NCY", 1, "NBW", 1,
  "NRAM", 1,
  0, 0
};

static Bit_Field_Spec gapp_instruction_spec[] = {
  "NSINS", 3, "EWINS", 3, "CINS", 3, "RAMINS", 2,
  0, 0
};

#define GAPP_IREG_SIZE (GAPP_NS_SIZE + GAPP_EW_SIZE + GAPP_C_SIZE)
#define GAPP_OREG_SIZE (GAPP_SM_SIZE + GAPP_CY_SIZE + GAPP_BW_SIZE) 

static Bit_Field_Spec gapp_iparts_spec[] = {
  "INS", GAPP_NSI_SIZE + GAPP_EWI_SIZE + GAPP_CI_SIZE + GAPP_RAMI_SIZE,
  "REG", GAPP_IREG_SIZE + GAPP_OREG_SIZE,
  "EXT", GAPP_RAM_SIZE + GAPP_NOS_SIZE + GAPP_EOW_SIZE,
  0, 0
};

/*
 * ALU
 */

static int gapp_alu[] = {	/* SM CY BW */
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

Bit_Field* Bit_Field_new(Bit_Field* zis, char* prefix, Bit_Field_Spec* spec) {
  int i, pos;

  if (!zis) {
    zis = (Bit_Field*)malloc(sizeof(Bit_Field));
    assert(zis);
  }
  memset(zis, 0, sizeof(Bit_Field));
  zis->prefix = prefix;
  for (i = 0; spec[i].name; ++i) {;}
  zis->cnt = i;
  zis->fields = (typeof(zis->fields))malloc(sizeof(*zis->fields) * zis->cnt);
  zis->explode = (int*)malloc(sizeof(int*) * zis->cnt);
  
  zis->size = pos = 0;
  for (i = 0; i < zis->cnt; ++i) {
    zis->fields[i].pos = pos;
    zis->fields[i].size = spec[i].size;
    zis->fields[i].mask = ((1 << spec[i].size) - 1) << pos;
    zis->fields[i].name = spec[i].name;
    pos += spec[i].size;
    zis->size += spec[i].size;
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
    fprintf(fp, "#define %s_%s %d\n", zis->prefix, zis->fields[i].name, i);
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
  Bit_Field instruction;
  Bit_Field iparts;
  int* alu;
  int size;
  unsigned char* pe_tab;
  void (**ctl_tab)();
  char** ctl_tab_names;
} Gapp;

void Gapp_mk_pe_table(Gapp* zis) {
  int i;

  for (i = 0; i < zis->size; ++i) {
    extern int verbose;

    zis->pe_tab[i] = Gapp_next_state(zis, i);
    if (verbose) {
      if ((i & (1 << 18) - 1) == 0 ) {
	fprintf(stderr, "%d ", i >> 20);
      }
    }
  }
  fprintf(stderr, "\n");
}

void Gapp_print_pe_table(Gapp* zis, FILE* fp) {
  int i, o;
  int *ti;
  int *to;
  
  if (1) {
    fprintf(fp, "_EOW _NOS _RAM __BW __CY __SM ___C __EW __NS RAMI __CI _EWI _NSI\n");
    fprintf(fp, "_RAM __BW __CY __SM ___C __EW __NS\n");
    fprintf(fp, "HVRBYMCHVRCHW RBYSCHW\n");
    fprintf(fp, "XARMCHVARM\n");
  }
  for (i = 0; i < zis->size; ++i) {
    o = zis->pe_tab[i];
    Bit_Field_explode(&zis->input, i);
    Bit_Field_explode(&zis->iparts, i);
    if ((int)zis->ctl_tab[zis->iparts.explode[GAPP_INS]] < 0) {
      continue;
    }
    Bit_Field_explode(&zis->output, o);
    ti = zis->input.explode;
    to = zis->output.explode;
    if (0) {
      fprintf(fp, "  _EOW _NOS _RAM __BW __CY __SM ___C __EW __NS RAMI __CI _EWI _NSI\n");
      fprintf(fp, "I %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d (%d)\n",
	      ti[GAPP_EOW], ti[GAPP_NOS], ti[GAPP_RAM],
	      ti[GAPP_BW], ti[GAPP_CY], ti[GAPP_SM],
	      ti[GAPP_C], ti[GAPP_EW], ti[GAPP_NS],
	      ti[GAPP_RAMI], ti[GAPP_CI], ti[GAPP_EWI], ti[GAPP_NSI], i);
      fprintf(fp, "O           %4d %4d %4d %4d %4d %4d %4d                     (%d)\n",
	      to[GAPP_NRAM], to[GAPP_NBW], to[GAPP_NCY], to[GAPP_NSM],
	      to[GAPP_NC], to[GAPP_NEW], to[GAPP_NNS], o);
    } else if (0) {
      fprintf(fp, "%d%d%d%d%d%d%d%d%d%d%d%d%d ",
	      ti[GAPP_EOW], ti[GAPP_NOS], ti[GAPP_RAM],
	      ti[GAPP_BW], ti[GAPP_CY], ti[GAPP_SM],
	      ti[GAPP_C], ti[GAPP_EW], ti[GAPP_NS],
	      ti[GAPP_RAMI], ti[GAPP_CI], ti[GAPP_EWI], ti[GAPP_NSI]);
      fprintf(fp, "%d%d%d%d%d%d%d\n",
	      to[GAPP_NRAM], to[GAPP_NBW], to[GAPP_NCY], to[GAPP_NSM],
	      to[GAPP_NC], to[GAPP_NEW], to[GAPP_NNS]);
    } else {
      fprintf(fp, "%d%d%d%d%d%d%d",
	      (ti[GAPP_EOW] << 1) | ti[GAPP_NOS],
	      (ti[GAPP_BW] << 2) | (ti[GAPP_CY] << 1) | ti[GAPP_SM],
	      (ti[GAPP_C] << 2) | (ti[GAPP_EW] << 1) | ti[GAPP_NS],
	      ti[GAPP_RAMI], ti[GAPP_CI], ti[GAPP_EWI], ti[GAPP_NSI]);
      fprintf(fp, "%d%d",
	      (to[GAPP_NBW] << 2) | (to[GAPP_NCY] << 1) | to[GAPP_NSM],
	      (to[GAPP_NC] << 2) | (to[GAPP_NEW] << 1) | to[GAPP_NNS]);
      fprintf(fp, "%d\n", (ti[GAPP_RAM] << 1) | to[GAPP_NRAM]);
    }
  }
}

/*
   for r in 0 i o; do for w in 0 1; do for e in 0 1; do for s in 0 1; do for n in 0 1; do
   if [ $n = "1" -a $s = "1" ]; then continue; fi;
   if [ $e = "1" -a $w = "1" ]; then continue; fi;
   echo "Gappsim_run_r${r}_w${w}_e${e}_s${s}_n${n}"; done; done; done; done; done;
*/

extern void Gappsim_run_r0_w0_e0_s0_n0();
extern void Gappsim_run_r0_w0_e0_s0_n1();
extern void Gappsim_run_r0_w0_e0_s1_n0();
extern void Gappsim_run_r0_w0_e1_s0_n0();
extern void Gappsim_run_r0_w0_e1_s0_n1();
extern void Gappsim_run_r0_w0_e1_s1_n0();
extern void Gappsim_run_r0_w1_e0_s0_n0();
extern void Gappsim_run_r0_w1_e0_s0_n1();
extern void Gappsim_run_r0_w1_e0_s1_n0();
extern void Gappsim_run_ri_w0_e0_s0_n0();
extern void Gappsim_run_ri_w0_e0_s0_n1();
extern void Gappsim_run_ri_w0_e0_s1_n0();
extern void Gappsim_run_ri_w0_e1_s0_n0();
extern void Gappsim_run_ri_w0_e1_s0_n1();
extern void Gappsim_run_ri_w0_e1_s1_n0();
extern void Gappsim_run_ri_w1_e0_s0_n0();
extern void Gappsim_run_ri_w1_e0_s0_n1();
extern void Gappsim_run_ri_w1_e0_s1_n0();
extern void Gappsim_run_ro_w0_e0_s0_n0();
extern void Gappsim_run_ro_w0_e0_s0_n1();
extern void Gappsim_run_ro_w0_e0_s1_n0();
extern void Gappsim_run_ro_w0_e1_s0_n0();
extern void Gappsim_run_ro_w0_e1_s0_n1();
extern void Gappsim_run_ro_w0_e1_s1_n0();
extern void Gappsim_run_ro_w1_e0_s0_n0();
extern void Gappsim_run_ro_w1_e0_s0_n1();
extern void Gappsim_run_ro_w1_e0_s1_n0();

/*
   for r in 0 i o; do for w in 0 1; do for e in 0 1; do for s in 0 1; do for n in 0 1; do
   if [ $n = "1" -a $s = "1" ]; then echo -n "{0, 0}, "; continue; fi;
   if [ $e = "1" -a $w = "1" ]; then echo -n "{0, 0}, "; continue; fi;
   echo "{\"r${r}_w${w}_e${e}_s${s}_n${n}\", Gappsim_run_r${r}_w${w}_e${e}_s${s}_n${n}},";
   done; done; done; done; done;
*/

typedef struct {
  char* name;
  void (*func)();
} Gapp_Ctl;

static Gapp_Ctl gapp_ctl[] = {
  {"r0_w0_e0_s0_n0", Gappsim_run_r0_w0_e0_s0_n0},
  {"r0_w0_e0_s0_n1", Gappsim_run_r0_w0_e0_s0_n1},
  {"r0_w0_e0_s1_n0", Gappsim_run_r0_w0_e0_s1_n0},
  {0, 0},{"r0_w0_e1_s0_n0", Gappsim_run_r0_w0_e1_s0_n0},
  {"r0_w0_e1_s0_n1", Gappsim_run_r0_w0_e1_s0_n1},
  {"r0_w0_e1_s1_n0", Gappsim_run_r0_w0_e1_s1_n0},
  {0, 0}, {"r0_w1_e0_s0_n0", Gappsim_run_r0_w1_e0_s0_n0},
  {"r0_w1_e0_s0_n1", Gappsim_run_r0_w1_e0_s0_n1},
  {"r0_w1_e0_s1_n0", Gappsim_run_r0_w1_e0_s1_n0},
  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
  {"ri_w0_e0_s0_n0", Gappsim_run_ri_w0_e0_s0_n0},
  {"ri_w0_e0_s0_n1", Gappsim_run_ri_w0_e0_s0_n1},
  {"ri_w0_e0_s1_n0", Gappsim_run_ri_w0_e0_s1_n0},
  {0, 0}, {"ri_w0_e1_s0_n0", Gappsim_run_ri_w0_e1_s0_n0},
  {"ri_w0_e1_s0_n1", Gappsim_run_ri_w0_e1_s0_n1},
  {"ri_w0_e1_s1_n0", Gappsim_run_ri_w0_e1_s1_n0},
  {0, 0}, {"ri_w1_e0_s0_n0", Gappsim_run_ri_w1_e0_s0_n0},
  {"ri_w1_e0_s0_n1", Gappsim_run_ri_w1_e0_s0_n1},
  {"ri_w1_e0_s1_n0", Gappsim_run_ri_w1_e0_s1_n0},
  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
  {"ro_w0_e0_s0_n0", Gappsim_run_ro_w0_e0_s0_n0},
  {"ro_w0_e0_s0_n1", Gappsim_run_ro_w0_e0_s0_n1},
  {"ro_w0_e0_s1_n0", Gappsim_run_ro_w0_e0_s1_n0},
  {0, 0}, {"ro_w0_e1_s0_n0", Gappsim_run_ro_w0_e1_s0_n0},
  {"ro_w0_e1_s0_n1", Gappsim_run_ro_w0_e1_s0_n1},
  {"ro_w0_e1_s1_n0", Gappsim_run_ro_w0_e1_s1_n0},
  {0, 0}, {"ro_w1_e0_s0_n0", Gappsim_run_ro_w1_e0_s0_n0},
  {"ro_w1_e0_s0_n1", Gappsim_run_ro_w1_e0_s0_n1},
  {"ro_w1_e0_s1_n0", Gappsim_run_ro_w1_e0_s1_n0},
  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
};

static int gapp_nsi[] = { 0, 16, 1, 2, 0, 0, 0 };
static int gapp_ewi[] = { 0, 16, 4, 8, 0, 0, 0 };
static int gapp_ci[] = { 0, 16, 0, 0, 0, 0, 0, 0 };
static int gapp_rami[] = { 0, 32, 0, 0 };

static char* gapp_nsi_names[] = {
  0, "ns:=ram", "ns:=n", "ns:=s", "ns:=ew", "ns:=c", "ns:=0", "ns:=??"
};

static char* gapp_ewi_names[] = {
  0, "ew:=ram", "ew:=e", "ew:=w", "ew:=ns", "ew:=c", "ew:=0", "ew:=??"
};

static char* gapp_ci_names[] = {
  0, "c:=ram", "c:=ns", "c:=ew", "c:=cy", "c:=bw", "c:=0", "c:=1"
};

static char* gapp_rami_names[] = {
  0, "ram:=cm", "ram:=c", "ram:=sm"
};

void Gapp_mk_ctl_table(Gapp* zis) {
  int i, size;
  int insi, iewi, ici, irami;
  int nsi, ewi, ci, rami;
  
  size = 1 << GAPP_INS_SIZE;
  for (i = 0; i < size; ++i) {
    Bit_Field_explode(&zis->instruction, i);
    insi = zis->instruction.explode[GAPP_NSINS];
    iewi = zis->instruction.explode[GAPP_EWINS];
    ici = zis->instruction.explode[GAPP_CINS];
    irami = zis->instruction.explode[GAPP_RAMINS];
    if (insi == 7 || iewi == 7) {
      zis->ctl_tab[i] = (void(*)())-1;
      zis->ctl_tab_names[i] = "undefined";
    } else {
      nsi = gapp_nsi[insi];
      ewi =  gapp_ewi[iewi];
      ci = gapp_ci[ici];
      rami = gapp_rami[irami];

      if (nsi + ewi + ci >= 32 || nsi + ewi + ci + rami >= 48) {
	zis->ctl_tab[i] = (void(*)())-2;
	zis->ctl_tab_names[i] = "illegal";
      } else {
	zis->ctl_tab[i] = gapp_ctl[nsi + ewi + ci + rami].func;
	zis->ctl_tab_names[i] = gapp_ctl[nsi + ewi + ci + rami].name;
      }
    }
    assert(zis->ctl_tab[i]);
  }
}

void Gapp_print_ctl_table(Gapp* zis, FILE* fp) {
  int i, size, flag;
  char* nsi; char* ewi; char* ci; char* rami;

  size = 1 << GAPP_INS_SIZE;
  for (i = 0; i < size; ++i) {
    Bit_Field_explode(&zis->instruction, i);
    nsi = gapp_nsi_names[zis->instruction.explode[GAPP_NSINS]];
    ewi = gapp_ewi_names[zis->instruction.explode[GAPP_EWINS]];
    ci = gapp_ci_names[zis->instruction.explode[GAPP_CINS]];
    rami = gapp_rami_names[zis->instruction.explode[GAPP_RAMINS]];
    flag = 0;
    if (0) {
      if (nsi) { fprintf(fp, "%s", nsi); ++flag; }
      if (ewi) { fprintf(fp, "%s%s", flag ? "; " : "", ewi); ++flag; }
      if (ci) { fprintf(fp, "%s%s", flag ? "; " : "", ci); ++flag; }
      if (rami) { fprintf(fp, "%s%s", flag ? "; " : "", rami); ++flag; }
    } else {
      if (nsi) { fprintf(fp, "%s\t", nsi); } else { fprintf(fp, "\t"); }
      if (ewi) { fprintf(fp, "%s\t", ewi); } else { fprintf(fp, "\t"); }
      if (ci) {	fprintf(fp, "%s\t", ci); } else { fprintf(fp, "\t"); }
      if (rami) { fprintf(fp, "%s\t", rami); } else { fprintf(fp, "\t"); }
    }
    fprintf(fp, "%s\n", zis->ctl_tab_names[i]);
  }
}

Gapp* Gapp_new(Gapp* zis) {
  int maptab, fd, n;

  maptab = 0;
  if (!zis) {
    zis = (Gapp*)malloc(sizeof(Gapp));
    assert(zis);
  }
  Bit_Field_new(&zis->input, "GAPP", gapp_input_spec);
  Bit_Field_new(&zis->output,"GAPP", gapp_output_spec);
  Bit_Field_new(&zis->instruction,"GAPP", gapp_instruction_spec);
  Bit_Field_new(&zis->iparts, "GAPP", gapp_iparts_spec);
  zis->alu = gapp_alu;
  zis->size = 1 << zis->input.size;
  if (!maptab) {
    zis->pe_tab = malloc(zis->size);
  }
  assert(zis->pe_tab);
  fd = open("gapp-pe.t", 0);
  if (fd == -1) {
    Gapp_mk_pe_table(zis);
    fd = creat("gapp-pe.t", 0666);
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
  zis->ctl_tab = (void(**)())malloc(sizeof(void(**)()) * (1 << GAPP_INS_SIZE));
  zis->ctl_tab_names = (char**)malloc(sizeof(char**) * (1 << GAPP_INS_SIZE));
  assert(zis->ctl_tab);
  Gapp_mk_ctl_table(zis);
  return zis;
}

inline void gapp_pe(int* a, int* i, int* o) {
  int nst[] = { i[GAPP_NS], i[GAPP_RAM], i[GAPP_NOS], i[GAPP_NOS], i[GAPP_EW], i[GAPP_C], 0 };
  int ewt[] = { i[GAPP_EW], i[GAPP_RAM], i[GAPP_EOW], i[GAPP_EOW], i[GAPP_NS], i[GAPP_C], 0 };
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
 * GAPP SIM
 */

typedef struct {
  int* north;
  int* south;
  int* east;
  int* west;
} Neighboor_VN;

typedef struct {
  int* first;
  int* mid;
  int* last;
} Neighboor_Lines;

typedef struct {
  int side;
  int size;
  Neighboor_VN first;
  Neighboor_VN mid;
  Neighboor_VN last;
  Neighboor_Lines north;
  Neighboor_Lines south;
  Neighboor_Lines east;
  Neighboor_Lines west;
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

typedef struct {
  Gapp gapp;
  int gen;
  Neighboor_Offset* neighboor_offset;
  Neighboor_Offset torus;
  int instruction;
  int address;
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

#if 0

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
#endif

/*
 * ACCESS MACROS
 *
 * op = zis->instruction;	current instruction
 * a = zis->address;		current address
 * p = zis->past;		past plane
 * f = zis->futur;		futur plane
 *				(not used if neighboors not acceded)
 * m = zis->memory		pe memory
 * t = zis->gapp.pe_tab;	transiton table
 * d = l-><first|mid|last>;	neighboor offset relative to current
 *				pe index
 * nsd = nsl-><first|mid|last>;	neighboor offset for ns axes
 *				if both axes used
 * ewd = ewl-><first|mid|last>;	neighboor offset for ew axes
 * i = <current pe>		current pe index
 * mask = <GAPP_NOS_MASK|GAPP_EOW_MASK>
 * pos = <GAPP_NOS_POS|GAPP_EOW_POS>
 *
 */

/*
 * COMMON ACCES MACROS
 */

/* pe state to index pos */
#define PE (p[i] << GAPP_REG_POS)

/* one neighboor access to index pos */
#define NE1 (!!(p[d[i]] & mask) << pos)

/* two neighboor access to index pos */
#define NE2 ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS) \
            | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))

/*
 * make ``m'' point to the correct byte bank offset
 * and ``a'' be the mask of addressed bit in the bank
 * this one is not realy an access macros
 * and is not use in the inner loop
 * but once for each run.
 */
#define LOAD_BANK m += a >> 2; a = 1 << (a & 31)

/* RAM to index pos */
#define LRAM (!!(*m & a) << GAPP_RAM_POS)

/* pe state with ram cleared
 * to allow ram loading */
#define PEC ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS)

/*
 * to store the ram value in pe state after pe update:
 * first clear the ram adressed
 * then set it to the value of pe ram bit
 */
#define SRAM *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;

/*
 * NO RAM ACCESS MACROS
 */

#define NR0 p[i] = t[op | PE]; ++i;
#define NR1 f[i] = t[op | PE | NE1]; ++i;
#define NR2 f[i] = t[op | PE | NE2]; ++i;

/*
 * LOAD RAM MACROS
 */

#define LR0 p[i] = t[op | PEC | LRAM]; ++i; m += 4;
#define LR1 f[i] = t[op | PEC | LRAM | NE1]; ++i; m += 4;
#define LR2 f[i] = t[op | PEC | LRAM | NE2]; ++i; m += 4;

/*
 * STORE RAM MACROS
 */

#define SR0 p[i] = t[op | PE]; SRAM; ++i; m+= 4;
#define SR1 f[i] = t[op | PE | NE1]; SRAM; ++i; m+= 4;
#define SR2 f[i] = t[op | PE | NE2]; SRAM; ++i; m+= 4;

/*
 * NO RAM ACCESS FUNCS
 */

/*
 * used by:
 *
 * r0_w0_e0_s0_n1
 * r0_w0_e0_s1_n0
 * r0_w0_e1_s0_n0
 * r0_w1_e0_s0_n0
 */

void Gappsim_run_r0_we1_or_sn1(Gappsim* zis,
			       Neighboor_Lines* l,
			       int mask, int pos) {
  unsigned char* p;
  unsigned char* f;
  unsigned char* t;
  int n, m, i, j;
  int op;
  int* d;

  op = zis->instruction;
  p = zis->past;
  f = zis->futur;
  t = zis->gapp.pe_tab;
  n = zis->side;
  d = l->first;
  for (i = 0; i < n;) {
    NR1; NR1; NR1; NR1;
    NR1; NR1; NR1; NR1;
  }
  d = l->mid;
  m = zis->side - 2;
  for (j = 0; j < m; ++j) {
    p += n;
    f += n;
    for (i = 0; i < n;) {
      NR1; NR1; NR1; NR1;
      NR1; NR1; NR1; NR1;
    }
  }
  d = l->last;
  p += n;
  f += n;
  for (i = 0; i < n;) {
    NR1; NR1; NR1; NR1;
    NR1; NR1; NR1; NR1;
  }
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->gen;
}

/*
 * used by:
 *
 * r0_w0_e1_s0_n1
 * r0_w1_e0_s0_n1
 * r0_w0_e1_s1_n0
 * r0_w1_e0_s1_n0
 */

void Gappsim_run_r0_we1_and_sn1(Gappsim* zis, Neighboor_Lines* nsl,
				Neighboor_Lines* ewl) {
  unsigned char* p;
  unsigned char* f;
  unsigned char* t;
  int n, m, i, j;
  int op;
  int* nsd;
  int* ewd;

  op = zis->instruction;
  p = zis->past;
  f = zis->futur;
  t = zis->gapp.pe_tab;
  n = zis->side;
  nsd = nsl->first;
  ewd = ewl->first;
  for (i = 0; i < n;) {
    NR2; NR2; NR2; NR2;
    NR2; NR2; NR2; NR2;
  }
  nsd = nsl->mid;
  ewd = ewl->mid;
  m = zis->side - 2;
  for (j = 0; j < m; ++j) {
    p += n;
    for (i = 0; i < n;) {
      NR2; NR2; NR2; NR2;
      NR2; NR2; NR2; NR2;
    }
  }
  nsd = nsl->last;
  ewd = ewl->last;
  for (i = 0; i < n;) {
    NR2; NR2; NR2; NR2;
    NR2; NR2; NR2; NR2;
  }
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->gen;
}

/*
 * NO RAM ACCESS ENTRY POINTS START HERE
 */

void Gappsim_run_r0_w0_e0_s0_n0(Gappsim* zis) {
  unsigned char* p;
  unsigned char* t;
  int op, n, i;

  op = zis->instruction;
  p = zis->past;
  n = zis->size;
  t = zis->gapp.pe_tab;
  for (i = 0; i < n;) {
    NR0; NR0; NR0; NR0;
    NR0; NR0; NR0; NR0;
  }
}

void Gappsim_run_r0_w0_e0_s0_n1(Gappsim* zis) {
  Gappsim_run_r0_we1_or_sn1(zis, &zis->neighboor_offset->north,
			    GAPP_NNS_MASK, GAPP_NOS_POS);
}

void Gappsim_run_r0_w0_e0_s1_n0(Gappsim* zis) {
  Gappsim_run_r0_we1_or_sn1(zis, &zis->neighboor_offset->south,
			    GAPP_NNS_MASK, GAPP_NOS_POS);
}

void Gappsim_run_r0_w0_e1_s0_n0(Gappsim* zis) {
  Gappsim_run_r0_we1_or_sn1(zis, &zis->neighboor_offset->east,
			    GAPP_NEW_MASK, GAPP_EOW_POS);
}

void Gappsim_run_r0_w1_e0_s0_n0(Gappsim* zis) {
  Gappsim_run_r0_we1_or_sn1(zis, &zis->neighboor_offset->west,
			    GAPP_NEW_MASK, GAPP_EOW_POS);
}

void Gappsim_run_r0_w0_e1_s0_n1(Gappsim* zis) {
  Gappsim_run_r0_we1_and_sn1(zis, &zis->neighboor_offset->north,
			     &zis->neighboor_offset->east);
}

void Gappsim_run_r0_w1_e0_s0_n1(Gappsim* zis) {
  Gappsim_run_r0_we1_and_sn1(zis, &zis->neighboor_offset->north,
			     &zis->neighboor_offset->west);
}

void Gappsim_run_r0_w0_e1_s1_n0(Gappsim* zis) {
  Gappsim_run_r0_we1_and_sn1(zis, &zis->neighboor_offset->south,
			     &zis->neighboor_offset->east);
}

void Gappsim_run_r0_w1_e0_s1_n0(Gappsim* zis) {
  Gappsim_run_r0_we1_and_sn1(zis, &zis->neighboor_offset->south,
			     &zis->neighboor_offset->west);
}

/*
 * LOAD RAM
 */

void Gappsim_run_ri_w0_e0_s0_n0(Gappsim* zis) {
  unsigned char* p;
  unsigned char* t;
  unsigned int* m;
  int op, a, n, i;

  op = zis->instruction;
  a = zis->address;
  p = zis->past;
  m = zis->memory;
  n = zis->size;
  t = zis->gapp.pe_tab;
  for (i = 0; i < n;) {
    LR0; LR0; LR0; LR0;
    LR0; LR0; LR0; LR0;
  }
}

void Gappsim_run_ri_w0_e0_s0_n1(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ri_w0_e0_s1_n0(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ri_w0_e1_s0_n0(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ri_w1_e0_s0_n0(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ri_w0_e1_s0_n1(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ri_w0_e1_s1_n0(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ri_w1_e0_s0_n1(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ri_w1_e0_s1_n0(Gappsim* zis) {
	assert(0);
}

/*
 * STORE RAM
 */

void Gappsim_run_ro_w0_e0_s0_n0(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ro_w0_e0_s0_n1(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ro_w0_e0_s1_n0(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ro_w0_e1_s0_n0(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ro_w1_e0_s0_n0(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ro_w0_e1_s0_n1(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ro_w1_e0_s0_n1(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ro_w0_e1_s1_n0(Gappsim* zis) {
	assert(0);
}

void Gappsim_run_ro_w1_e0_s1_n0(Gappsim* zis) {
	assert(0);
}

typedef struct {
  char* name;
  int help;
  int version;
  int copyright;
  int debug;
  int verbose;
  int include;
  int instlist;
  int table;
  int tablelist;
  int side;
  int cnt;
  int single;
} Gappsim_options;

static Gappsim_options gappsim_options;

void Gappsim_options_init(Gappsim_options* zis, char* name) {
  zis->name = name;
  zis->side = 7;
}

enum { OPT_SIDE = 'a', OPT_CNT };

static struct option long_options[] = {
  {"help", no_argument, &gappsim_options.help, 1},
  {"version", no_argument, &gappsim_options.version, 1},
  {"copyright", no_argument, &gappsim_options.copyright, 1},
  {"debug", no_argument, &gappsim_options.debug, 1},
  {"verbose", no_argument, &gappsim_options.verbose, 1},
  {"include", no_argument, &gappsim_options.include, 1},
  {"instlist", no_argument, &gappsim_options.instlist, 1},
  {"table", no_argument, &gappsim_options.table, 1},
  {"tablelist", no_argument, &gappsim_options.tablelist, 1},
  {"side", required_argument, NULL, OPT_SIDE},
  {"cnt", required_argument, NULL, OPT_CNT},
  {"single", no_argument, &gappsim_options.single, 1},
  0, 0, 0, 0
};

void Gappsim_options_help(Gappsim_options* zis, int flag) {
  if (flag) {
    fprintf (stderr, "Try `%s %s' for more information.\n",
	     zis->name, "--help");
  } else {
      printf ("\
Usage: %s [OPTION]\n", zis->name);
      printf ("\
      -help             display this help\n\
      -version          output version information\n\
      -copyright        display Copyright and copying conditions\n\
      -debug            toggle debug mode \n\
      -verbose          toggle verbose mode \n\
      -include          make ``gappfields.h''\n\
      -instlist         make ``gappinstlist.txt''\n\
      -table            force making of ``gapp-pe.t''\n\
      -tablelist        make ``gapp-pelist.txt''\n\
      -side=<int>       log(side) of the gapp pe plane, default do 7\n\
      -cnt=<int>        number of times to iterate gapp prog\n\
      -single           put a single 1 to center of plane\n\
                        (default is to randomize plane)\n");
    }
}

void Gappsim_options_version(Gappsim_options* zis) {
  fprintf(stderr, "!@#\n");
}

void Gappsim_options_copyright(Gappsim_options* zis) {
  fprintf(stderr, "!@#\n");
}

void Gappsim_options_check(Gappsim_options* zis) {
  assert(zis->side >= 2 && zis->side <= 10);
  if (zis->verbose) {
    extern int verbose;

    verbose = 1;
  }
}

int verbose;

int main(int ac, char** av) {
  extern int optind;		/* index of argument */
  int option_char;		/* option character */
  Gappsim_options* options;
  Gappsim* gappsim;

  options = &gappsim_options;
  Gappsim_options_init(options, av[0]);
  while (option_char = getopt_long_only(ac, av, "dvilts:S:c:p:", long_options, NULL),
	 option_char != EOF) {
    switch (option_char) {
    default:
      Gappsim_options_help(options, 1);
      return 1;
    case '\0':
      break;
    case OPT_SIDE:
      options->side = atoi(optarg);
      break;
    case OPT_CNT:
      options->cnt = atoi(optarg);
    }
  }
  if (options->help) {
    Gappsim_options_help(options, 0);
    return 0;
  }
  if (options->version) {
    Gappsim_options_version(options);
    return 0;
  }
  if (options->copyright) {
    Gappsim_options_copyright(options);
    return 0;
  }
  if (optind < ac) {
    fprintf(stderr, "non-option ARGV-elements: ");
    while (optind < ac) {
      fprintf(stderr, "%s ", av[optind++]);
    }
    fprintf(stderr, "\n");
    return 1;
  }
  Gappsim_options_check(options);
  if (options->table) {
    system("rm -f gapp-pe.t");
  }
  gappsim = Gappsim_new(0, 1 << options->side);
  if (options->debug) {
    Neighboor_Offset_print(gappsim->neighboor_offset);
  }
  if (options->include) {
    FILE* fp;

    system("mv gappfields.h gappfields.h.bak");
    fp = fopen("gappfields.h", "w");
    assert(fp);
    fprintf(fp, "%s%s generated defs, dont edit %s%s\n", "/", "*", "*", "/");
    Bit_Field_mk_include(&gappsim->gapp.input, fp);
    Bit_Field_mk_include(&gappsim->gapp.output, fp);
    Bit_Field_mk_include(&gappsim->gapp.instruction, fp);
    Bit_Field_mk_include(&gappsim->gapp.iparts, fp);
    close(fp);
  }
  if (options->instlist) {
    FILE* fp;

    fp = fopen("gappinstlist.txt", "w");
    assert(fp);
    Gapp_print_ctl_table(&gappsim->gapp, fp);
    close(fp);
  }
  if (options->tablelist) {
    FILE* fp;

    fp = fopen("gapp-pelist.txt", "w");
    assert(fp);
    Gapp_print_pe_table(&gappsim->gapp, fp);
    close(fp);
  }
  gapptst(gappsim, options);
  return 0;
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

#define RA(I, A) zis->address = A; R(I)
#define R(I) zis->instruction = I; zis->gapp.ctl_tab[I](zis)
#define E(P) Gappsim_extract(zis, P); write(1, zis->plane, zis->size >> 3)
#define S() if (0) { fprintf(stderr, "? "); getchar(); }

gapptst(Gappsim* zis, Gappsim_options* options) {
  int side;

  side = 1 << options->side;
  if (options->single) {
    int i = ((side >> 1) << options->side) + (side >> 1);
    zis->past[i] = 3;
    if (0) {
      fprintf(stderr, "%d %d\n", i / zis->side, i % zis->side);
    }
  } else {
    randomize(zis->past, zis->size);
  }

  E(0); S();
  while(options->cnt > 0) {
    if (1) {
      R(NS_N); E(0); S();
    }
    if (1) {
      R(EW_W); E(1); S();
    }
    if (0) {
      R(EW_NS); S();
      R(NS_EW); S();
    }
    if (1) {
      options->cnt -= 1;
    }
  }
}

randomize(unsigned char* p, int size) {
  srand48(time(0) & getpid());
  while (--size) {
    *p++ = (lrand48() >> 16) & 3;
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
