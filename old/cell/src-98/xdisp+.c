#include <stdio.h>   // For standard input/output functions (fprintf, perror)
#include <assert.h>  // For the assert macro, used for debugging checks
#include <malloc.h>  // For memory allocation functions like malloc (or stdlib.h)
#include <memory.h>  // For memory functions like memset (or string.h)

#include <X11/Xlib.h> // Core X11 library for windowing and graphics

// Global variables
char* cmd_name; // Stores the name of the executable for error messages
Bool debug;     // Boolean flag to enable/disable debugging output (True/False from X11/Xlib.h)

// Main function: parses command-line arguments and calls the display function
int main(int ac, char** av)
{
    // extern char *optarg; // Pointer to the current option argument (from getopt)
    // extern int optind;   // Index of the next argument to be processed (from getopt)
    // These are usually included via <unistd.h>

    static char* usage = "oops!"; // A placeholder for a more descriptive usage message

    int c;        // Character for the current command-line option from getopt
    int errflg;   // Flag to indicate an error during argument parsing
    int xsize;    // Width of the data grid/image
    int ysize;    // Height of the data grid/image
    int scale;    // Scaling factor for displaying each pixel/cell
    int lplane;   // Last plane to display or process in a cycle
    int delay;    // Boolean flag to introduce a delay in the display loop
    int step;     // Number of data frames to read per display update
    int fast;     // Boolean flag to enable/disable a "fast" drawing mode (optimized updates)
    int fplane;   // First plane to display or process in a cycle
    int ncolor;   // Number of colors to use or a flag for color mode

    cmd_name = av[0]; // Store the program's name

    // Initialize default values for parameters
    errflg = 0;
    xsize = ysize = 256; // Default grid size 256x256
    scale = 4;           // Default display scale factor
    delay = 0;           // Default: no delay (delay is False)
    step = 1;            // Default: process one data frame per update
    fast = 1;            // Default: fast drawing mode enabled (fast is True)
    fplane = 0;          // Default first plane
    lplane = 0;          // Default last plane
    ncolor = 0;          // Default: not using special ncolor mode

    // Parse command-line options using getopt
    // Options x:s:t:f:l:c: expect an argument
    // Options PFD are flags
    while ((c = getopt(ac, av, "x:s:t:f:l:c:PFD")) != EOF) // EOF is typically -1
        switch (c) {
          case 'x': // Option to set grid size (xsize and ysize)
            xsize = ysize = atoi(optarg);
            break;
          case 's': // Option to set display scale
            scale = atoi(optarg);
            assert(scale > 0 && scale < 100); // Assert scale is within a reasonable range
            break;
          case 't': // Option to set step (frames per update)
            step = atoi(optarg);
            break;
          case 'f': // Option to set the first plane (fplane)
            fplane = atoi(optarg);
            break;
          case 'l': // Option to set the last plane (lplane)
            lplane = atoi(optarg);
            break;
          case 'c': // Option to set number of colors or color mode
            ncolor = atoi(optarg);
            break;
          case 'P': // Option to enable delay (Pause/Paced)
            delay = True;
            break;
          case 'F': // Option to disable fast drawing mode
            fast = 0; // fast becomes False
            break;
          case 'D': // Option to enable debugging output
            debug = True;
            break;
          case '?': // Error in option parsing (unknown option or missing argument)
          default:  // Also catches unhandled valid options if any were added to string but not case
            errflg++;
        }

    // If there was an error parsing options, print usage and exit
    if (errflg) {
        fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
        exit(1);
    }

    // Check for any extraneous non-option arguments
    for (; optind < ac; optind++) {
        fprintf(stderr, "%s: extraneous argument %s\n", cmd_name, av[optind]);
        fprintf(stderr, "%s, usage: %s\n", cmd_name, usage); // Print usage (though 'usage' is "oops!")
        // It might be better to exit(1) here if extraneous arguments are not allowed.
    }

    // Call the main display function with parsed or default parameters
    // The first argument '0' is likely the file descriptor for stdin (for input data)
    return disp(0, xsize, ysize, scale, lplane, delay, step, fast, fplane, ncolor);
}

