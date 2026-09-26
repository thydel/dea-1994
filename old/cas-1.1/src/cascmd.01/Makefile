include $(CASDIR)/make/std-vars

INCLUDES = \
	-I$(CASDIR)/src/include \
	-I$(CASDIR)/src/lib \
	$(XINCLUDES) \
	-I$(TCLINCDIR)

DEFINES = \
	-DTCL_DEFAULT=\"/usr/local/lib/tcldefault\"

#DEFINES = \
#	-DTCL_DEFAULT=\"/solair/people/thy/local/lib/tcldefault\"

CFLAGS = $(INCLUDES) $(DEFINES)
CC = gcc $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS)

CMDNAME = newbin

SRCS = \
	tclXAppInit.c \
	init.c \
	named-func.c

HEADERS =

#	$(CASDIR)/src/lib/loop/loop.a 
#	$(CASDIR)/src/lib/conex/conex.a
CELL_LIBS = \
	$(CASDIR)/src/lib/disp/disp.a \
	$(CASDIR)/src/lib/frame/frame.a \
	$(CASDIR)/src/lib/extract/extract.a \
	$(CASDIR)/src/lib/conexlib/conexlib.a \
	$(CASDIR)/src/lib/rule/rule.a \
	$(CASDIR)/src/lib/util/util.a \
	$(CASDIR)/src/lib/new/new.a \
	$(CASDIR)/src/lib/util/util.a \
	$(PBMLIBDIR)/libpgm.a \
	$(PBMLIBDIR)/libpbm.a \
	$(TCLLIBDIR)/libtcl.a \
	$(TCLLIBDIR)/libtclx.a

LIBS = $(CELL_LIBS) $(XLIBS)

OBJS = $(SRCS:.c=.o)
EXECS = $(CMDNAME)

top: $(CMDNAME)

$(CMDNAME): $(CELL_LIBS)

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
named-func.o: /home/uruk/thy/usr/cas/src/lib/util/named.h
