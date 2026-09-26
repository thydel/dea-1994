typedef struct {
    int magic;
    int stat;
    int cnt;
    Conex* conex;
    StateVect* rule_tbl;
    StateFrame* past;
    StateFrame* futur;
    CntVect* rule_sum;
    CntVect* hor_sum;
    CntFrame* vert_sum;
} Trans;

extern Trans* trans_new(Conex*, StateFrame*, bool);
void trans_bind(Trans*, int (*)());
extern void trans_next(Trans*);
