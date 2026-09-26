#include <stdio.h>
#include <stdlib.h>

#include "named_func.h"

char* cell(char*, char*, char*,char*, char*, char*, char*, char*, char*, char*,
	   int, int, int, int, int);
char* mk_cell_name(char*, int, int, int, int);
char* mk_cell_args(char*, char*, char*, char*, char*);
char* mk_cell_locals(char*, char*, char*, char*, char*, char*);
char* cell_body(char*,char*, char*, char*, char*, char*, char*, char*, char*, char*,
		int, int, int, int, int);
char* conex(char*, char*, char*, char*, char*, char*, char*, char*, int, int, int, int);
char* first_col(char*, char*, char*, char*, char*, char*, char*, int, int, int, int);
char* cols(char*, char*, char*, char*, char*, char*, char*, char*, int, int, int, int);
char* last_col(char*, char*, char*, char*, char*, char*, char*, int, int, int, int);
char* set_first_col_index(char*, char*, char*, char*, int, int, int);
char* set_col_index(char*, char*, char*, char*, int, int, int);
char* set_last_col_index(char*, char*, char*, char*, int, int, int, int);
char* set_first_local(char*, char*, int, int, int);
char* set_local(char*, char*, int, int, int);
char* set_last_local(char*, char*, int, int, int);
char* set_local_common(char*, char*, int, int, int, int);
char* set_futur(char*, char*, char*, char*, int, int, int);
char* use_index(char*, int, int);
char* get_index_part(char*, int, int, int);
char* get_public(char*, int, int);

int mask(int);

char* declare(char*, char*, char*, char*);
char* mk_int(char*);
char* mk_reg_int(char*);
char* mk_ptr(char*, char*);
char* mk_arg_ptr(char*, char*);
char* mk_arg_int(char*);
char* mk_reg_ptr(char*, char*);

char* comment(char*, char*);
char* seq1(char*);
char* seq2(char*, char*);
char* seq3(char*, char*, char*);
char* seq4(char*, char*, char*, char*);
char* seq5(char*, char*, char*, char*, char*);
char* seq6(char*, char*, char*, char*, char*, char*);
char* set(char*, char*);
char* or2(char*, char*);
char* or3(char*, char*, char*);
char* or4(char*, char*, char*, char*);
char* add_i(char*, int);
char* add(char*, char*);
char* sub(char*, char*);
char* and_i(char*, int);
char* lshift_i(char*, int);
char* rshift_i(char*, int);
char* array_i(char*, int);
char* array(char*, char*);
char* next(char*);
char* star(char*);
char* loop(int, char*, char*);
char* cond(int, char*, char*);
char* nop();
char* mkstr(char*);

#define MOORE 0
#define VON_NEUMANN 1

int space = 64;
int pipe_size = 9;
int pipe_step = 3;

int neighboor_cardinal[] = { /* MOORE */ 8, /* VON_NEUMANN */ 4, };

int moore() { return MOORE; }
int von_neumann() { return VON_NEUMANN; }

Named_Func neighboor_names[] = {
    "moore", moore,
    "von_neumann", von_neumann,
    0, 0,
};

int debug;
char* cmd_name;

char* usage =
    "[-x{size} <int>] [y{size} <int>] [-n{eighboor} moore|von_neumann] [-e{xtern} <int>] [-l{ocal} <int>] [-D{debug}]";

