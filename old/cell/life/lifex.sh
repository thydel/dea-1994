size=8
loop=256
skip=0

../src/cell \
	-c moore-1+7 \
	-s $size \
	-l `expr $loop \* $skip` \
	-k $skip \
	-t ../rule/lifex.t \
	-f ../frame/random-0 \
	-e 3 \
| tee life-3x256.raw | ../src/xdump-1 -s $size
# | rsh colombie dd of=/dev/audio
# > /dev/null

