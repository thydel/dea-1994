#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include "visual.h"

char* cmd_name;

main(int ac, char** av) {
    Display* display;
    XVisualInfo vTemplate;
    XVisualInfo *visualList;
    int visualMatched;

    cmd_name = av[0];

    display = XOpenDisplay(NULL);
    if (display == NULL) {
	fprintf(stderr, "%s: Cannot open Display\n", cmd_name);
	exit(1);
    }
    
    vTemplate.depth = 8;
    vTemplate.class = DirectColor;
    visualList = XGetVisualInfo(display, VisualDepthMask | VisualClassMask, &vTemplate, &visualMatched);

    printVisuals(visualList, visualMatched);
}

