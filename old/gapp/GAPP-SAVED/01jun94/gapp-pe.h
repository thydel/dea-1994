typedef struct {
  Bit_Field input;
  Bit_Field output;
  Bit_Field instruction;
  Bit_Field iparts;
  int* alu;
  int size;
  unsigned char* pe_tab;
  void (**ctl_tab)();
  char** ctl_tab_names;
} Gapp;

Gapp *Gapp_new(Gapp *zis);
void Gapp_mk_pe_table(Gapp *zis);
void Gapp_print_pe_table(Gapp *zis, FILE *fp);
void Gapp_mk_ctl_table(Gapp *zis);
void Gapp_print_ctl_table(Gapp *zis, FILE *fp);
char* Gapp_instruction2ascii(Gapp* zis, int instruction);
