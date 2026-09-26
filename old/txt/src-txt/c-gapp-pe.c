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

