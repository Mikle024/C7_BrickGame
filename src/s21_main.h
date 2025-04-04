#ifndef S21_MAIN_H
#define S21_MAIN_H

#include "gui/cli/inc/s21_frontend.h"
#include "gui/cli/inc/s21_frontend_defs.h"

/**
 * @brief Main game loop that handles game states and user interactions
 *
 * @param winGame pointer to the game windows structure
 */
void gameLoop(WinCurses *winGame);

/**
 * @brief Initializes the initial state of the game
 *
 * @return GameInfo_t current state of game
 */
GameInfo_t initializeGameState(void);

/**
 * @brief Renders the current state of the game
 *
 * @param gameInfo pointer to the structure with game state information
 * @param winGame pointer to the interface windows structure
 */
void renderGameState(GameInfo_t *gameInfo, WinCurses *winGame);

/**
 * @brief Handles user input
 *
 * @param ch key code of the pressed key
 * @param lastKey key code of the last pressed key
 * @param winGame pointer to the interface windows structure
 * @return int 1 - if the game should terminate, 0 - otherwise
 */
int handleUserInput(const int ch, const int lastKey, WinCurses *winGame);

/**
 * @brief Updates the game state
 *
 * @param gameInfo pointer to the structure with game state information
 * @param lastKey pointer to the code of the last pressed key
 * @param ch code of the current pressed key
 */
void updateGameState(GameInfo_t *gameInfo, int *lastKey, int ch);

/**
 * @brief Handles game over state
 *
 * @param gameInfo pointer to the structure with game state information
 * @param winGame pointer to the interface windows structure
 */
void handleGameOver(GameInfo_t *gameInfo, WinCurses *winGame);

#endif