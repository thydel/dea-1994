TABLE=.
TABLES = \
	$(TABLE)/neighburhood-size.tbl \
	$(TABLE)/neighburhood-size-1.tbl \
	$(TABLE)/neighburhood-size-2.tbl \
	$(TABLE)/space-size.tbl \
	$(TABLE)/compute-time-100kcps.tbl \
	$(TABLE)/compute-time-10mcps.tbl \
	$(TABLE)/lifex-sum-1.tbl \
	$(TABLE)/lifex-sum-2.tbl

# TARGETS

top: $(TABLES)

tst: $(TABLES) ltx-tst.ltx
	latex ltx-tst.ltx

clean:
	rm -f *~ *.tbl

# TBLS DEPS

$(TABLE)/lifex-sum-1.tbl $(TABLE)/lifex-sum-2.tbl: \
	$(TABLE)/texture.head-ltx $(TABLE)/texture.tail-ltx
$(TABLE)/compute-time-10mcps.tbl $(TABLE)/compute-time-100kcps.tbl: $(TABLE)/compute-time.skel

# RULES

.SUFFIXES: .tbl .bc .m4 .texture

.bc.tbl:
	bc < $*.bc | sed -e '/\\$$/N' -e '/\\\n/s///' > $*.tbl

.m4.tbl:
	m4 < $*.m4 | bc | sed -e '/\\$$/N' -e '/\\\n/s///' > $*.tbl

.texture.tbl:
	sed -e '1d' \
		-e 's/\([a-zA-Z]\) \([a-zA-Z]\)/\1_\2/g' \
		-e 's/  */\&/g' \
		-e 's/_/ /g' \
		-e 's/$$/\\\\\\hline/' $*.texture | \
	cat $(TABLE)/texture.head-ltx - $(TABLE)/texture.tail-ltx > $*.tbl
