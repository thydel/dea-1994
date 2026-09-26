m4_define(`moore_t_8_gen', `
    w_index = north[side - 1] + center[side - 1] + south[side - 1];
    c_index = *north++ + (c1 = *center++) + *south++;
    e_index = *north++ + (c2 = *center++) + *south++;
    index = (w_index + c_index + e_index);
    *futur++ = $1;
    c1 = c2;
    for (i = count; i--;) {
        w_index = c_index;
	c_index = e_index;
	e_index = *north++ + (c2 = *center++) + *south++;
        index = (w_index + c_index + e_index);
	*futur++ = $1;
	c1 = c2;
    }
    w_index = c_index;
    c_index = e_index;
    e_index = north[-side] + center[-side] + south[-side];
    index = (w_index + c_index + e_index);
    *futur++ = $1;
')

m4_define(`moore_t_8_transition', `(index - c1 | c1 << 12)')
m4_define(`moore_t_8_next', `moore_t_8_gen(simple_transition(moore_t_8_transition))')
m4_define(`moore_t_8_stat_next', `moore_t_8_gen(stat_transition_1(moore_t_8_transition))')
