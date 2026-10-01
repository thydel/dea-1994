.PHONY: all clean check
all: main.pdf
SOURCES := $(wildcard *.tex chapters/*.tex compat/*.tex bib/*.bib tables/*.tbl)
main.pdf: $(SOURCES) build.py Makefile
	python3 build.py
check: main.pdf
	python3 validate.py
	python3 inventory.py
clean:
	python3 -c 'from pathlib import Path; [p.unlink() for pattern in ["*.aux","*.log","*.bbl","*.blg","*.lof","*.lot","*.toc","*.fls","*.resources","build-*.txt","main.pdf","chapters/*.aux"] for p in Path(".").glob(pattern)]'
