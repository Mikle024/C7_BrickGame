#ifndef S21_LIBRARY_H
#define S21_LIBRARY_H

#include <stdbool.h>

#include "s21_backend.h"
#include "s21_defines.h"
#include "s21_types.h"

/**
 * @brief Handles user input and performs corresponding actions.
 *
 * @param action The action to be performed.
 * @param hold Indicates whether the action should be held.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Updates the current state of the game.
 *
 * @return The updated game information.
 */
GameInfo_t updateCurrentState();

#endif