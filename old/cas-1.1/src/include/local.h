extern char* cmd_name;

typedef enum { false, true } bool;

#define FATAL(x) fprintf(stderr, "%s %s %d\n", cmd_name, __FILE__, __LINE__), exit(x)
