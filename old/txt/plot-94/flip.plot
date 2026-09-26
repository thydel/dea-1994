load 'head.plot'

set title 'flip pour 128/16384 entiers'

plot [0:128] 'Data/lambda-flip.data' using 6 title 'flip' with lines;
