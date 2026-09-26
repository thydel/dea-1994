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
#include "moore-t.h"
#include "util/named.h"

#include "bind.h"

CELL_P1(moore_t_8, MOORE_T_8)

