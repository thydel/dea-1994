.PHONY: all clean check
all: main.pdf
SOURCES := $(wildcard *.tex chapters/*.tex compat/*.tex bib/*.bib tables/*.tbl)
figures/.prepared: prepare_figures.py figure_inventory.py figure-manifest.json $(wildcard figures/source/*/*)
	python3 prepare_figures.py
	touch figures/.prepared
main.pdf: $(SOURCES) build.py Makefile figures/.prepared
	python3 build.py
check: main.pdf
	python3 validate.py
	python3 inventory.py
clean:
	python3 -c 'from pathlib import Path; [p.unlink() for pattern in ["*.aux","*.log","*.bbl","*.blg","*.lof","*.lot","*.toc","*.fls","*.resources","build-*.txt","main.pdf","chapters/*.aux","figures/.prepared","figures/pdf/*/*.pdf"] for p in Path(".").glob(pattern)]'
