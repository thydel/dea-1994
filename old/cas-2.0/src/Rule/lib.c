#include "conex.h"

#define SE i->se
#define E i->e
#define NE i->ne
#define S i->s
#define C i->c
#define N i->n
#define SW i->sw
#define W i->w
#define NW i->nw

#define moore(name, expr) \
void Moore_ ## name(Moore* i, Local* o) { *o = expr; }

#define vn(name, expr) \
void VN_ ## name(VN* i, Local* o) { *o = expr; }

#define def(name, expr) vn(name, expr); moore(name, expr)

#define defop(name, op) \
    def(name ## 4, four(op)); \
    def(name ## 5, five(op)); \
    moore(name ## 8, height(op)); \
    moore(name ## 9, nine(op))

#define four(op) N op E op S op W
#define five(op) C op four(op)
#define height(op) four(op) op NE op SE op SW op NW
#define nine(op) C op height(op)

defop(sum, +);
defop(and, &);
defop(or, |);
defop(xor, ^);

def(stir5, C & four(^))
def(inv, ~C)

def(north, N)
def(south, S)
def(east, E)
def(west, W)

void Local_mov(Local* src, Local* dest) {
    *dest = *src;
}

void Local_inv(Local* src, Local* dest) {
    *dest = ~*src;
}

void Local_or(Local* src1, Local* src2, Local* dest) {
    *dest = *src1 | *src2;
}

