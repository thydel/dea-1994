#	tsum-128x3-rel.ps 
top: life-00.eps anneal-00.eps anneal-01.eps anneal-02.eps anneal-03.eps \
	superglider.eps \
	tsum-128x3-diag.ps \
	tsum-128x3-trans-bits.ps \
	tsum-128x3-trans-byte.ps \
	tsum-128x3-relmovedge.ps \
	tsum-128x3-faces.ps \
	anneal-256x3-diag.ps \
	anneal-256x3-trans-bits.ps \
	anneal-256x3-rel.ps \
	life-256x3-trans-bits.ps \
	life-256x3-rel.ps \
	life-256x3-relmov.ps \
	cantata-1.ps \
	cantata-cell.ps \
	cantata-mk-rule.ps \
	qmean-9-128.ps \
	qmean-9-256.ps \
	qmean-9-300.ps \
	qmean-9-384.ps \
	qmean-9-512.ps \
	anneal-256-rel.ps \
	tsum-128x3-diag-1.ps \
	tsum-128-trans-byte.ps \
	tsum-128-trans-bits.ps \
	tsum-128-faces.ps

life-00.eps: life-00.margin life-00.scale
anneal-00.eps: anneal-00.margin anneal-00.scale

anneal-01.eps: anneal-01-1.eps anneal-01-2.eps
	tgif anneal-01.obj
	tgif -print -eps anneal-01.obj

anneal-01-1.eps: anneal-01-1.margin anneal-01-1.scale
anneal-01-2.eps: anneal-01-2.margin anneal-01-2.scale

anneal-02.eps: anneal-02-1.eps anneal-02-2.eps
	tgif anneal-02.obj
	tgif -print -eps anneal-02.obj

anneal-02-1.eps: anneal-02-1.margin anneal-02-1.scale
anneal-02-2.eps: anneal-02-2.margin anneal-02-2.scale

anneal-03.eps: anneal-03.margin anneal-03.scale

%.eps: %.ps
	ps2epsi $< $@

%.ppm: %.wd
	xwdtopnm $< > $@

%.pgm: %.ppm
	ppmtopgm $< > $@

%.ps: %.pbm
	if [ -f $*.margin ]; then pnmmargin `cat $*.margin` $< > $*-margin.pbm; \
	else ln -s $< $*-margin.pbm; fi
	if [ -f $*.scale ]; then pnmtops -noturn -s `cat $*.scale` $*-margin.pbm > $@; \
	else pnmtops -noturn $*-margin.pbm > $@; fi
	rm $*-margin.pbm

%.ps: %.pgm
	pnmtops -noturn $< > $@

# %.ps: %.pnm
#	pnmtops -noturn $< > $@

