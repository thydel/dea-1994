proc mk_obj {w list} {
	if [winfo exist $w] {cmd_close $w}
	frame $w -relief raised -borderwidth 4
	set opts {top expand}
	foreach arg $list {
		if ![string compare [lindex $arg 0] name] {
			frame $w.obj
			set class [lindex $arg 1]
			set object [winfo name $w]
			label $w.obj.type -text [capitalize $class]
			if {[string first ${class}_ $object] == 0} {
				set object [string range $object [string length ${class}_] end]
			}
			label $w.obj.name -relief raised -text $object
			pack append $w.obj $w.obj.type {left expand} $w.obj.name {left expand}
			pack append $w $w.obj $opts
		}
		if ![string compare [lindex $arg 0] cmd] {
			mk_cmd_set $w.cmd [lindex $arg 1]
			pack append $w $w.cmd $opts
		}
		if ![string compare [lindex $arg 0] param] {
			mk_param_set $w.param [lindex $arg 1]
			pack append $w $w.param $opts
		}
		if ![string compare [lindex $arg 0] flag] {
			mk_flag_set $w.flag [lindex $arg 1]
			pack append $w $w.param $opts
		}
		if ![string compare [lindex $arg 0] info] {
			mk_info_set $w.info [lindex $arg 1]
			pack append $w $w.info $opts
		}
	}
}

proc mk_obj1 {w list} {
	if [winfo exist $w] {cmd_close $w}
	frame $w -relief raised -borderwidth 4
	set opts {top expand}
	foreach arg $list {
		if ![string compare [lindex $arg 0] name] {
			frame $w.obj
			label $w.obj.type -text [capitalize [lindex $arg 1]]
			label $w.obj.name -relief raised -text [winfo name $w]
			pack append $w.obj $w.obj.type {left expand} $w.obj.name {left expand}
			pack append $w $w.obj $opts
		}
		if ![string compare [lindex $arg 0] cmd] {
			mk_cmd_set $w.cmd [lindex $arg 1]
			pack append $w $w.cmd $opts
		}
		if ![string compare [lindex $arg 0] param] {
			mk_param_set $w.param [lindex $arg 1]
			pack append $w $w.param $opts
		}
		if ![string compare [lindex $arg 0] flag] {
			mk_flag_set $w.flag [lindex $arg 1]
			pack append $w $w.param $opts
		}
		if ![string compare [lindex $arg 0] info] {
			mk_info_set $w.info [lindex $arg 1]
			pack append $w $w.info $opts
		}
	}
}

proc obj_param {name entry {val _noval_}} {
	if ![string compare $val _noval_] {
		$name.param.$entry.val get
	} else {
#		$name.param.$entry.val delete 0 [srting length [$name.param.$entry.val get]]
		$name.param.$entry.val icursor 0
		$name.param.$entry.val delete 0 end
		$name.param.$entry.val insert 0 $val
	}
}

proc mk_cmd_set {w list} {
	frame $w
	foreach arg $list {
		set name [lindex $arg 0]
		set text [capitalize $name]
		if {[llength $arg] == 2} {
			set command [lindex $arg 1]
		} else {
			set command $w.$arg.cmd
		}
		button $w.$name -text $text -command $command
		pack append $w $w.$name {left padx 10 expand}
	}
}

proc mk_param_set {w list} {
	frame $w
	foreach arg $list {
		set var [lindex $arg 0]
		set val [lindex $arg 1]
		frame $w.$var
		label $w.$var.var -text $var
		global $w.$var
		set $w.$var $val
		entry $w.$var.val -width 6 -relief sunken -textvariable $w.$var
		pack append $w.$var $w.$var.var {left expand} $w.$var.val {left expand}
		pack append $w $w.$var {left padx 10 expand}
	}
}

proc mk_info_set {w list} {
	frame $w
	foreach arg $list {
		set name [lindex $arg 0]
		set var [lindex $arg 1]
		frame $w.$name
		label $w.$name.name -text $name
		global $var
		label $w.$name.var -relief raised -textvariable $var
		pack append $w.$name $w.$name.name {left expand} $w.$name.var {left expand}
		pack append $w $w.$name {left padx 10 expand}
	}
}

proc mk_info_set1 {w list} {
	frame $w
	foreach arg $list {
		frame $w.$arg
		label $w.$arg.var -text $arg
		global $w.$arg
		label $w.$arg.val -relief raised -textvariable $w.$arg
		pack append $w.$arg $w.$arg.var {left expand} $w.$arg.val {left expand}
		pack append $w $w.$arg {left padx 10 expand}
	}
}

# Local Variables:
# tab-width: 4
# End:
