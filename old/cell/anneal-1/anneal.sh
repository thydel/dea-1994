#s=$1
#l=$2
#k=$3

s=8
l=256
k=0

../src/cell \
	-s $s \
	-l $l \
	-k $k \
	-c moore-1 \
	-t ../rule/anneal.t \
	-f ../frame/random-$s-0 > anneal-256x3.raw
#	-e 8 \
#	| ../src/xdump-1 -s $s -P
# > /dev/null

