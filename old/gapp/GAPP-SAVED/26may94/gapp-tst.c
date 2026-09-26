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
#include "space.h"

typedef struct {
  int inst;
  int address;
  int extract;
} Gapp_Step;

#define KILO 1024

void gapp_step(Gappsim* zis, Gappsim_options* options, FILE* input, int output) {
  Gapp_Step prog[16 * KILO];
  char buf[BUFSIZ];
  int cnt, i, j;

  cnt = 0;
  while (fgets(buf, BUFSIZ, input)) {
    static char* delim = " \n";
    static char* numstr = "0123456789";

    int inst, address, extract;
    char* istr; char* astr; char* estr;

    inst = address = extract = 0;

    istr = strtok(buf, delim);
    assert(istr);
    assert(strlen(istr) == strspn(istr, numstr));
    inst = atoi(istr);
    assert(inst >= 0 && inst < zis->gapp.size);
    assert((int)zis->gapp.ctl_tab[inst] > 0);
    prog[cnt].inst = inst;

    astr = strtok(NULL, delim);
    assert(strlen(astr) == strspn(astr, numstr));
    address = atoi(astr);
    assert(address >= 0 && address < 128);
    prog[cnt].address = address;

    estr = strtok(NULL, delim);
    assert(strlen(estr) == strspn(estr, numstr));
    extract = atoi(estr);
    assert(extract >= 0 && extract <= 6);
    prog[cnt].extract = extract;

    ++cnt;
  }
  for (i = 0; i < options->cnt; ++i) {
    for (j = 0; j < cnt; ++j) {
      if (prog[j].inst) {
	zis->instruction = prog[j].inst;
	zis->address = prog[j].address;
	zis->gapp.ctl_tab[zis->instruction](zis);
      }
      if (prog[j].extract) {
	Gappsim_extract(zis, prog[j].extract - 1);
	write(output, zis->plane, zis->size >> 3);
      }
    }
  }
}

gapptst(Gappsim* zis, Gappsim_options* options) {
  int side;

  side = 1 << options->side;
  if (options->single) {
    int i = ((side >> 1) << options->side) + (side >> 1);
    zis->past[i] = 3;
  } else {
    randomize(zis->past, zis->size);
  }
  gapp_step(zis, options, stdin, 1);
}
