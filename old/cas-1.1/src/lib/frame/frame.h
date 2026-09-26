typedef unsigned char State;
typedef int Cnt;

typedef struct {
    int magic;
    unsigned char* ptr;
    int size;
    int plane;
} StateVect;

extern StateVect* SV_new(int);
extern void SV_delete(StateVect*);
extern void SV_zero(StateVect*);
extern int SV_read(StateVect*, int);
extern void SV_write(StateVect*, int);

typedef struct {
    int magic;
    int* ptr;
    int size;
} CntVect;

extern CntVect* CV_new(int);
extern void CV_delete(CntVect*);
extern void CV_zero(CntVect*);
extern int CV_read(CntVect*, int);
extern void CV_write(CntVect*, int);

typedef struct {
    int magic;
    unsigned char* ptr;
    int xsize;
    int ysize;
    int size;
    int plane;
} StateFrame;

extern StateFrame* SF_new(int, int, int);
extern void SF_delete(StateFrame*);
extern void SF_zero(StateFrame*);
extern int SF_read(StateFrame*, int);
extern void SF_write(StateFrame*, int);
extern void SF_set(StateFrame*, int, int, int, int);
extern void SF_fill(StateFrame*, int, int, int);
extern bool SF_match(StateFrame*, StateFrame*);
extern void SF_swap(StateFrame*, StateFrame*);

typedef struct {
    int magic;
    unsigned char* ptr;
    int xsize;
    int ysize;
    int size;
    int plane;
} PlaneFrame;

extern PlaneFrame* PF_new(int, int, int);
extern void PF_delete(PlaneFrame*);
extern void PF_zero(PlaneFrame*);
extern int PF_read(PlaneFrame*, int);
extern void PF_extract(PlaneFrame*, StateFrame*, int, bool);

typedef struct {
    int magic;
    int* ptr;
    int xsize;
    int ysize;
    int size;
} CntFrame;

extern CntFrame* CF_new(int, int);
extern void CF_zero(CntFrame*);
extern int CF_read(CntFrame*, int);
extern void CF_2_SF(CntFrame*, StateFrame*);

extern void Frame_init(Tcl_Interp*);

extern void* Frame_tbl;

#define StateVectType(n) ARG_TYPE(StateVect, n)
#define CntVectType(n) ARG_TYPE(CntVect, n)
#define PlaneFrameType(n) ARG_TYPE(PlaneFrame, n)
#define StateFrameType(n) ARG_TYPE(StateFrame, n)
#define CntFrameType(n) ARG_TYPE(CntFrame, n)
