size=10

#for gen in 1024 2048 4096 8192 16384 32768
for gen in 2 4 8 16
do

../src/cell \
	-D \
	-c moore-1+7 \
	-t rule/lifex.t \
	-f ../frame/random-10-0 \
	-s $size \
	-l $gen \
	-k 512 \
	-u biglife-$size-$gen.sum \
	-a biglife-$size-$gen.tmp \
	-e $plane \
	> /dev/null 2> biglife-$size-$gen.debug
#	| xdump-1 -s $size

mv last.pbm biglife-$size-$gen.pbm
mv sum.pgm biglife-sum-$size-$gen.pgm
mv sum.out biglife-sum-$size-$gen.out
mv sum.ascii biglife-sum-$size-$gen.ascii

done
