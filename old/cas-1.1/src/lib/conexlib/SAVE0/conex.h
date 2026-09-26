typedef struct {
    int magic;
    int (*size)();
    int (*bind)(StateVect*, int (*)());
    int (*next)(StateVect*, StateFrame*, StateFrame*);
    int (*stat_next)(StateVect*, StateFrame*, StateFrame*, CntVect*, CntVect*, CntFrame*);
} Conex;

