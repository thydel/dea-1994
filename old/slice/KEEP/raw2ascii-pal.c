main() {
  int i;
  unsigned char t[768];

  read(0, t, 768);
  for (i = 0; i < 256; ++i) {
    printf("%d %d %d\n", t[i*3], t[i*3+1], t[i*3+2]);
  }
}
