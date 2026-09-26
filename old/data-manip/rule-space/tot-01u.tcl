#!casbin -f

source ../../tcl/conex.tcl

Func cmd sum8_tab [ConexSpec $moore_1 $local_1 moore_1] Moore_sum8_tab sum8_tab_parse
Func cmd sum9_tab [ConexSpec $moore_1 $local_1 moore_1] Moore_sum9_tab sum9_tab_parse

if 1 {
	set life 00U100000
	sum8_tab bind $life
	echo $life [sum8_tab lambda] [sum8_tab enchassement]
}

if 0 {
	set xxx 00U1F0000
	sum8_tab bind $xxx
	echo $xxx [sum8_tab lambda] [sum8_tab enchassement]
}

if 0 {	
	foreach i {000000000 111111111 UUUUUUUUU 0000U1111} {
		sum8_tab bind $i
		set E [sum8_tab enchassement]
		echo [sum8_tab lambda] [lindex $E 0] [lindex $E 4] [lindex $E 9] $i
	}
}


# set val {0 1}
set val {0 1 U}
# set val {0 1 U F}
	
if 0 {
	foreach i0 $val {
	foreach i1 $val {
	foreach i2 $val {
	foreach i3 $val {
	foreach i4 $val {
	foreach i5 $val {
	foreach i6 $val {
	foreach i7 $val {
	foreach i8 $val {
		set rule $i0$i1$i2$i3$i4$i5$i6$i7$i8
		sum8_tab bind $rule
		set E [sum8_tab enchassement]
		echo [sum8_tab lambda] [lindex $E 0] [lindex $E 4] [lindex $E 9] $rule
	}}}}}}}}}
}

if 0 {
	foreach i0 $val {
	foreach i1 $val {
	foreach i2 $val {
	foreach i3 $val {
	foreach i4 $val {
	foreach i5 $val {
	foreach i6 $val {
	foreach i7 $val {
	foreach i8 $val {
	foreach i9 $val {
		set rule $i0$i1$i2$i3$i4$i5$i6$i7$i8$i9
		sum9_tab bind $rule
		set E [sum9_tab enchassement]
		echo [sum9_tab lambda] [lindex $E 0] [lindex $E 4] [lindex $E 9] $rule
	}}}}}}}}}}
}

exit
