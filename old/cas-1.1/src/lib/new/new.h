typedef struct {
    int magic;
    StateVect* past;
    StateVect* futur;
    int time;
    int nstate;

    /* stats */
    int sum;
    CntVect* histogram;
    CntFrame* time_sum;
} Space1D;

typedef struct {
    int magic;
    int msg;
    StateFrame* state;
    PlaneFrame* plane;
    int time;
    int nstate;

    /* stats */
    int sum;
    CntVect* histogram;
    CntFrame* time_sum;
} Space2D;

extern Space2D* Space2D_new(int, int, int);

Space2D* Space2D_new(int x, int y, int z) {
    Space2D* zis;

    zis = (Space2D*)malloc(sizeof(Space2D));
    assert(zis);
    zis->magic = magic(SPACE_2D);
    zis->state = SF_new(x, y, z);
    zis->plane = PF_new(z, y, z);
    zis->time = 0;
    zis->nstate = 1 << z;
    zis->sum = 0
    zis->histogram = 0;
    zis->time_sum = 0;
    return zis;
}

void Space2D_alloc_stats(Space2D* zis) {
    assert(zis && zis->magic == magic(SPACE_2D) && !zis->msg);
    if (zis->histogram || zis->time_sum) {
	zis->msg = "stats already allocated";
	return;
    }
    zis->histogram = CntVect_new(zis->nstate);
    zis->time_sum = StateVect(zis->state->xisze, zis->state->ysize);
}

void Space2D_compute_stats(Space2D* zis) {
    State* iptr;
    Cnt* hptr;
    Cnt* sptr;
    int cnt;
    int sum;

    assert(zis && zis->magic == magic(SPACE_2D) && !zis->msg);
    if (!zis->histogram || !zis->time_sum) {
	zis->msg = "stats not allocated";
	return;
    }
    CV_zero(zis->histogram);
    iptr = zis->state->ptr;
    hptr = zis->histogram->ptr;
    sptr = zis->time_sum->ptr;
    cnt = zis->state->size;
    sum = 0;
    for (i = 0; i < cnt; ++i) {
	int state;

	state = iptr[i];
	sum += state;
	++hptr[state];
	sptr[i] += state;
    }
    zis->sum = sum;
}

typedef struct {
    int magic;
    Space2D** space;		/* vector of space used as a circular buffer */
				/* of space, keeping first n entries for history */
    int cnt;			/* cnt of allocated spaces */
    int first;			/* index of first usable space */
    int past;			/* index of last computed space */
    int futur;			/* index of next space to compute */
    int free;			/* cnt of free space */
    int time;			/* cnt of computed translation */
} Time2D;

Time2D* Time2D_new(Space2D* space, int cnt) {
    Time2D* zis;
    int x;
    int y;
    int z;

    assert(space && space->magic == magic(SPACE_2D) && cnt >= 2);
    zis = (Time2D*)malloc(sizeof(Time2D));
    assert(zis);
    zis->magic = magic(TIME_2D);
    zis->cnt = cnt;
    zis->space = (Space2D**)malloc(sizeof(Space2D**));
    assert(zis->space);
    zis->seed = space;
    z = space->state->xsize;
    y = space->state->ysize;
    z = space->state->plane;
    for (i = 0; i < cnt; ++i) {
	zis->space[i] = Space2D_new(x, y, z);
	zis->space[i]->time = 0;
    }

    zis->time = 0;
    zis->past = 0;
    zis->now = zis->past;
    Space2D_copy(zis->space[zis->time], zis->seed);
    zis->space[zis->past]->time = zis->time;
    zis->futur = 1;
    zis->first = 0;
    zis->free = zis->cnt - 2;
}

extern bool Time2D_next(Time2D*);

Time2D_assert(Time2D* zis) {
    assert(zis && zis->magic == magic(TIME_2D));
    assert(zis->free >= 0);
    assert(zis->first >= 0 && zis->first < zis->cnt - 2);
    assert(zis->past < zis->futur);
    assert(zis->past >= zis->first && zis->past < zis->cnt - 1);
    assert(zis->futur > zis->first && zis->futur < zis->cnt);
    assert(zis->now >= 0 && zis->now < futur);
}

