

extern void __eprintf (const char *, const char *, unsigned, const char *);
typedef enum { 
	false, true 
} bool;
typedef struct {
	int magic;
	unsigned char* ptr;
	int size;
	int plane;
} StateVect;
extern StateVect* SV_new(int);
typedef struct {
	int magic;
	int* ptr;
	int size;
} CntVect;
extern CntVect* CV_new(int);
typedef struct {
	int magic;
	unsigned char* ptr;
	int xsize;
	int ysize;
	int size;
	int plane;
} StateFrame;
extern StateFrame* SF_new(int, int, int);
extern void SF_set(StateFrame*, int, int, int, int);
extern void SF_fill(StateFrame*, int, int, int);
typedef struct {
	int magic;
	unsigned char* ptr;
	int xsize;
	int ysize;
	int size;
	int plane;
} PlaneFrame;
extern PlaneFrame* PF_new(int, int, int);
extern void PF_extract(PlaneFrame*, StateFrame*, int, bool);
typedef struct {
	int magic;
	int* ptr;
	int xsize;
	int ysize;
	int size;
} CntFrame;
extern CntFrame* CF_new(int, int);
typedef struct {
	int magic;
	int (*size)();
	int (*bind)(StateVect*, int (*)());
	int (*next)(StateVect*, StateFrame*, StateFrame*);
	int (*stat_next)(StateVect*, StateFrame*, StateFrame*, CntVect*, CntVect*, CntFrame*);
} Conex;




