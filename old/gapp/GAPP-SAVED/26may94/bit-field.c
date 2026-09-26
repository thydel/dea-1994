#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#include "bit-field.h"

Bit_Field* Bit_Field_new(Bit_Field* zis, char* prefix, Bit_Field_Spec* spec) {
  int i, pos;

  if (!zis) {
    zis = (Bit_Field*)malloc(sizeof(Bit_Field));
    assert(zis);
  }
  memset(zis, 0, sizeof(Bit_Field));
  zis->prefix = prefix;
  for (i = 0; spec[i].name; ++i) {;}
  zis->cnt = i;
  zis->fields = (typeof(zis->fields))malloc(sizeof(*zis->fields) * zis->cnt);
  zis->explode = (int*)malloc(sizeof(int*) * zis->cnt);
  
  zis->size = pos = 0;
  for (i = 0; i < zis->cnt; ++i) {
    zis->fields[i].pos = pos;
    zis->fields[i].size = spec[i].size;
    zis->fields[i].mask = ((1 << spec[i].size) - 1) << pos;
    zis->fields[i].name = spec[i].name;
    pos += spec[i].size;
    zis->size += spec[i].size;
  }
  return zis;
}

int* Bit_Field_explode(Bit_Field* zis, int implode) {
  int i;

  zis->implode = implode;
  for (i = 0; i < zis->cnt; ++i) {
    zis->explode[i] = (zis->implode & zis->fields[i].mask) >> zis->fields[i].pos;
  }
  return zis->explode;
}

int Bit_Field_implode(Bit_Field* zis) {
  int i;
  
  zis->implode = 0;
  for (i = 0; i < zis->cnt; ++i) {
    zis->implode |= zis->explode[i] << zis->fields[i].pos;
  }
  return zis->implode;
}

void Bit_Field_mk_include(Bit_Field* zis, FILE* fp) {
  int i;

  for (i = 0; i < zis->cnt; ++i) {
    fprintf(fp, "#define %s_%s %d\n", zis->prefix, zis->fields[i].name, i);
    fprintf(fp, "#define %s_%s_POS %d\n",
	    zis->prefix, zis->fields[i].name, zis->fields[i].pos);
    fprintf(fp, "#define %s_%s_SIZE %d\n",
	    zis->prefix, zis->fields[i].name, zis->fields[i].size);
    fprintf(fp, "#define %s_%s_MASK 0%o\n",
	    zis->prefix, zis->fields[i].name, zis->fields[i].mask);
  }
}
