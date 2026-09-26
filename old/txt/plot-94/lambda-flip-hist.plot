load 'head.plot'

set title 'hist. de flip et lambda pour 16384 entiers'

plot [0:14] 'Data/lambda-flip.data' using 15 title 'lambda' with lines, \
	'Data/lambda-flip.data' using 16 title 'flip' with lines;
