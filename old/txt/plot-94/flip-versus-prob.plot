load 'head.plot'

set title 'flip versus prob. de flip pour 16384 entiers'

plot 'Data/lambda-flip.data' using 6:10 notitle with lines
