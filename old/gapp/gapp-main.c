#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <getopt.h>

#include "bit-field.h"
#include "gapp-defs.h"
#include "gapp-arch.h"
#include "gapp-pe.h"
#include "gapp-sim.h"
#include "gapp-opts.h"
#include "space.h"

static Gappsim_options gappsim_options;

void Gappsim_options_init(Gappsim_options* zis, char* name) {
  zis->name = name;
  zis->side = 7;
  zis->cnt = 1;
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
      -cnt=<int>        number of times to iterate gapp prog\n");
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
  while (option_char = getopt_long_only(ac, av, "", long_options, NULL),
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

    system("mv gapp-defs.h gapp-defs.h.bak");
    fp = fopen("gapp-defs.h", "w");
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

    fp = fopen("gapp-inst-set.txt", "w");
    assert(fp);
    Gapp_print_ctl_table(&gappsim->gapp, fp);
    close(fp);
  }
  if (options->tablelist) {
    FILE* fp;

    fp = fopen("gapp-pe.txt", "w");
    assert(fp);
    Gapp_print_pe_table(&gappsim->gapp, fp);
    close(fp);
  }
  gapptst(gappsim, options);
  return 0;
}


