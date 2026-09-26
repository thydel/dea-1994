proc mk_obj {w name cmd param flag info} {
	frame $w -relief raised -borderwidth 4
	# set opts {top padx 10 pady 10 expand fill}
	# set opts {top expand fill}
	set opts {top fill}
	if [string compare $name {}] {
		label $w.label -text $name
		pack append $w $w.label $opts
	}
	if [string compare $cmd {}] {
		eval "mk_cmd_set $w.cmd $cmd"
		pack append $w $w.cmd $opts
	}
	if [string compare $param {}] {
		eval "mk_param_set $w.param $param"
		pack append $w $w.param $opts
	}
	if [string compare $flag {}] {
		eval "mk_flag_set $w.flag $flag"
		pack append $w $w.param $opts
	}
	if [string compare $info {}] {
		eval "mk_info_set $w.info $info"
		pack append $w $w.info $opts
	}
}

proc mk_cmd_set {w args} {
	frame $w
	foreach arg $args {
		button $w.$arg -text \
			"[string toupper [string index $arg 0]][string range $arg 1 end]" \
			-command "cmd_$arg"
		pack append $w $w.$arg {left padx 10 expand}
	} 
}

proc mk_param_set {w args} {
	frame $w
	foreach arg $args {
		set text [lindex $arg 0]
		set default [lindex $arg 1]
		mk_param_elt $w.$text $text 6
		$w.$text.entry insert 0 $default
		pack append $w $w.$text {left padx 10 expand}
	}
}

proc mk_param_elt {w text length} {
	frame $w
	label $w.label -text $text
	entry $w.entry -width $length -relief sunken
	pack append $w \
		$w.label {left} \
		$w.entry {left}
}

proc mk_info_set {w args} {
	frame $w
	foreach arg $args {
		label $w.$arg -relief sunken -textVariable $arg
		pack append $w $w.$arg {left padx 10 expand}
	}
}

