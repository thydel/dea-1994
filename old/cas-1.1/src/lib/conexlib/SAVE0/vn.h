/*
 * VON NEUMANN 1
 */

#define VN_1_SIZE (1 << 4 + 1)

#define VN_1_NEXT \
    index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6; \
    index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3; \
    index |=   *north++ << 2 |    *center++ << 1 |    *south++; \
    *futur++ = TRANSITION((index & 2) >> 1 | (index & 070) >> 2 | (index & 128) >> 3); \
    for (i = count; i--;) { \
	index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++; \
	*futur++ = TRANSITION((index & 2) >> 1 | (index & 070) >> 2 | (index & 128) >> 3); \
    } \
    index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side]; \
    *futur++ = TRANSITION((index & 2) >> 1 | (index & 070) >> 2 | (index & 128) >> 3);

#define VN_1_BIND \
    W = (index & 1 << 4) >> 4; \
    N = (index & 1 << 3) >> 3; \
    C = (index & 1 << 2) >> 2; \
    S = (index & 1 << 1) >> 1; \
    E = (index & 1 << 0) >> 0;

/*
 * VON NEUMANN 2
 */

#define VN_2_SIZE (1 << (4 + 1) * 2)

#define VN_2_NEXT \
    index = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12; \
    index |=   *north++ << 10 |    *center++ << 8  |    *south++ << 6; \
    index |=   *north++ << 4  |    *center++ << 2  |    *south++; \
    *futur++ = \
    TRANSITION((index & 12) >> 2 | (index & 07700) >> 4 | (index & 0xc000) >> 6); \
    for (i = count; i--;) { \
	index = index << 6 & 0x0003ffff | *north++ << 4 | *center++ << 2 | *south++; \
        *futur++ = \
        TRANSITION((index & 12) >> 2 | (index & 07700) >> 4 | (index & 0xc000) >> 6); \
    } \
    index = index << 6 & 0x0003ffff | north[-side] << 4 | center[-side] << 2 | south[-side]; \
    *futur++ = \
    TRANSITION((index & 12) >> 2 | (index & 07700) >> 4 | (index & 0xc000) >> 6);

#define VN_2_BIND \
    W = (index & 3 << 8) >> 8; \
    W0 = W & 1; \
    W1 = (W & 2) >> 1; \
    N = (index & 3 << 6) >> 6; \
    N0 = N & 1; \
    N1 = (N & 2) >> 1; \
    C = (index & 3 << 4) >> 4; \
    C0 = C & 1; \
    C1 = (C & 2) >> 1; \
    S = (index & 3 << 2) >> 2; \
    S0 = S & 1; \
    S1 = (S & 2) >> 1; \
    E = index & 3; \
    E0 = E & 1; \
    E1 = (E & 2) >> 1;

/*
 * VON NEUMANN 1 + 7
 */

#define VN_1_7_SIZE (1 << 4 + 1 + 7)

#define VN_1_7_NEXT \
    local = (*center & 0x000000fe) << 5; \
    index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6; \
    index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3; \
    index |=   *north++ << 2 |    *center++ << 1 |    *south++; \
    *futur++ = \
    TRANSITION(local | (index & 2) >> 1 | (index & 070) >> 2 | (index & 128) >> 3); \
    for (i = count; i--;) { \
	local = (*center & 0x000000fe) << 5; \
	index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++; \
	*futur++ = \
	TRANSITION(local | (index & 2) >> 1 | (index & 070) >> 2 | (index & 128) >> 3); \
    } \
    local = (*center & 0x000000fe) << 5; \
    index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side]; \
    *futur++ = \
    TRANSITION(local | (index & 2) >> 1 | (index & 070) >> 2 | (index & 128) >> 3);

#define VN_1_7_BIND \
    W = (index & 1 << 4) >> 4; \
    N = (index & 1 << 3) >> 3; \
    C = (index & 1 << 2) >> 2; \
    S = (index & 1 << 1) >> 1; \
    E = (index & 1 << 0) >> 0; \
    L = (index & (1 << 7) - 1 << 5) >> 5;

/*
 * VON NEUMANN 2 + 6
 */

#define VN_2_6_SIZE (1 << (4 + 1) * 2 + 6)

#define VN_2_6_NEXT \
    local = (*center & 0x000000fc) << 8; \
    index = (north[side - 1] & 3) << 16 | \
            (center[side - 1] & 3) << 14 | (south[side - 1] & 3) << 12; \
    index |=   (*north++ & 3) << 10 |    (*center++ & 3) << 8 |    (*south++ & 3) << 6; \
    index |=   (*north++ & 3) << 4  |     (*center & 3) << 2  |    (*south++ & 3); \
    *futur++ = \
    TRANSITION(local | (index & 12) >> 2 | (index & 07700) >> 4 | (index & 0xc000) >> 6); \
    for (i = count; i--;) { \
        local = (*center++ & 0x000000fc) << 8; \
	index = index << 6 | \
	        (*north++ & 3) << 4 | (*center & 3) << 2 | (*south++ & 3); \
        *futur++ = \
        TRANSITION(local | (index & 12) >> 2 | (index & 07700) >> 4 | (index & 0xc000) >> 6); \
    } \
    local = (*center++ & 0x000000fc) << 8; \
    index = index << 6 | (north[-side] & 3) << 4 | \
            (center[-side] & 3) << 2 | (south[-side] & 3); \
    *futur++ = \
    TRANSITION(local | (index & 12) >> 2 | (index & 07700) >> 4 | (index & 0xc000) >> 6);

#define VN_2_6_BIND \
    W = (index & 3 << 8) >> 8; \
    W0 = W & 1; \
    W1 = (W & 2) >> 1; \
    N = (index & 3 << 6) >> 6; \
    N0 = N & 1; \
    N1 = (N & 2) >> 1; \
    C = (index & 3 << 4) >> 4; \
    C0 = C & 1; \
    C1 = (C & 2) >> 1; \
    S = (index & 3 << 2) >> 2; \
    S0 = S & 1; \
    S1 = (S & 2) >> 1; \
    E = (index & 3 << 0) >> 0; \
    E0 = E & 1; \
    E1 = (E & 2) >> 1; \
    L = (index & (1 << 6) - 1 << 10) >> 10;
