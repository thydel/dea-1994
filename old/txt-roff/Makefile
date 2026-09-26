#	mm/others.mm
MM = \
	mm/top.mm \
	mm/cover.mm \
	mm/head.mm \
	mm/intro.mm \
	mm/newintro.mm \
	mm/about-ca.mm \
	mm/objects.mm \
	mm/obj-space.mm \
	mm/obj-time.mm \
	mm/obj-law.mm \
	mm/rules.mm \
	mm/annexes.mm \
	mm/abstract.mm \
	mm/lexik.mm \
	mm/conclusion.mm \
	mm/tail.mm

MAC = \
	mac/bib.mac \
	mac/mymm.mac \
	mac/thy.mac

TABLES = \
	tbl/neighburhood-size.tbl \
	tbl/neighburhood-size-1.tbl \
	tbl/neighburhood-size-2.tbl \
	tbl/space-size.tbl \
	tbl/compute-time-100kcps.tbl \
	tbl/compute-time-10mcps.tbl \
	tbl/lifex-sum-1.tbl \
	tbl/lifex-sum-2.tbl

FIGURES = \
	fig/func-1.ps \
	fig/func-2.ps \
	fig/func-3.ps \
	fig/func-4.ps \
	fig/func-7.ps \
	fig/apply-1.ps \
	fig/apply-2.ps \
	fig/gap.ps \
	fig/gap-pe.ps \
	fig/life-tree.ps \
	fig/life-dfa.ps

PLOTS = \
	plot/anneal-pop.ps \
	plot/anneal-pop-detail.ps \
	plot/heart-pop.ps \
	plot/heart-pop-detail.ps \
	plot/anneal-sum.ps \
	plot/lifex.ps \
	plot/rabbit-gnans-1.ps \
	plot/rabbit-gnans-2.ps \
	plot/rabbit-1.ps \
	plot/rabbit-1-512.ps \
	plot/rabbit-2.ps \
	plot/rabbit-3.ps \
	plot/lifex-sum-1.ps \
	plot/lifex-sum-2.ps

#	dump/anneal-sum-1k4k8k-he.ps
DUMPS = \
	dump/anneal.ps \
	dump/anneal-g128-s11.ps \
	dump/tube-worm-mix.ps \
	dump/anneal-sum.ps \
	dump/tsum-grey.ps \
	dump/tsum.ps \
	dump/life-time-xor.ps \
	dump/anneal-time-xor.ps \
	dump/lifex-sum-1.ps \
	dump/lifex-sum-2.ps \
	dump/loop-1024.ps \
	dump/anneal-sum-1k-8k-xv.ps \
	dump/anneal-sum-1k-8k.ps \
	dump/tsum-ray-one.ps \
	dump/tsum-ray-all.ps \
	dump/neighburhood-size-tbl-16xor9.ps \
	dump/tsum-128-edge.ps \
	dump/cas-cmd-1.ps \
	dump/cas-dump.ps \
	dump/anneal-3d.ps \
	dump/life-3d.ps \
	dump/lifex-3d.ps \
	dump/xu-photo-1.ps \
	dump/xu-photo-1-top.ps \
	dump/xu-film-1-1.ps \
	dump/xu-film-1-2.ps \
	dump/xu-Cfilm-1-1.ps \
	dump/xu-Cfilm-1-2.ps \
	dump/xu-Cfilm-2-1.ps \
	dump/xu-Cfilm-2-2.ps \
	dump/dummy.ps

SOURCES = \
	src/anneal.c-src \
	src/anneal.tcl-src \
	src/tube-worm.c-src \
	src/cas.tcl-src \
	src/conex.tcl-src \
	src/data.tcl-src \
	src/func.tcl-src

REFERS = \
	ref/bib.ref.i

ALLS = $(MM) $(MAC) $(TABLES) $(FIGURES) $(PLOTS) $(DUMPS) $(SOURCES) $(REFERS)

default: top

all: top.ps top.ditroff top.ascii top.tty top.prn top.lj

