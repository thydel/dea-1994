include $(CASDIR)/make/std-vars

INCLUDES = \
	-I$(CASDIR)/src/include \
	-I$(CASDIR)/src/lib \
	$(XINCLUDES) \
	-I$(TCLINCDIR)

CFLAGS = $(INCLUDES)
CC = gcc $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS)

LIBNAME = loop

SRCS = \
	simple.c

HEADERS = \
	simple.h

OBJS = $(SRCS:.c=.o)
EXECS = $(LIBNAME).a

top: $(LIBNAME).a

a: a.o
	$(CC) a.o

include $(CASDIR)/make/lib-targets

include $(CASDIR)/make/std-targets

# DO NOT DELETE THIS LINE -- make depend depends on it.

simple.o: /usr/include/stdio.h /usr/include/features.h
simple.o: /usr/include/sys/cdefs.h /usr/include/_G_config.h
simple.o: /usr/include/errno.h /usr/include/linux/errno.h
simple.o: /usr/include/string.h
simple.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h
simple.o: /usr/include/malloc.h /usr/include/assert.h
simple.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/varargs.h
simple.o: /usr/include/tcl/tclExtend.h /usr/include/tcl/tcl.h
simple.o: /home/uruk/thy/usr/cas/src/include/local.h
simple.o: /home/uruk/thy/usr/cas/src/include/magic.h
simple.o: /home/uruk/thy/usr/cas/src/lib/util/str.h
simple.o: /home/uruk/thy/usr/cas/src/lib/util/named.h
simple.o: /home/uruk/thy/usr/cas/src/lib/frame/frame.h
simple.o: /home/uruk/thy/usr/cas/src/lib/conex/conex.h
simple.o: /home/uruk/thy/usr/cas/src/lib/conex/func.h simple.h
