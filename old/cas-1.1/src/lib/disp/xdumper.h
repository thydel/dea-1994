typedef struct {
    StateFrame* frame;
    Display* display;
    Window win;
    GC gc;
    XImage* image;
    Colormap colormap;
    XSetWindowAttributes attributes;
    unsigned long valuemask;
    XVisualInfo vTemplate;
    XVisualInfo *visualList;
    int visualMatched;
} Xdumper;

extern Xdumper* Xdumper_new(StateFrame*);
extern void Xdumper_next(Xdumper*);
extern void Xdumper_init(Tcl_Interp*);

extern void* xdumper_tbl;

#define XdumperType(n) ARG_TYPE(Xdumper, n)