GXDITVIEW_GEOMETRY = 660x740
GXDITVIEW = -P-geometry -P$(GXDITVIEW_GEOMETRY)

# lp -dlj -o nobanner -T hplaserjet files
# rsh colombie /usr/local/bin/epelle < mm/file.mm

# TOP

top: top.gqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < top.gqwf | geqn -TX75 > top.tmp
	groff -mgm -z -TX75 < top.tmp
	groff -mgm $(GXDITVIEW) -TX75 < top.tmp

top.ps: top.gqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < top.gqwf | geqn -Tps > top.tmp
	groff -mgm -z -Tps < top.tmp
	groff -mgm -Tps < top.tmp > $@

top.dvi: top.gqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < top.gqwf | geqn -Tdvi > top.tmp
	groff -mgm -z -Tdvi < top.tmp
	groff -mgm -Tdvi < top.tmp > $@

top.pspage: top.ps
	IN=top; page=1; last_page=`grep '%%Pages:' $$IN.ps | head -1 | cut -f2 -d " "`; \
	echo $$last_page pages; \
	while [ $$page -le $$last_page ] ;\
	do \
		if [ $$page -lt 10 ] ; then page=`echo "00$$page"`; \
		else if [ $$page -lt 100 ] ; then page=`echo "0$$page"`; fi;fi; \
		OUT=spl/$${IN}_$$page.ps; echo $$OUT; psxlate -n $$page < $$IN.ps > $$OUT; \
		page=`expr $$page + 1`; \
	done

top.ditroff: top.gqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < top.gqwf | geqn -TX75 > top.tmp
	groff -mgm -z -TX75 < top.tmp
	groff -mgm -TX75 -Z < top.tmp > $@

top.ascii: top.aqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < top.aqwf | geqn -Tascii > top.tmp
	groff -mgm -z -P-buo -Tascii < top.tmp
	groff -mgm -P-buo -Tascii < top.tmp > $@

top.tty: top.aqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < top.aqwf | geqn -Tascii > top.tmp
	groff -mgm -z -Tascii < top.tmp
	groff -mgm -Tascii < top.tmp > $@

top.prn: top.aqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < top.aqwf | geqn -Tascii > top.tmp
	groff -mgm -z -P-f -Tascii < top.tmp
	groff -mgm -P-f -Tascii < top.tmp > $@

top.gqwf: qwf/gqwf $(ALLS)
	gsoelim mm/top.mm | qwf/gqwf | grefer > $@

top.aqwf: qwf/aqwf $(ALLS)
	gsoelim mm/top.mm | qwf/aqwf | grefer > $@

# PREVIEW AND PRINT

top.view: top.ditroff
	gxditview -geometry $(GXDITVIEW_GEOMETRY) top.ditroff

top.ul: top.tty
	xterm -geometry 96x35 -fn 8x16 -e sh -c 'ul top.tty | pg'

top.lj: top.ps
	cp top.ps lj
	cd lj; \
	gs -q -dNOPAUSE -sPAPERSIZE=a4 -sDEVICE=laserjet -r300 -sOutputFile=top-%02d.lj \
		top.ps quit.ps
	gs -q -dNOPAUSE -sPAPERSIZE=a4 -sDEVICE=laserjet -r300 -sOutputFile=top.lj \
		top.ps quit.ps

# JAN04

jan04: jan04.gqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < jan04.gqwf | geqn -TX75 > jan04.tmp
	groff -mgm -z -TX75 < jan04.tmp
	groff -mgm $(GXDITVIEW) -TX75 < jan04.tmp

jan04.ps: jan04.gqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < jan04.gqwf | geqn -Tps > jan04.tmp
	groff -mgm -z -Tps < jan04.tmp
	groff -mgm -Tps < jan04.tmp > $@

