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

enum {
  FUNK_ZERO,
  FUNK_GAPP,
  FUNK_EXTRACT,
  FUNK_PAUSE,
  FUNK_CLEAR,
  FUNK_SINGLE,
  FUNK_RANDOM,
  FUNK_BLOC,
  FUNK_LABEL,
  FUNK_GOTO,
  FUNK_STATE2ASCII,
  FUNK_FRAME2ASCII,
  FUNK_PRINT,
  FUNK_LAST
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

inline int* get_n_int(char* p, int n) {
  int* a; int i; char* pp;

  a = (int*)malloc(sizeof(int) * n); assert(a);
  for (i = 0; i < n; ++i) {
    a[i] = strtol(p, &pp, 0);
    assert(pp);
    p = pp;
  }
  return a;
}

inline char** get_n_str(char* p, int n) {
  static char* delim = " \n";
  char** a; int i;

  a = (char**)malloc(sizeof(char*) * n); assert(a);
  a[0] = strtok(p, delim); assert(a[0]);
  for (i = 1; i < n; ++i) {
    a[i] = strtok(0, delim); assert(a[i]);
  }
  return a;
}

void Gapp_Step_load(Gapp_Step* zis, FILE* input) {
  char buf[BUFSIZ];
  
  zis->cnt = 0;
  while (fgets(buf, BUFSIZ, input)) {
    char* p;
    int funk;

    funk = strtol(buf, &p, 0);
    assert(p);
    assert(funk >= FUNK_GAPP && funk < FUNK_LAST);
    switch (funk) {
    default:
      assert(0);
    case FUNK_GAPP: {
      int* a;
      a = get_n_int(p, 2);
      assert(a[0] >= 0 && a[0] < (2 << 11));
      assert(a[1] >= 0 && a[1] < 128);
      zis->prog[zis->cnt].funk = funk;
      zis->prog[zis->cnt].args = a;
      break;
    }
    case FUNK_EXTRACT:
    case FUNK_PAUSE:
      {
	zis->prog[zis->cnt].funk = funk;
	zis->prog[zis->cnt].args = get_n_int(p, 1);
	break;
      }
    case FUNK_CLEAR:
    case FUNK_SINGLE:
    case FUNK_RANDOM:
    case FUNK_BLOC:
      {
	zis->prog[zis->cnt].funk = funk;
	zis->prog[zis->cnt].args = 0;
	break;
      }
    case FUNK_LABEL: {
      int* a = get_n_int(p, 1);
      assert(a && a[0] >= 0 && a[0] <= 8);
      zis->label[a[0]] = zis->cnt;
      free(a);
      continue;
    }
    case FUNK_GOTO: {
      int* a = get_n_int(p, 1);
      assert(a && a[0] >= 0 && a[0] <= 8);
      zis->prog[zis->cnt].funk = funk;
      zis->prog[zis->cnt].args = a;
      break;
    }
    case FUNK_STATE2ASCII: {
      zis->prog[zis->cnt].funk = funk;
      zis->prog[zis->cnt].args = get_n_int(p, 1);
      break;
    }
    case FUNK_FRAME2ASCII: {
      zis->prog[zis->cnt].funk = funk;
      zis->prog[zis->cnt].args = get_n_int(p, 1);
      break;
    }
    case FUNK_PRINT: {
      zis->prog[zis->cnt].funk = funk;
      zis->prog[zis->cnt].args = strcpy(malloc(strlen(p) + 1), p);
      ((char*)(zis->prog[zis->cnt].args))[strlen(p) - 1] = 0;
      assert(zis->prog[zis->cnt].args);
    }
    }
    ++zis->cnt;
  }
}

void Gapp_Step_run(Gapp_Step* zis, int output) {
  int i, j;

  zis->output = output;
  for (i = 0; i < zis->options->cnt; ++i) {
    for (j = 0; j < zis->cnt; ++j) {
    top:
      switch(zis->prog[j].funk) {
      default:
	assert(0);
      case FUNK_GAPP: {
	Gappsim* sim = zis->gappsim;
	int* a = zis->prog[j].args;
	void (*funk)();

	sim->instruction = a[0];
	sim->address = a[1];
	funk = sim->gapp.ctl_tab[sim->instruction];
	if ((int)funk < 0 || sim->instruction > (1 << GAPP_INS_SIZE)) {
	  if ((int)funk == -1) {
	    fprintf(stderr, "undefined instruction %s\n",
		    Gapp_instruction2ascii(&sim->gapp, sim->instruction));
	  } else if ((int)funk == -2) {
	    fprintf(stderr, "illegal instruction %s\n",
		    Gapp_instruction2ascii(&sim->gapp, sim->instruction));
	  } else {
	    fprintf(stderr, "garbage instruction %d\n", sim->instruction);
	  }
	  exit(1);
	}
	if (zis->options->verbose) {
	  fprintf(stderr, "*** %s %d ***\n",
		  Gapp_instruction2ascii(&sim->gapp, sim->instruction),
		  sim->address);
	}
	sim->gapp.ctl_tab[sim->instruction](sim);
	break;
      }
      case FUNK_EXTRACT: {
	Gappsim_extract(zis->gappsim, ((int*)zis->prog[j].args)[0]);
	write(zis->output, zis->gappsim->plane, zis->gappsim->size >> 3);
	break;
      }
      case FUNK_PAUSE: {
	int* a = zis->prog[j].args;

	if (!a[0]) {
	  pause();
	}
	sleep(a[0]);
	break;
      }
      case FUNK_CLEAR:
	zero(zis->gappsim->past, zis->options->side);
	break;
      case FUNK_SINGLE:
	single(zis->gappsim->past, zis->options->side);
	break;
      case FUNK_RANDOM:
	randomize(zis->gappsim->past, zis->options->side);
	break;
      case FUNK_BLOC:
	bloc(zis->gappsim->past, zis->options->side);
	break;
      case FUNK_LABEL:
	assert(0);
      case FUNK_GOTO:
	j = zis->label[((int*)zis->prog[j].args)[0]];
	goto top;
      case FUNK_STATE2ASCII: {
	state2ascii(zis->gappsim->past, zis->options->side,
		    ((int*)zis->prog[j].args)[0], stderr);
	break;
      }
      case FUNK_FRAME2ASCII: {
       frame2ascii(zis->gappsim->memory, zis->options->side,
		    ((int*)zis->prog[j].args)[0], stderr);
	break;
      }
      case FUNK_PRINT: {
	fprintf(stderr, "%s\n", (char*)zis->prog[j].args);
	fflush(stderr);
	break;
      }
      }
    }
  }
}
