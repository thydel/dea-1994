typedef struct {
  char* name;
  int size;
} Bit_Field_Spec;

typedef struct {
  int cnt;
  int size;
  char* prefix;
  struct {
    int pos;
    int size;
    int mask;
    char* name;
  }* fields;
  int* explode;
  int implode;
} Bit_Field;

Bit_Field *Bit_Field_new(Bit_Field *zis, char *prefix, Bit_Field_Spec *spec);
int *Bit_Field_explode(Bit_Field *zis, int implode);
int Bit_Field_implode(Bit_Field *zis);
void Bit_Field_mk_include(Bit_Field *zis, FILE *fp);
