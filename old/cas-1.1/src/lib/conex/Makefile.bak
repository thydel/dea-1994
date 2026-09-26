include $(CASDIR)/make/std-vars

INCLUDES = \
	-I$(CASDIR)/src/include \
	-I$(CASDIR)/src/lib \
	$(XINCLUDES) \
	-I$(TCLINCDIR)

CFLAGS = $(INCLUDES)
CC = cc $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS)

LIBNAME = conex

SRCS = \
	conex.c \
	func.c

HIDE =

HEADERS = \
	conex.h \
	func.h

OBJS = $(SRCS:.c=.o)
EXECS = $(LIBNAME).a

top: $(LIBNAME).a

include $(CASDIR)/make/lib-targets

include $(CASDIR)/make/std-targets

# DO NOT DELETE THIS LINE -- make depend depends on it.

conex.o: /usr/include/malloc.h /usr/include/features.h
conex.o: /usr/include/sys/cdefs.h
conex.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h
conex.o: /usr/include/assert.h
conex.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/varargs.h
conex.o: /usr/include/tcl/tclExtend.h /usr/include/stdio.h
conex.o: /usr/include/_G_config.h /usr/include/tcl/tcl.h
conex.o: /home/uruk/thy/usr/cas/src/include/local.h
conex.o: /home/uruk/thy/usr/cas/src/include/magic.h
conex.o: /home/uruk/thy/usr/cas/src/lib/util/named.h conex.h
func.o: /usr/include/malloc.h /usr/include/features.h
func.o: /usr/include/sys/cdefs.h
func.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h
func.o: /usr/include/assert.h /usr/include/tcl/tclExtend.h
func.o: /usr/include/stdio.h /usr/include/_G_config.h /usr/include/tcl/tcl.h
func.o: /home/uruk/thy/usr/cas/src/include/local.h
func.o: /home/uruk/thy/usr/cas/src/include/magic.h
func.o: /home/uruk/thy/usr/cas/src/lib/util/named.h
func.o: /home/uruk/thy/usr/cas/src/lib/frame/frame.h conex.h func.h
