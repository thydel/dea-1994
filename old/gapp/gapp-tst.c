#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "bit-field.h"
#include "gapp-defs.h"
#include "gapp-arch.h"
#include "gapp-pe.h"
#include "gapp-sim.h"
#include "gapp-opts.h"
#include "gapp-step.h"
#include "space.h"

gapptst(Gappsim* gappsim, Gappsim_options* options) {
  Gapp_Step* gapp_step;

  gapp_step = Gapp_Step_new(0, gappsim, options);
  Gapp_Step_load(gapp_step, stdin);
  Gapp_Step_run(gapp_step, 1);
}
