foreach func {brain} {
	lappend func_list $func
}

foreach func {4 5 8 9} {
	lappend func_list sum${func}_tab
}

foreach func {and or xor} {
	foreach narg {4 5} {
		lappend func_list VN_$func$narg Moore_$func$narg
	}
}

foreach func {and or xor} {
	foreach narg {4 5 8 9} {
		lappend func_list Moore_$func$narg
	}
}

