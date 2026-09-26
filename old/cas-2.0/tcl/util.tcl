proc out {args} {
	foreach arg $args {
		puts -nonewline stdout $arg
		flush stdout
	}
	puts ""
	flush stdout
}

# tcl>set a aaa; set b bbb; set c ccc
# tcl>expand {a b} {$a $b $c $d}
# aaa bbb $c $d
# tcl>
#
# useful to dynamically define proc
#
proc expand {vars str} {
	foreach var $vars {
		regsub -all \\\$${var}(\[^a-z]) $str [uplevel [list set $var]]\\1 str
	}
	return $str
}

# tcl>gen_varlist {q w e r}
# $q $w $e $r 
# tcl>
#
# this help to dynamically construct proc call
#
proc gen_varlist {arglist} {
	set tmp {}
	foreach arg $arglist {
		append tmp "\$$arg "
	}
	return $tmp
}

# tcl>gen_top foo {a b}
# tcl>showproc top_foo
# proc top_foo {w a b} {
# 		if [winfo exist .$w] {return}
# 		catch {destroy .$w}
# 		toplevel .$w -borderwidth 0
# 		wm title .$w $w
# 		wm iconname .$w $w
# 		wm minsize .$w 64 64
# 		mk_foo .$w.$w $a $b
# 		pack append .$w .$w.$w {top expand fill}
# 	}
# 
# tcl>
#
# ie. create a ``foo'' top level window
# to support a call to the ``mk_foo'' proc
# wich create a embeded ``foo'' window
#
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
