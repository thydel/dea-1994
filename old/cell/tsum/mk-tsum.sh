s=7
ss=128

for l in 8 16 32 64 128 256 512 1024
do

for i in 0 1 2 3 4 5 6 7
do
../src/cell \
	-c moore-t-8 \
	-t ../rule/tsum-3.3.0.-1.t \
	-f ../frame/random-0-7 \
	-l $l \
	-s $s \
	-k 0 \
	-e `expr 8 + $i` > /dev/null
#	| ../src/xdump-1 -s $s
mv last.pbm tmp/tsum-$l-$i.pbm
done
