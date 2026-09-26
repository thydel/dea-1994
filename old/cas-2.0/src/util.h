#define FATAL(x) fprintf(stderr, "%s %s %d\n", cmd_name, __FILE__, __LINE__), exit(x)

typedef enum { false, true } bool;

extern char* cmd_name;

extern char* getword(char*, char*, unsigned int);
extern int readn(int, char*, unsigned int);