void Time2D_incr(Time2D* zis) {
    assert(zis && zis->magic == magic(TIME_2D));
    assert(zis->past < zis->futur);
    assert(zis->space[zis->past]->time < zis->time + 1);
    ++zis->time;
    zis->space[zis->past]->time = zis->time;
}

void Time2D_swap(Time2D* zis, int a, int b) {
    Space* tmp;

    assert(zis && zis->magic == magic(TIME_2D));
    assert(a >= 0 && b >= 0 && a <= zis->cnt && b <= zis->cnt);
    tmp = zis->space[a];
    zis->space[a] = zis->space[b];
    zis->space[b] = tmp;
}

bool Time2D_next(Time2D* zis) {
    int tmp;

    Time2D_assert(zis);
    if (!zis->free) {
	if (zis->cnt == 2) {
	    Time2D_swap(zis, zis->past, zis->futur);
	    Time2D_incr(zis);
	    return true;
	}
	return false;
    }
    --zis->free;
    ++zis->past;
    ++zis->futur;
    Time2D_incr(zis);
    Time2D_assert(zis);
    return true;
}

void Time2D_forget(Time2D* zis) {
    Time2D_assert(zis);
    Time2D_swap(zis, zis->first, zis->futur);
    zis->past = zis->first;
    Time2D_incr(zis);
    zis->futur = zis->past + 1;
    zis->free = zis->cnt - zis->first;
    Time2D_assert(zis);
}

Time2D_save(Time2D* zis) {
    Time2D_assert(zis);
    Time2D_swap(zis, zis->first, zis->futur);
    zis->past = zis->first;
    ++zis->first;
    Time2D_incr(zis);
    zis->futur = zis->past + 1;
    zis->free = zis->cnt - zis->first;
    Time2D_assert(zis);
}

Time2D_shrink(Time2D* zis) {
    for (i = 0; i < zis->futur >> 1; ++i) {
	Time2D_swap(zis, i, i << 1);
    }
    zis->now = zis->cnt >> 1;
}

extern void Time_first(Time*);
extern void Time_last(Time*);

typedef struct {
    int magic;
    void (*func)(void*);
} Action;

typedef struct {
    int magic;
    int timer_val;
    int timer;
    Action* action;
    void* data
} CallBack;

typedef struct {
    Time2D* time;
    Space2D* now;		/* current space for callback */
    Func* func;
    CallBack** callback;
    int cnt;
} Simple2D;

main() {
    ConexType* moore_type = ConexType_new("moore", 9);
    ConexType* local_type = ConexType_new("local", 1);
    ConexSpec* moore = ConexSpec_new(ConexList_new(ConexVar_new(moore_type, 1), 0),
				     ConexList_new(ConexVar_new(local, 1), 0),
				     moore_1);
    Simple2D simple = Simple2D_new(Time2D_new(Space2D_new(256, 256, 1), 2),
				   Func_new(moore, 0, life, 0));
    CallBack* dumper CallBack_new(Xdumper_new(0), &simple->now, 1);
    CallBack* stater CallBack_new(Stater_new(0), &simple->now, 1);
    Simple_add_callback(simple, dumper);
    Simple_add_callback(simple, stater);
}

extern Simple* Simple_new(Func*, Time*);
extern void Simple_step(Simple*);
extern void Simple_func(Simple*, Func*);
extern void Simple_bind(Simple*, int, char**);
extern void Simple_dump(Simple*, int, bool);

void Simple_step(Simple* zis) {
    assert(zis && zis->magic == magic(SIMPLE));
    zis->func->spec->apply(Time_now(zis->time));
    Time_next(zis->time);
}

void Simple_play(Simple* zis) {
    for (i = 0; i < zis->time->futur; ++i) {
	zis->now = zis->time->space[i];
	for (j = 0; j < zis->cnt; ++j) {
	    zis->callback[j]->action->func(*zis->callback[j]->data);
	}
    }
}
