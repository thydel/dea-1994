proc atomp {list} {
	expr {[llength $list] == 1 &&
		[string compare [string index [string trim $list] 0] "\{"]}
}
proc car {list} {lindex $list 0}
proc cdr {list} {lrange $list 1 end}
proc cons {car cdr} {linsert $cdr 0 $car}

proc expand {list {level 0}} {
#	puts $list
	incr level
	if ![llength $list] {
		return {}
	} elseif {![string compare [lindex $list 0] expand]} {
		cons [uplevel $level [lindex $list 1]] [expand [lrange $list 2 end] $level]
	} elseif [atomp [lindex $list 0]] {
		cons [lindex $list 0] [expand [lrange $list 1 end] $level]
	} else {
		cons [expand [lindex $list 0] $level] [expand [lrange $list 1 end] $level]
	}
}

proc expand1 {list {level 1}} {
#	puts $list
	if ![llength $list] {
		return {}
	} elseif {[llength $list] == 2 && ![string compare [car $list] expand]} {
		uplevel $level return [lindex $list 1]
	} elseif [atomp [car $list]] {
		cons [car $list] [expand [cdr $list] [expr {$level + 1}]]
	} else {
		cons [expand [car $list] [expr {$level + 1}]] \
			[expand [cdr $list] [expr {$level + 1}]]
	}
}
