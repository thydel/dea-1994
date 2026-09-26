LATEX = latex

top: 20may.dvi

# top: all.dvi

view: all.dvi 
	xdvi -paper a4 $<

all.dvi: qwf \
	all.tex \
	pg-notes.tex \
	rule-space.tex \
	thy-notes.tex \
	objects.tex \
	all.bbl

clean:
	rm -f *.tex *.aux *.log *.bbl *.blg *.dvi

%: %.l
	$(LEX.l) $< > $@.c
	$(COMPILE.c) $@.c
	$(LINK.c) $@.o $(LOADLIBES) $(LDLIBS) -lfl -o $(dir $<)$@
	@$(RM) $@.[co]

%.bbl: %.aux
	bibtex $*

%.tex: %.qwf
	qwf < $< > $@

%.dvi %.aux: %.tex
	$(LATEX) $<
