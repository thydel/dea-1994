#!/usr/local/bin/wish -f

source widget/browse.tcl
source widget/object.tcl
source widget/showVars.tcl

source func_list.tcl

set casdir $env(CASDIR)

proc out {str} { puts stdout $str; flush stdout }

proc cmd_quit {} { destroy . }
proc cmd_frame_select {frame} { out "frame $frame" }
proc cmd_frame {} { browse_dir frame data/frame cmd_frame_select}
proc cmd_func_select {func} { out "func $func" }
proc cmd_func {} { global func_list; browse_list func $func_list cmd_func_select}

proc cmd_first {} { puts stdout "first; view"; flush stdout }
proc cmd_last {} { puts stdout "last; view"; flush stdout }
proc cmd_next {} { puts stdout "next; view"; flush stdout }
proc cmd_prev {} { puts stdout "prev; view"; flush stdout }

proc var_cnt {} { return [.cas.ctl.param.cnt.entry get] }
proc var_skip {} { return [.cas.ctl.param.skip.entry get] }
proc var_view {} { return [.cas.ctl.param.view.entry get] }
proc var_store {} { return [.cas.ctl.param.store.entry get] }

proc cmd_run {} { out "run [var_cnt]" }
proc cmd_step {} { out "run 1" }
proc cmd_cont {} { out "cont" }
proc cmd_cycle {} { out "cycle [var_skip]" }
proc cmd_forw {} { out "forw [var_skip]" }
proc cmd_back {} { out "back [var_skip]" }
proc cmd_rec {} { out "seq [var_view] [var_store]" }

proc var_rand {} { return [.cas.space.param.rand.entry get] }
proc var_solid {} { return [.cas.space.param.solid.entry get] }

proc cmd_zero {} { out "zero; sync" }
proc cmd_one {} { out "one; sync" }
proc cmd_solid {} { out "solid [var_solid]; sync" }
proc cmd_rand {} { out "rand [var_rand]; sync" }
proc cmd_bloc {} { out "brand [var_solid] [var_rand]; sync" }

proc mk_cas {} {
	wm minsize . 64 64

	# set opts {top pady 10 expand fill}
	set opts {top pady 10}

	mk_obj .cas Cas \
		{quit func frame} {} {} {}
	pack append . .cas {top fill}

	mk_obj .cas.ctl Ctl \
		{run step cont cycle forw back rec} \
		{{skip 1} {cnt 1} {view 1} {store 1}} {} {}
	pack append .cas .cas.ctl $opts

	mk_obj .cas.space Space \
		{zero one solid rand bloc} \
		{{rand 2} {solid 16}} {} {}
	pack append .cas .cas.space $opts

	mk_obj .cas.pos Pos \
		{first last next prev} {} {} {}
	pack append .cas .cas.pos $opts
}

mk_cas
