load 'plot/head.plot'

set size 4, 1
set title 'life rabbit version 1'

plot \
	'data/rabbit-gnans-2.data' using 1 title 'fox' with lines, \
	'data/rabbit-gnans-2.data' using 2 title 'rabbit' with lines;
