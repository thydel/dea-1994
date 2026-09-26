cut -f1 -d' ' $1.out > /tmp/1
cut -f2 -d' ' $1.out | sed -e 1d > /tmp/2
echo 0 >> /tmp/2
cut -f3 -d' ' $1.out | sed -e '1,2d' > /tmp/3
echo '0\n0' >> /tmp/3
paste /tmp/1 /tmp/2 /tmp/3 | gawk -f data/xor-sum.awk | sed -e 's/-inf/0/g' > $1.data
