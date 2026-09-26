CFLAGS = -O2 -g

top: gapp tst

GAPP_SRCS = \
	gapp-main.c \
	gapp-tst.c \
	gapp-step.c \
	gapp-sim.c \
	gapp-pe.c \
	gapp-apply.c \
	gapp-arch.c \
	bit-field.c \
	space.c \
	getopt.c \
	getopt1.c

GAPP_OBJS = $(GAPP_SRCS:.c=.o)

gapp: $(GAPP_OBJS)
	$(CC) -o $@ $(GAPP_OBJS)

gapp-apply.c: gapp-apply.head gapp-apply.txt
	cat gapp-apply.head gapp-apply.txt > gapp-apply.c

gapp-apply.txt: gapp-apply.m4
	m4 --prefix-builtins gapp-apply.m4 | sed -e '/^#/d' -e '/^$$/d' > gapp-apply.txt

tst: \
	tst-01.go \
	tst-02.go \
	tst-03.go \
	tst-04.go

depends:
	$(CC) -E -M $(subst gapp-apply.c,,$(GAPP_SRCS)) > dependencies

%.go: %.gas
	awk -f gapp-as.awk $< > $@

%.gas: %.mgas
	m4 < $< | gas-clean.sh > $@

clean:
	rm -f $(GAPP_OBJS) *.go gapp-apply.c gapp-apply.txt *~

clobber: clean
	rm -f gapp gapp-pe.t gapp-inst-set.txt gapp-pe.txt

# dependencies

include dependencies
