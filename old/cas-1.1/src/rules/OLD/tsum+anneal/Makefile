#OPTIM = -O2 -m486
DEBUG = -g
INCLUDE= -I../../lib -I/usr/X386/include
CFLAGS= $(INCLUDE)
CC=gcc $(DEBUG) $(OPTIM)

XLIBS=-lm -lX11 -lsocket -lnsl

CMDNAME = life
OBJS = main.o life.o anneal.o tsum.o
LIBS = \
	../../lib/conex/conex.a \
	../../lib/disp/disp.a \
	../../lib/frame/frame.a \
	../../lib/extract/extract.a \
	../../lib/util/util.a

top: $(CMDNAME)

$(CMDNAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(XLIBS)

clean:
	rm -f $(OBJS) *~

# DO NOT DELETE THIS LINE -- make depend depends on it.
