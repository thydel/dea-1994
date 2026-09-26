if [ -z "$1" ]
then
	file=data
else
	file=$1
fi
bc bin.bc > $file.tmp
# ed $file.tmp < filt.ed > /dev/null
filt.sed $file.tmp > $file
# gawk -f filt.awk $file.tmp > $file
# sort -n +2 -n +3 -n +0 $file > $file.sorted
