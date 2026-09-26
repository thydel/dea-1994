export CC_OPTIM_FLAGS = -O2
export CC_DEBUG_FLAGS = -g

export RANLIB = ranlib

X11TOPDIR = /usr/X11R6
X11INCDIR = $(X11TOPDIR)/include
X11LIBDIR = $(X11TOPDIR)/lib

TCLINCDIR = /usr/include
TCLLIBDIR = /usr/lib

PBMINCDIR = /usr/include
PBMLIBDIR = /usr/lib

LOCALLIBDIR = /usr/uruk/lib
LOCALINCDIR = /usr/uruk/include

XXX = -DTcl_HandleAlloc=TclX_HandleAlloc -DTcl_HandleXlate=TclX_HandleXlate -DTcl_HandleTblInit=TclX_HandleTblInit

CFLAGS = $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS) $(INCLUDES) $(DEFINES) $(XXX)

INCLUDES = -I$(TCLINCDIR) -I$(PBMINCDIR) -I$(LOCALINCDIR) -I$(X11INCDIR)
DEFINES =

CMDNAME = casbin

DIRLIST = \
	Conex \
	Rule

SRCS = \
	conex.c \
	dump.c \
	extract.c \
	frame.c \
	func.c \
	init.c \
	named.c \
	named-func.c \
	simple.c \
	space.c \
	str.c \
	time.c \
	tkXAppInit.c \
	util.c

HEADERS = \
	conex.h \
	dump.h \
	extract.h \
	frame.h \
	func.h \
	magic.h \
	named.h \
	simple.h \
	space.h \
	str.h \
	time.h \
	util.h

CAS_LIBS = Conex/libconex.a Rule/librule.a 
PBM_LIBS = -L$(PBMLIBDIR) -lpgm -lpbm
TCL_LIBS = -L$(TCLLIBDIR) -ltkx -ltk -ltclx -ltcl -litcl -lBLT
#LOCAL_LIBS = -L$(LOCALLIBDIR) -ltcldbg
#X11_LIBS = -L$(X11LIBDIR) -lX11
X11_LIBS = -L$(X11LIBDIR) -lX11
SYS_LIBS = -lieee -lm

LIBS = $(CAS_LIBS) $(PBM_LIBS) $(LOCAL_LIBS) $(TCL_LIBS) $(X11_LIBS) $(SYS_LIBS)

OBJS = $(SRCS:.c=.o)

top: top_dirs $(CMDNAME)

$(CMDNAME): $(OBJS)
	$(CC) -o $(CMDNAME) $(OBJS) $(LIBS)

depends: depends_dirs
	$(CC) $(INCLUDES) -M -E $(SRCS) > depends.txt

clean: clean_dirs
	rm -f $(OBJS) *~ core

clobber: clean clobber_dirs
	rm -f $(CMDNAME)

clean_dirs clobber_dirs depends_dirs top_dirs:
	@for i in $(DIRLIST); do cd $$i; $(MAKE) $(subst _dirs,,$@); cd ..; done

include depends.txt
