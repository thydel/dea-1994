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
#include "vn.h"
#include "util/named.h"

#include "bind.h"

CELL_P1(vn_1, VN_1)
CELL_P1(vn_2, VN_2)
CELL_P1(vn_1_7, VN_1_7)
CELL_P1(vn_2_6, VN_2_6)
