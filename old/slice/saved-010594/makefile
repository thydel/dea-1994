CFLAGS = -g

OBJS = main.o tools.o manip.o cublib.o debug.o

cub: $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f cub $(OBJS)

cublib.o : cublib.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/assert.h debug.h magic.h cublib.h 
debug.o : debug.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/assert.h debug.h 
main.o : main.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/sys/types.h /usr/include/linux/types.h \
  /usr/include/fcntl.h /usr/include/linux/fcntl.h /usr/include/unistd.h /usr/include/posix_opt.h \
  /usr/include/gnu/types.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/malloc.h /usr/include/assert.h debug.h magic.h cublib.h manip.h 
manip.o : manip.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/assert.h debug.h magic.h cublib.h 
oldcub.o : oldcub.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/assert.h 
tools.o : tools.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/assert.h debug.h magic.h cublib.h 
