#define MOORE_T_8_SIZE (1 << 12 + 8)

#define MOORE_T_8_NEXT \
    w_index = north[side - 1] + center[side - 1] + south[side - 1]; \
    c_index = *north++ + (c1 = *center++) + *south++; \
    e_index = *north++ + (c2 = *center++) + *south++; \
    index = (w_index + c_index + e_index); \
    *futur++ = TRANSITION(index - c1 | c1 << 12); \
    c1 = c2; \
    for (i = count; i--;) { \
        w_index = c_index; \
	c_index = e_index; \
	e_index = *north++ + (c2 = *center++) + *south++; \
        index = (w_index + c_index + e_index); \
	*futur++ = TRANSITION(index - c1 | c1 << 12); \
	c1 = c2; \
    } \
    w_index = c_index; \
    c_index = e_index; \
    e_index = north[-side] + center[-side] + south[-side]; \
    index = (w_index + c_index + e_index); \
    *futur++ = TRANSITION(index - c1 | c1 << 12);

#define MOORE_T_8_BIND \
    SUM = index & 0xfff; \
    C = (index & (0xff << 12)) >> 12;
