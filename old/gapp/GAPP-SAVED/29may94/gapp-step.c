#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "bit-field.h"
#include "gapp-defs.h"
#include "gapp-arch.h"
#include "gapp-pe.h"
#include "gapp-sim.h"
#include "gapp-opts.h"
#include "gapp-step.h"
#include "space.h"

static char* numstr = "0123456789";
static char* delim = " \n";


enum {
  FUNK_ZERO,
  FUNK_GAPP, FUNK_EXTRACT, FUNK_PAUSE,
  FUNK_LAST
};

void *funk_gapp1(char *p);
void funk_gapp(Gapp_Step* zis, int);
void *funk_extract1(char *p);
void funk_extract(Gapp_Step *zis, int);
void *funk_pause1(char *p);
void funk_pause(Gapp_Step *zis, int);

void (*tfunk[])(Gapp_Step*, int) = {
  0, funk_gapp, funk_extract, funk_pause
};

void* (*tfunk1[])(char*) = {
  0, funk_gapp1, funk_extract1, funk_pause1
};

Gapp_Step* Gapp_Step_new(Gapp_Step* zis, Gappsim* gappsim, Gappsim_options* options) {
  if (!zis) {
    zis = (Gapp_Step*)malloc(sizeof(Gapp_Step));
    assert(zis);
  }
  zis->gappsim = gappsim;
  zis->options = options;
  zis->cnt = 0;
  return zis;
}

void Gapp_Step_load(Gapp_Step* zis, FILE* input) {
  char buf[BUFSIZ];
  
  zis->cnt = 0;
  while (fgets(buf, BUFSIZ, input)) {
    int tmp, funk;

    tmp = strspn(buf, numstr);
    assert(tmp);
    buf[tmp] = 0;
    assert(strlen(buf) == strspn(buf, numstr));
    funk = atoi(buf);
    assert(funk >= FUNK_GAPP && funk < FUNK_LAST);
    zis->prog[zis->cnt].funk = tfunk[funk];
    zis->prog[zis->cnt].args = tfunk1[funk](buf + tmp + 1);
    
    ++zis->cnt;
  }
}

void Gapp_Step_run(Gapp_Step* zis, int output) {
  int i, j;

  zis->output = output;
  for (i = 0; i < zis->options->cnt; ++i) {
    for (j = 0; j < zis->cnt; ++j) {
      zis->prog[j].funk(zis, j);
    }
  }
}

inline int* get_one_int(char* p) {
  int* a;
  
  assert(strspn(p, numstr));
  a = (int*)malloc(sizeof(int)); assert(a);
  a[0] = atoi(p);
  return a;
}

inline int* get_two_int(char* p) {
  int* a;
  char* s;
  
  a = (int*)malloc(sizeof(int) * 2); assert(a);
  s = strtok(p, delim);
  assert(s);
  assert(strlen(s) == strspn(s, numstr));
  a[0] = atoi(s);
  s = strtok(0, delim);
  assert(s);
  assert(strlen(s) == strspn(s, numstr));
  a[1] = atoi(s);
  return a;
}

void* funk_gapp1(char* p) {
  int *a;

  a = get_two_int(p);
  assert(a[0] >= 0 && a[0] < (2 << 11));
  assert(a[1] >= 0 && a[1] < 128);
  return a;
}

void funk_gapp(Gapp_Step* zis, int n) {
  Gappsim* sim = zis->gappsim;
  int* a = zis->prog[n].args;

  sim->instruction = a[0];
  sim->address = a[1];
  sim->gapp.ctl_tab[sim->instruction](sim);
}

void* funk_extract1(char* p) {
  return get_one_int(p);
}

void funk_extract(Gapp_Step* zis, int n) {
  int* a = zis->prog[n].args;

  Gappsim_extract(zis->gappsim, a[0]);
  write(zis->output, zis->gappsim->plane, zis->gappsim->size >> 3);
}

void* funk_pause1(char* p) {
  return get_one_int(p);
}

void funk_pause(Gapp_Step* zis, int n) {
  int* a = zis->prog[n].args;

  if (!a[0]) {
    pause();
  }
  sleep(a[0]);
}
