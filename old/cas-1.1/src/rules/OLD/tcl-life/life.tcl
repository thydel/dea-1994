#!./life
set f [frame 256 256 1]
set t [trans $f]
set p [plane 256 256 1]
set d [dump $p]

frame_fill $f 0 0 2

proc life cnt {
	global p t d
	for {set i 1} {$i<=$cnt} {incr i} {
		trans_extract $p $t 0 1
		dump_next $d
		trans_next $t
	}
}

life [lindex $argv 0]
