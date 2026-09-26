def(`left', `(`src', `dest', `dist', `size')',`
	loop(`i', ifelse(size,,1,size),`
		ew := src;
		loop(`j', ifelse(dist,,1,dist),`
			ew := e;
		')
		c := ew;
		ram ifelse(dest,,src,dest) := c;
	')
')

def(`right', `(`src', `dest', `dist', `size')',`
	loop(`i', ifelse(size,,1,size),`
		ew := src;
		loop(`j', ifelse(dist,,1,dist),`
			ew := w;
		')
		c := ew;
		ram ifelse(dest,,src,dest) := c;
	')
')

# add(src1, src2, dest)
# dest = src1 + src2
define(`add',`
	ns := ram $1; c := 0;
	ew := ram $2;
	ram $3 := sm; c := cy;
	repeat(decr(nbits),
		ew := c;
		ew := e; ns := ram $3; c := 0;
		ram $3 := sm; c := cy;
	)
')

def(`Add',`(`src1', `src2', `dest')',`
	ns := ram src1; c := 0;
	ew := ifelse(src2,,src1,src2);
	ram ifelse(dest,,src1,dest) := sm; c := cy;
	repeat(decr(NBITS),`
		ew := c;
		ew := e; ns := ifelse(dest,,src1,dest); c := 0;
		ram ifelse(dest,,src1,dest) := sm; c := cy;
	')
')

# neg(src, dest)
# dest = -src
define(`neg',`
alloc(1)
	not($1, $2)
	least(tmp(1))
	add($2, tmp(1), $2)
free(1)
')

# sub(src1, src2, dest)
# dest = src1 - src2 
define(`sub',`
	neg($2, $3)
	add($1, $3, $3)
')

# wide_l(src, dest, n)
# loop(i = $n) dest |= (src << i)
define(`wide_l',`
	c := ram $1;
	repeat(decr($3),
		ew := c;
		ew := e; ns := 0;
		c := bw;
		ram $2 := c;
	)
')

# wide_r(src, dest, n)
# loop(i = $n) dest |= (src >> i)
define(`wide_r',`
	c := ram $1;
	repeat(decr($3),
		ew := c;
		ew := w; ns := 0;
		c := bw;
		ram $2 := c;
	)
')

# wide(src, dest)
# loop(i = $most) dest |= src[i]
define(`wide',`
	wide_l($1, $2, nbits)
	wide_r($1, $2, nbits)
')

# wide_most(src, dest)
# dest = src[$most]
define(`wide_most',`
	wide_r($1, $3, nbits)
')

# wide_least(src, dest)
# dest = src[1]
define(`wide_least',`
	wide_l($1, $3, nbits)
')

# equalp(src1, src2, dest)
# dest = (src1 == src2) ? 1 : 0
# (one means all bits to 1) 
define(`equal',`
	sub($1, $2, $3)
	wide($3, $3)
	not($3, $3)
')

# mostp(src, dest)
# dest = (src < 0) ? 1 : 0
# dest = src[$most]
define(`mostp',`
alloc(1)
	most(tmp(1))
	and($1, tmp(1), $2)
	wide_most($2, $2)
free(1)
')

# leastp(src, dest)
# dest = src[0]
define(`leastp',`
alloc(1)
	least(tmp(1))
	and($1, tmp(1), $2)
	wide_least($2, $2)
free(1)
')

# cond(dest, test, src1, src2)
# dest = (test == 1) ? src1 : (test == 0 ? src2 : *garbage*)
define(`cond',`
alloc(2)
	and($2, $3, tmp(1))
	not($2, tmp(2))
	and(tmp(2), $4, tmp(2))
	or(tmp(1), tmp(2), $1)
free(2)
')

# abs(src, dest)
# dest = (src < 0) ? -src : src
define(`abs',`
alloc(2)
	mostp($1, tmp(1))
	neg($1, tmp(2))
	cond($2, tmp(1), tmp(2), $1)
free(2)
')

# mul(multplicande, multiplicateur, dest)
# dest = multiplicande * multiplicateur
define(`mul',`
alloc(6)
	mostp($1, tmp(1))
	mostp($2, tmp(2))
	xor(tmp(1), tmp(2), tmp(1))
	abs($1, tmp(2))
	abs($2, tmp(3))
	zero($3)
	least(tmp(4))
	repeat(nbits,
		add(tmp(2), $3, tmp(5))
		and(tmp(4), tmp(3), tmp(6))
		wide(tmp(6), tmp(6))
		cond($3, tmp(6), tmp(5), $3)
		shift_l(tmp(4), tmp(4), 1)
		shift_l(tmp(2), tmp(2), 1)
	)
	neg($3, tmp(4))
	cond($3, tmp(1), tmp(4), $3)
free(6)
')

# unsigned mul
# umul(multplicande, multiplicateur, dest)
# dest = multiplicande * multiplicateur
define(`umul',`
alloc(3)
	zero($3)
	least(tmp(1))
	move($1, tmp(2))
	repeat(nbits,
		add(tmp(2), $3, tmp(3))
		and(tmp(1), $2, tmp(4))
		wide(tmp(4), tmp(4))
		cond($3, tmp(4), tmp(3), $3)
		shift_l(tmp(1), tmp(1), 1)
		shift_l(tmp(2), tmp(2), 1)
	)
free(3)
')

# ge(src1, src2, dest)
# dest = (src1 >= src2) ? 1 : 0
define(`ge',`
	sub($1, $2, $3)
	mostp($3, $3)
	not($3, $3)
')

# lt(src1, src2, dest)
# dest = (src1 < src2) ? 1 : 0
define(`gt',`
	sub($1, $2, $3)
	mostp($3, $3)
')

# bump_l(src, dest, mask)
# dest = src << $most - $high(src)
# mask = 0, mask[$most - $high(src)] = 1
# src	00010010
# dest	10010000
# mask	00001000
define(`bump_l',`
alloc(3)
	move($1, $2)
	least(mask)
	repeat(decr(nbits),
		shift_l($2, tmp(1), 1)
		shift_l(mask, tmp(2), 1)
		mostp($2, tmp(3))
		cond($2, tmp(3), $2, tmp(1))
		cond(mask, tmp(3), mask, tmp(2))
	)
free(3)
')

# bump_r(src, mask, dest)
# dest = src >> $high(mask)
# src	10010000
# mask	00001000
# dest	00010010
define(`bump_r',`
alloc(3)
	move($1, $3)
	repeat(decr(nbits),
		shift_r($2, tmp(1), 1)
		shift_r($3, tmp(2), 1)
		leastp(tmp(1), tmp(3))
		cond($2, tmp(3), $2, tmp(1))
		cond($3, tmp(3), $3, tmp(2))
	)
free(3)
')

# most(dest)
# dest[$most] = 1
# dest[$most - 1 ... 0] = 0
def(`Most', `(`dest')',`
	one(dest)
	right(dest)
	not(dest)
')

# least(dest)
# dest[0] = 1
# dest[$most ... 1] = 0
def(`Least', `(`dest')',`
	one(dest)
	left(dest)
	not(dest)
')
