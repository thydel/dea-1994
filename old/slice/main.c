#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <malloc.h>
#include <assert.h>

#include "debug.h"
#include "magic.h"

#include "cublib.h"

#define INPUT_NAME "stdin"

char* cmd_name;
int debug_flag;
int verbose_flag;

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

  while ((c = getopt(ac, av, "s:i:o:DV")) != EOF)
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
    case 'V':
      verbose_flag = 1;
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

  cub = Cub_new(0, 3, side, 0);
  Cub_read(cub, input);
  Cub_test(cub, output_prefix);
}

void Cub_test(Cub* zis, char* output_prefix) {
  debug(0, Cub_print(zis, stderr));

  if (1) {
    Cub_slice_thru_2diagonale_to_file(zis, "out/2diag");
  }
  if (1) {
    Cub_faces_slice_ortho_to_files(zis, 0, output_prefix);
    Cub_faces_slice_ortho_to_files(zis, zis->size[1] >> 1, output_prefix);
  }
  if (1) {
    Cub_plane_relative_to_files(zis, "out/relative");
    Cub_plane_relative_move_to_files(zis, "out/relative-move");
  }
  if (1) {
    Cub* a_ramp;
    Cub* a_zero;

    a_ramp = Cub_line_new_from_volume(0, zis);
    Cub_line_ramp(a_ramp);
    a_zero = Cub_line_new_from_volume(0, zis);
    Cub_zero(a_zero);
    Cub_faces_transparence_ortho_to_files(zis, a_ramp, "out/trans-A");
    Cub_faces_transparence_ortho_on_bits_to_files(zis, a_zero, "out/trans-B");
  }
  if (1) {
    Cub_fill(zis);
    Cub_faces_slice_ortho_to_files(zis, 0, "out/filled");
    Cub_volume_to_file(zis, "out/filled");
  }
}
