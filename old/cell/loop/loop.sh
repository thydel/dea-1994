../src/cell \
	-u loop-sum.out \
	-h loop-hist.out \
	-l 1024 \
	-s 8 \
	-c von-neumann-256-256-3-0 \
	-t ../rule/loop-v3 \
	-f ../cellsim/Images/loop.256x \
	-e 9 > /dev/null
#	| ../src/xdump-1 -s 8
