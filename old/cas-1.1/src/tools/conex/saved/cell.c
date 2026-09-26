#include <stdio.h>
#include <varargs.h>
#include <malloc.h>
#include <assert.h>

#include "str.h"
#include "cgen.h"
#include "cell.h"

int _conex_cnt[] = { /* MOORE */ 8, /* VON_NEUMANN */ 4, };
int _pipe_size = 9;
int _pipe_step = 3;

char* conex_name;
int _conex;
int _size;
int _xsize;
int _ysize;
int _public;
int _private;
int _stat;
int _reduce;

STR(rule_vect);
STR(past_frame);
STR(futur_frame);
STR(rule_sum_vect);
STR(hor_sum_vect);
STR(vert_sum_frame);
STR(rule);
STR(past);
STR(futur);
STR(rule_sum);
STR(hor_sum);
STR(vert_sum);
STR(north);
STR(center);
STR(south);
STR(line);
STR(col);
STR(xsize);
STR(ysize);
STR(side);
STR(size);
STR(index);
STR(local);
STR(StateVect);
STR(StateFrame);
STR(CntVect);
STR(CntFrame);

char* fptr = "ptr";

char* State = "unsigned char";
char* Cnt = "int";

char* lf = "\n";

char* cell() {
    if (_reduce) {
	size = eval(_xsize * _ysize);
	xsize = eval(_xsize);
	ysize = eval(_ysize);
    }
    return declare(cell_name(),
		   list(ptr(StateVect, rule_vect),
			ptr(StateFrame, past_frame),
			ptr(StateFrame, futur_frame),
			cond(_stat, ptr(CntVect, rule_sum_vect), nul),
			cond(_stat, ptr(CntVect, hor_sum_vect), nul),
			cond(_stat, ptr(CntFrame, vert_sum_frame), nul),
			nil),
		   seq(ptr(State, past),
		       ptr(State, futur),
		       ptr(State, rule),
		       cond(_stat, ptr(Cnt, rule_sum), nul),
		       cond(_stat, ptr(Cnt, hor_sum), nul),
		       cond(_stat, ptr(Cnt, vert_sum), nul),
		       rptr(State, north),
		       rptr(State, center),
		       rptr(State, south),
		       rptr(State, index),
		       cond(_private, rptr(State, local), nul),
		       var(Cnt, xsize),
		       var(Cnt, ysize),
		       var(Cnt, size),
		       var(Cnt, line),
		       var(Cnt, col),
		       nil),
		   cell_body());
}

char* cell_name() {
    return strn(buf, sprintf(buf, "%s_%d_%d_%d", conex_name, _public, _private, _stat));
}

char* cell_body() {
    return append(cell_init(), lf, do_lines(), nil);
}

char* cell_init() {
    return seq(set(past, field(past_frame, fptr)),
	       set(futur, field(futur_frame, fptr)),
	       set(rule, field(rule_vect, fptr)),
	       set(xsize, field(past_frame, xsize)),
	       set(ysize, field(past_frame, ysize)),
	       set(size, field(past_frame, size)),
	       nil);
}

char* do_lines() {
    return append(cmnt("FIRST LINE", first_line()),
		  cmnt("MID_LINES", mid_lines()),
		  cmnt("LAST LINE", last_line()),
		  nil);
}

char* first_line() {
    return append(seq(set(north, add(past, sub(size, xsize))),
		      set(center, past),
		      set(south, add(center, xsize)),
		      nil),
		  do_cols(),
		  nil);
}

char* mid_lines() {
    return append(seq(set(north, past),
		      set(center, add(north, xsize)),
		      set(south, add(center, xsize)),
		      nil),
		  loop(sub(ysize, eval(2)), line, do_cols()),
		  nil);
}

char* last_line() {
    return append(seq(set(north, add(past, sub(size, lshift(xsize, eval(1))))),
		      set(center, add(north, xsize)),
		      set(south, past),
		      nil),
		  do_cols(),
		  nil);
}

char* do_cols() {
    return append(cmnt("FIRST COL", first_col()),
		  cmnt("MID_COLS", mid_cols()),
		  cmnt("LAST COL", last_col()),
		  nil);
}

char* first_col() {
    return seq(cond(_private, set_first_local(), nul),
	       set_first_col_index(),
	       set_futur(),
	       nil);
}

char* mid_cols() {
    return loop(sub(xsize, eval(2)), col,
		seq(cond(_private, set_local(), nul),
		    set_col_index(),
		    set_futur(),
		    nil));
}

char* last_col() {
    return seq(cond(_private, set_last_local(), nul),
	       set_last_col_index(),
	       set_futur(),
	       nil);
}

char* set_first_col_index() {
    return cmnt("SET FIRST COL INDEX",
		set(index, or(get_index(array(north, sub(xsize, eval(1))), 8),
			      get_index(array(center, sub(xsize, eval(1))), 7),
			      get_index(array(south, sub(xsize, eval(1))), 6),
			      get_index(next(north), 5),
			      get_index(next(center), 4),
			      get_index(next(south), 3),
			      get_index(next(north), 2),
			      get_index(cond(_private, star(center), next(center)), 1),
			      get_index(next(south), 0),
			      nil)));
}

char* set_col_index() {
    return cmnt("SET COL INDEX",
		set(index, or(cond(_conex == MOORE,
				   and(lshift(index, eval(_pipe_step * _public)),
				       eval(mask(_pipe_size * _public))),
				   lshift(index, eval(_pipe_step * _public))),
			      get_index(next(north), 2),
			      get_index(cond(_private, star(center), next(center)), 1),
			      get_index(next(south), 0),
			      nil)));
}

char* set_last_col_index() {
    return cmnt("SET LAST COL INDEX",
		set(index, or(cond(_conex == MOORE,
				   and(lshift(index, eval(_pipe_step * _public)),
				       eval(mask(_pipe_size * _public))),
				   lshift(index, eval(_pipe_step * _public))),
			      get_index(array(north, uminus(xsize)), 2),
			      get_index(array(center, uminus(xsize)), 1),
			      get_index(array(south, uminus(xsize)), 0),
			      nil)));
}

char* set_first_local() {
    return set_local_common(0);
}

char* set_local() {
    return set_local_common(1);
}

char* set_last_local() {
    return set_local_common(1);
}

char* set_local_common(int incr) {
    return cmnt("SET LOCAL",
		set(local,
		    lshift(and(cond(incr,
				    next(center),
				    star(center)),
			       eval(mask(_private) << _public)),
			   eval(_conex_cnt[_conex] * _public))));
}

char* set_futur() {
    return cmnt("SET FUTUR",
		set(next(futur), array(rule, cond(_private,
						  or(local, use_index(), nil),
						  use_index()))));
}
    
char* use_index() {
    return cond(_conex == VON_NEUMANN,
		or(rshift(and(index, eval(mask(_public) << _public)),
			  eval(_public)),
		   rshift(and(index, eval(mask(3 * _public) << 3 * _public)),
			  eval(2 * _public)),
		   rshift(and(index, eval(mask(_public) << 7 * _public)),
			  eval(3 * _public)),
		   nil),
		index);
}

char* get_index(char* e, int n) {
    return cond(n,
		lshift(get_public(e), eval(n * _public)),
		get_public(e));
}

char* get_public(char* e) {
    return cond(_private, and(e, eval(mask(_public))), e);
}

int mask(int n) {
    return (1 << n) - 1;
}