// Main display function: handles X11 setup, event loop, drawing, and data reading
int disp(int input, int xsize, int ysize, int scale, int lplane, int delay, int step,
         int fast, int fplane, int ncolor)
{
    Display* display;   // Pointer to the X display structure
    int screen;         // Default screen number
    // Visual* visual;  // Visual structure (not explicitly used beyond default)
    Window win;         // The main window
    Pixmap pixmap;      // Off-screen buffer (pixmap) for double buffering
    GC gc;              // Graphics Context for drawing operations
    XGCValues gcv;      // Structure for GC values
    XEvent e;           // Event structure to store X events

    unsigned char* tab;    // Buffer for current frame data read from input
    unsigned char* ptab;   // Buffer for previous frame data (used in 'fast' mode for diffing)
    unsigned char* tmptab; // Temporary pointer for swapping tab and ptab
    int tabsize;        // Total size of the data buffers (xsize * ysize)
    // int i;           // Generic loop counter (not consistently used here)
    int loop;           // Counter for the number of data reading loops
    int bitn;           // Current bit plane or frame index being processed/displayed

    // Calculate buffer size and allocate memory for current and previous frames
    tabsize = xsize * ysize;
    tab = malloc(tabsize); // Allocate current frame buffer
    if (!tab) { fprintf(stderr, "%s: malloc failed for tab\n", cmd_name); exit(1); }
    memset(tab, '\0', tabsize); // Initialize current frame buffer to zeros

    ptab = malloc(tabsize); // Allocate previous frame buffer
    if (!ptab) { fprintf(stderr, "%s: malloc failed for ptab\n", cmd_name); exit(1); }
    memset(ptab, '\0', tabsize); // Initialize previous frame buffer to zeros

    // Open connection to the X server
    display = XOpenDisplay(NULL); // NULL uses the DISPLAY environment variable
    if (display == NULL) {
        fprintf(stderr, "%s: Cannot open Display\n", cmd_name);
        exit(1);
    }

    screen = XDefaultScreen(display); // Get the default screen

    // Create a simple window
    win = XCreateSimpleWindow(display, DefaultRootWindow(display), // Parent window
                              0, 0, xsize * scale, ysize * scale, // x, y, width, height
                              2, BlackPixel(display, screen),     // Border width and color
                              WhitePixel(display, screen));   // Background color

    // These functions are assumed to be defined elsewhere, for color palette setup
    SetNColors(256); // Potentially sets up a number of colors to be used
    AllocColors(display, screen); // Allocates the colors on the X server

    // Create an off-screen pixmap for drawing (double buffering)
    pixmap = XCreatePixmap(display, win, xsize * scale, ysize * scale,
                           XDefaultDepth(display, screen)); // Depth of the screen

    // Create a Graphics Context (GC)
    gcv.foreground = WhitePixel(display, screen); // Set default foreground for GC
    gc = XCreateGC(display, win, GCForeground, &gcv); // Create GC with specified foreground

    XMapWindow(display, win); // Map the window (make it visible)
    XSelectInput(display, win, ExposureMask); // Select input events to listen for (only Expose here)

    // Initialize the pixmap by filling it with black
    XSetForeground(display, gc, BlackPixel(display, screen));
    XFillRectangle(display, pixmap, gc, 0, 0, xsize * scale, ysize * scale);


    bitn = fplane; // Initialize current bit plane/frame index to the first plane
    for (loop = 0; /**/; /**/) { // Main event and drawing loop (infinite until readn returns 0 or -1)
        int n; // Stores result of readn

        // Wait for and get the next X event
        XNextEvent(display, &e);
        switch (e.type) {
          default: // Ignore other event types
            continue;

          case Expose: { // If the window needs to be redrawn (e.g., initially or after being unobscured)
            int pv;     // Previous pixel value/color (used for optimization)
            int x, y;   // Loop counters for grid coordinates

            // XClearArea with True generates an Expose event, useful for triggering redraws on demand.
            // Clearing a 1x1 area and generating an Expose event seems like a way to force a redraw cycle.
            // However, the main drawing happens after this. If this is for animation, it might be
            // used to ensure the event loop proceeds after new data is read.
            XClearArea(display, win, 0, 0, 1, 1, True); // Generate a new Expose if needed

            // If not in 'fast' mode, clear the entire pixmap to black first
            if (!fast) {
                XSetForeground(display, gc, BlackPixel(display, screen));
                XFillRectangle(display, pixmap, gc, 0, 0, xsize * scale, ysize * scale);
            }

            // Set foreground for drawing actual data (default to white if not changed by data)
            XSetForeground(display, gc, WhitePixel(display, screen));
            pv = -1; // Initialize previous pixel value to an invalid state

            // Iterate through the grid data (tab)
            for (x = 0; x < xsize; ++x) {
                for (y = 0; y < ysize; ++y) {
                    if (ncolor) { // If ncolor mode is active
                        int v; // Pixel value from tab

                        // If the pixel value in 'tab' is non-zero
                        if ((v = tab[x * xsize + y])) { // Assignment and check
                            if (v > ncolor) { // Cap value at ncolor
                                v = ncolor;
                            }
                            // ToPixel is an external function, presumably mapping 'v' to an X pixel value
                            XSetForeground(display, gc, ToPixel((int)(v & 0x7fff))); // Set color
                            if (scale == 1) { // If no scaling, draw a point
                                XDrawPoint(display, pixmap, gc, x, y);
                            }
                            // The XFillRectangle here seems to use 'v' for width and height, which is unusual.
                            // This might be a bug or a very specific visual effect.
                            // Typically, it would be scale, scale.
                            XFillRectangle(display, pixmap, gc,
                                           x * scale, y * scale, v, v); // Draw scaled rectangle (size v x v)
                        }
                    } else if (fast) { // If 'fast' mode is active (optimized drawing)
                        int c; // Current pixel's relevant bit(s) from 'tab'
                        int p; // Previous pixel's relevant bit(s) from 'ptab'
                        int v_color; // X pixel color value

                        // Compare current bit in 'tab' with previous bit in 'ptab'
                        p = ptab[x * xsize + y] & (1 << bitn); // Get bit 'bitn' from previous frame
                        c = tab[x * xsize + y] & (1 << bitn);  // Get bit 'bitn' from current frame

                        if (c != p) { // If the bit has changed, redraw this cell
                            v_color = c ? WhitePixel(display, screen)  // If bit is set, use white
                                    : BlackPixel(display, screen); // If bit is clear, use black
                            if (pv != v_color) { // Optimization: only change foreground if color is different
                                XSetForeground(display, gc, v_color);
                                pv = v_color; // Update previous color
                            }
                            XFillRectangle(display, pixmap, gc, // Draw the scaled cell
                                           x * scale, y * scale, scale, scale);
                        }
                    } else { // Default drawing mode (not ncolor, not fast)
                        int v; // Pixel value (likely interested in lower bits)
                        // Checks if the lower 2 bits of the pixel data are non-zero
                        if ((v = tab[x * xsize + y] & 3)) { // Assignment and check
                            // This mode seems to use bits 0 and 1 of tab[idx] to determine intensity/color.
                            // The XFillRectangle call with v,v for size is still unusual.
                            if (scale == 1) {
                                XDrawPoint(display, pixmap, gc, x, y);
                            }
                            // It might be intended that v represents a color index and XSetForeground
                            // should be used with ToPixel(v) or similar.
                            // Or, if v=1,2,3 are sizes, then white is drawn.
                            // Assuming white from the earlier XSetForeground.
                            XFillRectangle(display, pixmap, gc,
                                           x * scale, y * scale, v, v); // Draw scaled rectangle (size v x v)
                        }
                    }
                }
            }

            // Copy the drawn content from the off-screen pixmap to the visible window
            XCopyArea(display, pixmap, win, gc, 0, 0, xsize * scale, ysize * scale, 0, 0);
            XFlush(display); // Ensure drawing commands are sent to the X server

            // Logic for cycling through bit planes or frames
            if (bitn++ == lplane) { // Increment bitn and check if it reached the last plane
                bitn = fplane; // If so, reset to the first plane
                break;         // Break from the Expose event handling (will proceed to read new data)
            }
            continue; // If not last plane, continue in Expose (likely means it re-triggers Expose via XClearArea)
                      // This structure with continue/break in Expose is a bit complex for typical animation.
                      // Usually, one Expose draws one full state, then new data is read outside.
                      // Here, it seems one Expose event might loop internally via XClearArea to draw multiple planes
                      // before breaking to read new data.
            } // End of Expose case
        } // End of switch (e.type)

        // Swap current (tab) and previous (ptab) frame buffers
        tmptab = tab;
        tab = ptab;
        ptab = tmptab;

        // Read new data frames
        {
            int s = step; // Number of steps (frames) to read

            while (s--) { // Loop 'step' times
                n = readn(input, tab, tabsize); // Read one full frame of data into 'tab'
                if (delay) sleep(1); // If delay is enabled, pause for 1 second (sleep needs <unistd.h>)
                ++loop;             // Increment loop counter (total frames read)
                if (n != tabsize) { // If readn did not read a full frame
                    if (!n) { // If readn returned 0 (EOF)
                        if (debug) fprintf(stderr, "\nEOF reached after %d loops.\n", loop);
                        XCloseDisplay(display); // Close X display connection
                        free(tab); free(ptab);   // Free allocated memory
                        return 0; // Successful exit
                    }
                    if (n == -1) { // If readn returned -1 (error)
                        if (debug) fprintf(stderr, "\nRead error after %d loops.\n", loop);
                        XCloseDisplay(display);
                        free(tab); free(ptab);
                        return 1; // Error exit
                    }
                    // If n is non-zero but not tabsize, it's a partial read (problematic for fixed-size frames)
                    // The assert below will catch this.
                }
                // Assert that a full frame was read if n was not 0 or -1 and not equal to tabsize already.
                // This assert should be: assert(n == tabsize);
                // The original `assert(n = tabsize)` is an assignment, not a comparison, and will always be true if tabsize > 0.
                assert(n == tabsize); // Corrected assert: ensure a full frame was read
            }
        }
        if (debug) {
            fprintf(stderr, "%d ", loop); // Print loop count in debug mode
            fflush(stderr); // Ensure debug output is visible immediately
        }
    } // End of main loop
    // This part of the code (after the infinite loop) is unreachable unless there's another break.
    // The exit paths are inside the loop based on readn's return value.
    /*
    if (debug) {
        fprintf(stderr, "\n", loop); // This 'loop' variable is not in scope here.
    }
    XCloseDisplay(display);
    free(tab); free(ptab);
    return 0; // Should be unreachable
    */
}

