def(`foo1',`(`src', `dest', `size', `n')',`
	mov(src, dest, size)
	loop(`i', eval(n - 1),`
		left(src, src, 1, size)
		add(src, dest, dest, eval(size + i))
	')
')

def(`ladd',`(`src', `dest', `dist', `size')',`
	ew := ram src;
	loop(`i', eval(dist - 1),`
		ew := e;
	')
	ew := e; ns := ram src; c := 0;
	ram dest := sm; c := cy;
	for(`i', 1, size, 1,`
		ew := ram eval(src + i);
		loop(`j', eval(dist - 1),`
			ew := e;
		')
		ew := e; ns := ram eval(src + i);
		ram eval(dest + i) := sm; c := cy;
	')
	ram eval(dest + size) := c;
')

def(`foo2',`(`src', `size', `n')',`
	loop(`i', n,`
		ladd(src, src, eval(2**i), eval(size + i))
	')
')
