source conex.tcl
source func.tcl

set cnt 64

Space2D cmd space ../../data/frame/random-0.pgm
Time2D cmd time2d [space] $cnt
Simple2D cmd simple [time2d] [sum9_tab]
Dump2D cmd dump [time2d] 1
