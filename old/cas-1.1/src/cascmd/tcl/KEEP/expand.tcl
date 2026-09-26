proc atomp {list} {
	expr {[llength $list] == 1 &&
		[string compare [string index [string trim $list] 0] "\{"]}
}
proc car {list} {lindex $list 0}
proc cdr {list} {lrange $list 1 end}
proc cons {car cdr} {linsert $cdr 0 $car}

proc expand {list {level 0}} {
	incr level
	if ![llength $list] {
		return {}
	} elseif {![string compare [lindex $list 0] expand]} {
		cons [uplevel $level [list set [lindex $list 1]]] [expand [lrange $list 2 end] $level]
	} elseif [atomp [lindex $list 0]] {
		cons [lindex $list 0] [expand [lrange $list 1 end] $level]
	} else {
		cons [expand [lindex $list 0] $level] [expand [lrange $list 1 end] $level]
	}
}
