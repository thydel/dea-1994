load 'head.plot'

set title 'deriv. de lambda pour 256/16384 entiers'

plot [0:256] 'Data/lambda-flip.data' using 7 notitle with lines;
