main(int ac, char** av) {
  int n, i;
  char t[64];
  int x;
  int tt;

  tt = atoi(av[1]);
  n = atoi(av[2]);
  switch (tt) {
  case 1:
    for (i = 0; i < n; ++i) {
      t[42];
    }
    break;
  case 2:
    x = 42;
    for (i = 0; i < n; ++i) {
      t[x];
    }
    break;
  case 3:
    for (i = 0; i < n;) {
      t[42]; ++i; t[42]; ++i; t[42]; ++i; t[42]; ++i;
      t[42]; ++i; t[42]; ++i; t[42]; ++i; t[42]; ++i;
    }
    break;
  case 4:
    x = 30;
    for (i = 0; i < n; ++i) {
      1 << x;
    }
    break;
  case 5:
    x = 2;
    for (i = 0; i < n; ++i) {
      1 << x;
    }
    break;
  }
  return 0;
}
