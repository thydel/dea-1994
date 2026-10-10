#define _POSIX_C_SOURCE 200809L
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <errno.h>
#include <getopt.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void help(void) {
    puts("Usage: cell-viewer [-s exponent | -S side] [-z scale] [--exit-on-eof]\n"
         "Read square packed binary frames from stdin, LSB first.\n"
         "  -s N  side = 2^N (default: 8, i.e. 256)\n"
         "  -S N  explicit side, positive multiple of 8\n"
         "  -z N  integer pixel scale (default: 1)\n"
         "  --exit-on-eof  close after the last frame; otherwise keep it visible\n"
         "  -h, --help    show this help\n"
         "Bit 1 is white, bit 0 black. Close the window or press q/Escape.\n"
         "Empty input exits; a partial final frame or read error exits with status 1.");
}
static int number(const char *s) {
    char *end;
    errno = 0;
    long n = strtol(s, &end, 10);
    if (errno || !*s || *end || n < 1 || n > 8192) return 0;
    return (int)n;
}
int main(int argc, char **argv) {
    int side = 256, scale = 1, exit_eof = 0, c;
    static const struct option opts[] = {
        {"help", no_argument, NULL, 'h'},
        {"exit-on-eof", no_argument, NULL, 'E'}, {NULL, 0, NULL, 0}
    };
    while ((c = getopt_long(argc, argv, "s:S:z:h", opts, NULL)) != -1) {
        int n = optarg ? number(optarg) : 0;
        switch (c) {
        case 'h': help(); return 0;
        case 'E': exit_eof = 1; break;
        case 's': if (n < 3 || n > 13) goto usage; side = 1 << n; break;
        case 'S': if (!n || n % 8) goto usage; side = n; break;
        case 'z': if (!n) goto usage; scale = n; break;
        default: goto usage;
        }
    }
    if (optind != argc || side > 8192 / scale) goto usage;
    size_t bytes = (size_t)side * side / 8, used = 0, frames = 0;
    unsigned char *raw = malloc(bytes);
    if (!raw) { perror("malloc"); return 1; }
    Display *d = XOpenDisplay(NULL);
    if (!d) { fputs("cell-viewer: cannot open X display\n", stderr); free(raw); return 1; }
    int screen = DefaultScreen(d), dim = side * scale;
    Window w = XCreateSimpleWindow(d, RootWindow(d, screen), 0, 0,
        (unsigned)dim, (unsigned)dim, 0, BlackPixel(d, screen), BlackPixel(d, screen));
    XStoreName(d, w, "cell-viewer");
    XSelectInput(d, w, ExposureMask | KeyPressMask | StructureNotifyMask);
    Atom close = XInternAtom(d, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(d, w, &close, 1);
    XSizeHints hints = {0};
    hints.flags = PMinSize | PMaxSize;
    hints.min_width = hints.max_width = dim;
    hints.min_height = hints.max_height = dim;
    XSetWMNormalHints(d, w, &hints);
    GC gc = XCreateGC(d, w, 0, NULL);
    XSetForeground(d, gc, WhitePixel(d, screen));
    XSetBackground(d, gc, BlackPixel(d, screen));
    XImage *im = XCreateImage(d, DefaultVisual(d, screen), 1, XYBitmap,
        0, NULL, (unsigned)dim, (unsigned)dim, 8, 0);
    if (!im || !(im->data = calloc((size_t)im->bytes_per_line, (size_t)dim))) {
        fputs("cell-viewer: image allocation failed\n", stderr);
        if (im) XDestroyImage(im);
        XFreeGC(d, gc); XDestroyWindow(d, w); XCloseDisplay(d); free(raw); return 1;
    }
    im->bitmap_bit_order = LSBFirst;
    im->byte_order = LSBFirst;
    XInitImage(im);
    XMapWindow(d, w);
    XFlush(d);
    int eof = 0, status = 0, running = 1;
    while (running) {
        while (XPending(d)) {
            XEvent e; XNextEvent(d, &e);
            if (e.type == Expose && e.xexpose.count == 0 && frames)
                XPutImage(d, w, gc, im, 0, 0, 0, 0, (unsigned)dim, (unsigned)dim);
            if (e.type == ClientMessage && (Atom)e.xclient.data.l[0] == close) running = 0;
            if (e.type == KeyPress) {
                KeySym key = XLookupKeysym(&e.xkey, 0);
                if (key == XK_q || key == XK_Escape) running = 0;
            }
        }
        XFlush(d);
        if (!running) break;
        struct pollfd fds[2] = {{ConnectionNumber(d), POLLIN, 0},
                               {eof ? -1 : STDIN_FILENO, POLLIN, 0}};
        int ret = poll(fds, 2, -1);
        if (ret < 0) { if (errno == EINTR) continue; perror("poll"); status = 1; break; }
        if (fds[1].revents & (POLLIN | POLLHUP | POLLERR | POLLNVAL)) {
            ssize_t n = read(STDIN_FILENO, raw + used, bytes - used);
            if (n < 0) { if (errno == EINTR || errno == EAGAIN) continue; perror("stdin"); status = 1; break; }
            if (!n) {
                eof = 1;
                if (used) { fprintf(stderr, "cell-viewer: truncated frame (%zu/%zu bytes)\n", used, bytes); status = 1; break; }
                fprintf(stderr, "cell-viewer: EOF after %zu frames\n", frames);
                if (!frames || exit_eof) break;
            } else {
                used += (size_t)n;
                if (used == bytes) {
                    for (int y = 0; y < dim; ++y)
                        for (int x = 0; x < dim; ++x) {
                            size_t i = (size_t)(y / scale) * side + x / scale;
                            XPutPixel(im, x, y, (raw[i / 8] >> (i % 8)) & 1);
                        }
                    ++frames; used = 0;
                    XPutImage(d, w, gc, im, 0, 0, 0, 0, (unsigned)dim, (unsigned)dim);
                    XSync(d, False);
                }
            }
        }
    }
    XDestroyImage(im); XFreeGC(d, gc); XDestroyWindow(d, w); XCloseDisplay(d); free(raw);
    return status;
usage:
    fputs("cell-viewer: invalid arguments (see --help)\n", stderr); return 2;
}
