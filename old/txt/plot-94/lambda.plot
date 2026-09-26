load 'head.plot'

set title 'lambda pour 128/16384 entiers'

plot [0:128] 'Data/lambda-flip.data' using 5 title 'lambda' with lines;
