load 'plot/head.plot'
set title 'heart detail'
set xlabel "population plane 0"
set ylabel "population plane 1"
plot [17000:19000] [14500:16500] 'data/heart-pop.data' title 'plane0 versus plane1'
