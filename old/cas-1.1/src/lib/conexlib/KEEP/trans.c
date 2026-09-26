#include <malloc.h>
#include <assert.h>

#include "local.h"
#include "magic.h"

#include "frame/frame.h"
#include "conex.h"
#include "trans.h"

Trans* trans_new(Conex* conex, StateFrame* frame, bool stat) {
    Trans* zis;

    assert(conex->magic == CONEX &&
	   frame->magic == STATE_FRAME);
    zis = malloc(sizeof(Trans));
    assert(zis);
    zis->magic = TRANS;
    zis->stat = 0;
    zis->conex = conex;
    zis->rule_tbl = SV_new(conex->size());
    zis->past = frame;
    zis->futur = SF_new(frame->xsize, frame->ysize, frame->plane);
    zis->stat = stat;
    if (stat == true) {
	zis->rule_sum = CV_new(zis->rule_tbl->size);
	zis->hor_sum = CV_new(8);
	zis->vert_sum = CF_new(frame->xsize, frame->ysize);
    }
    return zis;
}

void trans_bind(Trans* zis, int (*func)()) {
    zis->conex->bind(zis->rule_tbl, func);
}

int trans_read(Trans* zis, int input) {
    return readn(input, zis->rule_tbl, zis->rule_tbl->size);
}

void trans_next(Trans* zis) {
    StateFrame* tmp;

    if (zis->stat) {
	CV_zero(zis->hor_sum);
	zis->conex->stat_next(zis->rule_tbl,
			      zis->past, zis->futur,
			      zis->rule_sum, zis->hor_sum, zis->vert_sum);
    } else {
	zis->conex->next(zis->rule_tbl, zis->past, zis->futur);
    }

    tmp = zis->past;
    zis->past = zis->futur;
    zis->futur = tmp;

    ++zis->cnt;
}
