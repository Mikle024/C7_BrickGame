#ifndef S21_FSM_H
#define S21_FSM_H

#include "s21_backend.h"
#include "s21_tetris.h"

void transitionToState();

void stateOfStart();
void stateOfSpawn();
void stateOfMoving();
void stateOfShifting();
void stateOfAttaching();
void stateOfGameOver();

void processShift();
bool processAttaching();
bool processGameOver();

#endif