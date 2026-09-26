# VN shift
set vnfunclist [list north south east west]

# VN op
foreach func {and or xor} {
	foreach narg {4 5} {
		lappend vnfunclist $func$narg
	}
}

foreach func $vnfunclist {
	Func cmd VN_$func $VN_1 VN_$func
	VN_$func bind
	lappend func_list VN_$func
}

# Moore op
foreach func {and or xor} {
	foreach narg {4 5 8 9} {
		lappend moorefunclist $func$narg
	}
}

foreach func $moorefunclist {
	Func cmd Moore_$func $Moore_1 Moore_$func
	Moore_$func bind
	lappend func_list Moore_$func
}

# SumTab
Func cmd sum4_tab $VN_1 VN_sum4_tab sum4_tab_parse
Func cmd sum5_tab $VN_1 VN_sum5_tab sum5_tab_parse
Func cmd sum8_tab [ConexSpec $moore_1 $local_1 moore_1] Moore_sum8_tab sum8_tab_parse
Func cmd sum9_tab [ConexSpec $moore_1 $local_1 moore_1] Moore_sum9_tab sum9_tab_parse

linsert func_list 0 sum4_tab sum5_tab sum8_tab sum9_tab

set casdir $env(CASDIR)

# Cellsim tbl
# Func cmd tunnel [ConexSpec $vn_3 $local_3 vn_3] -f tunnel.pgm
Func cmd brain [ConexSpec $moore_2 $local_2 moore_2] -f $casdir/data/cellsim/Rules/brain.pgm
Func cmd xxx $VN_1 -f $casdir/data/cell/rule/xxx.pgm
Func cmd yyy $VN_1 -f $casdir/data/cell/rule/yyy.pgm

set life	00U100000
set ink8	UUU1UUUUU
set maj9	0000011111
set anneal9	0000101111

sum8_tab bind $life
sum9_tab bind $anneal9
