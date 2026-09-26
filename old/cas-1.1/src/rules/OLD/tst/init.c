#include <varargs.h>
#include <malloc.h>
#include <assert.h>

#include "local.h"
#include "frame/frame.h"
#include "
#include "conex_spec.h"
#include "func.h"
#include "conex.h"

init() {

    ConexInfo_decl(MOORE, StrVect_new("NW", "W", "SW", "N", "C", "S", "NE", "E", "SE", 0));
    ConexInfo_decl(VN, StrVect_new("W", "N", "C", "S", "E", 0));
    ConexInfo_decl(LOCAL, StrVect_new("L", 0));

    Conex_decl(ConexSpec_new(ConexVar_new(MOORE, 1, 0, false), 0), 
	       moore_1_0_run, moore_1_0_bind);
    Conex_decl(ConexSpec_new(ConexVar_new(MOORE, 1, 0, false),
			     ConexVar_new(LOCAL, 7, 1, true),
			     0), 
	       moore_1_0_7_1run, moore_1_0_7_1bind);
}
