define(`bin',`ifelse($1,,,`pushdef(`$1',$2)$0(shift(shift($@)))')')
