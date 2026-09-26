load 'plot/head.plot'
set title 'anneal detail'
set xlabel "generations time"
set ylabel "population"
plot [100:300] 'data/anneal-pop.data' title 'plane 0' with line
