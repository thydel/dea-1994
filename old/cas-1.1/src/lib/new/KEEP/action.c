#include <malloc.h>
#include <assert.h>

#include "tclExtend.h"

#include "local.h"
#include "magic.h"
#include "frame/frame.h"
#include "action.h"

Action* Action_new(void (*func)(void*), void* data, int timer) {
    Action* zis;

    assert(timer >= 1);
    zis = (Action*)malloc(sizeof(Action));
    assert(zis);
    zis->magic = magic(ACTION);
    zis->func = func;
    zis->data = data;
    zis->timer_val = zis->timer = timer;
    return zis;
}

void Action_delete(Action* zis) {
    assert(zis && zis->magic == magic(ACTION));
    free(zis);
}

void Action_trigger(Action* zis) {
    assert(zis && zis->magic == magic(ACTION));
    if (!zis->timer--) {
	zis->timer = zis->timer_val;
	zis->func(zis->data);
    }
}
