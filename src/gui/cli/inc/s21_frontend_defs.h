#ifndef S21_FRONTEND_DEFS_H
#define S21_FRONTEND_DEFS_H

// board size
#define Y_START 5
#define X_START 5
#define F_HEIGHT 20
#define F_WIDTH 10

// board size for printing
#define BOARD_HEIGHT (FIELD_HEIGHT + 2)
#define BOARD_WIDTH (FIELD_WIDTH * 2 + 2)

// figure size
#define FIGURE_X (F_WIDTH / 2 - 2)
#define FIGURE_S 4

//  next figure size
#define NEXT_HEIGHT 8
#define NEXT_WIDTH 14
#define NEXT_Y 5
#define NEXT_X 27

// score size
#define SCORE_HEIGHT 14
#define SCORE_WIDTH 14
#define SCORE_Y 13
#define SCORE_X 27

// input size
#define INPUT_HEIGHT 7
#define INPUT_WIDTH 36
#define INPUT_Y 27
#define INPUT_X 5

// message box size
#define MSG_BOX_WIDTH 20
#define MSG_BOX_HEIGHT 5

#define GAME_LOOP_DELAY 10

// Colour pairs
#define COLOR_EMPTY 1
#define COLOR_BORDER 2
#define COLOR_TEXT 3
#define COLOR_FIGURE_START 4

#endif