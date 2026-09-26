#include <stdio.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>	/* Get standard string definations. */

#include <X11/Xaw/Box.h>	
#include <X11/Xaw/Command.h>	
#include <X11/Xaw/Label.h>	
#include <X11/Xaw/Cardinals.h>	
#include <X11/Xaw/Dialog.h>

typedef struct {
	int i;
	XtAppContext app_con;
} Foo;

static void iSet(Widget w, XtPointer client_data, XtPointer call_data) {
	Foo* foo = (Foo*)client_data;

	if (foo->i == 0) {
		foo->i = 1;
	} else {
		foo->i = 0;
	}
}

static void dialogcmd(Widget w, XtPointer junk, XtPointer garbage) {
	printf("txt is %s \n", XawDialogGetValueString(XtParent(w)));
}

Foo* foonew() {
	Widget toplevel, box, dialog, widget;
	Foo* foo = (Foo*)malloc(sizeof(Foo));
	Arg args[4];
	foo->i = 0;
	
	toplevel = XtAppInitialize(&foo->app_con, "try", NULL, ZERO,
				   0, 0, NULL,
				   NULL, ZERO);

	box = XtCreateManagedWidget("box", boxWidgetClass, toplevel, NULL, ZERO);

	widget = XtCreateManagedWidget("widget1", commandWidgetClass, box, NULL, ZERO);
	XtAddCallback(widget, XtNcallback, iSet, (char*)foo);

	widget = XtCreateManagedWidget("widget2", commandWidgetClass, box, NULL, ZERO);
	XtAddCallback(widget, XtNcallback, iSet, (char*)foo);

	XtSetArg(args[0], XtNvalue, "");
	dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, box, args, 1);
	XawDialogAddButton(dialog, "cmd", dialogcmd, NULL);

	XtRealizeWidget(toplevel);
	return foo;
}

foo_x(Foo* foo) {
	XEvent event;

	while(XtAppPending(foo->app_con)) {
		XtAppNextEvent(foo->app_con, &event);
		XtDispatchEvent(&event);
		fprintf(stderr, "*");
	}
}

main(argc, argv)
int argc;
char **argv;
{
	int i;
	int n = atoi(argv[1]);
	Foo* foo = foonew();

	for (;;) {
		for (i = 0; i < n; i++) {
		}
		fprintf(stderr, "%d ", foo->i);
		foo_x(foo);
	}
	fprintf(stderr, "\n");
}



