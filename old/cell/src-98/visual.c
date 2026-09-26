#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include "xstrings.h"

extern char* cmd_name;

void printVisual(XVisualInfo visual) {
	printf("screen=%d, depth=%d. class=%-11s, red_m=0x%02x, green_m=0x%02x, blue_m=0x%02x, cmap_sz=%d\n",
	       visual.screen, visual.depth, visualClassName(visual.class),
	       visual.red_mask, visual.green_mask, visual.blue_mask,
	       visual.colormap_size);
}

void printVisuals(XVisualInfo* visualList, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printVisual(visualList[i]);
	}
}

Visual* chooseVisual(Display* display, int screen, int depth, 
		    int* requiredVisual, int requiredVisualSize,
		    VisualID* choosenVisualID) {

    Visual*  visual;
    XVisualInfo vTemplate;
    XVisualInfo *visualList;
    int visualMatched;
    int i, j, succed;

    *choosenVisualID = -1; /* error case */
    vTemplate.screen = screen;
    vTemplate.depth = depth;
    visualList = XGetVisualInfo(display, VisualScreenMask | VisualDepthMask,
				&vTemplate, &visualMatched);
    if (visualMatched == 0) {
	    fprintf(stderr, "%s : No matching visuals screen %d, depth %d\n",
		    cmd_name, screen, depth);
#ifdef DEBUG
	    printf("List of avaliable visuals :\n");
	    printVisuals(visualList, visualMatched);
#endif
	    return visual;
    }


    succed = 0;
    for (i = 0; (!succed) && (i < requiredVisualSize); i++) {
	    printf("trying %s class \n", visualClassName(requiredVisual[i]));
	    for (j = 0; i < visualMatched; j++) {
		    if (visualList[j].class == requiredVisual[i]) {
			    *choosenVisualID = visualList[j].visualid;
			    visual = visualList[j].visual;
			    succed = 1;
			    break;
		    }
	    }
    }
    if (!succed) {
	    fprintf(stderr, "%s : I need ", cmd_name);
	    for (i = 0; requiredVisualSize; i++) {
	      //fprintf(stderr, "%s ", visualClassName[i]);
	    }
	    fprintf(stderr, "\n");
	    return visual;
    }
#ifdef DEBUG
    printf("choosen visual :\n");
    printVisual(visualList[j]);
#endif
    XFree((char*)visualList);
    return visual;
}
