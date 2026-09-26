ss=128
for l in 8 16 32 64 128 256 512 1024
do
pnmcat -lr \
	tmp/tsum-$l-0.pbm ../pbm/vsep-$ss.pbm \
	tmp/tsum-$l-1.pbm ../pbm/vsep-$ss.pbm \
	tmp/tsum-$l-2.pbm ../pbm/vsep-$ss.pbm \
	tmp/tsum-$l-3.pbm ../pbm/vsep-$ss.pbm \
	tmp/tsum-$l-4.pbm ../pbm/vsep-$ss.pbm \
	tmp/tsum-$l-5.pbm ../pbm/vsep-$ss.pbm \
	tmp/tsum-$l-6.pbm ../pbm/vsep-$ss.pbm \
	tmp/tsum-$l-7.pbm > tsum-$l.pbm

done