typedef struct {
	char* name;
	void* ptr;
} Named;
extern Named null_named;
void* Named_get(Named*, char*);
extern int L;
extern int SUM;
extern int C;
extern int C0;
extern int C1;
extern int C2;
extern int C3;
extern int _C;
extern int _C0;
extern int _C1;
extern int _C2;
extern int _C3;
extern int N;
extern int N0;
extern int N1;
extern int N2;
extern int N3;
extern int _N;
extern int _N0;
extern int _N1;
extern int _N2;
extern int _N3;
extern int S;
extern int S0;
extern int S1;
extern int S2;
extern int S3;
extern int _S;
extern int _S0;
extern int _S1;
extern int _S2;
extern int _S3;
extern int E;
extern int E0;
extern int E1;
extern int E2;
extern int E3;
extern int _E;
extern int _E0;
extern int _E1;
extern int _E2;
extern int _E3;
extern int W;
extern int W0;
extern int W1;
extern int W2;
extern int W3;
extern int _W;
extern int _W0;
extern int _W1;
extern int _W2;
extern int _W3;
extern int NE;
extern int NE0;
extern int NE1;
extern int NE2;
extern int NE3;
extern int _NE;
extern int _NE0;
extern int _NE1;
extern int _NE2;
extern int _NE3;
extern int SE;
extern int SE0;
extern int SE1;
extern int SE2;
extern int SE3;
extern int _SE;
extern int _SE0;
extern int _SE1;
extern int _SE2;
extern int _SE3;
extern int NW;
extern int NW0;
extern int NW1;
extern int NW2;
extern int NW3;
extern int _NW;
extern int _NW0;
extern int _NW1;
extern int _NW2;
extern int _NW3;
extern int SW;
extern int SW0;
extern int SW1;
extern int SW2;
extern int SW3;
extern int _SW;
extern int _SW0;
extern int _SW1;
extern int _SW2;
extern int _SW3;
moore_1_size() { 
	return   (1 << 8 + 1) ; 
}  
moore_1_bind(StateVect* rt, int (*func)()) { 
	int index; 
	((void) ((rt->size ==   (1 << 8 + 1) ) ? 0 : (__eprintf ("%s:%u: failed assertion `%s'\n",	 "moore.c",  14, "rt->size == MOORE_1_SIZE"),
	    0) )) ; 
	for (index = 0; index <   (1 << 8 + 1) ; ++index) {   
		NW = (index & 1 << 8) >> 8; 
		W = (index & 1 << 7) >> 7; 
		SW = (index & 1 << 6) >> 6; 
		N = (index & 1 << 5) >> 5; 
		C = (index & 1 << 4) >> 4; 
		S = (index & 1 << 3) >> 3; 
		NE = (index & 1 << 2) >> 2; 
		E = (index & 1 << 1) >> 1; 
		SE = (index & 1 << 0) >> 0;  
		rt->ptr[index] = func(); 
	} 
}  
moore_1_next(StateVect* rule_tbl, StateFrame* sf_past, StateFrame* sf_futur) { 
	int i; 
	int j; 
	unsigned char* past; 
	unsigned char* futur; 
	unsigned char* transition; 
	int side; 
	int size; 
	register unsigned char* north; 
	register unsigned char* center; 
	register unsigned char* south; 
	register int index; 
	int w_index; 
	int c_index; 
	int e_index; 
	int c1; 
	int c2; 
	int index1; 
	int index2; 
	register int local; 
	int local1; 
	int local2; 
	int count;  
	past = sf_past->ptr; 
	futur = sf_futur->ptr; 
	transition = rule_tbl->ptr; 
	side = sf_past->xsize; 
	size = sf_past->ysize; 
	count = side - 2;  
	north = past + size - side; 
	center = past; 
	south = center + side;    
	index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6; 
	index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3; 
	index |=   *north++ << 2 |    *center++ << 1 |    *south++; 
	*futur++ = transition[index] ; 
	for (i = count; i--;) { 
		index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++; 
		*futur++ = transition[index] ; 
	} 
	index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side]; 
	*futur++ = transition[index] ;  
	; 
	north = past; 
	center = north + side; 
	south = center + side;  
	for (j = count; j--;) {   
		index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6; 
		index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3; 
		index |=   *north++ << 2 |    *center++ << 1 |    *south++; 
		*futur++ = transition[index] ; 
		for (i = count; i--;) { 
			index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++; 
			*futur++ = transition[index] ; 
		} 
		index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side]; 
		*futur++ = transition[index] ;  
		; 
	} 
	north = past + size - (side << 1); 
	center = north + side; 
	south = past;    
	index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6; 
	index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3; 
	index |=   *north++ << 2 |    *center++ << 1 |    *south++; 
	*futur++ = transition[index] ; 
	for (i = count; i--;) { 
		index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++; 
		*futur++ = transition[index] ; 
	} 
	index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side]; 
	*futur++ = transition[index] ;  
	; 
}
moore_1_stat_next(StateVect* rule_tbl, StateFrame* sf_past, StateFrame* sf_futur, CntVect* cv_rule_sum, CntVect* cv_hor_sum,
CntFrame* cf_vert_sum) { 
	int* rule_sum; 
	int* hor_sum; 
	int* vert_sum; 
	int tmp; 
	int i; 
	int j; 
	unsigned char* past; 
	unsigned char* futur; 
	unsigned char* transition; 
	int side; 
	int size; 
	register unsigned char* north; 
	register unsigned char* center; 
	register unsigned char* south; 
	register int index; 
	int w_index; 
	int c_index; 
	int e_index; 
	int c1; 
	int c2; 
	int index1; 
	int index2; 
	register int local; 
	int local1; 
	int local2; 
	int count;  
	rule_sum = cv_rule_sum->ptr; 
	hor_sum = cv_rule_sum->ptr; 
	vert_sum = cf_vert_sum->ptr; 
	past = sf_past->ptr; 
	futur = sf_futur->ptr; 
	transition = rule_tbl->ptr; 
	side = sf_past->xsize; 
	size = sf_past->ysize; 
	count = side - 2;  
	north = past + size - side; 
	center = past; 
	south = center + side;    
	index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6; 
	index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3; 
	index |=   *north++ << 2 |    *center++ << 1 |    *south++; 
	*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ; 
	for (i = count; i--;) { 
		index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++; 
		*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ; 
	} 
	index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side]; 
	*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ;  
	; 
	north = past; 
	center = north + side; 
	south = center + side;  
	for (j = count; j--;) {   
		index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6; 
		index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3; 
		index |=   *north++ << 2 |    *center++ << 1 |    *south++; 
		*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ; 
		for (i = count; i--;) { 
			index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++; 
			*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ; 
		} 
		index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side]; 
		*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ;  
		; 
	} 
	north = past + size - (side << 1); 
	center = north + side; 
	south = past;    
	index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6; 
	index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3; 
	index |=   *north++ << 2 |    *center++ << 1 |    *south++; 
	*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ; 
	for (i = count; i--;) { 
		index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++; 
		*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ; 
	} 
	index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side]; 
	*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ;  
	; 
}  
Conex moore_1_conex = { 
	(0  + 7) , moore_1_size, moore_1_bind, moore_1_next, moore_1_stat_next };
