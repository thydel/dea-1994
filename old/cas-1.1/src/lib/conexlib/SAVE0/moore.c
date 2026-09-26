#include <assert.h>

#include "local.h"
#include "magic.h"

#include "frame/frame.h"
#include "conex.h"
#include "conex_mac.h"
#include "moore.h"
#include "util/named.h"

#include "bind.h"

CELL_P1(moore_1, MOORE_1)
CELL_P2(moore_1, MOORE_1)
CELL_P1(moore_2, MOORE_2)
CELL_P2(moore_2, MOORE_2)
CELL_P1(moore_1_7, MOORE_1_7)
CELL_P2(moore_1_7, MOORE_1_7)

Named moore_named[] = {
    NAMED_S(moore_1_conex),
    NAMED_S(moore_2_conex),
    NAMED_S(moore_1_7_conex),
    NULL_NAMED
};
