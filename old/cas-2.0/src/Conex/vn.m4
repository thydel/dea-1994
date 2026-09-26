m4_define(`vn_1_gen', `
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

m4_define(`vn_1_transition', `((index & 2) >> 1 | (index & 070) >> 2 | (index & 128) >> 3)')
m4_define(`vn_1_next', `vn_1_gen(simple_transition(vn_1_transition))')
m4_define(`vn_1_stat_next', `vn_1_gen(stat_transition_1(vn_1_transition))')

m4_define(`vn_2_gen', `
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

m4_define(`vn_2_transition',
	`((index & 12) >> 2 | (index & 07700) >> 4 | (index & 0xc000) >> 6)')
m4_define(`vn_2_next', `vn_1_gen(simple_transition(vn_2_transition))')
m4_define(`vn_2_stat_next', `vn_1_gen(stat_transition_2(vn_2_transition))')

m4_define(`vn_3_gen', `
    index = north[side - 1] << 24 | center[side - 1] << 21 | south[side - 1] << 18;
    index |=   *north++ << 15 |    *center++ << 12  |    *south++ << 9;
    index |=   *north++ << 6  |    *center++ << 3  |    *south++;
    *futur++ = $1;
    for (i = count; i--;) {
	index = index << 9 & 0x0003ffff | *north++ << 4 | *center++ << 2 | *south++;
        *futur++ = $1;
    }
    index = index << 9 & 0x0003ffff | north[-side] << 4 | center[-side] << 2 | south[-side];
    *futur++ = $1;
')

m4_define(`vn_3_transition',
	`((index & 56) >> 3 | (index & 0777000) >> 6 | (index & 0xe00000) >> 9)')
m4_define(`vn_3_next', `vn_1_gen(simple_transition(vn_3_transition))')
m4_define(`vn_3_stat_next', `vn_1_gen(stat_transition_3(vn_3_transition))')

m4_define(`vn_1_7_gen', `
    local = (*center & 0x000000fe) << 5;
    index = north[side - 1] << 8 | center[side - 1] << 7 | south[side - 1] << 6;
    index |=   *north++ << 5 |    *center++ << 4 |    *south++ << 3;
    index |=   *north++ << 2 |    *center++ << 1 |    *south++;
    *futur++ = $1;
    for (i = count; i--;) {
	local = (*center & 0x000000fe) << 5;
	index = index << 3 & 0x000001ff | *north++ << 2 | *center++ << 1 | *south++;
	*futur++ = $1;
    }
    local = (*center & 0x000000fe) << 5;
    index = index << 3 & 0x000001ff | north[-side] << 2 | center[-side] << 1 | south[-side];
    *futur++ = $1;
')

m4_define(`vn_1_7_transition',
	`(local | (index & 2) >> 1 | (index & 070) >> 2 | (index & 128) >> 3)')
m4_define(`vn_1_7_next', `vn_1_gen(simple_transition(vn_1_7_transition))')
m4_define(`vn_1_7_stat_next', `vn_1_gen(stat_transition_1(vn_1_7_transition))')

m4_define(`vn_2_6_gen', `
    local = (*center & 0x000000fc) << 8;
    index = (north[side - 1] & 3) << 16 |
            (center[side - 1] & 3) << 14 | (south[side - 1] & 3) << 12;
    index |=   (*north++ & 3) << 10 |    (*center++ & 3) << 8 |    (*south++ & 3) << 6;
    index |=   (*north++ & 3) << 4  |     (*center & 3) << 2  |    (*south++ & 3);
    *futur++ = $1;
    for (i = count; i--;) {
        local = (*center++ & 0x000000fc) << 8;
	index = index << 6 |
	        (*north++ & 3) << 4 | (*center & 3) << 2 | (*south++ & 3);
        *futur++ = $1;
    }
    local = (*center++ & 0x000000fc) << 8;
    index = index << 6 | (north[-side] & 3) << 4 |
            (center[-side] & 3) << 2 | (south[-side] & 3);
    *futur++ = $1;
')

m4_define(`vn_2_6_transition',
	`(local | (index & 12) >> 2 | (index & 07700) >> 4 | (index & 0xc000) >> 6)')
m4_define(`vn_2_6_next', `vn_1_gen(simple_transition(vn_2_6_transition))')
m4_define(`vn_2_6_stat_next', `vn_1_gen(stat_transition_2(vn_2_6_transition))')
