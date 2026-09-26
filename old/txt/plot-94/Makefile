PLOT=.
DATA=Data

PLOTS = \
	$(PLOT)/flip-deriv.ps \
	$(PLOT)/flip-prob.ps \
	$(PLOT)/flip-versus-prob.ps \
	$(PLOT)/flip.ps \
	$(PLOT)/lambda-deriv.ps \
	$(PLOT)/lambda-prob.ps \
	$(PLOT)/lambda-versus-prob.ps \
	$(PLOT)/lambda.ps \
	$(PLOT)/lambda-flip-hist.ps \
	$(PLOT)/lambda-versus-flip.ps \
	$(PLOT)/E-lambda-1.ps \
	$(PLOT)/lambda-flip-ratio-sorted.ps \
	$(PLOT)/lambda-flip-prob-sorted.ps

# TARGETS

top: $(PLOTS)

clean:
	rm -f *.ps

# PLOT DEPS

# $(PLOTS): $(DATA)/lamdba-flip.data

# DATA DEPS

# RULES

.SUFFIXES: .ps .plot .data .out

.out.data:
	$*.cmd $*

.plot.ps:
	gnuplot $*.plot
	mv $(PLOT)/tmp.ps $*.ps
