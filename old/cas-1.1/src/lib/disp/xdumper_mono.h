typedef struct {
    int magic;
    char* msg;
    PlaneFrame* frame;
    Display* display;
    Window win;
    GC gc;
    XImage* image;
} XdumperMono;

extern XdumperMono* XdumperMono_new(PlaneFrame*);
extern XdumperMono_next(XdumperMono*);

extern void XdumperMono_init(Tcl_Interp*);
extern void* XdumperMono_tbl;
