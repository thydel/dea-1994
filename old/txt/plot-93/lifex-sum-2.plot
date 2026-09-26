load 'head.plot'
set size 0.721, 1.0
set contour
set nosurface
set view 0, 0, 1.5
set cntrparam levels 12
set cntrparam bspline
set cntrparam order 6
set data style lines
set noclabel
set title 'life-sum'
splot 'Data/lifex-sum-2.data' using 1 title 'sum'
