include $(CASDIR)/make/std-vars

INCLUDES = \
	-I$(CASDIR)/src/include \
	-I$(CASDIR)/src/lib \
	$(XINCLUDES) \
	-I$(TCLINCDIR)

CFLAGS = $(INCLUDES)
CC = gcc $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS)

LIBNAME = disp

SRCS = \
	xdumper_mono.c

HEADERS = \
	xdumper_mono.h

OBJS = $(SRCS:.c=.o)
EXECS = $(LIBNAME).a

top: $(LIBNAME).a

include $(CASDIR)/make/lib-targets

include $(CASDIR)/make/std-targets

# DO NOT DELETE THIS LINE -- make depend depends on it.

xdumper_mono.o: /usr/include/malloc.h /usr/include/features.h
xdumper_mono.o: /usr/include/sys/cdefs.h
xdumper_mono.o: /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h
xdumper_mono.o: /usr/include/assert.h /usr/X386/include/X11/Xlib.h
xdumper_mono.o: /usr/include/sys/types.h /usr/include/linux/types.h
xdumper_mono.o: /usr/X386/include/X11/X.h /usr/X386/include/X11/Xfuncproto.h
xdumper_mono.o: /usr/X386/include/X11/Xosdefs.h /usr/include/tcl/tclExtend.h
xdumper_mono.o: /usr/include/stdio.h /usr/include/_G_config.h
xdumper_mono.o: /usr/include/tcl/tcl.h
xdumper_mono.o: /home/uruk/thy/usr/cas/src/include/local.h
xdumper_mono.o: /home/uruk/thy/usr/cas/src/include/magic.h
xdumper_mono.o: /home/uruk/thy/usr/cas/src/lib/frame/frame.h xdumper_mono.h
