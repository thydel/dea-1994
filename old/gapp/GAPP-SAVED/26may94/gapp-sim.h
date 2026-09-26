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
  Gapp gapp;
  int gen;
  Neighboor_Offset* neighboor_offset;
  Neighboor_Offset torus;
  int instruction;
  int address;
  unsigned char* past;
  unsigned char* futur;
  unsigned char* tmp;
  unsigned int* memory;
  unsigned char* plane;
  int side;
  int size;
} Gappsim;

Neighboor_Offset *Neighboor_Offset_new(Neighboor_Offset *zis, int side);
void Neighboor_Offset_print(Neighboor_Offset *zis);
Gappsim *Gappsim_new(Gappsim *zis, int side);
int Gappsim_extract(Gappsim *zis, int plane);
void Gappsim_trace(Gappsim *zis, int input, int output, int index);
