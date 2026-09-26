source conex.tcl
source func.tcl

set cnt 512

Space2D cmd space $casdir/Data/frame/tst.pgm
#Space2D cmd space $casdir/Data/frame/anneal-cycle-128x128.pgm
#Space2D cmd space 128 128 1
#Space2D cmd space 256 256 1
#Space2D cmd space $casdir/Data/frame/random-0.pgm
#Space2D cmd space1 $casdir/Data/frame/faces.pgm
#Space2D cmd space2 $casdir/Data/frame/neighburhood-size.pgm
Time2D cmd time2d [space] $cnt
Simple2D cmd simple [time2d] [sum9_tab]
Dump2D cmd dump [time2d] 1
