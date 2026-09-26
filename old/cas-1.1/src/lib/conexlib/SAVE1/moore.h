/*
 * MOORE 1
 */

#define MOORE_1_SIZE (1 << 8 + 1)

#define MOORE_1_GEN(TRANSITION) \
    index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6; \
    index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3; \
    index |=   *north++ << 2 |    *center++ << 1 |    *south++; \
    *futur++ = TRANSITION; \
    for (i = count; i--;) { \
	index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++; \
	*futur++ = TRANSITION; \
    } \
    index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side]; \
    *futur++ = TRANSITION;

#define MOORE_1_NEXT \
MOORE_1_GEN(SIMPLE_TRANSITION(index))

#define MOORE_1_STAT_NEXT \
MOORE_1_GEN(_1_STAT_TRANSITION(index))

#define MOORE_1_BIND \
    NW = (index & 1 << 8) >> 8; \
    W = (index & 1 << 7) >> 7; \
    SW = (index & 1 << 6) >> 6; \
    N = (index & 1 << 5) >> 5; \
    C = (index & 1 << 4) >> 4; \
    S = (index & 1 << 3) >> 3; \
    NE = (index & 1 << 2) >> 2; \
    E = (index & 1 << 1) >> 1; \
    SE = (index & 1 << 0) >> 0;

/*
 * MOORE 2
 */

#define MOORE_2_SIZE (1 << (8 + 1) * 2)

#define MOORE_2_GEN(TRANSITION) \
    index = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12; \
    index |=   *north++ << 10 |    *center++ << 8  |    *south++ << 6; \
    index |=   *north++ << 4  |    *center++ << 2  |    *south++; \
    *futur++ = TRANSITION; \
    for (i = count; i--;) { \
	index = index << 6 & 0x0003ffff | *north++ << 4 | *center++ << 2 | *south++; \
	*futur++ = TRANSITION; \
    } \
    index = index << 6 & 0x0003ffff | north[-side] << 4 | center[-side] << 2 | south[-side]; \
    *futur++ = TRANSITION;

#define MOORE_2_NEXT \
MOORE_2_GEN(SIMPLE_TRANSITION(index))

#define MOORE_2_STAT_NEXT \
MOORE_2_GEN(_2_STAT_TRANSITION(index))

#define MOORE_2_BIND \
    NW = (index & 3 << 16) >> 16; \
    NW0 = NW & 1; \
    NW1 = NW & 2 >> 1; \
    W = (index & 3 << 14) >> 14; \
    W0 = W & 1; \
    W1 = W & 2 >> 1; \
    SW = (index & 3 << 12) >> 12; \
    SW0 = SW & 1; \
    SW1 = SW & 2 >> 1; \
    N = (index & 3 << 10) >> 10; \
    N0 = N & 1; \
    N1 = N & 2 >> 1; \
    C = (index & 3 << 8) >> 8; \
    C0 = C & 1; \
    C1 = C & 2 >> 1; \
    S = (index & 3 << 6) >> 6; \
    S0 = S & 1; \
    S1 = S & 2 >> 1; \
    NE = (index & 3 << 4) >> 4; \
    NE0 = NE & 1; \
    NE1 = NE & 2 >> 1; \
    E = (index & 3 << 2) >> 2; \
    E0 = E & 1; \
    E1 = E & 2 >> 1; \
    SE = (index & 3 << 0) >> 0; \
    SE0 = SE & 1; \
    SE1 = SE & 2 >> 1; \
    NW = (index & 3 << 16) >> 16; \
    NW0 = NW & 1; \
    NW1 = NW & 2 >> 1; \
    W = (index & 3 << 14) >> 14; \
    W0 = W & 1; \
    W1 = W & 2 >> 1; \
    SW = (index & 3 << 12) >> 12; \
    SW0 = SW & 1; \
    SW1 = SW & 2 >> 1; \
    N = (index & 3 << 10) >> 10; \
    N0 = N & 1; \
    N1 = N & 2 >> 1; \
    C = (index & 3 << 8) >> 8; \
    C0 = C & 1; \
    C1 = C & 2 >> 1; \
    S = (index & 3 << 6) >> 6; \
    S0 = S & 1; \
    S1 = S & 2 >> 1; \
    NE = (index & 3 << 4) >> 4; \
    NE0 = NE & 1; \
    NE1 = NE & 2 >> 1; \
    E = (index & 3 << 2) >> 2; \
    E0 = E & 1; \
    E1 = E & 2 >> 1; \
    SE = (index & 3 << 0) >> 0; \
    SE0 = SE & 1; \
    SE1 = SE & 2 >> 1;

/*
 * MOORE 1 + 7
 */

#define MOORE_1_7_SIZE (1 << 8 + 1 + 7)

