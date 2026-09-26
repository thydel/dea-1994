l=256
s=10

#	-f ../frame/anneal-sum-1k-8k-9-7 \

../src/cell \
	-c moore-t-8 \
	-t ../rule/tsum-3.3.0.-1.t \
	-f ../frame/random-$s-0-7 \
	-s $s \
	-e 11 \
 | ../src/xdump-1 -s $s
#	> xxx

