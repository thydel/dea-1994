load 'plot/head.plot'

set size 2, 1
set title 'life time xor'
set xlabel "generations time"
set ylabel "log(population)"

plot \
	[1:1277] \
	'data/lifex-hist.data' using 1 title 'life' with lines 4, \
	'data/lifex-hist.data' using 2 title 'cycle 1' with lines 2, \
	'data/lifex-hist.data' using 3 title 'cycle 2' with lines 1, \
	'data/lifex-hist.data' using 4 title 'cycle > 2' with lines 3

