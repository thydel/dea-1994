def(`axes',`(`dir')',dnl
	`ifelse(dir, `n', `ns', dir, `s', `ns', dir, `e', `ew', dir, `w', `ew', `error')')

def(`get_ortho',`(`dir', `src', `dest', `size')',`
	loop(`i', ifelse(size,,1,size),`
		axes(dir) := ram eval(src + i)
		axes(dir) := dir
		c := axes(dir)
		ram eval(dest + i) := c
	')
')

def(`get_diag',`(`dir1', `dir2', `src', `dest', `size')',`
	loop(`i', ifelse(size,,1,size),`
		axes(dir1) := ram eval(src + i)
		axes(dir1) := dir1
		axes(dir2) := axes(dir1)
		axes(dir2) := dir2
		c := axes(dir2)
		ram eval(dest + i) := c
	')
')

def(`life',`(`src', `dest')',`
	get_ortho(`n', src, dest)
	get_ortho(`s', src, eval(dest + 1))
	get_ortho(`e', src, eval(dest + 2))
	get_ortho(`w', src, eval(dest + 3))
	get_diag(`n', `e', src, eval(dest + 4))
	get_diag(`n', `w', src, eval(dest + 5))
	get_diag(`s', `e', src, eval(dest + 6))
	get_diag(`s', `w', src, eval(dest + 7))
')
