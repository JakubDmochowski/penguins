#include <string.h>

#include "Placement.h"
#include "Init.h"
#include "Movement.h"

#ifndef _LOOP_
    #define _LOOP_

enum phase {
    PLACEMENT,
    MOVEMENT
};

void setPhase(char *P);
void Loop();

#endif // _LOOP_