jan04.pspage: jan04.ps
	IN=jan04; page=1; last_page=`grep '%%Pages:' $$IN.ps | head -1 | cut -f2 -d " "`; \
	echo $$last_page pages; \
	while [ $$page -le $$last_page ] ;\
	do \
		if [ $$page -lt 10 ] ; then page=`echo "00$$page"`; \
		else if [ $$page -lt 100 ] ; then page=`echo "0$$page"`; fi;fi; \
		OUT=spl/$${IN}_$$page.ps; echo $$OUT; psxlate -n $$page < $$IN.ps > $$OUT; \
		page=`expr $$page + 1`; \
	done

jan04.ditroff: jan04.gqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < jan04.gqwf | geqn -TX75 > jan04.tmp
	groff -mgm -z -TX75 < jan04.tmp
	groff -mgm -TX75 -Z < jan04.tmp > $@

jan04.ascii: jan04.aqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < jan04.aqwf | geqn -Tascii > jan04.tmp
	groff -mgm -z -P-buo -Tascii < jan04.tmp
	groff -mgm -P-buo -Tascii < jan04.tmp > $@

jan04.tty: jan04.aqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < jan04.aqwf | geqn -Tascii > jan04.tmp
	groff -mgm -z -Tascii < jan04.tmp
	groff -mgm -Tascii < jan04.tmp > $@

jan04.prn: jan04.aqwf
	rm -f mm/references.tmp mm/references.qrf
	gtbl < jan04.aqwf | geqn -Tascii > jan04.tmp
	groff -mgm -z -P-f -Tascii < jan04.tmp
	groff -mgm -P-f -Tascii < jan04.tmp > $@

jan04.gqwf: qwf/gqwf mm/jan04.mm $(REFERS)
	gsoelim mm/jan04.mm | qwf/gqwf | grefer > $@

jan04.aqwf: qwf/aqwf mm/jan04.mm $(REFERS)
	gsoelim mm/jan04.mm | qwf/aqwf | grefer > $@

# TARGETS

