#ifndef _PHASE_INIT_
    #define _PHASE_INIT_

#include <stdbool.h>

int penguins;
bool running;

int *computerPlayers;

void Init(char *Phase, int Penguins, char *input);
void definePenguins();
void setPenguins(int number);
void setRunning(bool running);
int getPenguins();
#endif // _PHASE_INIT_
