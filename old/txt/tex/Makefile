top:
	@echo "oops!"

#		'\usepackage{Sty/long-title-in-toc}'\
#		'\usepackage{Sty/mygrind}'\
#
#		'\input{Sty/email.sty}\'
#		'\input{Sty/greydraft.sty}\'
#		'\input{Sty/simple.sty}\'
#		'\input{Sty/ref-and-cite.sty}\'
#		'\input{Sty/fig-cap.sty}\'
#		'\input{Sty/old.sty}\'
mytex:
	initex '&latex'\
		'\documentclass[a4paper,12pt,dvips]{report}'\
		'\usepackage[francais,english]{babel}'\
		'\usepackage{amstex}'\
		'\usepackage{ifthen}'\
		'\usepackage{afterpage}'\
		'\usepackage{epsfig}'\
		'\usepackage{fancyheadings}'\
		'\usepackage{natbib}'\
		'\usepackage{xspace}'\
		'\usepackage{verbatim}'\
		'\usepackage{varioref}'\
		'\usepackage{multicol}'\
		'\usepackage{lgrind}'\
		'\usepackage{latexsym}'\
		'\dump'
	mv report.fmt mytex.fmt
	ln -s /usr/TeX/bin/virtex mytex

ps:
	time dvips -t a4 top -o deaps/top.ps

sps:
	dvips -t a4 Slide -o deaps/Slide.ps

rps:
	dvips -t a4 _region_ -o _region_.ps

nps:
	dvips -t a4 Notes -o Notes.ps

save:
	@echo "Saving in ../Saved/tex-`date +%d%b%y`"
	mkdir ../Saved/tex-`date +%d%b%y`
	find `sets * -d top.ps` -print | cpio -pdvm ../Saved/tex-`date +%d%b%y`
	(cd ../Saved/tex-`date +%d%b%y`; make clobber)

clean:
	rm -f *~ *.aux *.log *.bbl *.blg *.lof *.lot *.toc nohup.out

noauto:
	rm -rf auto

clobber: clean noauto
	rm -f *.dvi
	rm -f *.ps
	rm -f _region_.*
	rm -f *.fmt
	rm -f mytex
