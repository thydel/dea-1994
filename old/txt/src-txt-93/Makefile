SOURCES=.
SOURCES = \
	$(SOURCE)anneal.c-src \
	$(SOURCE)anneal.tcl-src \
	$(SOURCE)tube-worm.c-src \
	$(SOURCE)cas.tcl-src \
	$(SOURCE)conex.tcl-src \
	$(SOURCE)data.tcl-src \
	$(SOURCE)func.tcl-src

# TARGETS

top: $(SOURCES)

clean:
	rm *-src

# RULES

.SUFFIXES: .c-txt .c-src .tcl-txt .tcl-src

.c-txt.c-src:
	indent -kr -st < $*.c-txt > $*.c-src

.tcl-txt.tcl-src:
	cat $*.tcl-txt | sed -e 's/\\/\\\\/g' > $*.tcl-src