moore_2_size() { 
	return   (1 << (8 + 1) * 2) ; 
}  
moore_2_bind(StateVect* rt, int (*func)()) { 
	int index; 
	((void) ((rt->size ==   (1 << (8 + 1) * 2) ) ? 0 : (__eprintf ("%s:%u: failed assertion `%s'\n",	 "moore.c",  16,
	    "rt->size == MOORE_2_SIZE"), 0) )) ; 
	for (index = 0; index <   (1 << (8 + 1) * 2) ; ++index) {   
		NW = (index & 3 << 16) >> 16; 
		NW0 = NW & 1; 
		NW1 = NW & 2 >> 1; 
		W = (index & 3 << 14) >> 14; 
		W0 = W & 1; 
		W1 = W & 2 >> 1; 
		SW = (index & 3 << 12) >> 12; 
		SW0 = SW & 1; 
		SW1 = SW & 2 >> 1; 
		N = (index & 3 << 10) >> 10; 
		N0 = N & 1; 
		N1 = N & 2 >> 1; 
		C = (index & 3 << 8) >> 8; 
		C0 = C & 1; 
		C1 = C & 2 >> 1; 
		S = (index & 3 << 6) >> 6; 
		S0 = S & 1; 
		S1 = S & 2 >> 1; 
		NE = (index & 3 << 4) >> 4; 
		NE0 = NE & 1; 
		NE1 = NE & 2 >> 1; 
		E = (index & 3 << 2) >> 2; 
		E0 = E & 1; 
		E1 = E & 2 >> 1; 
		SE = (index & 3 << 0) >> 0; 
		SE0 = SE & 1; 
		SE1 = SE & 2 >> 1; 
		NW = (index & 3 << 16) >> 16; 
		NW0 = NW & 1; 
		NW1 = NW & 2 >> 1; 
		W = (index & 3 << 14) >> 14; 
		W0 = W & 1; 
		W1 = W & 2 >> 1; 
		SW = (index & 3 << 12) >> 12; 
		SW0 = SW & 1; 
		SW1 = SW & 2 >> 1; 
		N = (index & 3 << 10) >> 10; 
		N0 = N & 1; 
		N1 = N & 2 >> 1; 
		C = (index & 3 << 8) >> 8; 
		C0 = C & 1; 
		C1 = C & 2 >> 1; 
		S = (index & 3 << 6) >> 6; 
		S0 = S & 1; 
		S1 = S & 2 >> 1; 
		NE = (index & 3 << 4) >> 4; 
		NE0 = NE & 1; 
		NE1 = NE & 2 >> 1; 
		E = (index & 3 << 2) >> 2; 
		E0 = E & 1; 
		E1 = E & 2 >> 1; 
		SE = (index & 3 << 0) >> 0; 
		SE0 = SE & 1; 
		SE1 = SE & 2 >> 1;  
		rt->ptr[index] = func(); 
	} 
}  
moore_2_next(StateVect* rule_tbl, StateFrame* sf_past, StateFrame* sf_futur) { 
	int i; 
	int j; 
	unsigned char* past; 
	unsigned char* futur; 
	unsigned char* transition; 
	int side; 
	int size; 
	register unsigned char* north; 
	register unsigned char* center; 
	register unsigned char* south; 
	register int index; 
	int w_index; 
	int c_index; 
	int e_index; 
	int c1; 
	int c2; 
	int index1; 
	int index2; 
	register int local; 
	int local1; 
	int local2; 
	int count;  
	past = sf_past->ptr; 
	futur = sf_futur->ptr; 
	transition = rule_tbl->ptr; 
	side = sf_past->xsize; 
	size = sf_past->ysize; 
	count = side - 2;  
	north = past + size - side; 
	center = past; 
	south = center + side;    
	index = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12; 
	index |=   *north++ << 10 |    *center++ << 8  |    *south++ << 6; 
	index |=   *north++ << 4  |    *center++ << 2  |    *south++; 
	*futur++ = transition[index] ; 
	for (i = count; i--;) { 
		index = index << 6 & 0x0003ffff | *north++ << 4 | *center++ << 2 | *south++; 
		*futur++ = transition[index] ; 
	} 
	index = index << 6 & 0x0003ffff | north[-side] << 4 | center[-side] << 2 | south[-side]; 
	*futur++ = transition[index] ;  
	; 
	north = past; 
	center = north + side; 
	south = center + side;  
	for (j = count; j--;) {   
		index = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12; 
		index |=   *north++ << 10 |    *center++ << 8  |    *south++ << 6; 
		index |=   *north++ << 4  |    *center++ << 2  |    *south++; 
		*futur++ = transition[index] ; 
		for (i = count; i--;) { 
			index = index << 6 & 0x0003ffff | *north++ << 4 | *center++ << 2 | *south++; 
			*futur++ = transition[index] ; 
		} 
		index = index << 6 & 0x0003ffff | north[-side] << 4 | center[-side] << 2 | south[-side]; 
		*futur++ = transition[index] ;  
		; 
	} 
	north = past + size - (side << 1); 
	center = north + side; 
	south = past;    
	index = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12; 
	index |=   *north++ << 10 |    *center++ << 8  |    *south++ << 6; 
	index |=   *north++ << 4  |    *center++ << 2  |    *south++; 
	*futur++ = transition[index] ; 
	for (i = count; i--;) { 
		index = index << 6 & 0x0003ffff | *north++ << 4 | *center++ << 2 | *south++; 
		*futur++ = transition[index] ; 
	} 
	index = index << 6 & 0x0003ffff | north[-side] << 4 | center[-side] << 2 | south[-side]; 
	*futur++ = transition[index] ;  
	; 
}
moore_2_stat_next(StateVect* rule_tbl, StateFrame* sf_past, StateFrame* sf_futur, CntVect* cv_rule_sum, CntVect* cv_hor_sum,
CntFrame* cf_vert_sum) { 
	int* rule_sum; 
	int* hor_sum; 
	int* vert_sum; 
	int tmp; 
	int i; 
	int j; 
	unsigned char* past; 
	unsigned char* futur; 
	unsigned char* transition; 
	int side; 
	int size; 
	register unsigned char* north; 
	register unsigned char* center; 
	register unsigned char* south; 
	register int index; 
	int w_index; 
	int c_index; 
	int e_index; 
	int c1; 
	int c2; 
	int index1; 
	int index2; 
	register int local; 
	int local1; 
	int local2; 
	int count;  
	rule_sum = cv_rule_sum->ptr; 
	hor_sum = cv_rule_sum->ptr; 
	vert_sum = cf_vert_sum->ptr; 
	past = sf_past->ptr; 
	futur = sf_futur->ptr; 
	transition = rule_tbl->ptr; 
	side = sf_past->xsize; 
	size = sf_past->ysize; 
	count = side - 2;  
	north = past + size - side; 
	center = past; 
	south = center + side;    
	index = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12; 
	index |=   *north++ << 10 |    *center++ << 8  |    *south++ << 6; 
	index |=   *north++ << 4  |    *center++ << 2  |    *south++; 
	*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp & 1, hor_sum[1] += tmp & 2, *vert_sum++ +=
	    tmp, tmp) ; 
	for (i = count; i--;) { 
		index = index << 6 & 0x0003ffff | *north++ << 4 | *center++ << 2 | *south++; 
		*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp & 1, hor_sum[1] += tmp & 2, *vert_sum++
		    += tmp, tmp) ; 
	} 
	index = index << 6 & 0x0003ffff | north[-side] << 4 | center[-side] << 2 | south[-side]; 
	*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp & 1, hor_sum[1] += tmp & 2, *vert_sum++ +=
	    tmp, tmp) ;  
	; 
	north = past; 
	center = north + side; 
	south = center + side;  
	for (j = count; j--;) {   
		index = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12; 
		index |=   *north++ << 10 |    *center++ << 8  |    *south++ << 6; 
		index |=   *north++ << 4  |    *center++ << 2  |    *south++; 
		*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp & 1, hor_sum[1] += tmp & 2, *vert_sum++
		    += tmp, tmp) ; 
		for (i = count; i--;) { 
			index = index << 6 & 0x0003ffff | *north++ << 4 | *center++ << 2 | *south++; 
			*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp & 1, hor_sum[1] += tmp &
			    2, *vert_sum++ += tmp, tmp) ; 
		} 
		index = index << 6 & 0x0003ffff | north[-side] << 4 | center[-side] << 2 | south[-side]; 
		*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp & 1, hor_sum[1] += tmp & 2, *vert_sum++
		    += tmp, tmp) ;  
		; 
	} 
	north = past + size - (side << 1); 
	center = north + side; 
	south = past;    
	index = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12; 
	index |=   *north++ << 10 |    *center++ << 8  |    *south++ << 6; 
	index |=   *north++ << 4  |    *center++ << 2  |    *south++; 
	*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp & 1, hor_sum[1] += tmp & 2, *vert_sum++ +=
	    tmp, tmp) ; 
	for (i = count; i--;) { 
		index = index << 6 & 0x0003ffff | *north++ << 4 | *center++ << 2 | *south++; 
		*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp & 1, hor_sum[1] += tmp & 2, *vert_sum++
		    += tmp, tmp) ; 
	} 
	index = index << 6 & 0x0003ffff | north[-side] << 4 | center[-side] << 2 | south[-side]; 
	*futur++ = (rule_sum[index]++, tmp = transition[index], *hor_sum += tmp & 1, hor_sum[1] += tmp & 2, *vert_sum++ +=
	    tmp, tmp) ;  
	; 
}  
Conex moore_2_conex = { 
	(0  + 7) , moore_2_size, moore_2_bind, moore_2_next, moore_2_stat_next };
