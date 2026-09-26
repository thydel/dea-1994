load 'head.plot'

set title 'lambda versus flip pour 16384 entiers'

plot 'Data/lambda-flip.data' using 5:6 notitle with lines
