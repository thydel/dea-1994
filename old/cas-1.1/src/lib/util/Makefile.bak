include $(CASDIR)/make/std-vars

INCLUDES = \
	-I$(CASDIR)/src/include \
	-I$(CASDIR)/src/lib

CFLAGS = $(INCLUDES)
CC = gcc $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS)

LIBNAME = util

SRCS = \
	named.c \
	str.c \
	io.c

HEADERS = \
	io.h \
	str.h \
	named.h

OBJS = $(SRCS:.c=.o)
EXECS = $(LIBNAME).a

top: $(LIBNAME).a

include $(CASDIR)/make/lib-targets

include $(CASDIR)/make/std-targets

# DO NOT DELETE THIS LINE -- make depend depends on it.

named.o: /usr/include/malloc.h /usr/include/features.h
named.o: /usr/include/sys/cdefs.h
named.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h
named.o: /usr/include/assert.h named.h
str.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/varargs.h
str.o: /usr/include/malloc.h /usr/include/features.h /usr/include/sys/cdefs.h
str.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h
str.o: /usr/include/assert.h str.h
