#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <malloc.h>
#include <assert.h>

#include "debug.h"
#include "magic.h"

#include "cublib.h"
#include "manip.h"

#define INPUT_NAME "stdin"

char* cmd_name;
int debug_flag;

void top(int side, int input, char *output_prefix);
void Cub_test(Cub *zis, char *output_prefix);

main(int ac, char** av) {
  extern char *optarg;
  extern int optind;
  static char* usage =
    "-s{ize} <power-of-two>\n"
    "[-i{nput} <file-name> (default = stdin)]\n"
    "[-o{uput-prefix} <string> (default = \"out/00\")]\n"
    "[-D{edug}]\n";
  int c, errflg;
    
  int size;
  char* input_name;
  int input_file;
  char* output_prefix;
    
  cmd_name = av[0];
  debug_flag = 0;
  errflg = 0;
  size = -1;
  input_name = INPUT_NAME;
  input_file = 0;
  output_prefix = "out/00";

  while ((c = getopt(ac, av, "s:i:o:D")) != EOF)
    switch (c) {
    case 's':
      size = atoi(optarg);
      break;
    case 'i':
      input_name = malloc(strlen(optarg) + 1);
      strcpy(input_name, optarg);
      break;
    case 'o':
      output_prefix = malloc(strlen(optarg) + 1);
      strcpy(output_prefix, optarg);
      break;
    case 'D':
      debug_flag = 1;
      break;
    case '?':
      errflg++;
    }
    
  if (errflg) {
    fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
    exit(1);
  }
    
  for (; optind < ac; optind++) {
    fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
    exit(1);
  }

  if (strcmp(input_name, INPUT_NAME)) {
    input_file = open(input_name, O_RDONLY);
    if (input_file == -1) {
      error_open(__PRETTY_FUNCTION__, input_name);
      return 1;
    }
  }

  top(size, input_file, output_prefix);

  return 0;
}

void top(int side, int input, char* output_prefix) {
  Cub* cub;

  cub = Cub_new(0, 3, side);
  Cub_read(cub, input);
  Cub_test(cub, output_prefix);
}

void Cub_test(Cub* zis, char* output_prefix) {
  int side;
  int max;
  int i;
  int fd;
  int permut[CUB_MAXDIM + 1];

  debug(0, Cub_print(zis, stderr));

  Cub_faces(zis, output_prefix);

#if 0
  Cub_zero_plane(zis);
  Cub_slice_thru_diagonale_to_file(zis, "out/diag");

  Cub_fill(zis);
  Cub_faces(zis, "out/filled");
  Cub_volume_to_file(zis, "out/filled");
#endif
}
