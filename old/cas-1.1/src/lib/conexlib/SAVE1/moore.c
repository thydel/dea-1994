#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <varargs.h>

#include "tcl.h"
#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "util/str.h"
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
