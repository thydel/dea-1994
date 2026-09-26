
#define CMAP_TOGGLE 0
#define CMAP_OPEN 1
#define CMAP_CLOSE 2

/* commands HandleCEvent may return to main(): */
#define DO_REDRAW 1
#define DO_PREVIOUS 2
#define DO_RESTART 3
#define DO_QUIT 4

void ToggleCWin();
int HandleCEvent();
void AllocColors();
void FreeColors();
void SetNColors();
unsigned long ToPixel();

