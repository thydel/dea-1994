#include <stdio.h>
#include <assert.h>

main(int ac, char **av) {
  int n, i;

  assert(ac == 2);
  n = atoi(av[1]);
  for (i = 0; i < n; ++i) {
    printf("%04d ", i);
  }
  printf("\n");
  return 0;
}
