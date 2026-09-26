typedef struct {
    int magic;
    void (*func)(void*);
    void* data;
    int timer_val;
    int timer;
} Action;

extern Action* Action_new(void (*)(void*), void*, int);
extern void Action_trigger(Action*);
