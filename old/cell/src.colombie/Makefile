CC=gcc
#CFLAGS=-g -O2 -m486 -I/usr/X386/include
CFLAGS=-g -O2 -I/usr/include/X11
#XLIBS=-lm -lX11 -lsocket -lnsl
XLIBS=-lm -lX11

GENS= \
	moore-128-128-1-0.c \
	moore-256-256-1-0.c \
	moore-256-256-2-0.c \
	von-neumann-256-256-1-0.c \
	von-neumann-256-256-2-0.c \
	von-neumann-64-64-3-0.c \
	von-neumann-256-256-3-0.c \
	von-neumann-256-256-4-0.c \
	extract_lib.c

OBJS= \
	cell.o \
	mk-frame.o \
	mk-table.o \
	xdump.o \
	xdump-1.o \
	xdump-2.o \
	xdump-Z8.o \
	xdisp.o \
	extract.o \
	skip.o \
	iter.o \
	compil.o \
	rules.o \
	neighbor.o \
	getword.o \
	named_func.o \
	io.o \
	cmap.o \
	misc.o \
	visual.o \
	xstrings.o \
	extract_lib.o \
	moore-128-128-1-0.o \
	moore-256-256-1-0.o \
	moore-256-256-2-0.o \
	von-neumann-256-256-1-0.o \
	von-neumann-256-256-2-0.o \
	von-neumann-64-64-3-0.o \
	von-neumann-256-256-3-0.o \
	von-neumann-256-256-4-0.o

EXES=cell mk-frame mk-table xdump xdump-1 xdump-2 xdump-Z8 xdisp extract iter skip compil gen_extract

top: $(EXES)

CELL_OBJS= \
	cell.o \
	moore-256-256-1-0.o \
	moore-256-256-2-0.o \
	moore-128-128-1-0.o \
	von-neumann-256-256-1-0.o \
	von-neumann-256-256-2-0.o \
	von-neumann-64-64-3-0.o \
	von-neumann-256-256-3-0.o \
	von-neumann-256-256-4-0.o \
	extract_lib.o

cell: $(CELL_OBJS)
	$(CC) -o $@ $(CELL_OBJS)

FOO_OBJS= \
	foo.o \
	visual.o \
	xstrings.o

foo: $(FOO_OBJS)
	$(CC) -o $@ $(FOO_OBJS) $(XLIBS)

moore-128-128-1-0.c: compil
	compil -x 128 -y 128 | cb > moore-128-128-1-0.c

moore-256-256-1-0.c: compil
	compil | cb > moore-256-256-1-0.c

moore-256-256-2-0.c: compil
	compil -e 2 | cb > moore-256-256-2-0.c

von-neumann-256-256-1-0.c: compil
	compil -n von_neumann | cb > von-neumann-256-256-1-0.c

von-neumann-256-256-2-0.c: compil
	compil -n von_neumann -e 2 | cb > von-neumann-256-256-2-0.c

von-neumann-64-64-3-0.c: compil
	compil -x 64 -y 64 -n von_neumann -e 3 | cb > von-neumann-64-64-3-0.c

von-neumann-256-256-3-0.c: compil
	compil -n von_neumann -e 3 | cb > von-neumann-256-256-3-0.c

von-neumann-256-256-4-0.c: compil
	compil -n von_neumann -e 4 | cb > von-neumann-256-256-4-0.c

mk-frame: mk-frame.o getword.o named_func.o
	$(CC) -o $@ mk-frame.o getword.o named_func.o

mk-table: mk-table.o rules.o named_func.o neighbor.o
	$(CC) -o $@ mk-table.o rules.o named_func.o neighbor.o

xdump: xdump.o cmap.o misc.o visual.o xstrings.o
	$(CC) -o $@ xdump.o cmap.o misc.o visual.o xstrings.o $(XLIBS)

xdump-1: xdump-1.o cmap.o misc.o visual.o xstrings.o
	$(CC) -o $@ xdump-1.o cmap.o misc.o visual.o xstrings.o $(XLIBS)

xdump-2: xdump-2.o cmap.o misc.o visual.o xstrings.o
	$(CC) -o $@ xdump-2.o cmap.o misc.o visual.o xstrings.o $(XLIBS)

xdump-Z8: xdump-Z8.o cmap.o misc.o visual.o xstrings.o
	$(CC) -o $@ xdump-Z8.o cmap.o misc.o visual.o xstrings.o $(XLIBS)

xdisp: xdisp.o cmap.o misc.o
	$(CC) -o $@ xdisp.o cmap.o misc.o $(XLIBS)

extract: extract.o io.o extract_lib.o
	$(CC) -o $@ extract.o io.o extract_lib.o

extract_lib.c: gen_extract
	gen_extract > extract_lib.c

skip: skip.o
	$(CC) -o $@ $?

iter: iter.o
	$(CC) -o $@ $?

compil: compil.o named_func.o
	$(CC) -o $@ compil.o named_func.o

clean:
	rm -f $(OBJS) $(GENS) *~ core

clobber: clean
	rm -f $(EXES) fff ttt *.dat

rmexe:
	rm -f $(EXES)

named_func.o: named_func.h
neighbor.o: neighbor.h
mk-table.o: neighbor.h
