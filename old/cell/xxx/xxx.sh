#	-u loop-sum.out
#	-h loop-hist.out

../src/cell \
	-l 1024 \
	-s 8 \
	-c von-neumann-1 \
	-t ../rule/xxx \
	-f ../frame/random-0 \
	-e 8 \
	| ../src/xdump-1 -s 8
