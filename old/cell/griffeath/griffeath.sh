../src/cell \
	-s 8 \
	-c von-neumann-256-256-3-0 \
	-t ../cellsim/Rules/griffeath.v8 \
	-f ../frame/random-0-2 \
	-e 8 \
	| ../src/xdump-1 -s 9
