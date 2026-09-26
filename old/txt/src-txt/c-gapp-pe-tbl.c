inline int Gapp_next_state(Gapp* zis, int input) {
  Bit_Field_explode(&zis->input, input);
  gapp_pe(zis->alu, zis->input.explode, zis->output.explode);
  return Bit_Field_implode(&zis->output);
}

void Gapp_mk_pe_table(Gapp* zis) {
  int i;

  for (i = 0; i < zis->size; ++i) {
    zis->pe_tab[i] = Gapp_next_state(zis, i);
  }
}
