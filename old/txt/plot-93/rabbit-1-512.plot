load 'head.plot'

set size 4, 1
set title 'life rabbit version 1'

plot \
	'Data/rabbit-1-512-hist.data' using 1 title 'fox' with lines, \
	'Data/rabbit-1-512-hist.data' using 2 title 'rabbit' with lines;
