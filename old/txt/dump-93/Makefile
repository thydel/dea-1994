TMP=tmp
DUMP=.
#	$(DUMP)/anneal-sum-1k4k8k-he.ps
DUMPS = \
	$(DUMP)/anneal.ps \
	$(DUMP)/anneal-g128-s11.ps \
	$(DUMP)/tube-worm-mix.ps \
	$(DUMP)/anneal-sum.ps \
	$(DUMP)/tsum-grey.ps \
	$(DUMP)/tsum.ps \
	$(DUMP)/life-time-xor.ps \
	$(DUMP)/anneal-time-xor.ps \
	$(DUMP)/lifex-sum-1.ps \
	$(DUMP)/lifex-sum-2.ps \
	$(DUMP)/loop-1024.ps \
	$(DUMP)/anneal-sum-1k-8k-xv.ps \
	$(DUMP)/anneal-sum-1k-8k.ps \
	$(DUMP)/tsum-ray-one.ps \
	$(DUMP)/tsum-ray-all.ps \
	$(DUMP)/neighburhood-size-tbl-16xor9.ps \
	$(DUMP)/tsum-128-edge.ps \
	$(DUMP)/cas-cmd-1.ps \
	$(DUMP)/cas-dump.ps \
	$(DUMP)/anneal-3d.ps \
	$(DUMP)/life-3d.ps \
	$(DUMP)/lifex-3d.ps \
	$(DUMP)/xu-photo-1.ps \
	$(DUMP)/xu-photo-1-top.ps \
	$(DUMP)/xu-film-1-1.ps \
	$(DUMP)/xu-film-1-2.ps \
	$(DUMP)/xu-Cfilm-1-1.ps \
	$(DUMP)/xu-Cfilm-1-2.ps \
	$(DUMP)/xu-Cfilm-2-1.ps \
	$(DUMP)/xu-Cfilm-2-2.ps \
	$(DUMP)/life3d+lifex3d-top.ps \
	$(DUMP)/dummy.ps

# TARGETS

top: $(DUMPS)

