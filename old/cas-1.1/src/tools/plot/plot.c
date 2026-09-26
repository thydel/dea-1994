/*
 *      dplot.c
 *      Test 4: plotter using the athena widget set
 *
 *      Test plotting with extending data (simulated with timer)
 *
 *      klin, Sun Oct  4 10:56:45 1992
 */

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>

#include <X11/Xaw/Command.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Paned.h>

#include <X11/At/Plotter.h>
#include <X11/At/XYAxis.h>
#include <X11/At/XYLinePlot.h>

#define IVTM 50                 /* Update interval: 50 ms       */
#define MINW 300                /* Min window width             */
#define MINH 200                /* Min window height            */
#define MIN  0.0                /* Min X/Y values               */
#define TIC  1.0                /* Default tic interval         */
#define XMAX 2.0                /* Initial X min value          */
#define YMAX 2.0                /* Initial Y min value          */
#define NNUM 1000               /* # of data points             */

/*
 *      The application context, widgets and timer
 */

static XtAppContext appcontext;
static Widget form;
static Widget quitbutton, startbutton, stopbutton, contbutton;
static XtIntervalId timer = 0;


/*
 *      The plotter widgets
 */

static Widget plotter, xaxis, yaxis;
static Widget line1, line2;

/*
 *      The 'dynamic' plot data
 */

static AtDoublePoint curve1[NNUM];
static AtDoublePoint curve2[NNUM];
static int number = 0;
static double xmax;
static double ymax;
static Boolean running = False;

void SetTimer();

/*
 *      Create the plotter, the axes and the lines
 */

void MakePlotter(parent)
  Widget parent;
{
  Arg args[16];
  double min, tic;
  int n;

  /* Create the plotter */
  n = 0;
  XtSetArg(args[n], XtNtitle, "Dynamic Plotter Demo"); n++;
  XtSetArg(args[n], XtNshowLegend, True); n++;
  XtSetArg(args[n], XtNwidth,  640); n++;
  XtSetArg(args[n], XtNheight, 480); n++;
  XtSetArg(args[n], XtNborderWidth, 2); n++;
  XtSetArg(args[n], XtNuseCursors, False); n++;
  plotter = XtCreateManagedWidget("plotter", atPlotterWidgetClass,
				  parent, args, n);

  /* Create the x and y axes */
  n = 0;
  XtSetArg(args[n], XtNlabel, "Time (in secs)"); n++;
  XtSetArg(args[n], XtNaxisWidth, 1); n++;
  XtSetArg(args[n], XtNticsInside, True); n++;
  XtSetArg(args[n], XtNticsOutside, False); n++;
  XtSetArg(args[n], XtNlinTicFormat, "%g"); n++;
  tic = TIC;
  XtSetArg(args[n], XtNticInterval, &tic); n++;
  XtSetArg(args[n], XtNautoTics, False); n++;
  min = MIN;
  XtSetArg(args[n], XtNmin, &min); n++;
  xmax = XMAX;
  XtSetArg(args[n], XtNmax, &xmax); n++;
  XtSetArg(args[n], XtNautoScale, False); n++;
  xaxis = XtCreateWidget("xaxis", atXYAxisWidgetClass, plotter, args, n);

  n = 0;
  XtSetArg(args[n], XtNticsInside, True); n++;
  XtSetArg(args[n], XtNticsOutside, False); n++;
  XtSetArg(args[n], XtNvertical, True); n++;
  XtSetArg(args[n], XtNlabel, "Amplitude"); n++;
  XtSetArg(args[n], XtNaxisWidth, 1); n++;
  XtSetArg(args[n], XtNlinTicFormat, "%g"); n++;
  tic = TIC;
  XtSetArg(args[n], XtNticInterval, &tic); n++;
  XtSetArg(args[n], XtNautoTics, False); n++;
  min = MIN;
  XtSetArg(args[n], XtNmin, &min); n++;
  ymax = YMAX;
  XtSetArg(args[n], XtNmax, &ymax); n++;
  XtSetArg(args[n], XtNautoScale, False); n++;
  yaxis = XtCreateWidget("yaxis", atXYAxisWidgetClass, plotter, args, n);

  /* Attach the axes */
  n = 0;
  XtSetArg(args[n], XtNxAxis, xaxis); n++;
  XtSetArg(args[n], XtNyAxis, yaxis); n++;
  XtSetValues(plotter, args, n);

  /* Create the lines */
  line1 = XtVaCreateWidget("line1", atXYLinePlotWidgetClass, plotter,
			   XtNlegendName,    "calculated",
			   XtNplotLineType,  AtPlotLINES,
			   XtNplotLineStyle, AtLineSOLID,
			   NULL);
  line2 = XtVaCreateWidget("line2", atXYLinePlotWidgetClass, plotter,
			   XtNlegendName,    "measured",
			   XtNplotLineType,  AtPlotLINES,
			   XtNplotLineStyle, AtLineDOTTED,
			   NULL);
}

