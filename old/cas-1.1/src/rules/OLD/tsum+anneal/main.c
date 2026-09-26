#include <malloc.h>

#include <X11/Xlib.h>

#include "conex/rule_tbl.h"
#include "frame/frame.h"
#include "conex/conex.h"
#include "conex/trans.h"
#include "extract/extract.h"
#include "disp/xdumper_mono.h"

extern Conex moore_1_conex;
extern Conex moore_1_7_conex;
extern Conex moore_t_8_conex;
extern int life();
extern int anneal();
extern int tsum();

char* cmd_name;

main(int ac, char** av) {
    int n;
    int i;
    int x;
    int y;
    int flip;
    FramePair* fp;
    Frame* extract;
    Trans* trans;
    Trans* trans2;
    Xdumper_Mono* xdumper[8];

    cmd_name = av[0];
    n = atoi(av[1]);
    x = y = 256;
    flip = 1;

    fp = frame_pair_new(x, y, 8);
    for (i = 0; i < 8; ++i) {
	frame_fill(fp->past, i, 0, 2);
    }
    trans = trans_new(&moore_t_8_conex, fp);
    trans_run(trans, tsum);
    trans2 = trans_new(&moore_1_7_conex, fp);
    trans_run(trans2, anneal);
    extract = frame_new(x, y, FRAME_BIT, 1);
    for (i = 0; i < 3; ++i) {
	xdumper[i] = xdumper_mono_new(extract);
    }

    while (n--) {
	for (i = 0; i < 2; ++i) {
	    frame_extract(fp->past, extract, i, flip);
	    xdumper_mono_next(xdumper[i]);
	}
	frame_extract(fp->past, extract, i, flip);
	xdumper_mono_next(xdumper[i]);

	trans_next(trans);
	frame_pair_swap(fp);
	for (i = 0; i < 4; ++i) {
	    trans_next(trans2);
	    frame_pair_swap(fp);
	}
    }
}

