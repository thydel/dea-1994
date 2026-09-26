step=0
double=1
extract=0
lastf=0

if [ ! -z "$1" ]
then
	rule=$1
else
	rule=000323111
fi

if [ ! -z "$2" ]
then
	size=$2
else
	size=8
fi

if [ $double = 1 ]
then
	size_dump=`expr $size + 1`
	extract=18
else
	size_dump=$size
fi

if [ ! -z "$3" ]
then
	loop=$3
else
	loop=256
fi

table=no-table
tmp=`echo $rule | wc -c`
tmp=`expr $tmp - 1`
if [ $tmp = 9 ]
then
	table=totalistic
elif [ $tmp = 10 ]
then
	table=totalistic-9
fi

if [ $lastf = 1 -a -s last.pgm ]
then
	frame=last.pgm
	pgmf="-G "
else
	frame=../frame/random-$size-0
	pgmf=""
fi

../src/mk-table -f $table -s $rule > $rule.t
../src/cell \
	-l $loop \
	-s $size \
	-k $step \
	-t $rule.t \
	-a last.pbm \
	$pgmf \
	-f $frame \
	-e $extract \
	| ../src/xdump-1 -s $size_dump
