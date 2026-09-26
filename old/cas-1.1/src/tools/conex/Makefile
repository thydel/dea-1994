include $(CASDIR)/make/std-vars

INCLUDES = \
	-I$(CASDIR)/include \
	$(XINCLUDES) \
	-I/usr/local/include \
	-I$(TCLDIR)/tcl6.1 \
	-I$(TCLDIR)/extended/src

DEFINES = \
	-DTCL_DEFAULT=\"/usr/local/lib/tcldefault\"

CFLAGS = $(INCLUDES)
CC = gcc $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS)

CMDNAME = conex

SRCS = \
	$(CMDNAME).c \
	run.c \
	bind.c \
	cgen.c \
	str.c

HEADERS =

CELL_LIBS = $(CASDIR)/lib

LIBS = $(CELL_LIBS)/util.a

OBJS = $(SRCS:.c=.o)
EXECS = $(CMDNAME)

top: $(CMDNAME)

tst: conex
	conex | cb > xxx

include $(CASDIR)/make/bin-targets

include $(CASDIR)/make/std-targets

# DO NOT DELETE THIS LINE -- make depend depends on it.

conex.o: /usr/include/stdio.h /usr/include/stdlib.h
conex.o: /home/faust/thy/cell/include/util/named.h
run.o: /usr/include/stdio.h /usr/include/varargs.h /usr/include/malloc.h
run.o: /usr/include/assert.h cgen.h
bind.o: /usr/include/stdio.h /usr/include/varargs.h /usr/include/malloc.h
bind.o: /usr/include/assert.h cgen.h
cgen.o: /usr/include/stdio.h /usr/include/varargs.h /usr/include/malloc.h
cgen.o: /usr/include/assert.h cgen.h
