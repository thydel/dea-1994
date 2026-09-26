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

proc browse_dir_getsel {w usesel} {
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
		$usesel $casdir/$dir/$tmp
	} }

proc browse_list {name list cmd} {
	catch {destroy .$name}
	toplevel .$name
	wm title .$name $name
	wm iconname .$name $name
	wm minsize .$name 10 10

	global casdir
	mk_browser .$name.list $name "" browse_list_getsel $cmd $list
	button .$name.close -text close -command "destroy .$name"

	pack append .$name \
		.$name.list {top expand fill} \
		.$name.close {top expand fill} }

proc browse_list_getsel {w usesel} {
	set index [$w.browse.list curselection]
	if ![llength $index] {
		return
	}
	set selected [$w.browse.list get $index]
	$w.selected configure -text $selected
	$usesel $selected }

proc mk_browser {w label selected getcmd usecmd {list {}}} {
	frame $w -relief raised -borderwidth 4

	label $w.label -text $label
	label $w.selected -text $selected -relief sunken
	button $w.ok -text Ok -command "$getcmd $w $usecmd"

	frame $w.browse -borderwidth 10
	scrollbar $w.browse.scrolly -relief sunken -command \
		"$w.browse.list yview"
	scrollbar $w.browse.scrollx -relief sunken -command \
		"$w.browse.list xview" \
		-orient horizontal
	listbox $w.browse.list -relief sunken -setgrid 1 \
		-yscroll "$w.browse.scrolly set" \
		-xscroll "$w.browse.scrollx set"
	tk_listboxSingleSelect $w.browse.list
	bind $w.browse.list <Double-Button-1> "$getcmd $w $usecmd"
	pack append $w.browse \
		$w.browse.scrolly {right filly} \
		$w.browse.scrollx {bottom fillx} \
		$w.browse.list {left expand fill}

	pack append $w \
		$w.label {top expand} \
		$w.ok {top expand} \
		$w.selected {top expand} \
		$w.browse {top expand fill}

	if [string compare $list {}] {
		browser_fill $w $selected $list
	} }

proc browser_fill {w selected list} {
	$w.browse.list delete 0 end
	foreach arg $list { $w.browse.list insert end $arg }
#	$w.browse.list select clear #	$w.browse.list select to
	$w.selected configure -text $selected }

