#ifndef _PHASE_LOOP_
    #define _PHASE_LOOP_

#include "Define.h"

enum phase {
    PLACEMENT,
    MOVEMENT
};

int turn;

void setPhase(char *P);
void Loop();
void printGameOver();

#endif // _PHASE_LOOP_
