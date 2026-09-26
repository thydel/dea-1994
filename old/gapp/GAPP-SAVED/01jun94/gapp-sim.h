typedef struct {
  int* north;
  int* south;
  int* east;
  int* west;
} Neighboor_VN;

typedef struct {
  int* first;
  int* mid;
  int* last;
} Neighboor_Lines;

typedef struct {
  int side;
  int size;
  Neighboor_VN first;
  Neighboor_VN mid;
  Neighboor_VN last;
  Neighboor_Lines north;
  Neighboor_Lines south;
  Neighboor_Lines east;
  Neighboor_Lines west;
} Neighboor_Offset;

typedef struct {
  Gapp gapp;			/* gapp pe object */

  int generation;		/* how many cycle done */
  int current_pe;		/* index of current pe in plane */
  int instruction;		/* zis cycle instrution */
  int address;			/* zis cycle address */
  int input;			/* zis cycle instruction + address + neighboors */
  int output;			/* zis cycle new pe state */

  Neighboor_Offset* neighboor_offset; /* neighboor indirect positions */
  Neighboor_Offset torus;	/* torus border */

  int side;			/* side of plane */
  int size;			/* side * side */

  unsigned char* past;		/* zis cycle pe state */
  unsigned char* futur;		/* zis cycle pe next state */
  unsigned char* tmp;		/* use to swap past and futur */
  unsigned int* memory;		/* pe memory (size * 16 bytes) */
  unsigned char* plane;		/* bimap copy of one reg or ram bit
				   of zis cycle plane */
} Gappsim;

Neighboor_Offset *Neighboor_Offset_new(Neighboor_Offset *zis, int side);
void Neighboor_Offset_print(Neighboor_Offset *zis);
Gappsim *Gappsim_new(Gappsim *zis, int side);
int Gappsim_extract(Gappsim *zis, int plane);
void Gappsim_trace(Gappsim *zis);

