include $(CASDIR)/make/std-vars

INCLUDES = -I$(CASDIR)/include $(XINCLUDES)
CFLAGS = $(INCLUDES)
CC = gcc $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS)

CMDNAME = life

SRCS = \
	main.c \
	loop.c \
	life.c

HEADERS =

CELL_LIBS = \
	$(CASDIR)/lib/conex.a \
	$(CASDIR)/lib/disp.a \
	$(CASDIR)/lib/frame.a \
	$(CASDIR)/lib/extract.a \
	$(CASDIR)/lib/util.a

LIBS = $(CELL_LIBS) $(XLIBS)

OBJS = $(SRCS:.c=.o)
EXECS = $(CMDNAME)

top: $(CMDNAME)

include $(CASDIR)/make/bin-targets

include $(CASDIR)/make/std-targets

# DO NOT DELETE THIS LINE -- make depend depends on it.

main.o: /usr/include/stdio.h /usr/include/fcntl.h /usr/include/sys/types.h
main.o: /usr/include/sys/fcntl.h /usr/include/malloc.h loop.h
loop.o: /usr/include/malloc.h /usr/include/assert.h
loop.o: /usr/local/home/thy/work/cell/include/local.h
loop.o: /usr/local/home/thy/work/cell/include/magic.h
loop.o: /usr/local/home/thy/work/cell/include/frame/frame.h
loop.o: /usr/local/home/thy/work/cell/include/conex/conex.h
loop.o: /usr/local/home/thy/work/cell/include/conex/trans.h
loop.o: /usr/local/home/thy/work/cell/include/extract/extract.h
loop.o: /usr/local/home/thy/work/cell/include/disp/xdumper_mono.h
loop.o: /usr/local/home/thy/work/cell/include/disp/xdumper.h
life.o: /usr/local/home/thy/work/cell/include/local.h
life.o: /usr/local/home/thy/work/cell/include/magic.h
life.o: /usr/local/home/thy/work/cell/include/conex/bind.h
life.o: /usr/local/home/thy/work/cell/include/frame/frame.h
life.o: /usr/local/home/thy/work/cell/include/conex/conex.h
