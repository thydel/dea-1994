include $(CASDIR)/make/std-vars

INCLUDES =
CFLAGS = $(INCLUDES)
CC = gcc $(CC_DEBUG_FLAGS) $(CC_OPTIM_FLAGS)

CMDNAME = iter

SRCS = \
	$(CMDNAME).c

HEADERS =

CELL_LIBS =

LIBS =

OBJS = $(SRCS:.c=.o)
EXECS = $(CMDNAME)

top: $(CMDNAME)

include $(CASDIR)/make/bin-targets

include $(CASDIR)/make/std-targets

# DO NOT DELETE THIS LINE -- make depend depends on it.
