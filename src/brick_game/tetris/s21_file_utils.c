#include "inc/s21_file_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/s21_defines.h"

int initHighScore() {
  int highScore = 0;
  FILE *fp = fopen(HIGH_SCORE_FILE, "r");

  if (fp != NULL) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';

      char *endPtr;
      long score = strtol(buffer, &endPtr, 10);

      if (endPtr != buffer && *endPtr == '\0' && score > 0) {
        highScore = (int)score;
      }
    }

    fclose(fp);
  }

  return highScore;
}

bool updateScore(const int score) {
  bool result = false;
  FILE *fp = fopen(HIGH_SCORE_FILE, "w");

  if (fp) {
    result = fprintf(fp, "%d\n", score);
    fclose(fp);
  }
  return (result > 0);
}