#include <ctype.h>

#include "util.h"

/* copy in buf the nieme word (arg mot) found in line, and return buf
 * or NULL if there is less than <mot> words. line is a string ended by '\0',
 * a word is a group of any char betwen to space char as define in
 * isspace (3) and obviouly the start and the end of the line.
 */

char* getword(char* buf, char* line, unsigned int mot)
{
  int inword = 0;
  char c;
  char *sbuf = buf;

  while (c = *line++) {
    if (isspace (c) && inword) {
      inword = 0;
      continue;
    }
    if (!isspace(c) && !inword) {
      inword = 1;
      if(!--mot) {
	--line;
	while (*line && !isspace(*line))
	  *buf++ = *line++;
	*buf = '\0';
	return sbuf;
      }
    }
  }
  return 0;
}

int readn(int fd, char* buf, unsigned int size)
{
  unsigned int chunk;
  int n;
  static int eof = 0;

  if (eof) {
    eof = 0;
    return 0;
  }
  for (chunk = 0; chunk != size; chunk += n) {
    n = read(fd, buf + chunk, size - chunk);
    if (n == 0) {
      eof = 1;
      chunk += n;
      return chunk;
    }
    if (n == -1) {
      perror(cmd_name);
      return n;
    }
  }
  return size;
}
