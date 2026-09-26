#include <X11/X.h>
#include <X11/Xatom.h>

char* visualClassName(int visualClass) {
	switch(visualClass) {
	    case StaticGray : return "StaticGray";
	    case GrayScale : return "GrayScale";
	    case StaticColor : return "StaticColor";
	    case PseudoColor : return "PseudoColor";
	    case TrueColor : return "TrueColor";
	    case DirectColor : return "DirectColor";
	}
}

char *atomName(Atom atom) {
	switch(atom) {
	    case XA_PRIMARY : return "XA_PRIMARY";
	    case XA_SECONDARY : return "XA_SECONDARY";
	    case XA_ARC : return "XA_ARC";
	    case XA_ATOM : return "XA_ATOM";
	    case XA_BITMAP : return "XA_BITMAP";
	    case XA_CARDINAL : return "XA_CARDINAL";
	    case XA_COLORMAP : return "XA_COLORMAP";
	    case XA_CURSOR : return "XA_CURSOR";
	    case XA_CUT_BUFFER0 : return "XA_CUT_BUFFER0";
	    case XA_CUT_BUFFER1 : return "XA_CUT_BUFFER1";
	    case XA_CUT_BUFFER2 : return "XA_CUT_BUFFER2";
	    case XA_CUT_BUFFER3 : return "XA_CUT_BUFFER3";
	    case XA_CUT_BUFFER4 : return "XA_CUT_BUFFER4";
	    case XA_CUT_BUFFER5 : return "XA_CUT_BUFFER5";
	    case XA_CUT_BUFFER6 : return "XA_CUT_BUFFER6";
	    case XA_CUT_BUFFER7 : return "XA_CUT_BUFFER7";
	    case XA_DRAWABLE : return "XA_DRAWABLE";
	    case XA_FONT : return "XA_FONT";
	    case XA_INTEGER : return "XA_INTEGER";
	    case XA_PIXMAP : return "XA_PIXMAP";
	    case XA_POINT : return "XA_POINT";
	    case XA_RECTANGLE : return "XA_RECTANGLE";
	    case XA_RESOURCE_MANAGER : return "XA_RESOURCE_MANAGER";
	    case XA_RGB_COLOR_MAP : return "XA_RGB_COLOR_MAP";
	    case XA_RGB_BEST_MAP : return "XA_RGB_BEST_MAP";
	    case XA_RGB_BLUE_MAP : return "XA_RGB_BLUE_MAP";
	    case XA_RGB_DEFAULT_MAP : return "XA_RGB_DEFAULT_MAP";
	    case XA_RGB_GRAY_MAP : return "XA_RGB_GRAY_MAP";
	    case XA_RGB_GREEN_MAP : return "XA_RGB_GREEN_MAP";
	    case XA_RGB_RED_MAP : return "XA_RGB_RED_MAP";
	    case XA_STRING : return "XA_STRING";
	    case XA_VISUALID : return "XA_VISUALID";
	    case XA_WINDOW : return "XA_WINDOW";
	    case XA_WM_COMMAND : return "XA_WM_COMMAND";
	    case XA_WM_HINTS : return "XA_WM_HINTS";
	    case XA_WM_CLIENT_MACHINE : return "XA_WM_CLIENT_MACHINE";
	    case XA_WM_ICON_NAME : return "XA_WM_ICON_NAME";
	    case XA_WM_ICON_SIZE : return "XA_WM_ICON_SIZE";
	    case XA_WM_NAME : return "XA_WM_NAME";
	    case XA_WM_NORMAL_HINTS : return "XA_WM_NORMAL_HINTS";
	    case XA_WM_SIZE_HINTS : return "XA_WM_SIZE_HINTS";
	    case XA_WM_ZOOM_HINTS : return "XA_WM_ZOOM_HINTS";
	    case XA_MIN_SPACE : return "XA_MIN_SPACE";
	    case XA_NORM_SPACE : return "XA_NORM_SPACE";
	    case XA_MAX_SPACE : return "XA_MAX_SPACE";
	    case XA_END_SPACE : return "XA_END_SPACE";
	    case XA_SUPERSCRIPT_X : return "XA_SUPERSCRIPT_X";
	    case XA_SUPERSCRIPT_Y : return "XA_SUPERSCRIPT_Y";
	    case XA_SUBSCRIPT_X : return "XA_SUBSCRIPT_X";
	    case XA_SUBSCRIPT_Y : return "XA_SUBSCRIPT_Y";
	    case XA_UNDERLINE_POSITION : return "XA_UNDERLINE_POSITION";
	    case XA_UNDERLINE_THICKNESS : return "XA_UNDERLINE_THICKNESS";
	    case XA_STRIKEOUT_ASCENT : return "XA_STRIKEOUT_ASCENT";
	    case XA_STRIKEOUT_DESCENT : return "XA_STRIKEOUT_DESCENT";
	    case XA_ITALIC_ANGLE : return "XA_ITALIC_ANGLE";
	    case XA_X_HEIGHT : return "XA_X_HEIGHT";
	    case XA_QUAD_WIDTH : return "XA_QUAD_WIDTH";
	    case XA_WEIGHT : return "XA_WEIGHT";
	    case XA_POINT_SIZE : return "XA_POINT_SIZE";
	    case XA_RESOLUTION : return "XA_RESOLUTION";
	    case XA_COPYRIGHT : return "XA_COPYRIGHT";
	    case XA_NOTICE : return "XA_NOTICE";
	    case XA_FONT_NAME : return "XA_FONT_NAME";
	    case XA_FAMILY_NAME : return "XA_FAMILY_NAME";
	    case XA_FULL_NAME : return "XA_FULL_NAME";
	    case XA_CAP_HEIGHT : return "XA_CAP_HEIGHT";
	    case XA_WM_CLASS : return "XA_WM_CLASS";
	    case XA_WM_TRANSIENT_FOR : return "XA_WM_TRANSIENT_FOR";
	}
}