main(int ac, char** av)
{
    extern char *optarg;
    extern int optind;
    
    int c;
    int errflg;

    char* ret;
    int xsize;
    int ysize;
    int n_public_plane;
    int n_private_plane;
    char* neighboor_name;
    int (*neighboor_func)();
    int neighboor;

    cmd_name = av[0];
    errflg = 0;

    xsize = 256;
    ysize = 256;
    n_public_plane = 1;
    n_private_plane = 0;
    neighboor_name = "moore";

    while ((c = getopt(ac, av, "x:y:n:e:l:D")) != EOF) {
	switch (c) {
	  case 'x':
	    xsize = atoi(optarg);
	    break;
	  case 'y':
	    ysize = atoi(optarg);
	    break;
	  case 'n':
	    neighboor_name = malloc(strlen(optarg) + 1);
	    strcpy(neighboor_name, optarg);
	    break;
	  case 'e':
	    n_public_plane = atoi(optarg);
	    break;
	  case 'l':
	    n_private_plane = atoi(optarg);
	    break;
	  case 'D':
	    debug = 1;
	    break;
	  case '?':
	    ++errflg;
	}
    }
    
    if (errflg) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
	exit(1);
    }
    
    for (; optind < ac; optind++) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
    }

    neighboor_func = Named_Func_get(neighboor_names, neighboor_name);
    if (!neighboor_func) {
	fprintf(stderr, "%s: %s not found\n", cmd_name, neighboor_name);
	exit(1);
    }
    neighboor = neighboor_func();

    ret = cell(mkstr(neighboor_name),
	       mkstr("unsigned char"),
	       mkstr("past"),
	       mkstr("futur"),
	       mkstr("transition"),
	       mkstr("index"),
	       mkstr("local"),
	       mkstr("north"), mkstr("center"), mkstr("south"),
	       ysize,
	       xsize,
	       neighboor,
	       n_public_plane,
	       n_private_plane);

    printf("%s", ret);
    return 0;
}

char* cell(char* neighboor_name,
	   char* word,
	   char* past,
	   char* futur,
	   char* transition,
	   char* index,
	   char* local,
	   char* north, char* center, char* south,
	   int xsize,
	   int ysize,
	   int neighboor,
	   int n_public_plane,
	   int n_private_plane)
{
    char *ret;
    char* line;
    char* col;

    line = mkstr("line");
    col = mkstr("col");

    ret = declare(mk_cell_name(neighboor_name, xsize, ysize, n_public_plane, n_private_plane),
		  mk_cell_args(mk_arg_ptr(word, past),
			       mk_arg_ptr(word, futur),
			       mk_arg_ptr(word, transition),
			       mk_arg_int(mkstr("size")),
			       mk_arg_int(mkstr("side"))),
		  mk_cell_locals(mk_reg_ptr(word, north),
				 mk_reg_ptr(word, center),
				 mk_reg_ptr(word, south),
				 mk_reg_int(index),
				 mk_int(line),
				 mk_int(col)),
		  cell_body(past, futur, transition, index, local, north, center, south, line, col,
			    xsize, ysize, neighboor, n_public_plane, n_private_plane));
    return ret;
}

char* mk_cell_name(char* neighboor_name, int xsize, int ysize,
	     int n_private_plane, int n_public_plane)
{
    char *ret;

    ret = malloc(strlen(neighboor_name) + space);
    sprintf(ret, "%s_%d_%d_%d_%d", neighboor_name, xsize, ysize,
	    n_private_plane, n_public_plane);
    return ret;
}

char* mk_cell_args(char* past, char* futur, char* transition, char* size, char* side)
{
    char* ret;

    ret = malloc(strlen(past) + strlen(futur) + strlen(transition) + strlen(size) + strlen(side) + space);
    sprintf(ret, "%s, %s, %s, %s, %s", past, futur, transition, side, size);
    return ret;
}

char* mk_cell_locals(char* north, char* center, char* south, char* index, char* line, char* col)
{
    char* ret;
    
    ret = seq6(north, center, south, index, line, col);
    return ret;
}

char* cell_body(char* past,
		char* futur,
		char* transition,
		char* index,
		char* local,
		char* north, char* center, char* south,
		char* line, char* col,
		int xsize_i,
		int ysize_i,
		int neighboor,
		int n_public_plane,
		int n_private_plane)
{
    char* ret;
    char* side;
    char* size;
    int size_i;
    int reduce;
    
    side = mkstr("side");
    size = mkstr("size");

    reduce = 0;
    size_i = xsize_i * ysize_i;
    
    ret = seq3(seq4(set(north, cond(!reduce,
				    add(past, sub(size, side)),
				    add_i(past, size_i - xsize_i))),
		    set(center, past),
		    set(south, cond(!reduce,
			     add(center, side),
			     add_i(center, xsize_i))),
		    conex(futur, transition, index, local,
			  north, center, south, col,
			  xsize_i, neighboor, n_public_plane, n_private_plane)),
	       seq4(set(north, past),
		    set(center, cond(!reduce,
				     add(north, side),
				     add_i(north, xsize_i))),
		    set(south, cond(!reduce,
				    add(center, side),
				    add_i(center, xsize_i))),
		    loop(ysize_i - 2,
			 line,
			 conex(futur, transition, index, local,
			       north, center, south, col,
			       xsize_i, neighboor, n_public_plane, n_private_plane))),
	       seq4(set(north, cond(!reduce,
				    add(past, sub(size, lshift_i(side, 1))),
				    add_i(past, size_i - (xsize_i << 1)))),
		    set(center, cond(!reduce,
				     add(north, side),
				     add_i(north, xsize_i))),
		    set(south, past),
		    conex(futur, transition, index, local,
			  north, center, south, col,
			  xsize_i, neighboor, n_public_plane, n_private_plane)));
    
    return ret;
}

