proc expand {vars str} {
	foreach var $vars {
		regsub -all \\\$${var}(\[^a-z]) $str [uplevel [list set $var]]\\1 str
	}
	return $str
}

proc out {args} {
	foreach arg $args {
		puts -nonewline stdout $arg
		flush stdout
	}
	puts ""
	flush stdout
}

proc gen_varlist {arglist} {
	set tmp {}
	foreach arg $arglist {
		append tmp "\$$arg "
	}
	return $tmp
}

proc gen_top {obj {arglist {}}} {
	set call [concat "mk_$obj " ".\$w.\$w " [gen_varlist $arglist]]
	set body {
		if [winfo exist .$w] {return}
		catch {destroy .$w}
		toplevel .$w -borderwidth 0
		wm title .$w $w
		wm iconname .$w $w
		wm minsize .$w 64 64
		$call
		pack append .$w .$w.$w {top expand fill}
	}
	proc top_$obj [linsert $arglist 0 w] [expand call $body]
}

proc capitalize {string} {
	return [string toupper [string index $string 0]][string range $string 1 end]
}

proc father {w} {string range $w 0 [expr {[string last . $w] - 1}]}
proc self {w} {string range $w [expr {[string last . $w] + 1}] end}

proc cmd_close {w} {
	set class [winfo class [winfo parent $w]]
	if {![string compare $class Toplevel] || ![string compare $class Tk]} {
		destroy [winfo parent $w]
	} else {
		destroy $w
	}
}

proc cmd_unpack {w} {
	set class [winfo class [winfo parent $w]]
	if {![string compare $class Toplevel] || ![string compare $class Tk]} {
		destroy [winfo parent $w]
	} else {
		pack unpack $w
	}
}

# Local Variables:
# tab-width: 4
# End:
