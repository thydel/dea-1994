load 'plot/head.plot'
set title 'anneal'
set xlabel "generations time"
set ylabel "population"
set key 250, 9000
set label 1 "Un cycle limite" at 150, 9500 center
set arrow 1 from 150,9600 to 200, 10200
plot 'data/anneal-pop.data' title 'plane 0' with line 
