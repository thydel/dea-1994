PLOT=.
DATA=Data

PLOTS = \
	$(PLOT)/anneal-pop.ps \
	$(PLOT)/anneal-pop-detail.ps \
	$(PLOT)/heart-pop.ps \
	$(PLOT)/heart-pop-detail.ps \
	$(PLOT)/anneal-sum.ps \
	$(PLOT)/lifex.ps \
	$(PLOT)/rabbit-gnans-1.ps \
	$(PLOT)/rabbit-gnans-2.ps \
	$(PLOT)/rabbit-1.ps \
	$(PLOT)/rabbit-1-512.ps \
	$(PLOT)/rabbit-2.ps \
	$(PLOT)/rabbit-3.ps \
	$(PLOT)/lifex-sum-1.ps \
	$(PLOT)/lifex-sum-2.ps
# TARGETS

top: $(PLOTS)

clean:
	rm -f *.ps

# PLOT DEPS

$(PLOT)/exemple-1.ps: $(DATA)/exemple-1.data
$(PLOT)/exemple-2.ps: $(DATA)/exemple-1.data
$(PLOT)/exemple-3.ps: $(DATA)/exemple-2.data
$(PLOT)/exemple-4.ps: $(DATA)/exemple-2.data
$(PLOT)/anneal-sum.ps: $(DATA)/anneal-sum.data
$(PLOT)/lifex.ps: $(DATA)/lifex-hist.data
$(PLOT)/rabbit-gnans-1.ps: $(DATA)/rabbit-gnans-1.data
$(PLOT)/rabbit-gnans-2.ps: $(DATA)/rabbit-gnans-2.data
$(PLOT)/rabbit-1.ps: $(DATA)/rabbit-1-hist.data
$(PLOT)/rabbit-1-512.ps: $(DATA)/rabbit-1-512-hist.data
$(PLOT)/rabbit-2.ps: $(DATA)/rabbit-2-hist.data
$(PLOT)/rabbit-3.ps: $(DATA)/rabbit-3-hist.data
$(PLOT)/lifex-sum-1.ps : $(DATA)/lifex-sum-1.data
$(PLOT)/lifex-sum-2.ps : $(DATA)/lifex-sum-2.data

# DATA DEPS

$(DATA)/lifex-hist.data: \
	$(DATA)/lifex-hist.cmd \
	$(DATA)/xor-sum.cmd \
	$(DATA)/xor-sum.awk

# RULES

.SUFFIXES: .ps .plot .data .out

.out.data:
	$*.cmd $*

.plot.ps:
	gnuplot $*.plot
	mv $(PLOT)/tmp.ps $*.ps
