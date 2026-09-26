CFLAGS = -g -O2

EXES = cub xmovie

top: $(EXES)

CUB_OBJS = main.o tools.o cublib.o debug.o

cub: $(CUB_OBJS)
	$(CC) -o $@ $(CUB_OBJS)

XMOVIE_OBJS = xmovie.o

xmovie:	$(XMOVIE_OBJS)
	$(CC) $(XMOVIE_OBJS) -lX11 -lm -o $(@)

xmovie.o: xmovie.c
	$(CC) -w -DMERLIN -DTHY -c xmovie.c

OBJS = $(CUB_OBJS) $(XMOVIE_OBJS)

clean:
	rm -f $(EXES) $(OBJS)

cublib.o : cublib.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/assert.h debug.h magic.h cublib.h 
debug.o : debug.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/assert.h debug.h 
tools.o : tools.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/malloc.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/assert.h debug.h magic.h cublib.h tools.h 
xmovie.o : xmovie.c /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/_G_config.h /usr/include/sys/time.h /usr/include/linux/types.h \
  /usr/include/linux/time.h /usr/include/time.h /usr/include/sys/types.h /usr/include/X11/Xos.h \
  /usr/include/X11/Xosdefs.h /usr/include/string.h /usr/lib/gcc-lib/i486-linux/2.4.5/include/stddef.h \
  /usr/include/fcntl.h /usr/include/linux/fcntl.h /usr/include/unistd.h /usr/include/posix_opt.h \
  /usr/include/gnu/types.h /usr/include/X11/Xlib.h /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h \
  /usr/include/X11/Xutil.h /usr/include/X11/Xatom.h 