char* conex(char* futur,
	    char* transition,
	    char* index,
	    char* local,
	    char* north, char* center, char* south,
	    char* col,
	    int xsize_i,
	    int neighboor,
	    int n_public_plane,
	    int n_private_plane)
{
    char* ret;

    ret = seq3(first_col(futur, transition, index, local,
			 north, center, south,
			 xsize_i, neighboor, n_public_plane, n_private_plane),
	       cols(futur, transition, index, local,
		    north, center, south, col,
		    xsize_i, neighboor, n_public_plane, n_private_plane),
	       last_col(futur, transition, index, local,
			north, center, south,
			xsize_i, neighboor, n_public_plane, n_private_plane));
    return comment(mkstr("conex"),
		   ret);
}

char* first_col(char* futur,
		char* transition,
		char* index,
		char* local,
		char* north, char* center, char* south,
		int xsize_i,
		int neighboor,
		int n_public_plane,
		int n_private_plane)
{
    char* ret;
    
    ret = cond(n_private_plane,
	       seq3(set_first_local(local, center, neighboor, n_public_plane, n_private_plane),
		    set_first_col_index(north, center, south, index,
					xsize_i, n_public_plane, n_private_plane),
		    set_futur(futur, transition, local, index,
			      neighboor, n_public_plane, n_private_plane)),
	       seq2(set_first_col_index(north, center, south, index,
					xsize_i, n_public_plane, n_private_plane),
		    set_futur(futur, transition, local, index,
			      neighboor, n_public_plane, n_private_plane)));
    return comment(mkstr("first_col"),
		   ret);
}

char* cols(char* futur,
	   char* transition,
	   char* index,
	   char* local,
	   char* north, char* center, char* south,
	   char* col,
	   int xsize_i,
	   int neighboor,
	   int n_public_plane,
	   int n_private_plane)
{
    char* ret;
    
    ret = loop(xsize_i - 2,
	       col,
	       cond(n_private_plane,
		    seq3(set_local(local, center, neighboor, n_public_plane, n_private_plane),
			 set_col_index(north, center, south, index,
				       neighboor, n_public_plane, n_private_plane),
			 set_futur(futur, transition, local, index,
				   neighboor, n_public_plane, n_private_plane)),
		    seq2(set_col_index(north, center, south, index,
				       neighboor, n_public_plane, n_private_plane),
			 set_futur(futur, transition, local, index,
				   neighboor, n_public_plane, n_private_plane))));
    return comment(mkstr("cols"),
		   ret);
}

char* last_col(char* futur,
	       char* transition,
	       char* index,
	       char* local,
	       char* north, char* center, char* south,
	       int xsize_i,
	       int neighboor,
	       int n_public_plane,
	       int n_private_plane)
{
    char* ret;
    
    ret = cond(n_private_plane,
	       seq3(set_last_local(local, center, neighboor, n_public_plane, n_private_plane),
		    set_last_col_index(north, center, south, index,
				       xsize_i, neighboor, n_public_plane, n_private_plane),
		    set_futur(futur, transition, local, index,
			      neighboor, n_public_plane, n_private_plane)),
	       seq2(set_last_col_index(north, center, south, index,
				       xsize_i, neighboor, n_public_plane, n_private_plane),
		    set_futur(futur, transition, local, index,
			      neighboor, n_public_plane, n_private_plane)));
    return comment(mkstr("last_col"),
		   ret);
}

