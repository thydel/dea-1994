#include <malloc.h>
#include <assert.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "local.h"
#include "magic.h"

#include "frame/frame.h"
#include "conex/conex.h"
#include "conex/trans.h"
#include "extract/extract.h"
#include "disp/xdumper_mono.h"
#include "disp/xdumper.h"

extern Conex* conex;
extern (*func)();

void loop(int x, int y, int cnt, int nplane, int flip, int region, int density, int stat,
	  int iframe, int oframe, int rule_sum, int hor_sum, int vert_sum) {
    int i;
    StateFrame* past;
    StateFrame* SF_vert_sum;
    PlaneFrame* extract;
    Trans* trans;
    Xdumper_Mono* xdumper_mono[8];
    Xdumper* xdumper;

    past = SF_new(x, y, 1);
    for (i = 0; i < nplane; ++i) {
	SF_fill(past, i, region, density);
    }
    trans = trans_new(conex, past, stat);
    trans_bind(trans, func);
    extract = PF_new(x, y, 1);
    for (i = 0; i < nplane; ++i) {
	xdumper_mono[i] = xdumper_mono_new(extract);
    }
    if (stat) {
	SF_vert_sum = SF_new(trans->vert_sum->xsize, trans->vert_sum->ysize, 8);
	xdumper = xdumper_new(SF_vert_sum);
    }

    while (cnt == -1 || cnt--) {
	for (i = 0; i < nplane; ++i) {
	    PF_extract(extract, trans->past, i, flip);
	    xdumper_mono_next(xdumper_mono[i]);
	}
	if (stat) {
	    xdumper_next(xdumper);
	    if (hor_sum != -1) {
		CV_write(trans->hor_sum, hor_sum);
	    }
	    CF_2_SF(trans->vert_sum, SF_vert_sum);
	}
	trans_next(trans);
    }
}
