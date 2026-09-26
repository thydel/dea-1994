#define SIMPLE_TRANSITION(index) transition[index]

#define _1_STAT_TRANSITION(index) \
    (rule_sum[index]++, \
     tmp = transition[index], \
     *hor_sum += tmp, \
     *vert_sum++ += tmp, \
     tmp)

#define _2_STAT_TRANSITION(index) \
    (rule_sum[index]++, \
     tmp = transition[index], \
     *hor_sum += tmp & 1, \
     hor_sum[1] += tmp & 2, \
     *vert_sum++ += tmp, \
     tmp)

#define CELL_SIZE(name, CNX) \
name ## _size() { return CNX ## _SIZE; }

#define CELL_BIND(name, CNX) \
name ## _bind(StateVect* rt, int (*func)()) { \
    int index; \
    \
    assert(rt->size == CNX ## _SIZE); \
    for (index = 0; index < CNX ## _SIZE; ++index) { \
        CNX ## _BIND \
	rt->ptr[index] = func(); \
    } \
}

#define CELL_NEXT_DECL \
    int i; \
    int j; \
    unsigned char* past; \
    unsigned char* futur; \
    unsigned char* transition; \
    int side; \
    int size; \
    register unsigned char* north; \
    register unsigned char* center; \
    register unsigned char* south; \
    register int index; \
    int w_index; \
    int c_index; \
    int e_index; \
    int c1; \
    int c2; \
    int index1; \
    int index2; \
    register int local; \
    int local1; \
    int local2; \
    int count;

#define CELL_NEXT_STAT_DECL \
    int* rule_sum; \
    int* hor_sum; \
    int* vert_sum; \
    int tmp; \
    int i; \
    int j; \
    unsigned char* past; \
    unsigned char* futur; \
    unsigned char* transition; \
    int side; \
    int size; \
    register unsigned char* north; \
    register unsigned char* center; \
    register unsigned char* south; \
    register int index; \
    int w_index; \
    int c_index; \
    int e_index; \
    int c1; \
    int c2; \
    int index1; \
    int index2; \
    register int local; \
    int local1; \
    int local2; \
    int count;

#define CELL_NEXT_INIT \
    past = sf_past->ptr; \
    futur = sf_futur->ptr; \
    transition = rule_tbl->ptr; \
    side = sf_past->xsize; \
    size = sf_past->ysize; \
    count = side - 2; \

#define CELL_NEXT_STAT_INIT \
    rule_sum = cv_rule_sum->ptr; \
    hor_sum = cv_hor_sum->ptr; \
    vert_sum = cf_vert_sum->ptr; \
    past = sf_past->ptr; \
    futur = sf_futur->ptr; \
    transition = rule_tbl->ptr; \
    side = sf_past->xsize; \
    size = sf_past->ysize; \
    count = side - 2; \

#define CELL_NEXT_FIRST_LINE \
    north = past + size - side; \
    center = past; \
    south = center + side;

#define CELL_NEXT_LINES \
    north = past; \
    center = north + side; \
    south = center + side;

#define CELL_NEXT_LAST_LINE \
    north = past + size - (side << 1); \
    center = north + side; \
    south = past;

#define CELL_NEXT(name, CNX) \
name ## _next(StateVect* rule_tbl, StateFrame* sf_past, StateFrame* sf_futur) { \
    CELL_NEXT_DECL \
    CELL_NEXT_INIT \
    CELL_NEXT_FIRST_LINE \
    CNX ## _NEXT; \
    CELL_NEXT_LINES \
    for (j = count; j--;) { \
        CNX ## _NEXT; \
    } \
    CELL_NEXT_LAST_LINE \
    CNX ## _NEXT; \
}

#define CELL_STAT_NEXT(name, CNX) \
name ## _stat_next(StateVect* rule_tbl, StateFrame* sf_past, StateFrame* sf_futur, CntVect* cv_rule_sum, CntVect* cv_hor_sum, CntFrame* cf_vert_sum) { \
    CELL_NEXT_STAT_DECL \
    CELL_NEXT_STAT_INIT \
    CELL_NEXT_FIRST_LINE \
    CNX ## _STAT_NEXT; \
    CELL_NEXT_LINES \
    for (j = count; j--;) { \
        CNX ## _STAT_NEXT; \
    } \
    CELL_NEXT_LAST_LINE \
    CNX ## _STAT_NEXT; \
}

#define CELL_CNX(name, CNX) \
Conex name ## _conex = { CONEX, name ## _size, name ## _bind, name ## _next, name ## _stat_next };

#if 0

/*
 * this seems to big for cpp!
 * sob...
 */

#define CELL(name, CNX) \
    CELL_SIZE(name, CNX) \
    CELL_BIND(name, CNX) \
    CELL_NEXT(name, CNX) \
    CELL_STAT_NEXT(name, CNX) \
    CELL_CNX(name, CNX)

#else

#define CELL_P1(name, CNX) \
    CELL_SIZE(name, CNX) \
    CELL_BIND(name, CNX) \
    CELL_NEXT(name, CNX)

#define CELL_P2(name, CNX) \
    CELL_STAT_NEXT(name, CNX) \
    CELL_CNX(name, CNX)

#endif

