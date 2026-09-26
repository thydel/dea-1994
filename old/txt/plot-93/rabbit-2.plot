load 'head.plot'

set size 4, 1
set title 'life rabbit version 2'

plot \
	'Data/rabbit-2-hist.data' using 1 title 'fox' with lines, \
	'Data/rabbit-2-hist.data' using 2 title 'rabbit' with lines;
