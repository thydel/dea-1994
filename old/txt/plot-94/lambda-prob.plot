load 'head.plot'

set title 'lambda et prob. de lambda pour 512/16384 entiers'

plot [0:512] 'Data/lambda-flip.data' using 5 title 'lambda' with lines, \
	'Data/lambda-flip.data' using 9 title 'lambda prob' with lines;
