proc browse_dir {name dir cmd} {
	catch {destroy .$name}
	toplevel .$name
	wm title .$name $name
	wm iconname .$name $name
	wm minsize .$name 10 10

	global casdir
	mk_browser .$name.dir $name $dir browse_dir_getsel $cmd [exec ls -aF $casdir/$dir]
	button .$name.close -text close -command "destroy .$name"

	pack append .$name \
		.$name.dir {top expand fill} \
		.$name.close {top}
}

proc browse_dir_getsel {w} {
	global casdir
	set index [$w.browse.list curselection]
	if ![llength $index] {
		return
	}
	set dir [lindex [$w.selected configure -text] 4]
	set tmp [string trimright [$w.browse.list get $index] "*/@"]
	if [file isdirectory $casdir/$dir/$tmp] {
		if ![string compare $tmp ..] {
			set last [string last / $dir]
			if {$last == -1} {
				set newdir $dir
			} else {
				incr last -1
				set newdir [string range $dir 0 $last]
			}
		} elseif ![string compare $tmp .] {
			set newdir $dir
		} else {
			set newdir $dir/$tmp
		}
		browser_fill $w $newdir [exec ls -aF $casdir/$newdir]
	} else {
		$w.selected configure -text $casdir/$dir/$tmp
	}
}

set browse_list {
	{name browse_list}
	{cmd {
		{ok {
			global $w.info.selected
			set $w.info.selected [browser_getsel $w.browser]; $cmd
		}}
		{close {cmd_close $w}}
		{unpack {cmd_unpack $w}}
	}}
	{info {{selected $w.info.selected}}}
}

gen_top browse_list {list cmd}
proc mk_browse_list {w list cmd} {
	if [winfo exist $w] {cmd_close $w}
	set opts {top pady 10 padx 10 expand}

	global browse_list
	mk_obj $w [expand {w cmd} $browse_list]

	mk_browser $w.browser $list
	global $w.info.selected
	set tmp [lsearch $list [set $w.info.selected]]
	if {$tmp == -1} {
		set tmp 0
	}
	$w.browser.list select to $tmp
	$w.browser.list yview $tmp
	set $w.info.selected [browser_getsel $w.browser]
	pack append $w $w.browser $opts
}

proc mk_browser {w {list {}}} {
	frame $w -borderwidth 10
	scrollbar $w.scrolly -relief sunken -command "$w.list yview"
	scrollbar $w.scrollx -relief sunken -command "$w.list xview" -orient horizontal
	listbox $w.list -relief sunken -setgrid 1 \
		-yscroll "$w.scrolly set" \
		-xscroll "$w.scrollx set"
	tk_listboxSingleSelect $w.list
	pack append $w \
		$w.scrolly {right filly} \
		$w.scrollx {bottom fillx} \
		$w.list {left expand fill}
	browser_fill $w $list
}

proc browser_fill {w list} {
	$w.list delete 0 end
	foreach arg $list { $w.list insert end $arg }
}

proc browser_getsel {w} {$w.list get [$w.list curselection]}

# Local Variables:
# tab-width: 4
# End:
