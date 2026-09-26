m4_define(`moore_1_gen', `
    index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6;
    index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3;
    index |=   *north++ << 2 |    *center++ << 1 |    *south++;
    *futur++ = $1;
    for (i = count; i--;) {
	index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++;
	*futur++ = $1;
    }
    index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side];
    *futur++ = $1;
')

m4_define(`moore_1_next', `moore_1_gen(simple_transition(index))')
m4_define(`moore_1_stat_next', `moore_1_gen(stat_transition_1(index))')

m4_define(`moore_2_gen', `
    index = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12;
    index |=   *north++ << 10 |    *center++ << 8  |    *south++ << 6;
    index |=   *north++ << 4  |    *center++ << 2  |    *south++;
    *futur++ = $1;
    for (i = count; i--;) {
	index = index << 6 & 0x0003ffff | *north++ << 4 | *center++ << 2 | *south++;
	*futur++ = $1;
    }
    index = index << 6 & 0x0003ffff | north[-side] << 4 | center[-side] << 2 | south[-side];
    *futur++ = $1;
')

m4_define(`moore_2_next', `moore_2_gen(simple_transition(index))')
m4_define(`moore_2_stat_next', `moore_2_gen(stat_transition_2(index))')

m4_define(`moore_1_7_gen', `
    local = (*center & 0x000000fe) << 8;
    index = (north[side - 1] & 1) << 8 |
            (center[side - 1] & 1) << 7 | (south[side - 1] & 1) << 6;
    index |=   (*north++ & 1) << 5 |    (*center++ & 1) << 4 |    (*south++ & 1) << 3;
    index |=   (*north++ & 1) << 2 |      (*center & 1) << 1 |    (*south++ & 1);
    *futur++ = $1;
    for (i = count; i--;) {
	local = (*center++ & 0x000000fe) << 8;
	index = index << 3 & 0x000001ff |
	        (*north++ & 1) << 2 | (*center & 1) << 1 | (*south++ & 1);
	*futur++ = $1;
    }
    local = (*center++ & 0x000000fe) << 8;
    index = index << 3 & 0x000001ff | (north[-side] & 1) << 2 |
            (center[-side] & 1) << 1 | (south[-side] & 1);
    *futur++ = $1;
')

m4_define(`moore_1_7_next', `moore_1_7_gen(simple_transition(local | index))')
m4_define(`moore_1_7_stat_next', `moore_1_7_gen(stat_transition_1(local | index))')

m4_define(`moore_2x2_2_next', `
local1 = (*center & 3 << 2) << 18;
    local2 = (*center & 3) << 18;
    index1 = north[side - 1] << 16 | center[side - 1] << 14 | south[side - 1] << 12;
    index2 = north[side - 1] << 14 | center[side - 1] << 12 | south[side - 1] << 10;
    index1 |=   *north   << 10 |    *center   << 8  |    *south   << 6;
    index2 |=   *north++ << 8  |    *center++ << 6  |    *south++ << 4;
    index1 |=   *north   << 4  |    *center   << 2  |    *south;
    index2 |=   *north++ << 2  |    *center++       |    *south++ >> 2;
    *futur++ = transition1[local1 | index1] | transition2[local2 | index2] << 2;
    for (i = count; i--;) {
				local1 = (*center & 3 << 2) << 18;
        local2 = (*center & 3) << 18;
	index1 = index1 << 6 & 0x0003ffff | *north   << 4 | *center << 2 | *south;
	index2 = index2 << 6 & 0x0003ffff | *north++ << 2 | *center++    | *south++ >> 2;
	*futur++ = transition1[local1 | index1] | transition2[local2 | index2] << 2;
    }
    local1 = (*center & 3 << 2) << 18;
    local2 = (*center & 3) << 18;
    index1 = index1 << 6 & 0x3ffff | north[-side] << 4 | center[-side] << 2 | south[-side];
    index2 = index2 << 6 & 0x3ffff | north[-side] << 2 | center[-side] | south[-side] >> 2;
    *futur++ = transition1[local1 | index1] | transition2[local2 | index2] << 2;
')
