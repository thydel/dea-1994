#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#include "tclExtend.h"

#include "util.h"
#include "magic.h"
#include "frame.h"
#include "extract.h"

#define DATA_DCL(name) \
    Tcl_CreateCommand(interp, #name, cmd_ ## name ## _new, (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);

#define CMD_DCL(name) \
    Tcl_CreateCommand(interp, #name, cmd_ ## name, (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);

#define DATA_DEF(name) \
int cmd_ ## name ## _new(ClientData notUsed, Tcl_Interp* interp, int ac, char** av)

#define CMD_DEF(name) \
int cmd_ ## name(ClientData notUsed, Tcl_Interp* interp, int ac, char** av)

#define BAD_ARG(msg) Tcl_AppendResult(interp, "bad # arg: ", av[0], " ", msg, 0)

#define CHECK(n, msg) \
    if (ac != n + 1) { \
	BAD_ARG(msg); \
	return TCL_ERROR; \
    }

#define CREAT(type) \
    Tcl_HandleAlloc(type ## _tbl, buf); \
    ptr[0] = Tcl_HandleXlate(interp, type ## _tbl, buf); \
    assert(ptr[0]);

#define EXTRACT(type, n) \
{ \
    ptr[n] = Tcl_HandleXlate(interp, type ## _tbl, av[n]); \
    if (!ptr[n]) return TCL_ERROR; \
}

#define DATA_DONE \
{ \
    strcpy(interp->result, buf); \
    return TCL_OK; \
}

#define CMD_DONE \
{ \
      return TCL_OK; \
}

#define ARG_TYPE(t, n) *(t**)ptr[n]

#define CntType(n) atoi(av[n])
#define StrType(n) av[n]


#define NFRAME 64
#define MAX_PTR_ARG 64

void* Frame_tbl;
static char buf[64];
static void* ptr[MAX_PTR_ARG];

StateVect* SV_new(int size) {
    StateVect* zis;

    zis = malloc(sizeof(StateVect));
    assert(zis);
    zis->magic = magic(STATE_VECT);
    zis->size = size;
    zis->ptr = malloc(zis->size);
    assert(zis->ptr);
    memset(zis->ptr, 0, zis->size);
    return zis;
}

void SV_delete(StateVect* zis) {
    assert(zis && zis->magic == magic(STATE_VECT));
    free(zis->ptr);
    free(zis);
}

DATA_DEF(SV) {
    CHECK(1, "size");
    CREAT(Frame);

    StateVectType(0) = SV_new(CntType(1));

    DATA_DONE;
}

void SV_zero(StateVect* zis) {
    assert(zis && zis->magic == magic(STATE_VECT));
    memset(zis->ptr, 0, zis->size);
}

CMD_DEF(SV_zero) {
    CHECK(1, "StateVect");
    EXTRACT(Frame, 1);

    SV_zero(StateVectType(1));

    CMD_DONE;
}

int SV_read(StateVect* zis, int input) {
    int n;

    assert(zis && zis->magic == magic(STATE_VECT));
    n = readn(input, zis->ptr, zis->size);
    if (n != zis->size && n == -1) {
	FATAL(1);
    }
    return n;
}

void SV_write(StateVect* zis, int output) {
    assert(zis && zis->magic == magic(STATE_VECT));
    if (write(output, zis->ptr, zis->size) != zis->size) {
	FATAL(1);
    }
}

CntVect* CV_new(int size) {
    CntVect* zis;

    zis = malloc(sizeof(CntVect));
    assert(zis);
    zis->magic = magic(CNT_VECT);
    zis->size = size;
    zis->ptr = malloc(zis->size * sizeof(int));
    assert(zis->ptr);
    memset(zis->ptr, 0, zis->size * sizeof(int));
    return zis;
}

void CV_delete(CntVect* zis) {
    assert(zis && zis->magic == magic(CNT_VECT));
    free(zis->ptr);
    free(zis);
}

DATA_DEF(CV) {
    CHECK(1, "size");
    CREAT(Frame);

    CntVectType(0) = CV_new(CntType(1));

    DATA_DONE;
}

void CV_zero(CntVect* zis) {
    assert(zis && zis->magic == magic(CNT_VECT));
    memset(zis->ptr, 0, zis->size * sizeof(int));
}

int CV_read(CntVect* zis, int input) {
    int n;
    int size;

    assert(zis && zis->magic == magic(CNT_VECT));
    size = zis->size * sizeof(int);
    n = readn(input, (char*)zis->ptr, size);
    if (n != size && n == -1) {
	FATAL(1);
    }
    return n;
}

void CV_write(CntVect* zis, int output) {
    assert(zis && zis->magic == magic(CNT_VECT));
    if (write(output, zis->ptr, zis->size) != zis->size) {
	FATAL(1);
    }
}

StateFrame* SF_new(int xsize, int ysize, int plane) {
    StateFrame* zis;

    zis = malloc(sizeof(StateFrame));
    assert(zis);
    zis->magic = magic(STATE_FRAME);
    zis->xsize = xsize;
    zis->ysize = ysize;
    zis->size = xsize * ysize;
    zis->plane = plane;
    zis->ptr = malloc(zis->size);
    assert(zis);
    memset(zis->ptr, 0, zis->size);
    return zis;
}

DATA_DEF(SF) {
    CHECK(3, "xsize ysize plane");
    CREAT(Frame);

    StateFrameType(0) = SF_new(CntType(1), CntType(2), CntType(3));

    DATA_DONE;
}

void SF_delete(StateFrame* zis) {
    assert(zis && zis->magic == magic(STATE_FRAME));
    free(zis->ptr);
    free(zis);
}

void SF_zero(StateFrame* zis) {
    assert(zis && zis->magic == magic(STATE_FRAME));
    memset(zis->ptr, 0, zis->size);
}

int SF_read(StateFrame* zis, int input) {
    int n;

    assert(zis && zis->magic == magic(STATE_FRAME));
    n = readn(input, zis->ptr, zis->size);
    if (n != zis->size && n == -1) {
	FATAL(1);
    }
    return n;
}

void SF_write(StateFrame* zis, int output) {
    assert(zis && zis->magic == magic(STATE_FRAME));
    if (write(output, zis->ptr, zis->size) != zis->size) {
	FATAL(1);
    }
}

void SF_set(StateFrame* zis, int plane, int density, int x, int y)
{
    int tmp;
    
    assert(zis && zis->magic == magic(STATE_FRAME));
    if (density == 1) {
	tmp = 1;
    } else if (density == 0) {
	tmp = 0;
    } else {
	int neg;
	
	neg = density < 0;
	tmp = (lrand48() >> 16) % (neg ? -density : density);
	tmp = tmp ? 0 : 1;
	tmp = neg ? !tmp : tmp;
    }
    if (tmp) {
	zis->ptr[x * zis->xsize + y] |= 1 << plane;
    } else {
	zis->ptr[x * zis->xsize + y] &= ~(1 << plane);
    }
}

CMD_DEF(SF_set) {
    CHECK(5, "StateFrame plane density x y");
    EXTRACT(Frame, 1);

    SF_set(StateFrameType(1), CntType(2), CntType(3), CntType(4), CntType(5));

    CMD_DONE;
}

void SF_fill(StateFrame* zis, int plane, int region, int density)
{
    int side;
    int startx;
    int starty;
    int endx;
    int endy;
    int i;
    int x;
    int y;
    
    assert(zis && zis->magic == magic(STATE_FRAME));
    srand48(time(0) ^ getpid());
    if (!region) {
	startx = starty = 0;
	endx = zis->xsize;
	endy = zis->ysize;
    } else {
	startx = starty = zis->xsize / 2 - region / 2;
	endx = endy = startx + region;
    }
    
    for (x = startx; x < endx; ++x) {
	for (y = starty; y < endy; ++y) {
	    SF_set(zis, plane, density, x, y);
	}
    }
}

CMD_DEF(SF_fill) {
    CHECK(4, "StateFrame plane region density");
    EXTRACT(Frame, 1);

    SF_fill(StateFrameType(1), CntType(2), CntType(3), CntType(4));

    CMD_DONE;
}

bool SF_match(StateFrame* a, StateFrame* b) {
    return a && a->magic == magic(STATE_FRAME) &&
	b && b->magic == magic(STATE_FRAME) &&
	    a->size == b->size &&
		a->plane == b->plane;
}

void SF_swap(StateFrame* a, StateFrame* b) {
    unsigned char* tmp;

    assert(SF_match(a, b));
    tmp = a->ptr;
    a->ptr = b->ptr;
    b->ptr = tmp;
}

PlaneFrame* PF_new(int xsize, int ysize, int plane) {
    PlaneFrame* zis;

    zis = malloc(sizeof(PlaneFrame));
    assert(zis);
    zis->magic = magic(PLANE_FRAME);
    zis->xsize = xsize;
    zis->ysize = ysize;
    zis->size = ((xsize * ysize) >> 3) * plane;
    zis->plane = plane;
    zis->ptr = malloc(zis->size);
    assert(zis);
    memset(zis->ptr, 0, zis->size);
    return zis;
}

DATA_DEF(PF) {
    CHECK(3, "xsize ysize plane");
    CREAT(Frame);

    PlaneFrameType(0) = PF_new(CntType(1), CntType(2), CntType(3));

    DATA_DONE;
}

void PF_delete(PlaneFrame* zis) {
    assert(zis && zis->magic == magic(PLANE_FRAME));
    free(zis->ptr);
    free(zis);
}

void PF_zero(PlaneFrame* zis) {
    assert(zis && zis->magic == magic(PLANE_FRAME));
    memset(zis->ptr, 0, zis->size);
}

int PF_read(PlaneFrame* zis, int input) {
    int n;

    assert(zis && zis->magic == magic(PLANE_FRAME));
    n = readn(input, zis->ptr, zis->size);
    if (n != zis->size && n == -1) {
	FATAL(1);
    }
    return n;
}

void PF_write(PlaneFrame* zis, int output) {
    assert(zis && zis->magic == magic(PLANE_FRAME));
    if (write(output, zis->ptr, zis->size) != zis->size) {
	FATAL(1);
    }
}

void PF_extract(PlaneFrame* zis, StateFrame* sf, int plane, bool flip) {
    assert(zis && zis->magic == magic(PLANE_FRAME) &&
	   sf && sf->magic == magic(STATE_FRAME) &&
	   zis->xsize == sf->xsize &&
	   zis->ysize == sf->ysize);
    extract_tab[(plane << 1) + flip ](sf->ptr, zis->ptr, sf->size);
}

CMD_DEF(PF_extract) {
    CHECK(4, "PlaneFrame StateFrame plane flip");
    EXTRACT(Frame, 1);
    EXTRACT(Frame, 2);

    PF_extract(PlaneFrameType(1), StateFrameType(2), CntType(3), CntType(4));

    CMD_DONE;
}

CntFrame* CF_new(int xsize, int ysize) {
    CntFrame* zis;

    zis = malloc(sizeof(CntFrame));
    assert(zis);
    zis->magic = magic(CNT_FRAME);
    zis->xsize = xsize;
    zis->ysize = ysize;
    zis->size = xsize * ysize;
    zis->ptr = malloc(zis->size * sizeof(int));
    assert(zis);
    memset(zis->ptr, 0, zis->size * sizeof(int));
    return zis;
}

DATA_DEF(CF) {
    CHECK(2, "xsize ysize");
    CREAT(Frame);

    CntFrameType(0) = CF_new(CntType(1), CntType(2));

    DATA_DONE;
}

void CF_zero(CntFrame* zis) {
    assert(zis && zis->magic == magic(CNT_FRAME));
    memset(zis->ptr, 0, zis->size * sizeof(int));
}

int CF_read(CntFrame* zis, int input) {
    int n;
    int size;

    assert(zis && zis->magic == magic(CNT_FRAME));
    size = zis->size * sizeof(int);
    n = readn(input, (char*)zis->ptr, size);
    if (n != size && n == -1) {
	FATAL(1);
    }
    return n;
}

void CF_write(CntFrame* zis, int output) {
    assert(zis && zis->magic == magic(CNT_FRAME));
    if (write(output, zis->ptr, zis->size) != zis->size) {
	FATAL(1);
    }
}

void CFtoSF(CntFrame* cntf, StateFrame* stf) {
    int size;
    int n;
    int* cntp;
    unsigned char* stp;

    assert(cntf && cntf->magic == magic(CNT_FRAME) &&
	   stf && stf->magic == magic(STATE_FRAME) &&
	   cntf->size == stf->size);
    size = cntf->size;
    for (n = size, stp = stf->ptr, cntp = cntf->ptr; n--;) {
	*stp++ = *cntp++ & 255;
    }
}

CMD_DEF(CFtoSF) {
    CHECK(2, "CntFrame StateFrame");
    EXTRACT(Frame, 1);
    EXTRACT(Frame, 2);

    CFtoSF(CntFrameType(1), StateFrameType(2));

    CMD_DONE;
}

void Frame_init(Tcl_Interp *interp) {
    Frame_tbl = Tcl_HandleTblInit("Frame", sizeof(void*), NFRAME);
    DATA_DCL(SV);
    CMD_DCL(SV_zero);
    DATA_DCL(SF);
    CMD_DCL(SF_set);
    CMD_DCL(SF_fill);
    DATA_DCL(PF);
    CMD_DCL(PF_extract);
    DATA_DCL(CF);
    CMD_DCL(CFtoSF);
}


