lside=8
gen=8

../src/cell \
	-s $lside \
	-l `expr 1024 \* $gen`\
	-k 0 \
	-c von-neumann-256-256-3-0 \
	-t ../rule/tunnel-v3 \
	-e 8 \
	-f ../frame/brand-${lside}-0 \
	| ../src/xdump-1 -x 256 -y 768
#	| ../src/xdump-1 -s $lside
#	| ../src/mk-plane-and $lside | ../src/xdump-1 -s $lside
#	| ../src/mk-plane-diff $lside | ../src/xdump-1 -s $lside
#	> data-size=$lside-gen=${gen}k
#	| ../src/mk-hist $lside > pop-size=$lside-gen=${gen}k-col=1
#	-f ../frame/bloc-${lside}-0-1 \
#	| cat
#	| gzip > data-size=$lside-gen=${gen}k.gz
