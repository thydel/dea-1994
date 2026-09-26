#!/usr/local/bin/wish -f

source func_list.tcl

set but(first) "first; view"
set but(last) "last; view"
set but(next) "next; view"
set but(prev) "prev; view"

set but(run) "run \$cnt_val"
set but(step) "run 1"
set but(cont) "cont"
set but(cycle) "cycle \$skip_val"
set but(forw) "forw \$skip_val"
set but(back) "back \$skip_val"
set but(seq) "seq \$view_timer_val \$store_timer_val"

set but(zero) "zero; sync"
set but(one) "one; sync"
set but(rand) "rand \$rand_val; sync"
set but(solid) "solid \$solid_val; sync"
set but(brand) "brand \$solid_val \$rand_val; sync"

foreach button [array names but] {
	button .$button -text $button -command "puts stdout {$but($button)}; flush stdout"
}

button .quit -text "quit" -command "destroy ."
button .func -text "func" -command "mkListbox .list func $func_list"
button .cnt -text "cnt" -command "mkVScale .scale1 cnt 300 0 256"
button .randv -text "randv" -command "mkVScale .scale2 rand 300 0 64"
button .solidv -text "solidv" -command "mkVScale .scale3 solid 300 0 128"
button .skipv -text "skipv" -command "mkVScale .scale4 skip 300 0 64"
button .viewTv -text "viewTv" -command "mkVScale .scale5 view_timer 300 0 64"
button .storeTv -text "storeTv" -command "mkVScale .scale6 store_timer 300 0 64"
button .bind8 -text "bind8" -command "nbind .bind1 bind8 9"
button .bind9 -text "bind9" -command "nbind .bind2 bind9 10"

foreach button {quit func cnt skipv randv solidv viewTv storeTv bind8 bind9} {
	pack append . .$button {left}
}

foreach button [array names but] {
	pack append . .$button {left}
}

proc nbind {w name cnt} {
	catch {destroy $w}
	toplevel $w
	wm title $w $name
	wm iconname $w $name
	frame $w.frame
	pack append $w $w.frame {left}
	for {set i 0} {$i < $cnt} {incr i} {
		frame $w.frame.frame$i
		bind1 $w.frame.frame$i bit$i
		global bit$i
		set bit$i bit${i}1
		pack append $w.frame $w.frame.frame$i {left}
	}
	button $w.frame.ok -text ok -command "getbind $w.frame $cnt"
	button $w.frame.close -text close -command "destroy $w"
	pack append $w.frame $w.frame.ok {top} $w.frame.close {top}
}

proc getbind {w cnt} {
	global bind_val
	set bind_val ""
	for {set i 0} {$i < $cnt} {incr i} {
		global bit$i
		set tmp [expr "[string index [set bit$i] 4] - 1"]
		if {$tmp == 2} {set tmp U}
		set bind_val $bind_val$tmp
	}
	echo set bind_val $bind_val
	echo bind \$bind_val
}

proc bind1 {w name} {
	radiobutton $w.${name}1 -text 0 -variable $name
	radiobutton $w.${name}2 -text 1 -variable $name
	radiobutton $w.${name}3 -text U -variable $name
	pack append $w $w.${name}1 {top} $w.${name}2 {top} $w.${name}3 {top}
}

proc bind {w name} {
	catch {destroy $w}
	toplevel $w
	wm title $w $name
	wm iconname $w $name
	frame $w.frame
	radiobutton $w.radio1 -text 0
	radiobutton $w.radio2 -text 1
	radiobutton $w.radio3 -text U
	pack append $w $w.frame {top} $w.radio1 {top} $w.radio2 {top} $w.radio3 {top}
}

proc mkListbox {w name args} {
    catch {destroy $w}
    toplevel $w
#    dpos $w
    wm title $w $name
    wm iconname $w $name
    wm minsize $w 1 1
    frame $w.frame -borderwidth 10
    scrollbar $w.frame.scroll -relief sunken -command "$w.frame.list yview"
    listbox $w.frame.list -yscroll "$w.frame.scroll set" -relief sunken -setgrid 1
    pack append $w.frame $w.frame.scroll {right filly} \
	    $w.frame.list {left expand fill}
	foreach func $args { $w.frame.list insert 0 $func }
    button $w.ok -text ok -command "getsel $w.frame.list $name"
    button $w.close -text close -command "destroy $w"
    pack append $w $w.frame {top expand filly frame center} \
	$w.ok {bottom fill} $w.close {bottom fill}
}

proc dpos w {
    wm geometry $w +200+200
}

proc getsel {w cmd} {
	set l [$w curselection]
	if {[llength $l] == 1} {
		set tmp [$w get $l]
		puts stdout "$cmd $tmp"; flush stdout
	}
}

proc mkVScale {w name size min max} {
    catch {destroy $w}
    toplevel $w
#    dpos $w
    wm title $w $name
    wm iconname $w $name
    frame $w.frame -borderwidth 4
    pack append $w.frame \
	[scale $w.frame.scale -orient vertical -length $size -from $min -to $max \
	    -command "setHeight $w.frame.right.inner" -tickinterval 50 \
	    -bg "light blue" -fg black] {left expand frame ne} \
	[frame $w.frame.right -borderwidth 15] {right expand frame nw}
    pack append $w.frame.right \
	[frame $w.frame.right.inner -geometry 40x20 -relief raised \
	    -borderwidth 2 -bg SteelBlue1] {expand frame nw}
    $w.frame.scale set 20
    button $w.ok -text ok -command "getval $w.frame.scale $name"
    button $w.close -text close -command "destroy $w"
    pack append $w $w.frame {top expand fill} \
	$w.ok {bottom fill} \
	$w.close {bottom fill}
}

proc setHeight {w height} {
    $w config -geometry 40x${height}
}

proc getval {w cmd} {
	set tmp [$w get]
	puts stdout "set ${cmd}_val $tmp"
#	puts stdout "$cmd \$${cmd}_val"
	flush stdout
}