#define MOORE_1_7_GEN(TRANSITION) \
    local = (*center & 0x000000fe) << 8; \
    index = (north[side - 1] & 1) << 8 | \
            (center[side - 1] & 1) << 7 | (south[side - 1] & 1) << 6; \
    index |=   (*north++ & 1) << 5 |    (*center++ & 1) << 4 |    (*south++ & 1) << 3; \
    index |=   (*north++ & 1) << 2 |      (*center & 1) << 1 |    (*south++ & 1); \
    *futur++ = TRANSITION; \
    for (i = count; i--;) { \
	local = (*center++ & 0x000000fe) << 8; \
	index = index << 3 & 0x000001ff | \
	        (*north++ & 1) << 2 | (*center & 1) << 1 | (*south++ & 1); \
	*futur++ = TRANSITION; \
    } \
    local = (*center++ & 0x000000fe) << 8; \
    index = index << 3 & 0x000001ff | (north[-side] & 1) << 2 | \
            (center[-side] & 1) << 1 | (south[-side] & 1); \
    *futur++ = TRANSITION;

#define MOORE_1_7_NEXT \
MOORE_1_7_GEN(SIMPLE_TRANSITION(local | index))

#define MOORE_1_7_STAT_NEXT \
MOORE_1_7_GEN(_1_STAT_TRANSITION(local | index))

#define MOORE_1_7_BIND \
    NW = (index & 1 << 8) >> 8; \
    W = (index & 1 << 7) >> 7; \
    SW = (index & 1 << 6) >> 6; \
    N = (index & 1 << 5) >> 5; \
    C = (index & 1 << 4) >> 4; \
    S = (index & 1 << 3) >> 3; \
    NE = (index & 1 << 2) >> 2; \
    E = (index & 1 << 1) >> 1; \
    SE = (index & 1 << 0) >> 0; \
    L = (index & (1 << 7) - 1 << 9) >> 9;

/*
 * MOORE 2 * 2 + 2
 */

#define MOORE_2x2_2_SIZE (1 << (8 + 1) * 2 + 2)

#define MOORE_2x2_2_NEXT \
local1 = (*center & 3 << 2) << 18; \
    local2 = (*center & 3) << 18; \
    index1 = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12; \
    index2 = north[side - 1] << 14 | center[side - 1] << 12 | south[side - 1] << 10; \
    index1 |=   *north   << 10 |    *center   << 8  |    *south   << 6; \
    index2 |=   *north++ << 8  |    *center++ << 6  |    *south++ << 4; \
    index1 |=   *north   << 4  |    *center   << 2  |    *south; \
    index2 |=   *north++ << 2  |    *center++       |    *south++ >> 2; \
    *futur++ = transition1[local1 | index1] | transition2[local2 | index2] << 2; \
    for (i = count; i--;) { \
				local1 = (*center & 3 << 2) << 18; \
        local2 = (*center & 3) << 18; \
	index1 = index1 << 6 & 0x0003ffff | *north   << 4 | *center << 2 | *south; \
	index2 = index2 << 6 & 0x0003ffff | *north++ << 2 | *center++    | *south++ >> 2; \
	*futur++ = transition1[local1 | index1] | transition2[local2 | index2] << 2; \
    } \
    local1 = (*center & 3 << 2) << 18; \
    local2 = (*center & 3) << 18; \
    index1 = index1 << 6 & 0x3ffff | north[-side] << 4 | center[-side] << 2 | south[-side]; \
    index2 = index2 << 6 & 0x3ffff | north[-side] << 2 | center[-side] | south[-side] >> 2; \
    *futur++ = transition1[local1 | index1] | transition2[local2 | index2] << 2;

#define MOORE_2x2_2_BIND \
    NW = (index & 1 << 16) >> 16; \
    NW0 = NW & 1; \
    NW1 = NW & 2 >> 1; \
    W = (index & 3 << 14) >> 14; \
    W0 = W & 1; \
    W1 = W & 2 >> 1; \
    SW = (index & 3 << 12) >> 12; \
    SW0 = SW & 1; \
    SW1 = SW & 2 >> 1; \
    N = (index & 3 << 10) >> 10; \
    N0 = N & 1; \
    N1 = N & 2 >> 1; \
    C = (index & 3 << 8) >> 8; \
    C0 = C & 1; \
    C1 = C & 2 >> 1; \
    S = (index & 3 << 6) >> 6; \
    S0 = S & 1; \
    S1 = S & 2 >> 1; \
    NE = (index & 3 << 4) >> 4; \
    NE0 = NE & 1; \
    NE1 = NE & 2 >> 1; \
    E = (index & 3 << 2) >> 2; \
    E0 = E & 1; \
    E1 = E & 2 >> 1; \
    SE = (index & 3 << 0) >> 0; \
    SE0 = SE & 1; \
    SE1 = SE & 2 >> 1; \
    L = (index & (1 << 2) - 1 << 18) >> 18;
