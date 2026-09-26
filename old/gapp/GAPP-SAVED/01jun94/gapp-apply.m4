#
# generate the 27 gapp ctl functions
#

#
# ACCESS EXPRESSIONS MACROS
#

# op = zis->instruction;	current instruction
# a = zis->address;		current address
# p = zis->past;		past plane
# f = zis->futur;		futur plane
#				(not used if neighboors not acceded)
# m = zis->memory		pe memory
# t = zis->gapp.pe_tab;	transiton table
# d = l-><first|mid|last>;	neighboor offset relative to current
#				pe index
# nsd = nsl-><first|mid|last>;	neighboor offset for ns axes
#				if both axes used
# ewd = ewl-><first|mid|last>;	neighboor offset for ew axes
# i = <current pe>		current pe index
# mask = <GAPP_NOS_MASK|GAPP_EOW_MASK>
# pos = <GAPP_NOS_POS|GAPP_EOW_POS>

# COMMON ACCES MACROS

# pe state to index pos
m4_define(`PE',`(p[i] << GAPP_REG_POS)')

# one neighboor access to index pos
m4_define(`NE1',`(!!(p[d[i]] & mask) << pos)')

# two neighboor access to index pos
m4_define(`NE2',
	`((!!(p[nsd[i]] & GAPP_NNS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_NEW_MASK) << GAPP_EOW_POS))')

# make ``m'' point to the correct byte bank offset
# and ``a'' be the mask of addressed bit in the bank
# this one is not realy an access macros
# and is not use in the inner loop
# but once for each run.
m4_define(`LOAD_BANK',`m = (unsigned*)((char*)m + (a >> 3)); a = 1 << (a & 31);')

# RAM to index pos
m4_define(`LRAM',`(!!(*m & a) << GAPP_RAM_POS)')

# pe state with ram cleared
# to allow ram loading
m4_define(`PEC',`((p[i] & ~GAPP_NRAM_MASK) << GAPP_REG_POS)')

# to store the ram value in pe state after pe update:
# first clear the ram adressed
# then set it to the value of pe ram bit
m4_define(`SRAM',`*m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;')

# DEBUG STUFF

m4_define(`TRACE',`m4_ifelse(0,0,`
	zis->input = $1;
	zis->output = t[zis->input];
	Gappsim_trace(zis);
	f[i] = zis->output;
	++zis->current_pe;
	',`
	f[i] = t[$1];
	')
')

# NO RAM ACCESS MACROS

m4_define(`NR0',`f[i] = t[op | PE]; ++i')
m4_define(`NR1',`f[i] = t[op | PE | NE1]; ++i')
m4_define(`NR2',`f[i] = t[op | PE | NE2]; ++i')
# m4_define(`NR2',`TRACE(`op| PE | NE2'); ++i')

# LOAD RAM MACROS

m4_define(`LR0',`f[i] = t[op | PEC | LRAM]; ++i; m += 4')
m4_define(`LR1',`f[i] = t[op | PEC | LRAM | NE1]; ++i; m += 4')
m4_define(`LR2',`f[i] = t[op | PEC | LRAM | NE2]; ++i; m += 4')

# STORE RAM MACROS

m4_define(`SR0',`f[i] = t[op | PE]; SRAM; ++i; m+= 4')
m4_define(`SR1',`f[i] = t[op | PE | NE1]; SRAM; ++i; m+= 4')
m4_define(`SR2',`f[i] = t[op | PE | NE2]; SRAM; ++i; m+= 4')

#
# CTL FUNCTIONS MACROS
#

# COMMON CTL MACROS

m4_define(`INIT',`
  unsigned char* p = zis->past;
  unsigned char* f = zis->futur;
  unsigned char* t = zis->gapp.pe_tab;
  int op = zis->instruction;
  int n = zis->side;
  int nm = n - 2;
  int i, j;
')

m4_define(`RAM_INIT',`
  INIT
  unsigned int* m = zis->memory;
  int a = zis->address;
')

m4_define(`RAM_INIT_ONLY',`
  unsigned int* m = zis->memory;
  int a = zis->address;
')

m4_define(`LOOP',`
  for (i = 0; i < n;) {
    $1;
    $1;
    $1;
    $1;
    $1;
    $1;
    $1;
    $1;
  }
')

#
# FUNC GENERATORS
#

# no neighboor func generator(name, init, prefix, acces)
m4_define(`NO_NEIGHBOOR',`
void $1(Gappsim* zis) {
  unsigned char* p = zis->past;
  unsigned char* f = p;
  unsigned char* t = zis->gapp.pe_tab;
  int op = zis->instruction;
  int n = zis->size;
  int i;
  $2

  $3
  LOOP($4)
}
')

# one neighboor func generator(name, init, prefix, access)
m4_define(`WE1_OR_SN1',`
void $1(Gappsim* zis, Neighboor_Lines* l, int mask, int pos) {
  $2
  int* d;

  $3
  d = l->first;
  LOOP($4)
  d = l->mid;
  for (j = 0; j < nm; ++j) {
    p += n;
    f += n;
    LOOP($4)
  }
  d = l->last;
  p += n;
  f += n;
  LOOP($4)
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->generation;
}
')

# two neighboor func generator(name, init, prefix, access)
m4_define(`WE1_AND_SN1',`
void $1(Gappsim* zis, Neighboor_Lines* nsl, Neighboor_Lines* ewl) {
  $2
  int* nsd;
  int* ewd;

  $3
  nsd = nsl->first;
  ewd = ewl->first;
  LOOP($4)
  nsd = nsl->mid;
  ewd = ewl->mid;
  for (j = 0; j < nm; ++j) {
    p += n;
    f += n;
    LOOP($4)
  }
  nsd = nsl->last;
  ewd = ewl->last;
  p += n;
  f += n;
  LOOP($4)
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->generation;
}
')

#
# COMMON FUNC FOR ENTRY POINTS
#

# NO RAM ACCESS FUNCS

# used by:
#
# r0_w0_e0_s0_n1
# r0_w0_e0_s1_n0
# r0_w0_e1_s0_n0
# r0_w1_e0_s0_n0
WE1_OR_SN1(`Gappsim_run_r0_we1_or_sn1', `INIT', `', `NR1')

# used by:
#
# r0_w0_e1_s0_n1
# r0_w1_e0_s0_n1
# r0_w0_e1_s1_n0
# r0_w1_e0_s1_n0
WE1_AND_SN1(`Gappsim_run_r0_we1_and_sn1', `INIT', `', `NR2')

# LOAD RAM ACCESS FUNCS

# used by:
#
# ri_w0_e0_s0_n1
# ri_w0_e0_s1_n0
# ri_w0_e1_s0_n0
# ri_w1_e0_s0_n0
WE1_OR_SN1(`Gappsim_run_ri_we1_or_sn1', `RAM_INIT', `LOAD_BANK', `LR1')

# used by:
#
# ri_w0_e1_s0_n1
# ri_w1_e0_s0_n1
# ri_w0_e1_s1_n0
# ri_w1_e0_s1_n0
WE1_AND_SN1(`Gappsim_run_ri_we1_and_sn1', `RAM_INIT', `LOAD_BANK', `LR2')

# STORE RAM ACCESS FUNCS

# used by:
#
# ro_w0_e0_s0_n1
# ro_w0_e0_s1_n0
# ro_w0_e1_s0_n0
# ro_w1_e0_s0_n0
WE1_OR_SN1(`Gappsim_run_ro_we1_or_sn1', `RAM_INIT', `LOAD_BANK', `SR1')

# used by:
#
# ro_w0_e1_s0_n1
# ro_w1_e0_s0_n1
# ro_w0_e1_s1_n0
# ro_w1_e0_s1_n0
WE1_AND_SN1(`Gappsim_run_ro_we1_and_sn1', `RAM_INIT', `LOAD_BANK', `SR2')

#
# ENTRY POINTS
#

# NO RAM ACCESS ENTRY POINTS START HERE

NO_NEIGHBOOR(`Gappsim_run_r0_w0_e0_s0_n0', `', `', NR0)

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

#
# LOAD RAM ACCESS ENTRY POINTS START HERE
#

NO_NEIGHBOOR(`Gappsim_run_ri_w0_e0_s0_n0', RAM_INIT_ONLY, LOAD_BANK, LR0)

void Gappsim_run_ri_w0_e0_s0_n1(Gappsim* zis) {
  Gappsim_run_ri_we1_or_sn1(zis, &zis->neighboor_offset->north,
			    GAPP_NNS_MASK, GAPP_NOS_POS);
}

void Gappsim_run_ri_w0_e0_s1_n0(Gappsim* zis) {
  Gappsim_run_ri_we1_or_sn1(zis, &zis->neighboor_offset->south,
			    GAPP_NNS_MASK, GAPP_NOS_POS);
}

void Gappsim_run_ri_w0_e1_s0_n0(Gappsim* zis) {
  Gappsim_run_ri_we1_or_sn1(zis, &zis->neighboor_offset->east,
			    GAPP_NEW_MASK, GAPP_EOW_POS);
}

void Gappsim_run_ri_w1_e0_s0_n0(Gappsim* zis) {
  Gappsim_run_ri_we1_or_sn1(zis, &zis->neighboor_offset->west,
			    GAPP_NEW_MASK, GAPP_EOW_POS);
}

void Gappsim_run_ri_w0_e1_s0_n1(Gappsim* zis) {
  Gappsim_run_ri_we1_and_sn1(zis, &zis->neighboor_offset->north,
			     &zis->neighboor_offset->east);
}

void Gappsim_run_ri_w1_e0_s0_n1(Gappsim* zis) {
  Gappsim_run_ri_we1_and_sn1(zis, &zis->neighboor_offset->north,
			     &zis->neighboor_offset->west);
}

void Gappsim_run_ri_w0_e1_s1_n0(Gappsim* zis) {
  Gappsim_run_ri_we1_and_sn1(zis, &zis->neighboor_offset->south,
			     &zis->neighboor_offset->east);
}

void Gappsim_run_ri_w1_e0_s1_n0(Gappsim* zis) {
  Gappsim_run_ri_we1_and_sn1(zis, &zis->neighboor_offset->south,
			     &zis->neighboor_offset->west);
}

#
# STORE RAM ACCESS ENTRY POINTS START HERE
#

NO_NEIGHBOOR(`Gappsim_run_ro_w0_e0_s0_n0', RAM_INIT_ONLY, LOAD_BANK, SR0)

void Gappsim_run_ro_w0_e0_s0_n1(Gappsim* zis) {
  Gappsim_run_ro_we1_or_sn1(zis, &zis->neighboor_offset->north,
			    GAPP_NNS_MASK, GAPP_NOS_POS);
}

void Gappsim_run_ro_w0_e0_s1_n0(Gappsim* zis) {
  Gappsim_run_ro_we1_or_sn1(zis, &zis->neighboor_offset->south,
			    GAPP_NNS_MASK, GAPP_NOS_POS);
}

void Gappsim_run_ro_w0_e1_s0_n0(Gappsim* zis) {
  Gappsim_run_ro_we1_or_sn1(zis, &zis->neighboor_offset->east,
			    GAPP_NEW_MASK, GAPP_EOW_POS);
}

void Gappsim_run_ro_w1_e0_s0_n0(Gappsim* zis) {
  Gappsim_run_ro_we1_or_sn1(zis, &zis->neighboor_offset->west,
			    GAPP_NEW_MASK, GAPP_EOW_POS);
}

void Gappsim_run_ro_w0_e1_s0_n1(Gappsim* zis) {
  Gappsim_run_ro_we1_and_sn1(zis, &zis->neighboor_offset->north,
			     &zis->neighboor_offset->east);
}

void Gappsim_run_ro_w1_e0_s0_n1(Gappsim* zis) {
  Gappsim_run_ro_we1_and_sn1(zis, &zis->neighboor_offset->north,
			     &zis->neighboor_offset->west);
}

void Gappsim_run_ro_w0_e1_s1_n0(Gappsim* zis) {
  Gappsim_run_ro_we1_and_sn1(zis, &zis->neighboor_offset->south,
			     &zis->neighboor_offset->east);
}

void Gappsim_run_ro_w1_e0_s1_n0(Gappsim* zis) {
  Gappsim_run_ro_we1_and_sn1(zis, &zis->neighboor_offset->south,
			     &zis->neighboor_offset->west);
}
