#include <sys/types.h>
#include <sys/mman.h>

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#include "bit-field.h"
#include "gapp-defs.h"
#include "gapp-arch.h"
#include "gapp-pe.h"

Gapp* Gapp_new(Gapp* zis) {
  int maptab, fd, n;

  maptab = 0;
  if (!zis) {
    zis = (Gapp*)malloc(sizeof(Gapp));
    assert(zis);
  }
  Bit_Field_new(&zis->input, "GAPP", gapp_pe_spec.input);
  Bit_Field_new(&zis->output,"GAPP", gapp_pe_spec.output);
  Bit_Field_new(&zis->instruction,"GAPP", gapp_pe_spec.instruction);
  Bit_Field_new(&zis->iparts, "GAPP", gapp_pe_spec.iparts);
  zis->alu = gapp_pe_spec.alu;
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

#if 0
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
#else
inline void gapp_pe(int* a, int* i, int* o) {
  int nst[] = { i[GAPP_NS], i[GAPP_RAM], i[GAPP_NOS], i[GAPP_NOS], i[GAPP_EW], i[GAPP_C], 0 };
  int ewt[] = { i[GAPP_EW], i[GAPP_RAM], i[GAPP_EOW], i[GAPP_EOW], i[GAPP_NS], i[GAPP_C], 0 };
  int ct[] = { i[GAPP_C], i[GAPP_RAM], i[GAPP_NS], i[GAPP_EW], i[GAPP_CY], i[GAPP_BW], 0, 1 };
  int ramt[] = { i[GAPP_RAM], 0, i[GAPP_C], i[GAPP_SM] };
  int tmp;

  o[GAPP_NNS] = nst[i[GAPP_NSI]];
  o[GAPP_NEW] = ewt[i[GAPP_EWI]];
  o[GAPP_NC] = ct[i[GAPP_CI]];
  o[GAPP_NRAM] = ramt[i[GAPP_RAMI]];

  tmp = a[(o[GAPP_NNS] << 2) | (o[GAPP_NEW] << 1) | o[GAPP_NC]];

  o[GAPP_NSM] = !!(tmp & 4);
  o[GAPP_NCY] = !!(tmp & 2);
  o[GAPP_NBW] = tmp & 1;
}
#endif

inline int Gapp_next_state(Gapp* zis, int input) {
  Bit_Field_explode(&zis->input, input);
  gapp_pe(zis->alu, zis->input.explode, zis->output.explode);
  return Bit_Field_implode(&zis->output);
}

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

  /* 0 - no RAM acces*/

  {"r0_w0_e0_s0_n0", Gappsim_run_r0_w0_e0_s0_n0}, /* 00 */
  {"r0_w0_e0_s0_n1", Gappsim_run_r0_w0_e0_s0_n1}, /* 01 - N */
  {"r0_w0_e0_s1_n0", Gappsim_run_r0_w0_e0_s1_n0}, /* 02 - S */
  {0, 0},			/* 03 */
  {"r0_w0_e1_s0_n0", Gappsim_run_r0_w0_e1_s0_n0}, /* 04 - E */
  {"r0_w0_e1_s0_n1", Gappsim_run_r0_w0_e1_s0_n1}, /* 05 - E + N */
  {"r0_w0_e1_s1_n0", Gappsim_run_r0_w0_e1_s1_n0}, /* 06 - E + S */
  {0, 0},			/* 07 */
  {"r0_w1_e0_s0_n0", Gappsim_run_r0_w1_e0_s0_n0}, /* 08 - W */
  {"r0_w1_e0_s0_n1", Gappsim_run_r0_w1_e0_s0_n1}, /* 09 - W + N */
  {"r0_w1_e0_s1_n0", Gappsim_run_r0_w1_e0_s1_n0}, /* 10 - W + S */
  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},

  /* 16 - load RAM */

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

  /* 32 - store RAM */

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
static int gapp_rami[] = { 0, 32, 32, 32 };

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

char* Gapp_instruction2ascii(Gapp* zis, int instruction) {
  char buf[64];
  char* nsi; char* ewi; char* ci; char* rami;

  Bit_Field_explode(&zis->instruction, instruction);
  nsi = gapp_nsi_names[zis->instruction.explode[GAPP_NSINS]];
  ewi = gapp_ewi_names[zis->instruction.explode[GAPP_EWINS]];
  ci = gapp_ci_names[zis->instruction.explode[GAPP_CINS]];
  rami = gapp_rami_names[zis->instruction.explode[GAPP_RAMINS]];
  *buf = 0;
  if (nsi) { sprintf(buf + strlen(buf), "%s; ", nsi); }
  if (ewi) { sprintf(buf + strlen(buf), "%s; ", ewi); }
  if (ci) { sprintf(buf + strlen(buf), "%s; ", ci); }
  if (rami) { sprintf(buf + strlen(buf), "%s; ", rami); }

  return buf;
}
