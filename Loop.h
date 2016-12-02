#ifndef _LOOP_
    #define _LOOP_

#include "Define.h"

enum phase {
    PLACEMENT,
    MOVEMENT
};

int turn;

void setPhase(char *P);
void Loop();

#endif // _LOOP_