// Reads 'size' bytes from file descriptor 'fd' into 'buf'.
// Handles partial reads and EOF.
int readn(int fd, char *buf, unsigned int size)
{
    unsigned int chunk_read_total = 0; // Total bytes read so far for this call
    int n_read_current;             // Bytes read in the current read() call
    static int eof_reached = 0;    // Static flag to remember if EOF was hit in the previous call segment

    if (eof_reached) { // If EOF was detected in the part of a previous requested read
        eof_reached = 0; // Reset flag
        return 0;      // Return 0 to indicate EOF state to caller
    }

    // Loop until 'size' bytes are read or an error/EOF occurs
    for (chunk_read_total = 0; chunk_read_total != size; chunk_read_total += n_read_current) {
        // Read a chunk of data (up to remaining bytes)
        n_read_current = read(fd, buf + chunk_read_total, size - chunk_read_total); // read needs <unistd.h>

        if (n_read_current == 0) { // EOF reached
            eof_reached = 1;        // Set flag indicating EOF was hit during this attempt
            // chunk_read_total += n_read_current; // n_read_current is 0, no change to total
            return chunk_read_total; // Return number of bytes read before EOF (could be 0 to size-1)
        }
        if (n_read_current == -1) { // Error during read
            perror(cmd_name);    // Print system error message prefixed with program name
            return n_read_current; // Return -1 to indicate error
        }
        // If n_read_current > 0, it's implicitly added in the loop condition: chunk_read_total += n_read_current
    }
    return size; // Successfully read 'size' bytes
}
