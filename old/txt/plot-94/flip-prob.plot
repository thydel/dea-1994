load 'head.plot'

set title 'flip et prob. de flip pour 512/16384 entiers'

plot [0:512] 'Data/lambda-flip.data' using 6 title 'flip' with lines, \
	'Data/lambda-flip.data' using 10 title 'flip prob' with lines;