clean:
	rm -f tmp/* lj/* *.lj *.tmp *.[ag]qwf *.ditroff *.ascii *.prn *.tty
	rm -f dump/*.ps fig/*.pic fig/*.ps plot/*.ps qwf/[ag]qwf ref/*.i tbl/*.tbl

clobber: clean
	rm -f *.ps spl/*

# REFER DEPS

ref/bib.ref.i: ref/bib.ref
	qwf/gqwf < ref/bib.ref > ref/bib.ref.qwf
	gindxbib ref/bib.ref.qwf
	mv ref/bib.ref.qwf.i ref/bib.ref.i
	chmod 644 ref/bib.ref.i

# TBLS DEPS

tbl/lifex-sum-1.tbl tbl/lifex-sum-2.tbl: tbl/texture.head tbl/texture.tail

# DUMPS DEPS

dump/anneal-time-xor.ps: dump/anneal-time-xor.scale
dump/life-time-xor.ps: dump/life-time-xor.scale
dump/loop-1024.ps: dump/loop-1024.scale

dump/anneal-sum-1k4k8k-he.ps: /usr/local/images/thy/anneal-sum-1k4k8k-he.ppm
	pnmtops -noturn -s 0.5 /usr/local/images/thy/anneal-sum-1k4k8k-he.ppm > $@

dump/tsum-128-edge.ps: tmp/tsum-128-edge.pbm
	pnmtops -s 0.5 -noturn tmp/tsum-128-edge.pbm > $@

tmp/tsum-128-edge.pbm: dump/tsum-128-edge-1.pbm dump/tsum-128-edge-2.pbm
	pnmcat -lr \
		dump/tsum-128-edge-0.pbm \
		tmp/vsep-256.pbm dump/tsum-128-edge-1.pbm \
		tmp/vsep-256.pbm dump/tsum-128-edge-2.pbm > $@

dump/neighburhood-size-tbl-16xor9.ps: dump/neighburhood-size-tbl-16xor9.pbm
	pnmtops -noturn dump/neighburhood-size-tbl-16xor9.pbm > $@

dump/tsum-ray-one.ps: dump/tsum-ray-one.pgm
	pnmtops -noturn dump/tsum-ray-one.pgm > $@

dump/tsum-ray-all.ps: dump/tsum-ray-all.pgm
	pnmtops -s 0.5 -noturn dump/tsum-ray-all.pgm > $@

dump/anneal-sum-1k-8k-xv.ps: dump/anneal-sum-1k-8k-xv.pgm
	pnmtops -s 0.5 -noturn dump/anneal-sum-1k-8k-xv.pgm > $@

dump/anneal-sum-1k-8k.ps: dump/anneal-sum-1k-8k.pgm
	pnmtops -s 0.5 -noturn dump/anneal-sum-1k-8k.pgm > $@

dump/anneal-sum.ps: tmp/anneal-sum.pgm
	pnmtops -s 0.5 -noturn tmp/anneal-sum.pgm > $@

ANNEAL_SUM_PGM_LIST = dump/anneal-sum-64.pgm tmp/vsep-256.pbm \
	dump/anneal-sum-64-xv.pgm tmp/vsep-256.pbm \
	dump/anneal-sum-64-xv1.pgm tmp/vsep-256.pbm \
	dump/anneal-sum-64-xv2.pgm

tmp/anneal-sum.pgm: $(ANNEAL_SUM_PGM_LIST)
	pnmcat -lr $(ANNEAL_SUM_PGM_LIST) > $@

dump/anneal.ps: tmp/anneal.pbm
	pnmtops -s 0.25 -noturn tmp/anneal.pbm > $@

tmp/anneal.pbm: dump/anneal-64.pbm tmp/vsep-256.pbm dump/anneal-256.pbm
	pnmcat -lr dump/anneal-64.pbm tmp/vsep-256.pbm dump/anneal-256.pbm > $@

# Comment out if want to include grey level file.
#dump/tsum-grey.ps: tmp/tsum-grey.pbm
#	pnmtops -noturn tmp/tsum-grey.pbm > $@

# Comment out if want to include bitmap level file.
dump/tsum-grey.ps: tmp/tsum-grey.pgm
	pnmtops -noturn tmp/tsum-grey.pgm > $@

dump/tsum.ps: tmp/tsum.pbm dump/tsum.scale
	pnmtops -s `cat dump/tsum.scale` -noturn tmp/tsum.pbm > dump/tsum.ps

TSUM_PBM_LIST = dump/tsum-8.pbm dump/tsum-16.pbm dump/tsum-32.pbm dump/tsum-64.pbm \
	dump/tsum-128.pbm dump/tsum-256.pbm dump/tsum-512.pbm dump/tsum-1024.pbm

tmp/tsum.pbm: $(TSUM_PBM_LIST) tmp/hsep-1024+7x12.pbm
	pnmcat -tb \
	`echo $(TSUM_PBM_LIST) | sed -e 's; dump/; tmp/hsep-1024+7x12.pbm dump/;g'` > $@

tmp/tsum-grey.pgm: tmp/tsum-e.pgm tmp/hsep-512+12.pbm tmp/tsum-r.pgm
	pnmcat -tb tmp/tsum-e.pgm tmp/hsep-512+12.pbm tmp/tsum-r.pgm > $@

tmp/tsum-e.pgm: dump/tsum-128-xv.pgm tmp/vsep-256.pbm dump/tsum-256-xv.pgm
	pnmcat -lr dump/tsum-128-xv.pgm tmp/vsep-256.pbm dump/tsum-256-xv.pgm > $@

tmp/tsum-r.pgm: dump/tsum-128-xvr.pgm tmp/vsep-256.pbm dump/tsum-256-xvr.pgm
	pnmcat -lr dump/tsum-128-xvr.pgm tmp/vsep-256.pbm dump/tsum-256-xvr.pgm > $@

tmp/vsep-256.pbm: tmp/vblack-256.pbm tmp/vwhite-256.pbm
	pnmcat -lr tmp/vwhite-256.pbm tmp/vblack-256.pbm tmp/vwhite-256.pbm > $@

tmp/vsep-128.pbm: tmp/vblack-128.pbm tmp/vwhite-128.pbm
	pnmcat -lr tmp/vwhite-128.pbm tmp/vblack-128.pbm tmp/vwhite-128.pbm > $@

tmp/hsep-256.pbm: tmp/hblack-256.pbm tmp/hwhite-256.pbm
	pnmcat -tb tmp/hwhite-256.pbm tmp/hblack-256.pbm tmp/hwhite-256.pbm > $@

tmp/hsep-128.pbm: tmp/hblack-128.pbm tmp/hwhite-128.pbm
	pnmcat -tb tmp/hwhite-128.pbm tmp/hblack-128.pbm tmp/hwhite-128.pbm > $@

tmp/hsep-512+12.pbm: tmp/hsep-256.pbm tmp/cross-12.pbm
	pnmcat -lr tmp/hsep-256.pbm tmp/cross-12.pbm tmp/hsep-256.pbm > $@

tmp/hsep-1024+7x12.pbm: tmp/hsep-128.pbm tmp/cross-12.pbm
	pnmcat -lr \
	tmp/hsep-128.pbm tmp/cross-12.pbm \
	tmp/hsep-128.pbm tmp/cross-12.pbm \
	tmp/hsep-128.pbm tmp/cross-12.pbm \
	tmp/hsep-128.pbm tmp/cross-12.pbm \
	tmp/hsep-128.pbm tmp/cross-12.pbm \
	tmp/hsep-128.pbm tmp/cross-12.pbm \
	tmp/hsep-128.pbm tmp/cross-12.pbm \
	tmp/hsep-128.pbm > $@

tmp/dot-12.pbm:
	pbmmake -black 12 12 > $@

tmp/cross-12.pbm: tmp/wdot-4.pbm tmp/bdot-4.pbm
	pnmcat -lr tmp/wdot-4.pbm tmp/bdot-4.pbm tmp/wdot-4.pbm > tmp/1
	pnmcat -lr tmp/bdot-4.pbm tmp/bdot-4.pbm tmp/bdot-4.pbm > tmp/2
	pnmcat -tb tmp/1 tmp/2 tmp/1 > $@

tmp/bdot-4.pbm:
	pbmmake -black 4 4 > $@

tmp/wdot-4.pbm:
	pbmmake -white 4 4 > $@

tmp/vblack-256.pbm:
	pbmmake -black 4 256 > $@

tmp/vwhite-256.pbm:
	pbmmake -white 4 256 > $@

tmp/hblack-256.pbm:
	pbmmake -black 256 4 > $@

tmp/hwhite-256.pbm:
	pbmmake -white 256 4 > $@

tmp/vblack-128.pbm:
	pbmmake -black 4 128 > $@

tmp/vwhite-128.pbm:
	pbmmake -white 4 128 > $@

tmp/hblack-128.pbm:
	pbmmake -black 128 4 > $@

tmp/hwhite-128.pbm:
	pbmmake -white 128 4 > $@

# PLOT DEPS

plot/exemple-1.ps: data/exemple-1.data
plot/exemple-2.ps: data/exemple-1.data
plot/exemple-3.ps: data/exemple-2.data
plot/exemple-4.ps: data/exemple-2.data
plot/anneal-sum.ps: data/anneal-sum.data
plot/lifex.ps: data/lifex-hist.data
plot/rabbit-gnans-1.ps: data/rabbit-gnans-1.data
plot/rabbit-gnans-2.ps: data/rabbit-gnans-2.data
plot/rabbit-1.ps: data/rabbit-1-hist.data
plot/rabbit-1-512.ps: data/rabbit-1-512-hist.data
plot/rabbit-2.ps: data/rabbit-2-hist.data
plot/rabbit-3.ps: data/rabbit-3-hist.data
plot/lifex-sum-1.ps : data/lifex-sum-1.data
plot/lifex-sum-2.ps : data/lifex-sum-2.data


# DATA DEPS

data/lifex-hist.data: \
	data/lifex-hist.cmd \
	data/xor-sum.cmd \
	data/xor-sum.awk

# FIG DEPS

fig/func-1.pic: fig/func-1.scale
fig/func-2.pic: fig/func-2.scale
fig/func-3.pic: fig/func-3.scale
fig/func-4.pic: fig/func-4.scale
fig/apply-1.pic: fig/apply-1.scale
fig/apply-2.pic: fig/apply-2.scale

fig/func-1.ps: fig/func-1.scale
fig/func-2.ps: fig/func-2.scale
fig/func-3.ps: fig/func-3.scale
fig/func-4.ps: fig/func-4.scale
#fig/func-5.ps: fig/func-5.scale
fig/func-7.ps: fig/func-7.scale
fig/apply-1.ps: fig/apply-1.scale
fig/apply-2.ps: fig/apply-2.scale
fig/gap.ps: fig/gap.scale
fig/gap-pe.ps: fig/gap-pe.scale
fig/life-tree.ps: fig/life-tree.scale
fig/life-dfa.ps: fig/life-dfa.scale

# QWF DEPS

qwf/aqwf: qwf/aqwf.l
	lex qwf/aqwf.l
	cc -o qwf/aqwf lex.yy.c -ll
	rm lex.yy.[co]

qwf/gqwf: qwf/gqwf.l
	lex qwf/gqwf.l
	cc -o qwf/gqwf lex.yy.c -ll
	rm lex.yy.[co]

# RULES

.SUFFIXES: .pic .fig .ps .ppm .pbm .pgm .pgm-small \
	.plot .tbl .bc .m4 .xwd .xwdb .data .out .texture \
	.c-txt .c-src .tcl-txt .tcl-src

.fig.pic:
	if [ -f $*.scale ]; then fig2dev -L pic -m `cat $*.scale` $*.fig > $*.pic; \
	else fig2dev -L pic $*.fig > $*.pic; fi

.fig.ps:
	if [ -f $*.scale ]; then fig2dev -L ps -m `cat $*.scale` $*.fig > $*.ps; \
	else fig2dev -L ps $*.fig > $*.ps; fi
	ps/fig2dev-post.sh $*.ps

.ppm.pgm:
	ppmtopgm $*.ppm > $*.pgm

.pgm.pbm:
	pgmtopbm -value 0.5 $*.pgm > $*.pbm

.pbm.ps:
	if [ -f $*.scale ]; then pnmtops -noturn -s `cat $*.scale` $*.pbm > $*.ps; \
	else pnmtops -noturn -s 0.25 $*.pbm > $*.ps; fi

.pgm-small.ps:
	pnmscale 4 $*.pgm-small | pnmtops -noturn > $*.ps

.pgm.ps:
	pnmtops -noturn $*.pgm > $*.ps

.xwd.ps:
	xwdtopnm $*.xwd | pnmtops -noturn > $*.ps

.xwdb.ps:
	xwdtopnm $*.xwdb | pnminvert | pnmtops -noturn > $*.ps

.out.data:
	$*.cmd $*

.plot.ps:
	gnuplot $*.plot
	mv plot/tmp.ps $*.ps

.bc.tbl:
	bc < $*.bc > $*.tbl

.m4.tbl:
	m4 < $*.m4 | bc > $*.tbl

.texture.tbl:
	sed -e '1d' \
		-e 's/\([a-zA-Z]\) \([a-zA-Z]\)/\1_\2/g' \
		-e 's/  */	/g' \
		-e 's/_/ /g' $*.texture | \
	cat tbl/texture.head - tbl/texture.tail > $*.tbl

.c-txt.c-src:
	indent -kr -st < $*.c-txt > $*.c-src

.tcl-txt.tcl-src:
	cat $*.tcl-txt | sed -e 's/\\/\\\\/g' > $*.tcl-src
