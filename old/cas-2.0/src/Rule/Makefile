SYSTEM := $(shell uname)

CC_OPTIM_FLAGS = -O2
CC_DEBUG_FLAGS = -g

RANLIB = ranlib

INCLUDES = -I..
DEFINES =

CFLAGS = $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS) $(INCLUDES) $(DEFINES)

LIBNAME = rule

SRCS_TO_BE_NAMED = \
	life.c \
	sum_tab.c \
	sum_stir_tab.c \
	lib.c

SRCS_NOT_TO_BE_NAMED = \
	named-func.c

SRCS = $(SRCS_TO_BE_NAMED) $(SRCS_NOT_TO_BE_NAMED)

HEADERS = \
	lib.h \
	conex.h

OBJS_TO_BE_NAMED = $(SRCS_TO_BE_NAMED:.c=.o)
OBJS_NOT_TO_BE_NAMED = $(SRCS_NOT_TO_BE_NAMED:.c=.o)
OBJS = $(OBJS_TO_BE_NAMED) $(OBJS_NOT_TO_BE_NAMED)

GENS = \
	named-func.txt

top: lib$(LIBNAME).a

lib$(LIBNAME).a: $(OBJS)
	ar r lib$(LIBNAME).a $(OBJS)
	$(RANLIB) lib$(LIBNAME).a

named-func.o: named-func.txt

named-func.txt: $(OBJS_TO_BE_NAMED)
ifeq ($(SYSTEM),sysv42)
	nm -p $(OBJS_TO_BE_NAMED) | grep ' T ' | cut -d' ' -f3 | \
		sed -e 's/\(.*\)/gen(\1)/' > named-func.txt
endif
ifeq ($(SYSTEM),Linux-non-ELF)
	nm $(OBJS_TO_BE_NAMED) | grep ' T ' | cut -d' ' -f3 | \
		sed -e 's/_\(.*\)/gen(\1)/' > named-func.txt
endif
ifeq ($(SYSTEM),Linux)
	nm $(OBJS_TO_BE_NAMED) | grep ' T ' | cut -d' ' -f3 | \
		sed -e 's/\(.*\)/gen(\1)/' > named-func.txt
endif
ifndef SYSTEM
	@echo no SYSTEM define; false
endif

depends:
	$(CC) $(INCLUDES) -M -E $(SRCS_TO_BE_NAMED) > depends.txt

clean:
	rm -f $(OBJS) $(GENS) *~ core

clobber: clean
	rm -f lib$(LIBNAME).a

