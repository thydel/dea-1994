load 'plot/head.plot'

set size 4, 1
set title 'life rabbit version 2'

plot \
	'data/rabbit-2-hist.data' using 1 title 'fox' with lines, \
	'data/rabbit-2-hist.data' using 2 title 'rabbit' with lines;