char* set_first_col_index(char* north,
			  char* center,
			  char* south,
			  char* index,
			  int xsize_i,
			  int n_public_plane,
			  int n_private_plane)
{
    char* ret;

    ret = seq3(set(index,
		   or3(get_index_part(array_i(north,
					    xsize_i - 1),
				      n_public_plane,
				      n_private_plane,
				      8),
		       get_index_part(array_i(center,
					    xsize_i - 1),
				      n_public_plane,
				      n_private_plane,
				      7),
		       get_index_part(array_i(south,
					    xsize_i - 1),
				      n_public_plane,
				      n_private_plane,
				      6))),
	       set(index,
		   or4(index,
		       get_index_part(next(north),
				      n_public_plane,
				      n_private_plane,
				      5),
		       get_index_part(next(center),
				      n_public_plane,
				      n_private_plane,
				      4),
		       get_index_part(next(south),
				      n_public_plane,
				      n_private_plane,
				      3))),
	       set(index,
		   or4(index,
		       get_index_part(next(north),
				      n_public_plane,
				      n_private_plane,
				      2),
		       get_index_part(cond(n_private_plane,
					   star(center),
					   next(center)),
				      n_public_plane,
				      n_private_plane,
				      1),
		       get_index_part(next(south),
				      n_public_plane,
				      n_private_plane,
				      0))));
    return comment(mkstr("set_first_col_index"),
		   ret);
}

char* set_col_index(char* north,
		    char* center,
		    char* south,
		    char* index,
		    int neighboor,
		    int n_public_plane,
		    int n_private_plane)
{
    char* ret;

    ret = set(index,
	      or4(cond(neighboor == MOORE,
		       and_i(lshift_i(index,
				  pipe_step * n_public_plane),
			   mask(pipe_size * n_public_plane)),
		       lshift_i(index,
			      pipe_step * n_public_plane)),
		  get_index_part(next(north),
				 n_public_plane,
				 n_private_plane,
				 2),
		  get_index_part(cond(n_private_plane,
				      star(center),
				      next(center)),
				 n_public_plane,
				 n_private_plane,
				 1),
		  get_index_part(next(south),
				 n_public_plane,
				 n_private_plane,
				 0)));
    return comment(mkstr("set_col_index"),
		   ret);
}

char* set_last_col_index(char* north,
			 char* center,
			 char* south,
			 char* index,
			 int xsize_i,
			 int neighboor,
			 int n_public_plane,
			 int n_private_plane)
{
    char* ret;

    ret = set(index,
	      or4(cond(neighboor == MOORE,
		       and_i(lshift_i(index,
				  pipe_step * n_public_plane),
			   mask(pipe_size * n_public_plane)),
		       lshift_i(index,
			      pipe_step * n_public_plane)),
		  get_index_part(array_i(north,
				       -xsize_i),
				 n_public_plane,
				 n_private_plane,
				 2),
		  get_index_part(array_i(center,
				       -xsize_i),
				 n_public_plane,
				 n_private_plane,
				 1),
		  get_index_part(array_i(south,
				       -xsize_i),
				 n_public_plane,
				 n_private_plane,
				 0)));
    return comment(mkstr("set_last_col_index"),
		   ret);
}

char* set_first_local(char* local,
		char* center,
		int neighboor,
		int n_public_plane,
		int n_private_plane)
{
    return set_local_common(local, center, neighboor, n_public_plane, n_private_plane, 0);
}

char* set_local(char* local,
		char* center,
		int neighboor,
		int n_public_plane,
		int n_private_plane)
{
    return set_local_common(local, center, neighboor, n_public_plane, n_private_plane, 1);
}

char* set_last_local(char* local,
		char* center,
		int neighboor,
		int n_public_plane,
		int n_private_plane)
{
    return set_local_common(local, center, neighboor, n_public_plane, n_private_plane, 1);
}

char* set_local_common(char* local,
			char* center,
			int neighboor,
			int n_public_plane,
			int n_private_plane,
			int incr)
{
    char* ret;

    ret = set(local,
	      lshift_i(and_i(cond(incr,
			      next(center),
			      star(center)),
			 mask(n_private_plane) << n_public_plane),
		     neighboor_cardinal[neighboor] * n_public_plane));
    return comment(mkstr("set_local"),
		   ret);
}

