CFLAGS = -O2 -g

GAPP_SRCS = \
	gapp-main.c \
	gapp-tst.c \
	gapp-sim.c \
	gapp-pe.c \
	gapp-apply.c \
	gapp-arch.c \
	bit-field.c \
	space.c \
	getopt.c \
	getopt1.c \

GAPP_OBJS = $(GAPP_SRCS:.c=.o)

gapp: $(GAPP_OBJS)
	$(CC) -o $@ $(GAPP_OBJS)

gapp-apply.c: gapp-apply.head gapp-apply.txt
	cat gapp-apply.head gapp-apply.txt > gapp-apply.c

gapp-apply.txt: gapp-apply.m4
	m4 --prefix-builtins gapp-apply.m4 | sed -e '/^#/d' -e '/^$$/d' > gapp-apply.txt

tst: tst-01.go

%.go: %.gas
	awk -f gapp-as.awk $< > $@

clean:
	rm -f $(GAPP_OBJS) gapp-apply.c gapp-apply.txt *~

clobber: clean
	rm -f gapp gapp-pe.t gapp-inst-set.txt gapp-pe.txt

# dependencies

bit-field.o : bit-field.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/assert.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  bit-field.h 
gapp-arch.o : gapp-arch.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h bit-field.h gapp-defs.h gapp-arch.h 
gapp-main.o : gapp-main.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/assert.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/getopt.h bit-field.h gapp-defs.h gapp-arch.h gapp-pe.h gapp-sim.h \
  space.h 
gapp-pe.o : gapp-pe.c /usr/include/sys/types.h /usr/include/linux/types.h /usr/include/sys/mman.h \
  /usr/include/features.h /usr/include/sys/cdefs.h /usr/include/stdio.h /usr/include/_G_config.h \
  /usr/include/assert.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  bit-field.h gapp-defs.h gapp-arch.h gapp-pe.h 
gapp-sim.o : gapp-sim.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/assert.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  bit-field.h gapp-defs.h gapp-arch.h gapp-pe.h gapp-sim.h 
getopt.o : getopt.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h 
getopt1.o : getopt1.c getopt.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/_G_config.h 
space.o : space.c space.h 
speedtst.o : speedtst.c 
