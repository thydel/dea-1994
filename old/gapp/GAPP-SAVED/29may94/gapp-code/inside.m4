def(`one',`(`dest', `size')',`
	c := 1;
	loop(`i', ifelse(size,,1,size),`
		ram eval(dest + i) := c;
	')
')

def(`zero',`(`dest', `size')',`
	c := 0;
	loop(`i', ifelse(size,,1,size),`
		ram eval(dest + i) := c;
	')
')

def(`and',`(`src1', `src2', `dest', `size')',`
	loop(`i', ifelse(size,,1,size),`
		ns := ram eval(src1 + i); c := 0;
		ew := ram eval(ifelse(src2,,src1,src2) + i);
		c := cy;
		ram eval(ifelse(dest,,src1,dest) + i) := c;
	')
')

def(`or',`(`src1', `src2', `dest', `size')',`
	loop(`i', ifelse(size,,1,size),`
		ns := ram eval(src1 + i); c := 1;
		ew := ram eval(ifelse(src2,,src1,src2) + i);
		c := cy;
		ram eval(ifelse(dest,,src1,dest) + i) := c;
	')
')

def(`xor',`(`src1', `src2', `dest', `size')',`
	loop(`i', ifelse(size,,1,size),`
		ns := ram eval(src1 + i); c := 0;
		ew := ram eval(ifelse(src2,,src1,src2) + i);
		ram eval(ifelse(dest,,src1,dest) + i) := sm;
	')
')

def(`not',`(`src', `dest', `size')',`
	loop(`i', ifelse(size,,1,size),`
		ns := ram src; ew := 0; c := 1;
		ram ifelse(dest,,src,dest) := sm;
	')
')

def(`mov',`(`src', `dest', `size')',`
	loop(`i', ifelse(size,,1,size),`
		c := ram eval(src + i);
		ram eval(dest + i) := c;
	')
')

def(`add', `(`src1', `src2', `dest', `size')',`
	ns := ram src1; c := 0;
	ew := ram src2;
	ram ifelse(dest,,src1,dest) := sm; c := cy;
	for(`i', 1, ifelse(size,,1,size), 1,`
		ns := ram eval(src1 + i);
		ew := ram eval(ifelse(src2,,src1,src2) + i);
		ram eval(ifelse(dest,,src1,dest) + i) := sm; c := cy;
	')
	ram eval(ifelse(dest,,src1,dest) + ifelse(size,,1,size)) := c;
')

def(`sub', `(`src1', `src2', `dest', `size')',`
	ns := ram src1; c := 0;
	ew := ram src2;
	ram ifelse(dest,,src1,dest) := sm; c := bw;
	for(`i', 1, ifelse(size,,1,size), 1,`
		ns := ram eval(src1 + i);
		ew := ram eval(ifelse(src2,,src1,src2) + i);
		ram eval(ifelse(dest,,src1,dest) + i) := sm; c := bw;
	')
	ram eval(ifelse(dest,,src1,dest) + ifelse(size,,1,size)) := c;
')

def(`umul', `(`ande', `ande_size', `ateur', `ateur_size', `result')',`
	alloc_name(`carry', 1)
	zero(eval(ande_size + ateur_size), result)
	loop(`i', ateur_size,`
		c := 0;
		loop(`j', ande_size,`
			ram carry := c;
			ns := ram eval(ateur + i);
			ew := ram eval(ande + j); c := 0;
			c := cy; ns := ram eval(result + i + j);
			ew := ram carry;
			ram eval(result + i + j) := sm; c := cy;
		')
		ram eval(result + i + ande_size) := c;
	')
	free_name(`carry')
')

