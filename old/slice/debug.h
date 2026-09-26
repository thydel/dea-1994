#define DEBUG 1
#define debug(flag, expr) if(DEBUG && debug_flag && flag) {expr;}

#define VERBOSE 1
#define verbose(flag, str) if(VERBOSE && verbose_flag && flag) {fprintf(stderr, str);}

extern char* cmd_name;
extern int debug_flag;
extern int verbose_flag;

void error(char *str);
void error_creat(char *func, char *file);
void error_open(char *func, char *file);