char* set_futur(char* futur,
		char* transition,
		char* local,
		char* index,
		int neighboor,
		int n_public_plane,
		int n_private_plane)
{
    char* ret;

    ret = set(next(futur),
	      array(transition,
			cond(n_private_plane,
			     or2(local,
				 use_index(index, neighboor, n_public_plane)),
			     use_index(index, neighboor, n_public_plane))));
    return comment(mkstr("set_futur"),
		   ret);
}

char* use_index(char* index,
		int neighboor,
		int n_public_plane)
{
    char* ret;

    ret = cond(neighboor == VON_NEUMANN,
	       or3(rshift_i(and_i(index,
			      mask(n_public_plane) << 1 * n_public_plane),
			  1 * n_public_plane),
		   rshift_i(and_i(index,
			      mask(3 * n_public_plane) << 3 * n_public_plane),
			  2 * n_public_plane),
		   rshift_i(and_i(index,
			      mask(n_public_plane) << 7 * n_public_plane),
			  3 * n_public_plane)),
	       index);

    return ret;
}

char* get_index_part(char* part,
		     int n_public_plane,
		     int n_private_plane,
		     int pos)
{
    char* ret;
    
    ret = cond(pos,
	       lshift_i(get_public(part,
				 n_public_plane,
				 n_private_plane),
		      pos * n_public_plane),
	       get_public(part,
			  n_public_plane,
			  n_private_plane));
    return ret;
}

char* get_public(char* public,
		 int n_public_plane,
		 int n_private_plane)
{
    char* ret;

    ret = cond(n_private_plane,
	       and_i(public,
		   mask(n_public_plane)),
	       public);
    return ret;
}

int mask(int n)
{
    return (1 << n) - 1;
}

char* declare(char* name, char* args, char* local, char* body)
{
    char* ret;

    ret = malloc(strlen(name) + strlen(args) + strlen(local) + strlen(body) + space);
    sprintf(ret, "%s(%s)\n{\n%s\n%s}\n", name, args, local, body);
    return ret;
}

char* mk_int(char* name)
{
    char* ret;
    
    ret = malloc(strlen(name) + space);
    sprintf(ret, "int %s;\n", name);
    return ret;
}

char* mk_reg_int(char* name)
{
    char* ret;
    
    ret = malloc(strlen(name) + space);
    sprintf(ret, "register int %s;\n", name);
    return ret;
}

char* mk_ptr(char* word, char* name)
{
    char* ret;

    ret = malloc(strlen(word) + strlen(name) + space);
    sprintf(ret, "%s* %s;\n", word, name);
    return ret;
}

char* mk_reg_ptr(char* word, char* name)
{
    char* ret;

    ret = malloc(strlen(word) + strlen(name) + space);
    sprintf(ret, "register %s* %s;\n", word, name);
    return ret;
}

char* mk_arg_ptr(char* word, char* name)
{
    char* ret;

    ret = malloc(strlen(word) + strlen(name) + space);
    sprintf(ret, "%s* %s", word, name);
    return ret;
}

char* mk_arg_int(char* name)
{
    char* ret;

    ret = malloc(strlen(name) + space);
    sprintf(ret, "int %s", name);
    return ret;
}

char* comment(char* c, char* s)
{
    char* ret;

    ret = malloc(strlen(c) + strlen(s) + space);
    sprintf(ret, "/* %s */\n%s", c, s);
    return ret;
}

char* seq1(char* s)
{
    char *ret;

    ret = malloc(strlen(s) + space);
    sprintf(ret, "%s", s);
    return ret;
}

char* seq2(char* s1, char* s2)
{
    char *ret;

    ret = malloc(strlen(s1) + strlen(s2) + space);
    sprintf(ret, "%s%s", s1, s2);
    return ret;
}

char* seq3(char* s1, char* s2, char* s3)
{
    char *ret;

    ret = malloc(strlen(s1) + strlen(s2) + strlen(s3) + space);
    sprintf(ret, "%s%s%s", s1, s2, s3);
    return ret;
}

char* seq4(char* s1, char* s2, char* s3, char* s4)
{
    char *ret;

    ret = malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + space);
    sprintf(ret, "%s%s%s%s", s1, s2, s3, s4);
    return ret;
}

