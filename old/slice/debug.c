#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include "debug.h"

void error(char* str) {
  char buf[BUFSIZ];

  sprintf("%s, %s:", cmd_name, str);
  perror(buf);
}

void error_creat(char* func, char* file) {
  char buf[BUFSIZ];

  sprintf(buf, "%s, creat(%s)", file);
  error(buf);
}

void error_open(char* func, char* file) {
  char buf[BUFSIZ];

  sprintf(buf, "%s, open(%s)", file);
  error(buf);
}
