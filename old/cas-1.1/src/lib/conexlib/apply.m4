m4_define(`simple_transition', `transition[$1]')

m4_define(`stat_transition_1', `
    (rule_sum[$1]++,
     tmp = transition[$1],
     *hor_sum += tmp,
     *vert_sum++ += tmp,
     tmp)
')

m4_define(`stat_transition_2', `
    (rule_sum[$1]++,
     tmp = transition[$1],
     *hor_sum += tmp & 1,
     hor_sum[1] += tmp & 2,
     *vert_sum++ += tmp,
     tmp)
')

m4_define(`stat_transition_3', `
    (rule_sum[$1]++,
     tmp = transition[$1],
     *hor_sum += tmp & 1,
     hor_sum[1] += tmp & 2,
     *vert_sum++ += tmp,
     tmp)
')

m4_define(`cas_next_decl', `
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
')

m4_define(`cas_next_stat_decl', `
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
')

m4_define(`cas_next_init', `
    past = sf_past->ptr;
    futur = sf_futur->ptr;
    transition = rule_tbl->ptr;
    side = sf_past->xsize;
    size = sf_past->size;
    count = side - 2;
')

m4_define(`cas_next_stat_init', `
    rule_sum = cv_rule_sum->ptr;
    hor_sum = cv_hor_sum->ptr;
    vert_sum = cf_vert_sum->ptr;
    past = sf_past->ptr;
    futur = sf_futur->ptr;
    transition = rule_tbl->ptr;
    side = sf_past->xsize;
    size = sf_past->size;
    count = side - 2;
')

m4_define(`cas_next_first_line', `
    north = past + size - side;
    center = past;
    south = center + side;
')

m4_define(`cas_next_lines', `
    north = past;
    center = north + side;
    south = center + side;
')

m4_define(`cas_next_last_line', `
    north = past + size - (side << 1);
    center = north + side;
    south = past;
')

m4_define(`cas_next', `
$1(StateVect* rule_tbl, StateFrame* sf_past, StateFrame* sf_futur) {
    cas_next_decl
    cas_next_init
    cas_next_first_line
    $1_next
    cas_next_lines
    for (j = count; j--;) {
        $1_next
    }
    cas_next_last_line
    $1_next
}
')

m4_define(`cas_stat_next', `
$1_stat(StateVect* rule_tbl, StateFrame* sf_past, StateFrame* sf_futur, CntVect* cv_rule_sum, CntVect* cv_hor_sum, CntFrame* cf_vert_sum) {
    cas_next_stat_decl
    cas_next_stat_init
    cas_next_first_line
    $1_stat_next
    cas_next_lines
    for (j = count; j--;) {
        $1_stat_next
    }
    cas_next_last_line
    $1_stat_next
}
')

m4_define(`cas', `
    cas_next($1)
    cas_stat_next($1)
')

