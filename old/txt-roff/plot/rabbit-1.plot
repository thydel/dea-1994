load 'plot/head.plot'

set size 4, 1
set title 'rabbit gnans'

plot \
	'data/rabbit-1-hist.data' using 1 title 'fox' with lines, \
	'data/rabbit-1-hist.data' using 2 title 'rabbit' with lines;
