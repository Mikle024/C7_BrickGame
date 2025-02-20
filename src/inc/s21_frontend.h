#ifndef S21_FRONTEND_H
#define S21_FRONTEND_H

#include <unistd.h>

#include "s21_defines.h"
#include "s21_objects.h"

void print_overlay(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

void frontPrint(GameInfo_t *gameInfo);

#endif