/*
 *      Create the 'dynamic' plot data
 */

void MakeData()
{
  double x;
  int i;
  double cos();

  for(i = 0, x = 0.0; i < NNUM; i++, x += 0.01) {
    curve1[i].x = x;
    curve1[i].y = 0.1 * x * x;
    curve2[i].x = x;
    curve2[i].y = curve1[i].y + 0.25 * cos(x);
  }
}

/*
 *      Attach the data to the lines
 */

void AttachData()
{
  AtXYLinePlotAttachDoublePoints(line1, &curve1[0], 1, 0);
  AtXYLinePlotAttachDoublePoints(line2, &curve2[0], 1, 0);
}

/*
 *      Extend the data
 */
#if 0
int ExtendData()
{
  number += 1;
  if(number < NNUM) {
    if(curve1[number].x >= xmax) {
      xmax += XMAX;
      XtVaSetValues(xaxis, XtNmax, &xmax, NULL);
    }
    if(curve1[number].y >= ymax || curve2[number].y >= ymax) {
      ymax += YMAX;
      XtVaSetValues(yaxis, XtNmax, &ymax, NULL);
    }
    AtXYLinePlotExtendData(line1, number);
    AtXYLinePlotExtendData(line2, number);
    return(1);
  }
  return(0);
}
#else
int ExtendData()
{
    char buf[512];
    int v;

    gets(buf);
    v = atoi(buf);
    
  number += 1;
    curve1[number].y = v;
  if(number < NNUM) {
    if(curve1[number].x >= xmax) {
      xmax += XMAX;
      XtVaSetValues(xaxis, XtNmax, &xmax, NULL);
    }
    if(curve1[number].y >= ymax || curve2[number].y >= ymax) {
      ymax += v;
      XtVaSetValues(yaxis, XtNmax, &ymax, NULL);
    }
    AtXYLinePlotExtendData(line1, number);
/*    AtXYLinePlotExtendData(line2, number); */
    return(1);
  }
  return(0);
}
#endif

/*
 *      The callbacks
 */

void quit_callback()
{
  exit(0);
}

void start_callback()
{
  if(timer)
    XtRemoveTimeOut(timer);
  number = 0;
  AttachData();
  xmax = XMAX;
  ymax = YMAX;
  XtVaSetValues(xaxis, XtNmax, &xmax, NULL);
  XtVaSetValues(yaxis, XtNmax, &ymax, NULL);
  running = True;
  SetTimer();
  XtSetSensitive(stopbutton, True);
  XtSetSensitive(contbutton, False);
  printf("\nStarted ...\n");
}

void cont_callback()
{
  if(number < NNUM) {
    running = True;
    XtSetSensitive(stopbutton, True);
    XtSetSensitive(contbutton, False);
    SetTimer();
    printf("\nStarted at %2.2lf seconds\n", curve1[number].x);
  }
  else {
    running = False;
    XtSetSensitive(stopbutton, False);
    XtSetSensitive(contbutton, False);
    printf("\nAlready fininished. Press the <start> button to restart\n");
  }
}

void stop_callback()
{
  running = False;
  if(number < NNUM) {
    XtSetSensitive(contbutton, True);
    XtSetSensitive(stopbutton, False);
    printf("\nStopped at %2.2lf seconds\n", curve1[number].x);
  }
  else {
    XtSetSensitive(stopbutton, False);
    XtSetSensitive(contbutton, False);
    printf("\nAlready fininished. Press the <start> button to restart\n");
  }
}

/*
 *      Create form and buttons
 */

void MakeForm(parent)
  Widget parent;
{
  form = XtVaCreateManagedWidget("form", formWidgetClass, parent, NULL);
  quitbutton = XtVaCreateManagedWidget("quit", commandWidgetClass, form,
					XtNlabel, "Quit",
					XtNleft, XtChainLeft,
					NULL);
  XtAddCallback(quitbutton, XtNcallback, quit_callback, NULL);

  startbutton = XtVaCreateManagedWidget("start", commandWidgetClass, form,
					XtNlabel, "Start",
					XtNfromHoriz, quitbutton,
					NULL);
  XtAddCallback(startbutton, XtNcallback, start_callback, NULL);

  stopbutton = XtVaCreateManagedWidget("stop", commandWidgetClass, form,
				       XtNlabel, "Stop",
				       XtNfromHoriz, startbutton,
				       NULL);
  XtAddCallback(stopbutton, XtNcallback, stop_callback, NULL);
  XtSetSensitive(stopbutton, False);

  contbutton = XtVaCreateManagedWidget("cont", commandWidgetClass, form,
				       XtNlabel, "Continue",
				       XtNfromHoriz, stopbutton,
				       NULL);
  XtAddCallback(contbutton, XtNcallback, cont_callback, NULL);
  XtSetSensitive(contbutton, False);
}

