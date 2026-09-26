#include "conex.h"

extern moore_128_128_1_0();
int moore_128_128_1_0_size() { return MOORE_1_SIZE; }

extern moore_256_256_1_0();
int moore_256_256_1_0_size() { return MOORE_1_SIZE; }

extern moore_256_256_2_0();
int moore_256_256_2_0_size() { return MOORE_2_SIZE; }

extern von_neumann_256_256_1_0();
int von_neumann_256_256_1_0_size() { return VON_NEUMANN_1_SIZE; }

extern von_neumann_256_256_2_0();
int von_neumann_256_256_2_0_size() { return VON_NEUMANN_2_SIZE; }

#define VON_NEUMANN_3_SIZE (1 << (4 + 1) * 3)

extern von_neumann_64_64_3_0();
int von_neumann_64_64_3_0_size() { return VON_NEUMANN_3_SIZE; }

extern von_neumann_256_256_3_0();
int von_neumann_256_256_3_0_size() { return VON_NEUMANN_3_SIZE; }

#define VON_NEUMANN_4_SIZE (1 << (4 + 1) * 4)

extern von_neumann_256_256_4_0();
int von_neumann_256_256_4_0_size() { return VON_NEUMANN_4_SIZE; }