moore_1_7_size() { 
	return   (1 << 8 + 1 + 7) ; 
}  
moore_1_7_bind(StateVect* rt, int (*func)()) { 
	int index; 
	((void) ((rt->size ==   (1 << 8 + 1 + 7) ) ? 0 : (__eprintf ("%s:%u: failed assertion `%s'\n",	 "moore.c",  18, "rt->size == MOORE_1_7_SIZE"),
	    0) )) ; 
	for (index = 0; index <   (1 << 8 + 1 + 7) ; ++index) {   
		NW = (index & 1 << 8) >> 8; 
		W = (index & 1 << 7) >> 7; 
		SW = (index & 1 << 6) >> 6; 
		N = (index & 1 << 5) >> 5; 
		C = (index & 1 << 4) >> 4; 
		S = (index & 1 << 3) >> 3; 
		NE = (index & 1 << 2) >> 2; 
		E = (index & 1 << 1) >> 1; 
		SE = (index & 1 << 0) >> 0; 
		L = (index & (1 << 7) - 1 << 9) >> 9;  
		rt->ptr[index] = func(); 
	} 
}  
moore_1_7_next(StateVect* rule_tbl, StateFrame* sf_past, StateFrame* sf_futur) { 
	int i; 
	int j; 
	unsigned char* past; 
	unsigned char* futur; 
	unsigned char* transition; 
	int side; 
	int size; 
	register unsigned char* north; 
	register unsigned char* center; 
	register unsigned char* south; 
	register int index; 
	int w_index; 
	int c_index; 
	int e_index; 
	int c1; 
	int c2; 
	int index1; 
	int index2; 
	register int local; 
	int local1; 
	int local2; 
	int count;  
	past = sf_past->ptr; 
	futur = sf_futur->ptr; 
	transition = rule_tbl->ptr; 
	side = sf_past->xsize; 
	size = sf_past->ysize; 
	count = side - 2;  
	north = past + size - side; 
	center = past; 
	south = center + side;    
	local = (*center & 0x000000fe) << 8; 
	index = (north[side - 1] & 1) << 8 | (center[side - 1] & 1) << 7 | (south[side - 1] & 1) << 6; 
	index |=   (*north++ & 1) << 5 |    (*center++ & 1) << 4 |    (*south++ & 1) << 3; 
	index |=   (*north++ & 1) << 2 |      (*center & 1) << 1 |    (*south++ & 1); 
	*futur++ = transition[local | index] ; 
	for (i = count; i--;) { 
		local = (*center++ & 0x000000fe) << 8; 
		index = index << 3 & 0x000001ff | (*north++ & 1) << 2 | (*center & 1) << 1 | (*south++ & 1); 
		*futur++ = transition[local | index] ; 
	} 
	local = (*center++ & 0x000000fe) << 8; 
	index = index << 3 & 0x000001ff | (north[-side] & 1) << 2 | (center[-side] & 1) << 1 | (south[-side] & 1); 
	*futur++ = transition[local | index] ;  
	; 
	north = past; 
	center = north + side; 
	south = center + side;  
	for (j = count; j--;) {   
		local = (*center & 0x000000fe) << 8; 
		index = (north[side - 1] & 1) << 8 | (center[side - 1] & 1) << 7 | (south[side - 1] & 1) << 6; 
		index |=   (*north++ & 1) << 5 |    (*center++ & 1) << 4 |    (*south++ & 1) << 3; 
		index |=   (*north++ & 1) << 2 |      (*center & 1) << 1 |    (*south++ & 1); 
		*futur++ = transition[local | index] ; 
		for (i = count; i--;) { 
			local = (*center++ & 0x000000fe) << 8; 
			index = index << 3 & 0x000001ff | (*north++ & 1) << 2 | (*center & 1) << 1 | (*south++ & 1); 
			*futur++ = transition[local | index] ; 
		} 
		local = (*center++ & 0x000000fe) << 8; 
		index = index << 3 & 0x000001ff | (north[-side] & 1) << 2 | (center[-side] & 1) << 1 | (south[-side] & 1); 
		*futur++ = transition[local | index] ;  
		; 
	} 
	north = past + size - (side << 1); 
	center = north + side; 
	south = past;    
	local = (*center & 0x000000fe) << 8; 
	index = (north[side - 1] & 1) << 8 | (center[side - 1] & 1) << 7 | (south[side - 1] & 1) << 6; 
	index |=   (*north++ & 1) << 5 |    (*center++ & 1) << 4 |    (*south++ & 1) << 3; 
	index |=   (*north++ & 1) << 2 |      (*center & 1) << 1 |    (*south++ & 1); 
	*futur++ = transition[local | index] ; 
	for (i = count; i--;) { 
		local = (*center++ & 0x000000fe) << 8; 
		index = index << 3 & 0x000001ff | (*north++ & 1) << 2 | (*center & 1) << 1 | (*south++ & 1); 
		*futur++ = transition[local | index] ; 
	} 
	local = (*center++ & 0x000000fe) << 8; 
	index = index << 3 & 0x000001ff | (north[-side] & 1) << 2 | (center[-side] & 1) << 1 | (south[-side] & 1); 
	*futur++ = transition[local | index] ;  
	; 
}
moore_1_7_stat_next(StateVect* rule_tbl, StateFrame* sf_past, StateFrame* sf_futur, CntVect* cv_rule_sum, CntVect* cv_hor_sum,
CntFrame* cf_vert_sum) { 
	int* rule_sum; 
	int* hor_sum; 
	int* vert_sum; 
	int tmp; 
	int i; 
	int j; 
	unsigned char* past; 
	unsigned char* futur; 
	unsigned char* transition; 
	int side; 
	int size; 
	register unsigned char* north; 
	register unsigned char* center; 
	register unsigned char* south; 
	register int index; 
	int w_index; 
	int c_index; 
	int e_index; 
	int c1; 
	int c2; 
	int index1; 
	int index2; 
	register int local; 
	int local1; 
	int local2; 
	int count;  
	rule_sum = cv_rule_sum->ptr; 
	hor_sum = cv_rule_sum->ptr; 
	vert_sum = cf_vert_sum->ptr; 
	past = sf_past->ptr; 
	futur = sf_futur->ptr; 
	transition = rule_tbl->ptr; 
	side = sf_past->xsize; 
	size = sf_past->ysize; 
	count = side - 2;  
	north = past + size - side; 
	center = past; 
	south = center + side;    
	local = (*center & 0x000000fe) << 8; 
	index = (north[side - 1] & 1) << 8 | (center[side - 1] & 1) << 7 | (south[side - 1] & 1) << 6; 
	index |=   (*north++ & 1) << 5 |    (*center++ & 1) << 4 |    (*south++ & 1) << 3; 
	index |=   (*north++ & 1) << 2 |      (*center & 1) << 1 |    (*south++ & 1); 
	*futur++ = (rule_sum[local | index]++, tmp = transition[local | index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ; 
	for (i = count; i--;) { 
		local = (*center++ & 0x000000fe) << 8; 
		index = index << 3 & 0x000001ff | (*north++ & 1) << 2 | (*center & 1) << 1 | (*south++ & 1); 
		*futur++ = (rule_sum[local | index]++, tmp = transition[local | index], *hor_sum += tmp, *vert_sum++ += tmp,
		    tmp) ; 
	} 
	local = (*center++ & 0x000000fe) << 8; 
	index = index << 3 & 0x000001ff | (north[-side] & 1) << 2 | (center[-side] & 1) << 1 | (south[-side] & 1); 
	*futur++ = (rule_sum[local | index]++, tmp = transition[local | index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ;  
	; 
	north = past; 
	center = north + side; 
	south = center + side;  
	for (j = count; j--;) {   
		local = (*center & 0x000000fe) << 8; 
		index = (north[side - 1] & 1) << 8 | (center[side - 1] & 1) << 7 | (south[side - 1] & 1) << 6; 
		index |=   (*north++ & 1) << 5 |    (*center++ & 1) << 4 |    (*south++ & 1) << 3; 
		index |=   (*north++ & 1) << 2 |      (*center & 1) << 1 |    (*south++ & 1); 
		*futur++ = (rule_sum[local | index]++, tmp = transition[local | index], *hor_sum += tmp, *vert_sum++ += tmp,
		    tmp) ; 
		for (i = count; i--;) { 
			local = (*center++ & 0x000000fe) << 8; 
			index = index << 3 & 0x000001ff | (*north++ & 1) << 2 | (*center & 1) << 1 | (*south++ & 1); 
			*futur++ = (rule_sum[local | index]++, tmp = transition[local | index], *hor_sum += tmp, *vert_sum++
			    += tmp, tmp) ; 
		} 
		local = (*center++ & 0x000000fe) << 8; 
		index = index << 3 & 0x000001ff | (north[-side] & 1) << 2 | (center[-side] & 1) << 1 | (south[-side] & 1); 
		*futur++ = (rule_sum[local | index]++, tmp = transition[local | index], *hor_sum += tmp, *vert_sum++ += tmp,
		    tmp) ;  
		; 
	} 
	north = past + size - (side << 1); 
	center = north + side; 
	south = past;    
	local = (*center & 0x000000fe) << 8; 
	index = (north[side - 1] & 1) << 8 | (center[side - 1] & 1) << 7 | (south[side - 1] & 1) << 6; 
	index |=   (*north++ & 1) << 5 |    (*center++ & 1) << 4 |    (*south++ & 1) << 3; 
	index |=   (*north++ & 1) << 2 |      (*center & 1) << 1 |    (*south++ & 1); 
	*futur++ = (rule_sum[local | index]++, tmp = transition[local | index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ; 
	for (i = count; i--;) { 
		local = (*center++ & 0x000000fe) << 8; 
		index = index << 3 & 0x000001ff | (*north++ & 1) << 2 | (*center & 1) << 1 | (*south++ & 1); 
		*futur++ = (rule_sum[local | index]++, tmp = transition[local | index], *hor_sum += tmp, *vert_sum++ += tmp,
		    tmp) ; 
	} 
	local = (*center++ & 0x000000fe) << 8; 
	index = index << 3 & 0x000001ff | (north[-side] & 1) << 2 | (center[-side] & 1) << 1 | (south[-side] & 1); 
	*futur++ = (rule_sum[local | index]++, tmp = transition[local | index], *hor_sum += tmp, *vert_sum++ += tmp, tmp) ;  
	; 
}  
Conex moore_1_7_conex = { 
	(0  + 7) , moore_1_7_size, moore_1_7_bind, moore_1_7_next, moore_1_7_stat_next };
Named moore_named[] = {
	{ 
		"moore_1_conex", &moore_1_conex 	},
	{ 
		"moore_2_conex", &moore_2_conex 	},
	{ 
		"moore_1_7_conex", &moore_1_7_conex 	},
	{ 
		0, 0 	}
};