/*
 *      The interval timer routine
 */

void SetTimer()
{
  if(running) {
    fflush(stdout);
    if(ExtendData())
      timer = XtAppAddTimeOut(appcontext, IVTM, SetTimer, 0);
    else {
      timer = 0;
      XtSetSensitive(stopbutton, False);
      XtSetSensitive(contbutton, False);
      printf("\nFinished\n");
    }
  }
}


/*
 *      Main
 */

main(argc, argv)
  int argc;
  char **argv;
{
  Widget appshell;

  appshell = XtAppInitialize(&appcontext, "Plotter", NULL, 0, &argc, argv, NULL, NULL, 0);

  MakeForm(appshell);

  MakePlotter(form);
  XtVaSetValues(plotter, XtNleft, XtChainLeft, XtNfromVert, quitbutton, NULL);

  MakeData();

  XtVaSetValues(appshell, XtNminWidth,  MINW, XtNminHeight, MINH, NULL);

  XtRealizeWidget(appshell);

  printf("Press the <start> button to start\n");
  XtAppMainLoop(appcontext);

  exit(0);
}

#if 0
plotrun(int n) {
    while(XtAppPending(appcontext)) {
	XtAppNextEvent(appcontext, &event);
	XtDispatchEvent(&event);
	fprintf(stderr, "*");
    }
}
#endif

/*
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)strcasecmp.c	5.5 (Berkeley) 11/24/87";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <string.h>

/*
 * This array is designed for mapping upper and lower case letter
 * together for a case independent comparison.  The mappings are
 * based upon ascii character sequences.
 */
static u_char charmap[] = {
	'\000', '\001', '\002', '\003', '\004', '\005', '\006', '\007',
	'\010', '\011', '\012', '\013', '\014', '\015', '\016', '\017',
	'\020', '\021', '\022', '\023', '\024', '\025', '\026', '\027',
	'\030', '\031', '\032', '\033', '\034', '\035', '\036', '\037',
	'\040', '\041', '\042', '\043', '\044', '\045', '\046', '\047',
	'\050', '\051', '\052', '\053', '\054', '\055', '\056', '\057',
	'\060', '\061', '\062', '\063', '\064', '\065', '\066', '\067',
	'\070', '\071', '\072', '\073', '\074', '\075', '\076', '\077',
	'\100', '\141', '\142', '\143', '\144', '\145', '\146', '\147',
	'\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',
	'\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167',
	'\170', '\171', '\172', '\133', '\134', '\135', '\136', '\137',
	'\140', '\141', '\142', '\143', '\144', '\145', '\146', '\147',
	'\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',
	'\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167',
	'\170', '\171', '\172', '\173', '\174', '\175', '\176', '\177',
	'\200', '\201', '\202', '\203', '\204', '\205', '\206', '\207',
	'\210', '\211', '\212', '\213', '\214', '\215', '\216', '\217',
	'\220', '\221', '\222', '\223', '\224', '\225', '\226', '\227',
	'\230', '\231', '\232', '\233', '\234', '\235', '\236', '\237',
	'\240', '\241', '\242', '\243', '\244', '\245', '\246', '\247',
	'\250', '\251', '\252', '\253', '\254', '\255', '\256', '\257',
	'\260', '\261', '\262', '\263', '\264', '\265', '\266', '\267',
	'\270', '\271', '\272', '\273', '\274', '\275', '\276', '\277',
	'\300', '\341', '\342', '\343', '\344', '\345', '\346', '\347',
	'\350', '\351', '\352', '\353', '\354', '\355', '\356', '\357',
	'\360', '\361', '\362', '\363', '\364', '\365', '\366', '\367',
	'\370', '\371', '\372', '\333', '\334', '\335', '\336', '\337',
	'\340', '\341', '\342', '\343', '\344', '\345', '\346', '\347',
	'\350', '\351', '\352', '\353', '\354', '\355', '\356', '\357',
	'\360', '\361', '\362', '\363', '\364', '\365', '\366', '\367',
	'\370', '\371', '\372', '\373', '\374', '\375', '\376', '\377',
};

int
strcasecmp(s1, s2)
    const char *s1, *s2;
{
    register u_char u1, u2;

    for (;;) {
	u1 = (u_char) *s1++;
	u2 = (u_char) *s2++;
	if (charmap[u1] != charmap[u2]) {
	    return charmap[u1] - charmap[u2];
	}
	if (u1 == '\0') {
	    return 0;
	}
    }
}

int
strncasecmp(s1, s2, n)
	const char *s1, *s2;
	register size_t n;
{
    register u_char u1, u2;

    for (; n != 0; --n) {
	u1 = (u_char) *s1++;
	u2 = (u_char) *s2++;
	if (charmap[u1] != charmap[u2]) {
	    return charmap[u1] - charmap[u2];
	}
	if (u1 == '\0') {
	    return 0;
	}
    }
    return 0;
}