char* seq5(char* s1, char* s2, char* s3, char* s4, char* s5)
{
    char *ret;

    ret = malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + strlen(s5) + space);
    sprintf(ret, "%s%s%s%s%s", s1, s2, s3, s4, s5);
    return ret;
}

char* seq6(char* s1, char* s2, char* s3, char* s4, char* s5, char* s6)
{
    char *ret;

    ret = malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + strlen(s5) + strlen(s6) + space);
    sprintf(ret, "%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6);
    return ret;
}

char* set(char* name, char* value)
{
    char* ret;
    
    ret = malloc(strlen(name) + strlen(value) + space);
    sprintf(ret, "%s = %s;\n", name, value);
    return ret;
}

char* or2(char* v1, char* v2)
{
    char* ret;
    
    ret = malloc(strlen(v1) + strlen(v2) + space);
    sprintf(ret, "(%s | %s)", v1, v2);
    return ret;
}

char* or3(char* v1, char* v2, char* v3)
{
    char* ret;
    
    ret = malloc(strlen(v1) + strlen(v2) + strlen(v3) + space);
    sprintf(ret, "(%s | %s | %s)", v1, v2, v3);
    return ret;
}

char* or4(char* v1, char* v2, char* v3, char* v4)
{
    char* ret;
    
    ret = malloc(strlen(v1) + strlen(v2) + strlen(v3) + strlen(v4) + space);
    sprintf(ret, "(%s | %s | %s | %s)", v1, v2, v3, v4);
    return ret;
}

char* and_i(char* name, int mask)
{
    char* ret;

    ret = malloc(strlen(name) + space);
    sprintf(ret, "(%s & 0x%x)", name, mask);
    return ret;
}

char* add_i(char* name, int n)
{
    char* ret;

    ret = malloc(strlen(name) + space);
    sprintf(ret, "(%s + %d)", name, n);
    return ret;
}

char* add(char* s1, char* s2)
{
    char* ret;

    ret = malloc(strlen(s1) + strlen(s2) + space);
    sprintf(ret, "(%s + %s)", s1, s2);
    return ret;
}

char* sub(char* s1, char* s2)
{
    char* ret;

    ret = malloc(strlen(s1) + strlen(s2) + space);
    sprintf(ret, "(%s - %s)", s1, s2);
    return ret;
}

char* lshift_i(char* name, int shift)
{
    char* ret;

    ret = malloc(strlen(name) + space);
    sprintf(ret, "(%s << %d)", name, shift);
    return ret;
}

char* rshift_i(char* name, int shift)
{
    char* ret;

    ret = malloc(strlen(name) + space);
    sprintf(ret, "(%s >> %d)", name, shift);
    return ret;
}

char* array_i(char* name, int index)
{
    char* ret;

    ret = malloc(strlen(name) + space);
    sprintf(ret, "%s[%d]", name, index);
    return ret;
}

char* array(char* name, char* index )
{
    char* ret;

    ret = malloc(strlen(name) + strlen(index) + space);
    sprintf(ret, "%s[%s]", name, index);
    return ret;
}

char* next(char* name)
{
    char* ret;

    ret = malloc(strlen(name) + space);
    sprintf(ret, "*%s++", name);
    return ret;
}

char* star(char* name)
{
    char* ret;

    ret = malloc(strlen(name) + space);
    sprintf(ret, "*%s", name);
    return ret;
}

char* loop(int n, char* index, char* str)
{
    char* ret;

    ret = malloc(strlen(str) + strlen(index) + space);
    sprintf(ret, "for (%s = %d; %s--;) {\n%s}\n", index, n, index, str);
    return ret;
}

char* cond(int test, char* true, char* false)
{
    char* ret;
    
    if (test) {
	ret = malloc(strlen(true) + 1);
	strcpy(ret, true);
    } else {
	ret = malloc(strlen(false) + 1);
	strcpy(ret, false);
    }
    return ret;
}

char* nop()
{
    static char* str = ";";
    char* ret;
    
    ret = malloc(strlen(str) + 1);
    strcpy(ret, str);
    return ret;
}

char* mkstr(char* str)
{
    char* ret;

    ret = malloc(strlen(str) + 1);
    strcpy(ret, str);
    return ret;
}
