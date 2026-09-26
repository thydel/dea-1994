l=256
s=8

#	-f ../frame/anneal-sum-1k-8k-9-7 \

../src/cell \
	-c moore-t-8 \
	-t ../rule/tsum-3.3.0.-1.t \
	-f ../frame/random-0-7 \
	-s $s \
 | ../src/xdump -d 8 -s $s -E
# | ../src/xdump -d 8 -s $s -E -R
#	> xxx

