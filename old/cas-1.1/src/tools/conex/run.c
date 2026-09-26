#include <stdio.h>
#include <varargs.h>
#include <malloc.h>
#include <assert.h>

#include "local.h"
#include "util/str.h"
#include "frame/frame.h"
#include "conex/conex_spec.h"
#include "cgen.h"
#include "run.h"

int _conex_cnt[] = { /* MOORE */ 8, /* VON_NEUMANN */ 4, };
int _pipe_size = 9;
int _pipe_step = 3;

char* conex_name;

CVAR(_conex);
CVAR(_size);
CVAR(_xsize);
CVAR(_ysize);
CVAR(_public);
CVAR(_private);
CVAR(_stat);
CVAR(_reduce);

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
STR(ptr);
STR(State);
STR(Cnt);

char* lf = "\n";

char* run(ConexSpec* spec) {
    assert(spec->cnt >= 1 && spec->cnt <= 2);
    if (spec->ptr[0]->info->type == MOORE) {
	_conex = MOORE;
    } else if (spec->ptr[0]->info->type == VN) {
	_conex = VN;
    } else {
	assert(0);
    }
    _public = spec->ptr[0]->size;
    if (spec->cnt == 2) {
	assert(spec->ptr[1]->info->type == LOCAL);
	_private = spec->ptr[1]->size;
    }
    return _run()
}

char* _run() {
    if (_reduce) {
	size = eval(_xsize * _ysize);
	xsize = eval(_xsize);
	ysize = eval(_ysize);
    }
    return Cdeclare(cell_name(),
		   Clist(Cptr(StateVect, rule_vect),
			Cptr(StateFrame, past_frame),
			Cptr(StateFrame, futur_frame),
			cond(_stat, Cptr(CntVect, rule_sum_vect), nul),
			cond(_stat, Cptr(CntVect, hor_sum_vect), nul),
			cond(_stat, Cptr(CntFrame, vert_sum_frame), nul),
			nil),
		   Cseq(Cptr(State, past),
		       Cptr(State, futur),
		       Cptr(State, rule),
		       cond(_stat, Cptr(Cnt, rule_sum), nul),
		       cond(_stat, Cptr(Cnt, hor_sum), nul),
		       cond(_stat, Cptr(Cnt, vert_sum), nul),
		       Crptr(State, north),
		       Crptr(State, center),
		       Crptr(State, south),
		       Crptr(State, index),
		       cond(_private, Crptr(State, local), nul),
		       Cvar(Cnt, xsize),
		       Cvar(Cnt, ysize),
		       Cvar(Cnt, size),
		       Cvar(Cnt, line),
		       Cvar(Cnt, col),
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
    return Cseq(Cset(past, Cfield(past_frame, ptr)),
	       Cset(futur, Cfield(futur_frame, ptr)),
	       Cset(rule, Cfield(rule_vect, ptr)),
	       Cset(xsize, Cfield(past_frame, xsize)),
	       Cset(ysize, Cfield(past_frame, ysize)),
	       Cset(size, Cfield(past_frame, size)),
	       nil);
}

char* do_lines() {
    return append(Ccmnt("FIRST LINE", first_line()),
		  Ccmnt("MID_LINES", mid_lines()),
		  Ccmnt("LAST LINE", last_line()),
		  nil);
}

char* first_line() {
    return append(Cseq(Cset(north, Cadd(past, Csub(size, xsize))),
		      Cset(center, past),
		      Cset(south, Cadd(center, xsize)),
		      nil),
		  do_cols(),
		  nil);
}

char* mid_lines() {
    return append(Cseq(Cset(north, past),
		      Cset(center, Cadd(north, xsize)),
		      Cset(south, Cadd(center, xsize)),
		      nil),
		  Cloop(Csub(ysize, eval(2)), line, do_cols()),
		  nil);
}

char* last_line() {
    return append(Cseq(Cset(north, Cadd(past, Csub(size, Clshift(xsize, eval(1))))),
		      Cset(center, Cadd(north, xsize)),
		      Cset(south, past),
		      nil),
		  do_cols(),
		  nil);
}

char* do_cols() {
    return append(Ccmnt("FIRST COL", first_col()),
		  Ccmnt("MID_COLS", mid_cols()),
		  Ccmnt("LAST COL", last_col()),
		  nil);
}

char* first_col() {
    return Cseq(cond(_private, set_first_local(), nul),
	       set_first_col_index(),
	       set_futur(),
	       nil);
}

char* mid_cols() {
    return Cloop(Csub(xsize, eval(2)), col,
		Cseq(cond(_private, set_local(), nul),
		    set_col_index(),
		    set_futur(),
		    nil));
}

char* last_col() {
    return Cseq(cond(_private, set_last_local(), nul),
	       set_last_col_index(),
	       set_futur(),
	       nil);
}

char* set_first_col_index() {
    return Ccmnt("SET FIRST COL INDEX",
		Cset(index, Cor(get_index(Carray(north, Csub(xsize, eval(1))), 8),
			      get_index(Carray(center, Csub(xsize, eval(1))), 7),
			      get_index(Carray(south, Csub(xsize, eval(1))), 6),
			      get_index(Cnext(north), 5),
			      get_index(Cnext(center), 4),
			      get_index(Cnext(south), 3),
			      get_index(Cnext(north), 2),
			      get_index(cond(_private, Cstar(center), Cnext(center)), 1),
			      get_index(Cnext(south), 0),
			      nil)));
}

char* set_col_index() {
    return Ccmnt("SET COL INDEX",
		Cset(index, Cor(cond(_conex == MOORE,
				   Cand(Clshift(index, eval(_pipe_step * _public)),
				       eval(mask(_pipe_size * _public))),
				   Clshift(index, eval(_pipe_step * _public))),
			      get_index(Cnext(north), 2),
			      get_index(cond(_private, Cstar(center), Cnext(center)), 1),
			      get_index(Cnext(south), 0),
			      nil)));
}

char* set_last_col_index() {
    return Ccmnt("SET LAST COL INDEX",
		Cset(index, Cor(cond(_conex == MOORE,
				   Cand(Clshift(index, eval(_pipe_step * _public)),
				       eval(mask(_pipe_size * _public))),
				   Clshift(index, eval(_pipe_step * _public))),
			      get_index(Carray(north, Cuminus(xsize)), 2),
			      get_index(Carray(center, Cuminus(xsize)), 1),
			      get_index(Carray(south, Cuminus(xsize)), 0),
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
    return Ccmnt("SET LOCAL",
		Cset(local,
		    Clshift(Cand(cond(incr,
				    Cnext(center),
				    Cstar(center)),
			       eval(mask(_private) << _public)),
			   eval(_conex_cnt[_conex] * _public))));
}

char* set_futur() {
    return Ccmnt("SET FUTUR",
		Cset(Cnext(futur), Carray(rule, cond(_private,
						  Cor(local, use_index(), nil),
						  use_index()))));
}
    
char* use_index() {
    return cond(_conex == VON_NEUMANN,
		Cor(Crshift(Cand(index, eval(mask(_public) << _public)),
			  eval(_public)),
		   Crshift(Cand(index, eval(mask(3 * _public) << 3 * _public)),
			  eval(2 * _public)),
		   Crshift(Cand(index, eval(mask(_public) << 7 * _public)),
			  eval(3 * _public)),
		   nil),
		index);
}

char* get_index(char* e, int n) {
    return cond(n,
		Clshift(get_public(e), eval(n * _public)),
		get_public(e));
}

char* get_public(char* e) {
    return cond(_private, Cand(e, eval(mask(_public))), e);
}

int mask(int n) {
    return (1 << n) - 1;
}

