CC = cc
CFLAGS = -O2 -g -std=c11 -Wall -Wextra -Wpedantic
CPPFLAGS =
LDLIBS = -lX11

cell-viewer: cell-viewer.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

check: cell-viewer
	python3 test_viewer.py

.PHONY: check
