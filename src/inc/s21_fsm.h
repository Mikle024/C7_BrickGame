#ifndef S21_FSM_H
#define S21_FSM_H

#include "s21_backend.h"

void transitionTo(GameState newState);
void stateOfStart();
void stateOfSpawn();
void stateOfMoving();
void stateOfShifting();
void stateOfAttaching();
void stateOfGameOver();

// из GameState_Start только в GameState_Spawn
// из GameState_Spawn только в GameState_Moving
// из GameState_Moving в GameState_Attaching и в GameState_Shifting
// из GameState_Shifting в GameState_Moving  и в GameState_Attaching
// из GameState_Attaching в GameState_Spawn и GameState_GameOver
// из GameState_GameOver только в GameState_Start

#endif