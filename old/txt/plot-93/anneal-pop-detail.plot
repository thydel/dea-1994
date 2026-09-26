load 'head.plot'
set title 'anneal detail'
set xlabel "generations time"
set ylabel "population"
plot [100:300] 'Data/anneal-pop.data' title 'plane 0' with line
