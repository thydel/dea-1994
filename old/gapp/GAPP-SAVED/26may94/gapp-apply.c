/*
 * this file was macro generated from
 * an m4 spec file.
 * dont edit
 */

#include <stdio.h>

#include "bit-field.h"
#include "gapp-defs.h"
#include "gapp-arch.h"
#include "gapp-pe.h"
#include "gapp-sim.h"

void Gappsim_run_r0_we1_or_sn1(Gappsim* zis, Neighboor_Lines* l, int mask, int pos) {
  
  unsigned char* p = zis->past;
  unsigned char* f = zis->futur;
  unsigned char* t = zis->gapp.pe_tab;
  int op = zis->instruction;
  int n = zis->side;
  int nm = n - 2;
  int i, j;
  int* d;
  d = l->first;
  
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
  }
  d = l->mid;
  for (j = 0; j < nm; ++j) {
    p += n;
    f += n;
    
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
  }
  }
  d = l->last;
  p += n;
  f += n;
  
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; ++i;
  }
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->gen;
}
void Gappsim_run_r0_we1_and_sn1(Gappsim* zis, Neighboor_Lines* nsl, Neighboor_Lines* ewl) {
  
  unsigned char* p = zis->past;
  unsigned char* f = zis->futur;
  unsigned char* t = zis->gapp.pe_tab;
  int op = zis->instruction;
  int n = zis->side;
  int nm = n - 2;
  int i, j;
  int* nsd;
  int* ewd;
  nsd = nsl->first;
  ewd = ewl->first;
  
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
  }
  nsd = nsl->mid;
  ewd = ewl->mid;
  for (j = 0; j < nm; ++j) {
    p += n;
    f += n;
    
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
  }
  }
  nsd = nsl->last;
  ewd = ewl->last;
  
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i;
  }
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->gen;
}
void Gappsim_run_ri_we1_or_sn1(Gappsim* zis, Neighboor_Lines* l, int mask, int pos) {
  
  
  unsigned char* p = zis->past;
  unsigned char* f = zis->futur;
  unsigned char* t = zis->gapp.pe_tab;
  int op = zis->instruction;
  int n = zis->side;
  int nm = n - 2;
  int i, j;
  unsigned int* m = zis->memory;
  int a = zis->address;
  int* d;
  d = l->first;
  
  for (i = 0; i < n;) {
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
  }
  d = l->mid;
  for (j = 0; j < nm; ++j) {
    p += n;
    f += n;
    
  for (i = 0; i < n;) {
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
  }
  }
  d = l->last;
  p += n;
  f += n;
  
  for (i = 0; i < n;) {
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | (!!(p[d[i]] & mask) << pos)]; ++i; m += 4;
  }
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->gen;
}
void Gappsim_run_ri_we1_and_sn1(Gappsim* zis, Neighboor_Lines* nsl, Neighboor_Lines* ewl) {
  
  
  unsigned char* p = zis->past;
  unsigned char* f = zis->futur;
  unsigned char* t = zis->gapp.pe_tab;
  int op = zis->instruction;
  int n = zis->side;
  int nm = n - 2;
  int i, j;
  unsigned int* m = zis->memory;
  int a = zis->address;
  int* nsd;
  int* ewd;
  nsd = nsl->first;
  ewd = ewl->first;
  
  for (i = 0; i < n;) {
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
  }
  nsd = nsl->mid;
  ewd = ewl->mid;
  for (j = 0; j < nm; ++j) {
    p += n;
    f += n;
    
  for (i = 0; i < n;) {
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
  }
  }
  nsd = nsl->last;
  ewd = ewl->last;
  
  for (i = 0; i < n;) {
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
    f[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; ++i; m += 4;
  }
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->gen;
}
void Gappsim_run_ro_we1_or_sn1(Gappsim* zis, Neighboor_Lines* l, int mask, int pos) {
  
  
  unsigned char* p = zis->past;
  unsigned char* f = zis->futur;
  unsigned char* t = zis->gapp.pe_tab;
  int op = zis->instruction;
  int n = zis->side;
  int nm = n - 2;
  int i, j;
  unsigned int* m = zis->memory;
  int a = zis->address;
  int* d;
  d = l->first;
  
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
  }
  d = l->mid;
  for (j = 0; j < nm; ++j) {
    p += n;
    f += n;
    
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
  }
  }
  d = l->last;
  p += n;
  f += n;
  
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | (!!(p[d[i]] & mask) << pos)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
  }
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->gen;
}
void Gappsim_run_ro_we1_and_sn1(Gappsim* zis, Neighboor_Lines* nsl, Neighboor_Lines* ewl) {
  
  
  unsigned char* p = zis->past;
  unsigned char* f = zis->futur;
  unsigned char* t = zis->gapp.pe_tab;
  int op = zis->instruction;
  int n = zis->side;
  int nm = n - 2;
  int i, j;
  unsigned int* m = zis->memory;
  int a = zis->address;
  int* nsd;
  int* ewd;
  nsd = nsl->first;
  ewd = ewl->first;
  
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
  }
  nsd = nsl->mid;
  ewd = ewl->mid;
  for (j = 0; j < nm; ++j) {
    p += n;
    f += n;
    
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
  }
  }
  nsd = nsl->last;
  ewd = ewl->last;
  
  for (i = 0; i < n;) {
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    f[i] = t[op | (p[i] << GAPP_REG_POS) | ((!!(p[nsd[i]] & GAPP_NOS_MASK) << GAPP_NOS_POS)
        | (!!(p[ewd[i]] & GAPP_EOW_MASK) << GAPP_EOW_POS))]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
  }
  zis->tmp = zis->past; zis->past = zis->futur; zis->futur = zis->tmp; ++zis->gen;
}
void Gappsim_run_r0_w0_e0_s0_n0(Gappsim* zis) {
  unsigned char* p;
  unsigned char* t;
  int op, n, i;
  
  op = zis->instruction;
  p = zis->past;
  n = zis->size;
  t = zis->gapp.pe_tab;
  
  for (i = 0; i < n;) {
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; ++i;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; ++i;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; ++i;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; ++i;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; ++i;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; ++i;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; ++i;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; ++i;
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
void Gappsim_run_ri_w0_e0_s0_n0(Gappsim* zis) {
  unsigned char* p;
  unsigned char* t;
  int op, n, i;
  
  unsigned int* m = zis->memory;
  int a = zis->address;
  op = zis->instruction;
  p = zis->past;
  n = zis->size;
  t = zis->gapp.pe_tab;
  
  for (i = 0; i < n;) {
    p[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS)]; ++i; m += 4;
    p[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS)]; ++i; m += 4;
    p[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS)]; ++i; m += 4;
    p[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS)]; ++i; m += 4;
    p[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS)]; ++i; m += 4;
    p[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS)]; ++i; m += 4;
    p[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS)]; ++i; m += 4;
    p[i] = t[op | ((p[i] & ~GAPP_RAM_MASK) << GAPP_REG_POS) | (!!(*m & a) << GAPP_RAM_POS)]; ++i; m += 4;
  }
}
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
void Gappsim_run_ro_w0_e0_s0_n0(Gappsim* zis) {
  unsigned char* p;
  unsigned char* t;
  int op, n, i;
  
  unsigned int* m = zis->memory;
  int a = zis->address;
  op = zis->instruction;
  p = zis->past;
  n = zis->size;
  t = zis->gapp.pe_tab;
  
  for (i = 0; i < n;) {
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
    p[i] = t[op | (p[i] << GAPP_REG_POS)]; *m &= ~a; *m |= (p[i] & GAPP_NRAM_MASK) ? a : 0;; ++i; m+= 4;
  }
}
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
