#ifndef S21_DEFINES_H
#define S21_DEFINES_H

/* Dimensions of the playing field and figures */
#define FIELD_WIDTH 10  /* Playing field width */
#define FIELD_HEIGHT 20 /* Playing field height */
#define FIGURE_SIZE 4   /* Shape size */
#define FIGURE_COUNT 7  /* Number of figure types */

/* Initial coordinates for the appearance of figures */
#define START_COORD_F_X \
  (FIELD_WIDTH / 2 - FIGURE_SIZE / 2) /* Initial X coordinate */
#define START_COORD_F_Y (-2)          /* Initial Y coordinate */

/* Parameters of levels */
#define START_DELAY 700 /* Initial figure drop delay (ms) */
#define MIN_DELAY 50    /* Minimum figure drop delay (ms) */
#define START_LEVEL 1   /* Beginner level of play */
#define MAX_LEVEL 10    /* Maximum level of play */

/* File name for storing the record */
#define HIGH_SCORE_FILE "highScore.txt"

#endif