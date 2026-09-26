cut -f1 -d' ' $1-hist.out > tmp/1
cut -f3 -d' ' $1-hist.out | sed -e 1d > tmp/2
echo 0 >> tmp/2
cut -f4 -d' ' $1-hist.out | sed -e '1,2d' > tmp/3
echo '0\n0' >> tmp/3
paste tmp/1 tmp/2 tmp/3 | gawk -f xor-sum.awk > $1-hist.data
sed -e '501,$d' $1-hist.data > $1-hist-1.gobi
sed -e '1,500d' -e '1001,$d' $1-hist.data > $1-hist-2.gobi
sed -e '1,1001d' $1-hist.data > $1-hist-3.gobi