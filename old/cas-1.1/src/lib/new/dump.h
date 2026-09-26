typedef struct {
    int magic;
    char* msg;

    PlaneFrame* plane;
    char* text;
    int text_size;
    
    int xsize;
    int ysize;
    int size;
    int zoffset;

    /* minimal X11 */
    Display* display;
    Window win;
    GC gc;
    XImage* image;

    /* other X11 */
    XFontStruct *font;
    XGCValues gcv;
    XEvent report;
    char* window_name;
    char* icon_name;
    int ac;
    char** av;
    XSizeHints size_hints;
    XWMHints wm_hints;
    XClassHint class_hints;
    XTextProperty windowName, iconName;
} XdumpMono;

extern XdumpMono* XdumperMono_new(int, int, int);
extern void XdumpMono_dump(XdumpMono*);

typedef struct Dump2D {
    int magic;
    char* handle;
    char* name;
    int refcnt;
    struct Dump2D* self;

    Time2D* time;
    XdumpMono* mono[8];
} Dump2D;

extern Dump2D* Dump2D_alloc();
extern Dump2D* Dump2D_new(Dump2D*, Time2D*, int);
extern void Dump2D_delete(Dump2D*);
extern void Dump_init(Tcl_Interp*);
extern void* Dump_tbl;
