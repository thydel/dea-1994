#define DEBUG 1
#define debug(f, e) if(DEBUG && debug_flag && f) {e;}

extern char* cmd_name;
extern int debug_flag;

void error(char *str);
void error_creat(char *func, char *file);
void error_open(char *func, char *file);
