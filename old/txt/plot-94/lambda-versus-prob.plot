load 'head.plot'

set title 'lambda versus prob. de lambda pour 16384 entiers'

plot 'Data/lambda-flip.data' using 5:9 notitle with lines
