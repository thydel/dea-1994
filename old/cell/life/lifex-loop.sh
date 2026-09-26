size=6
side=64
sep=8

foo() {
	name=$1
	plane=$2
	size=$3
	gen=$4
#	cell -s $size -l $gen -a spl/life-$gen$name.tmp -c moore-1+7 -t rule/lifex.t -e $plane | xdump-1 -s $size
	cell -s $size -l $gen -a spl/life-$gen$name.tmp -c moore-1+7 -t rule/lifex.t -e $plane > /dev/null
#	pnminvert spl/life-$gen$name.tmp > spl/life-$gen$name.pbm
	mv spl/life-$gen$name.tmp spl/life-$gen$name.pbm
	rm -f spl/life-$gen$name.tmp
}

hsep=pbm/gray-${side}x${sep}.pbm
pbmmake -gray ${side} ${sep} > $hsep

rm -f spl/tmp.pbm

base=100
cnt=6
i=0
end=`expr $cnt - 0`
while [ $i -ne $end ]
do
	gen=`expr $base + $i`
	i=`expr $i + 1`

	name=""
	foo "$name" 0 $size $gen
	cp spl/life-$gen$name.pbm spl/tmp.pbm
	
	name="-xor-t0-t1"
	foo $name 2 $size $gen
	mv spl/tmp.pbm spl/tmp-1.pbm
	pnmcat -tb spl/tmp-1.pbm  $hsep spl/life-$gen$name.pbm > spl/tmp.pbm

	name="-xor-t0-t2"
	foo $name 3 $size $gen
	mv spl/tmp.pbm spl/tmp-1.pbm
	pnmcat -tb spl/tmp-1.pbm  $hsep spl/life-$gen$name.pbm > spl/tmp.pbm

	mv spl/tmp.pbm spl/$gen.pbm
done

x=`expr ${side} \* 3 + ${sep} \* 2`
vsep=pbm/gray-${sep}x${x}.pbm
pbmmake -gray ${sep} $x > $vsep

pnmcat -lr spl/$base.pbm $vsep > spl/tmp.pbm
i=1
end=`expr $cnt - 1`
while [ $i -ne $end ]
do
	gen=`expr $base + $i`
	mv spl/tmp.pbm spl/tmp-1.pbm
	pnmcat -lr spl/tmp-1.pbm spl/$gen.pbm $vsep > spl/tmp.pbm
	i=`expr $i + 1`
done

gen=`expr $base + $i`
pnmcat -lr spl/tmp.pbm spl/$gen.pbm > life-time-xor.pbm
