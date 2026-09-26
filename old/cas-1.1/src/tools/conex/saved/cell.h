#define MOORE 0
#define VON_NEUMANN 1

extern char* conex_name;
extern int _conex;
extern int _size;
extern int _xsize;
extern int _ysize;
extern int _public;
extern int _private;
extern int _stat;
extern int _reduce;

extern char* cell();
extern char* cell_name();
extern char* cell_body();
extern char* cell_init();
extern char* do_lines();
extern char* first_line();
extern char* mid_lines();
extern char* last_line();
extern char* do_cols();
extern char* first_col();
extern char* mid_cols();
extern char* last_col();
extern char* set_first_col_index();
extern char* set_col_index();
extern char* set_last_col_index();
extern char* set_first_local();
extern char* set_local();
extern char* set_last_local();
extern char* set_local_common(int);
extern char* set_futur();
extern char* use_index();
extern char* get_index(char*, int);
extern char* get_public(char*);
