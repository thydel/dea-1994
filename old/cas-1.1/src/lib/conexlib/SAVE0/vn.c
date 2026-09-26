#include "rule_tbl.h"
#include "frame/frame.h"
#include "conex.h"
#include "conex_mac.h"
#include "vn.h"
#include "util/named.h"

#include "bind.h"

CELL(vn_1, VN_1)
CELL(vn_2, VN_2)
CELL(vn_1_7, VN_1_7)
CELL(vn_2_6, VN_2_6)

Named vn_named[] = {
    NAMED_S(vn_1_conex),
    NAMED_S(vn_2_conex),
    NAMED_S(vn_1_7_conex),
    NAMED_S(vn_2_6_conex),
    NULL_NAMED
};
