C_SRCS = \
	c-anneal.c \
	c-tube-worm.c \
	c-qmean.c \
	c-gapp-pe-pe.c \
	c-gapp-pe-tbl.c \
	c-gapp-pe-h.c \
	c-gapp-arch-h.c

CLIT_SRCS = \
	c-gapp-arch.clit \
	c-gapp-arch-alu.clit

TCL_SRCS = \
	tcl-anneal.tcl \
	tcl-cas.tcl \
	tcl-conex.tcl \
	tcl-data.tcl \
	tcl-func.tcl

# TARGETS

C_TEX = $(C_SRCS:.c=.tex)

CLIT_TEX = $(CLIT_SRCS:.clit=.tex)

TCL_TEX = $(TCL_SRCS:.tcl=.tex)

top: $(C_TEX) $(CLIT_TEX) $(TCL_TEX)

clean:
	rm -f *.tex *~nn

# RULES

.SUFFIXES: .tex .tcl .clit

.clit.tex:
	c2latex $*.clit > $*.tex

.c.tex:
	lgrind -i $*.c > $*.tex

.tcl.tex:
	lgrind -i -ltcl $*.tcl > $*.tex
	
.c.ckr:
	indent -kr -st < $*.c > $*.ckr
