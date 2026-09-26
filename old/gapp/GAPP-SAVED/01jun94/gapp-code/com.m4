def(`left', `(`src', `dest', `dist', `size')',`
	loop(`i', ifelse(size,,1,size),`
		ew := ram eval(src + i);
		loop(`j', ifelse(dist,,1,dist),`
			ew := e;
		')
		c := ew;
		ram eval(ifelse(dest,,src,dest) + i) := c;
	')
')

def(`right', `(`src', `dest', `dist', `size')',`
	loop(`i', ifelse(size,,1,size),`
		ew := ram eval(src + i);
		loop(`j', ifelse(dist,,1,dist),`
			ew := w;
		')
		c := ew;
		ram eval(ifelse(dest,,src,dest) + i) := c;
	')
')

