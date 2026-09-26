load 'head.plot'
set size 0.721, 1.0
set view 60, 30, 1.25
set hidden3d
set contour
set cntrparam level 20
set data style lines
set noclabel
set title 'anneal-sum'
splot 'Data/anneal-sum.data' using 1 title 'sum'