clean:
	rm -f $(TMP)/* *.ps

# DUMPS DEPS

$(DUMP)/anneal-time-xor.ps: $(DUMP)/anneal-time-xor.scale
$(DUMP)/life-time-xor.ps: $(DUMP)/life-time-xor.scale
$(DUMP)/loop-1024.ps: $(DUMP)/loop-1024.scale

$(DUMP)/anneal-sum-1k4k8k-he.ps: /usr/local/images/thy/anneal-sum-1k4k8k-he.ppm
	pnmtops -noturn -s 0.5 /usr/local/images/thy/anneal-sum-1k4k8k-he.ppm > $@

$(DUMP)/tsum-128-edge.ps: $(TMP)/tsum-128-edge.pbm
	pnmtops -s 0.5 -noturn $(TMP)/tsum-128-edge.pbm > $@

$(TMP)/tsum-128-edge.pbm: $(DUMP)/tsum-128-edge-1.pbm $(DUMP)/tsum-128-edge-2.pbm
	pnmcat -lr \
		$(DUMP)/tsum-128-edge-0.pbm \
		$(TMP)/vsep-256.pbm $(DUMP)/tsum-128-edge-1.pbm \
		$(TMP)/vsep-256.pbm $(DUMP)/tsum-128-edge-2.pbm > $@

$(DUMP)/neighburhood-size-tbl-16xor9.ps: $(DUMP)/neighburhood-size-tbl-16xor9.pbm
	pnmtops -noturn $(DUMP)/neighburhood-size-tbl-16xor9.pbm > $@

$(DUMP)/tsum-ray-one.ps: $(DUMP)/tsum-ray-one.pgm
	pnmtops -noturn $(DUMP)/tsum-ray-one.pgm > $@

$(DUMP)/tsum-ray-all.ps: $(DUMP)/tsum-ray-all.pgm
	pnmtops -s 0.5 -noturn $(DUMP)/tsum-ray-all.pgm > $@

$(DUMP)/anneal-sum-1k-8k-xv.ps: $(DUMP)/anneal-sum-1k-8k-xv.pgm
	pnmtops -s 0.5 -noturn $(DUMP)/anneal-sum-1k-8k-xv.pgm > $@

$(DUMP)/anneal-sum-1k-8k.ps: $(DUMP)/anneal-sum-1k-8k.pgm
	pnmtops -s 0.5 -noturn $(DUMP)/anneal-sum-1k-8k.pgm > $@

$(DUMP)/anneal-sum.ps: $(TMP)/anneal-sum.pgm
	pnmtops -s 0.5 -noturn $(TMP)/anneal-sum.pgm > $@

ANNEAL_SUM_PGM_LIST = $(DUMP)/anneal-sum-64.pgm $(TMP)/vsep-256.pbm \
	$(DUMP)/anneal-sum-64-xv.pgm $(TMP)/vsep-256.pbm \
	$(DUMP)/anneal-sum-64-xv1.pgm $(TMP)/vsep-256.pbm \
	$(DUMP)/anneal-sum-64-xv2.pgm

$(TMP)/anneal-sum.pgm: $(ANNEAL_SUM_PGM_LIST)
	pnmcat -lr $(ANNEAL_SUM_PGM_LIST) > $@

$(DUMP)/anneal.ps: $(TMP)/anneal.pbm
	pnmtops -s 0.25 -noturn $(TMP)/anneal.pbm > $@

$(TMP)/anneal.pbm: $(DUMP)/anneal-64.pbm $(TMP)/vsep-256.pbm $(DUMP)/anneal-256.pbm
	pnmcat -lr $(DUMP)/anneal-64.pbm $(TMP)/vsep-256.pbm $(DUMP)/anneal-256.pbm > $@

# Comment out if want to include grey level file.
#$(DUMP)/tsum-grey.ps: $(TMP)/tsum-grey.pbm
#	pnmtops -noturn $(TMP)/tsum-grey.pbm > $@

# Comment out if want to include bitmap level file.
$(DUMP)/tsum-grey.ps: $(TMP)/tsum-grey.pgm
	pnmtops -noturn $(TMP)/tsum-grey.pgm > $@

$(DUMP)/tsum.ps: $(TMP)/tsum.pbm $(DUMP)/tsum.scale
	pnmtops -s `cat $(DUMP)/tsum.scale` -noturn $(TMP)/tsum.pbm > $(DUMP)/tsum.ps

TSUM_PBM_LIST = $(DUMP)/tsum-8.pbm $(DUMP)/tsum-16.pbm $(DUMP)/tsum-32.pbm \
	$(DUMP)/tsum-64.pbm $(DUMP)/tsum-128.pbm $(DUMP)/tsum-256.pbm \
	$(DUMP)/tsum-512.pbm $(DUMP)/tsum-1024.pbm

$(TMP)/tsum.pbm: $(TSUM_PBM_LIST) $(TMP)/hsep-1024+7x12.pbm
	pnmcat -tb \
	`echo $(TSUM_PBM_LIST) | sed -e 's; $(DUMP)/; $(TMP)/hsep-1024+7x12.pbm $(DUMP)/;g'` > $@

$(TMP)/tsum-grey.pgm: $(TMP)/tsum-e.pgm $(TMP)/hsep-512+12.pbm $(TMP)/tsum-r.pgm
	pnmcat -tb $(TMP)/tsum-e.pgm $(TMP)/hsep-512+12.pbm $(TMP)/tsum-r.pgm > $@

$(TMP)/tsum-e.pgm: $(DUMP)/tsum-128-xv.pgm $(TMP)/vsep-256.pbm $(DUMP)/tsum-256-xv.pgm
	pnmcat -lr $(DUMP)/tsum-128-xv.pgm $(TMP)/vsep-256.pbm $(DUMP)/tsum-256-xv.pgm > $@

$(TMP)/tsum-r.pgm: $(DUMP)/tsum-128-xvr.pgm $(TMP)/vsep-256.pbm $(DUMP)/tsum-256-xvr.pgm
	pnmcat -lr $(DUMP)/tsum-128-xvr.pgm $(TMP)/vsep-256.pbm $(DUMP)/tsum-256-xvr.pgm > $@

$(TMP)/vsep-256.pbm: $(TMP)/vblack-256.pbm $(TMP)/vwhite-256.pbm
	pnmcat -lr $(TMP)/vwhite-256.pbm $(TMP)/vblack-256.pbm $(TMP)/vwhite-256.pbm > $@

$(TMP)/vsep-128.pbm: $(TMP)/vblack-128.pbm $(TMP)/vwhite-128.pbm
	pnmcat -lr $(TMP)/vwhite-128.pbm $(TMP)/vblack-128.pbm $(TMP)/vwhite-128.pbm > $@

$(TMP)/hsep-256.pbm: $(TMP)/hblack-256.pbm $(TMP)/hwhite-256.pbm
	pnmcat -tb $(TMP)/hwhite-256.pbm $(TMP)/hblack-256.pbm $(TMP)/hwhite-256.pbm > $@

$(TMP)/hsep-128.pbm: $(TMP)/hblack-128.pbm $(TMP)/hwhite-128.pbm
	pnmcat -tb $(TMP)/hwhite-128.pbm $(TMP)/hblack-128.pbm $(TMP)/hwhite-128.pbm > $@

$(TMP)/hsep-512+12.pbm: $(TMP)/hsep-256.pbm $(TMP)/cross-12.pbm
	pnmcat -lr $(TMP)/hsep-256.pbm $(TMP)/cross-12.pbm $(TMP)/hsep-256.pbm > $@

$(TMP)/hsep-1024+7x12.pbm: $(TMP)/hsep-128.pbm $(TMP)/cross-12.pbm
	pnmcat -lr \
	$(TMP)/hsep-128.pbm $(TMP)/cross-12.pbm \
	$(TMP)/hsep-128.pbm $(TMP)/cross-12.pbm \
	$(TMP)/hsep-128.pbm $(TMP)/cross-12.pbm \
	$(TMP)/hsep-128.pbm $(TMP)/cross-12.pbm \
	$(TMP)/hsep-128.pbm $(TMP)/cross-12.pbm \
	$(TMP)/hsep-128.pbm $(TMP)/cross-12.pbm \
	$(TMP)/hsep-128.pbm $(TMP)/cross-12.pbm \
	$(TMP)/hsep-128.pbm > $@

$(TMP)/dot-12.pbm:
	pbmmake -black 12 12 > $@

$(TMP)/cross-12.pbm: $(TMP)/wdot-4.pbm $(TMP)/bdot-4.pbm
	pnmcat -lr $(TMP)/wdot-4.pbm $(TMP)/bdot-4.pbm $(TMP)/wdot-4.pbm > $(TMP)/1
	pnmcat -lr $(TMP)/bdot-4.pbm $(TMP)/bdot-4.pbm $(TMP)/bdot-4.pbm > $(TMP)/2
	pnmcat -tb $(TMP)/1 $(TMP)/2 $(TMP)/1 > $@

$(TMP)/bdot-4.pbm:
	pbmmake -black 4 4 > $@

$(TMP)/wdot-4.pbm:
	pbmmake -white 4 4 > $@

$(TMP)/vblack-256.pbm:
	pbmmake -black 4 256 > $@

$(TMP)/vwhite-256.pbm:
	pbmmake -white 4 256 > $@

$(TMP)/hblack-256.pbm:
	pbmmake -black 256 4 > $@

$(TMP)/hwhite-256.pbm:
	pbmmake -white 256 4 > $@

$(TMP)/vblack-128.pbm:
	pbmmake -black 4 128 > $@

$(TMP)/vwhite-128.pbm:
	pbmmake -white 4 128 > $@

$(TMP)/hblack-128.pbm:
	pbmmake -black 128 4 > $@

$(TMP)/hwhite-128.pbm:
	pbmmake -white 128 4 > $@

# RULES

.SUFFIXES: .ps .ppm .pbm .pgm .pgm-small .xwd .xwdb

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
