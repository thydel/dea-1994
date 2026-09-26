typedef struct {
  Bit_Field_Spec* input;
  Bit_Field_Spec* output;
  Bit_Field_Spec* instruction;
  Bit_Field_Spec* iparts;
  int* alu;
} Gapp_Pe_Spec;

extern Gapp_Pe_Spec gapp_pe_spec;
