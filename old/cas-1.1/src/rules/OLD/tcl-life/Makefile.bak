include $(CASDIR)/make/std-vars

INCLUDES = \
	-I$(CASDIR)/include \
	$(XINCLUDES) \
	-I$(TCLINCDIR)

DEFINES = \
	-DTCL_DEFAULT=\"/usr/local/lib/tcldefault\"

CFLAGS = $(INCLUDES) $(DEFINES)
CC = gcc $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS)

CMDNAME = life

SRCS = \
	tclXAppInit.c \
	cmd.c \
	life.c

HEADERS =

CELL_LIBS = \
	$(CASDIR)/lib/conex.a \
	$(CASDIR)/lib/disp.a \
	$(CASDIR)/lib/frame.a \
	$(CASDIR)/lib/extract.a \
	$(CASDIR)/lib/util.a \
	$(TCLLIB)/libtcl.a

LIBS = $(CELL_LIBS) $(XLIBS)

OBJS = $(SRCS:.c=.o)
EXECS = $(CMDNAME)

top: $(CMDNAME)

SIMPLE_SRCS = \
	simple.c \
	cmd.c \
	life.c

SIMPLE_OBJS = $(SIMPLE_SRCS:.c=.o)

simple: $(SIMPLE_OBJS)
	$(CC) $(CFLAGS) $(SIMPLE_OBJS) $(LIBS) -o simple

include $(CASDIR)/make/bin-targets

include $(CASDIR)/make/std-targets

# DO NOT DELETE THIS LINE -- make depend depends on it.

tclXAppInit.o: /usr/include/tcl/tclExtend.h /usr/include/stdio.h
tclXAppInit.o: /usr/include/features.h /usr/include/sys/cdefs.h
tclXAppInit.o: /usr/include/_G_config.h /usr/include/tcl/tcl.h
tclXAppInit.o: /usr/include/math.h /usr/include/huge_val.h
tclXAppInit.o: /usr/include/endian.h /usr/include/bytesex.h
tclXAppInit.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/float.h
tclXAppInit.o: /usr/include/values.h
cmd.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
cmd.o: /usr/include/_G_config.h /usr/include/errno.h
cmd.o: /usr/include/linux/errno.h /usr/include/string.h
cmd.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h
cmd.o: /usr/include/tcl/tcl.h /usr/include/malloc.h /usr/include/assert.h
cmd.o: /usr/X386/include/X11/Xlib.h /usr/include/sys/types.h
cmd.o: /usr/include/linux/types.h /usr/X386/include/X11/X.h
cmd.o: /usr/X386/include/X11/Xfuncproto.h /usr/X386/include/X11/Xosdefs.h
cmd.o: /usr/X386/include/X11/Xutil.h
