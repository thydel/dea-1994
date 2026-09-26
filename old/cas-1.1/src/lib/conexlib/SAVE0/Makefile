include $(CASDIR)/make/std-vars

INCLUDES = -I$(CASDIR)/include
CFLAGS = $(INCLUDES)
CC = gcc $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS)

LIBNAME = conex

SRCS = \
	moore.c \
	bind.c \
	trans.c

HIDE = \
	vn.c \
	moore-t.c

HEADERS = \
	bind.h \
	conex.h \
	conex_mac.h \
	moore-t.h \
	moore.h \
	trans.h \
	vn.h

OBJS = $(SRCS:.c=.o)
EXECS = $(LIBNAME).a

top: $(LIBNAME).a

include $(CASDIR)/make/lib-targets

include $(CASDIR)/make/std-targets

# debug

D = moore.c
1.c: $(D)
	$(CC) -E $(CFLAGS) $(D) | cpb > 1.c

# DO NOT DELETE THIS LINE -- make depend depends on it.

moore.o: /usr/include/assert.h /ching/people/thy/work/cell/include/local.h
moore.o: /ching/people/thy/work/cell/include/magic.h
moore.o: /ching/people/thy/work/cell/include/frame/frame.h conex.h
moore.o: conex_mac.h moore.h /ching/people/thy/work/cell/include/util/named.h
moore.o: bind.h
trans.o: /usr/include/malloc.h /usr/include/assert.h
trans.o: /ching/people/thy/work/cell/include/local.h
trans.o: /ching/people/thy/work/cell/include/magic.h
trans.o: /ching/people/thy/work/cell/include/frame/frame.h conex.h trans.h
