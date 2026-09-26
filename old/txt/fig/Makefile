PS=Ps
FIGURE=.
FIGURES = \
	$(FIGURE)/func-1.ps \
	$(FIGURE)/func-2.ps \
	$(FIGURE)/func-3.ps \
	$(FIGURE)/func-4.ps \
	$(FIGURE)/func-7.ps \
	$(FIGURE)/apply-1.ps \
	$(FIGURE)/apply-2.ps \
	$(FIGURE)/gap.ps \
	$(FIGURE)/gap-pe.ps \
	$(FIGURE)/life-tree.ps \
	$(FIGURE)/life-dfa.ps

# TARGETS

top: $(FIGURES)

clean:
	rm -f *~ *.ps

# FIG DEPS

$(FIGURE)/func-1.pic: $(FIGURE)/func-1.scale
$(FIGURE)/func-2.pic: $(FIGURE)/func-2.scale
$(FIGURE)/func-3.pic: $(FIGURE)/func-3.scale
$(FIGURE)/func-4.pic: $(FIGURE)/func-4.scale
$(FIGURE)/apply-1.pic: $(FIGURE)/apply-1.scale
$(FIGURE)/apply-2.pic: $(FIGURE)/apply-2.scale

$(FIGURE)/func-1.ps: $(FIGURE)/func-1.scale
$(FIGURE)/func-2.ps: $(FIGURE)/func-2.scale
$(FIGURE)/func-3.ps: $(FIGURE)/func-3.scale
$(FIGURE)/func-4.ps: $(FIGURE)/func-4.scale
#$(FIGURE)/func-5.ps: $(FIGURE)/func-5.scale
$(FIGURE)/func-7.ps: $(FIGURE)/func-7.scale
$(FIGURE)/apply-1.ps: $(FIGURE)/apply-1.scale
$(FIGURE)/apply-2.ps: $(FIGURE)/apply-2.scale
$(FIGURE)/gap.ps: $(FIGURE)/gap.scale
$(FIGURE)/gap-pe.ps: $(FIGURE)/gap-pe.scale
$(FIGURE)/life-tree.ps: $(FIGURE)/life-tree.scale
$(FIGURE)/life-dfa.ps: $(FIGURE)/life-dfa.scale

# RULES

.SUFFIXES: .pic .fig .ps

.fig.pic:
	if [ -f $*.scale ]; then fig2dev -L pic -m `cat $*.scale` $*.fig > $*.pic; \
	else fig2dev -L pic $*.fig > $*.pic; fi

.fig.ps:
	if [ -f $*.scale ]; then fig2dev -L ps -m `cat $*.scale` $*.fig > $*.ps; \
	else fig2dev -L ps $*.fig > $*.ps; fi
	$(PS)/fig2dev-post.sh $*.ps
