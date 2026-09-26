#define KILO 1024

typedef struct {
  Gappsim* gappsim;
  Gappsim_options* options;
  int output;
  struct {
    void (*funk)();
    void* args;
  } prog[8 * KILO];
  int cnt;
} Gapp_Step;

Gapp_Step *Gapp_Step_new(Gapp_Step *zis, Gappsim *gappsim, Gappsim_options *options);
void Gapp_Step_load(Gapp_Step *zis, FILE *input);
void Gapp_Step_run(Gapp_Step *zis, int);
