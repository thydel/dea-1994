load 'head.plot'

set title 'deriv. de flip pour 256/16384 entiers'

plot [0:256] 'Data/lambda-flip.data' using 8 notitle with lines;
