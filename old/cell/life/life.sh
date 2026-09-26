size=9
loop=1024

time ../src/cell \
	-s $size \
	-l $loop \
	-k 0 \
	-e 8 \
	-t ../rule/life.t \
	-f ../frame/random-9-0 \
 | ../src/xdump-1 -s $size
# > /dev/null
# > life-3x1k.raw
#	-a xxx
# | rsh colombie dd of=/dev/audio
# > /dev/null
