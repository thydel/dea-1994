void randomize(unsigned char *p, int size);
void rextract0(unsigned char *itab, unsigned char *otab, int size);
void rextract1(unsigned char *itab, unsigned char *otab, int size);
void rextract2(unsigned char *itab, unsigned char *otab, int size);
void rextract3(unsigned char *itab, unsigned char *otab, int size);
void rextract4(unsigned char *itab, unsigned char *otab, int size);
void rextract5(unsigned char *itab, unsigned char *otab, int size);
void rextract6(unsigned char *itab, unsigned char *otab, int size);
void rextract7(unsigned char *itab, unsigned char *otab, int size);

extern void (*textract[])(unsigned char*, unsigned char*, int);
