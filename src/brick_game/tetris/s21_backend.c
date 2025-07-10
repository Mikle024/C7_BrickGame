#include "inc/s21_backend.h"

GameContext_t *getCurrentContext() {
  static GameContext_t gameContext;
  static bool initGame = false;
  if (!initGame) {
    initRandom();
    initializeGame(&gameContext, &initGame);
  }
  return &gameContext;
}

void initRandom(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  srand((unsigned int)(tv.tv_sec * 1000000 + tv.tv_usec));
}

long long getCurrentTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

bool timer() {
  GameContext_t *gameContext = getCurrentContext();
  bool result = false;
  long long current_time = getCurrentTime();

  if (current_time - gameContext->lastTime >=
      gameContext->gameStateInfo.speed) {
    gameContext->lastTime = current_time;
    result = true;
  }
  return result;
}

void initializeGame(GameContext_t *context, bool *checkInit) {
  context->currentState = GameState_Start;

  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  context->gameStateInfo.next = createFigure(rand() % FIGURE_COUNT);
  context->gameStateInfo.score = 0;
  context->gameStateInfo.high_score = initHighScore();
  context->gameStateInfo.level = START_LEVEL;
  context->gameStateInfo.speed = START_DELAY;
  context->gameStateInfo.pause = 1;

  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  context->figureX = START_COORD_F_X;
  context->figureY = START_COORD_F_Y;
  context->oldFigureX = START_COORD_F_X;
  context->oldFigureY = START_COORD_F_Y;
  context->lastTime = 0;
  context->shiftRequested = false;
  context->goodMode = false;  // god mode

  *checkInit = true;
}

void freeGame() {
  GameContext_t *context = getCurrentContext();
  if (context) {
    freeMatrix(context->currentFigure, FIGURE_SIZE);
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
    freeMatrix(context->gameStateInfo.next, FIGURE_SIZE);

    context->currentFigure = NULL;
    context->gameStateInfo.field = NULL;
    context->gameStateInfo.next = NULL;

    context->figureX = 0;
    context->figureY = 0;
    context->oldFigureX = 0;
    context->oldFigureY = 0;
    context->lastTime = 0;
    context->currentState = GameState_Start;

    context->gameStateInfo.score = 0;
    context->gameStateInfo.high_score = 0;
    context->gameStateInfo.level = 0;
    context->gameStateInfo.speed = 0;
    context->gameStateInfo.pause = 0;
  }
}

int **createFigure(const int figureNum) {
  static const int patternFigure[FIGURE_COUNT][FIGURE_SIZE][FIGURE_SIZE] = {
      // I
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // O
      {{0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // T
      {{0, 0, 0, 0}, {3, 3, 3, 0}, {0, 3, 0, 0}, {0, 0, 0, 0}},
      // L
      {{0, 4, 0, 0}, {0, 4, 0, 0}, {0, 4, 4, 0}, {0, 0, 0, 0}},
      // J
      {{0, 0, 5, 0}, {0, 0, 5, 0}, {0, 5, 5, 0}, {0, 0, 0, 0}},
      // S
      {{0, 0, 0, 0}, {0, 0, 6, 6}, {0, 6, 6, 0}, {0, 0, 0, 0}},
      // Z
      {{0, 0, 0, 0}, {7, 7, 0, 0}, {0, 7, 7, 0}, {0, 0, 0, 0}}};
  int **newFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      newFigure[i][j] = patternFigure[figureNum][i][j];
    }
  }

  return newFigure;
}

void dropNewFigure(const int x, const int y) {
  GameContext_t *context = getCurrentContext();
  if (context && context->currentFigure) {
    freeMatrix(context->currentFigure, FIGURE_SIZE);
    context->currentFigure = context->gameStateInfo.next;

    context->gameStateInfo.next = createFigure(rand() % FIGURE_COUNT);

    context->figureX = x;
    context->figureY = y;
    context->oldFigureX = x;
    context->oldFigureY = y;
  }
}

void addCurrentFigureToField() {
  GameContext_t *context = getCurrentContext();
  if (context && context->currentFigure && context->gameStateInfo.field) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        if (context->currentFigure[i][j] != 0 && context->figureY + i >= 0 &&
            context->figureY + i < FIELD_HEIGHT && context->figureX + j >= 0 &&
            context->figureX + j < FIELD_WIDTH) {
          context->gameStateInfo
              .field[context->figureY + i][context->figureX + j] =
              context->currentFigure[i][j];
        }
      }
    }
  }
}

void clearCurrentFigureFromField() {
  GameContext_t *context = getCurrentContext();
  if (context && context->currentFigure && context->gameStateInfo.field) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        int fieldX = context->oldFigureX + j;
        int fieldY = context->oldFigureY + i;

        if (context->currentFigure[i][j] != 0 && fieldY >= 0 &&
            fieldY < FIELD_HEIGHT && fieldX >= 0 && fieldX < FIELD_WIDTH) {
          context->gameStateInfo.field[fieldY][fieldX] = 0;
        }
      }
    }

    context->oldFigureX = context->figureX;
    context->oldFigureY = context->figureY;
  }
}

void attachFigureToField() {
  GameContext_t *context = getCurrentContext();
  if (context && context->currentFigure && context->gameStateInfo.field) {
    addCurrentFigureToField();

    int **field = context->gameStateInfo.field;

    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        if (context->currentFigure[i][j] != 0) {
          int fx = context->figureX + j;
          int fy = context->figureY + i;

          if (fx >= 0 && fx < FIELD_WIDTH && fy >= 0 && fy < FIELD_HEIGHT) {
            field[fy][fx] = 8;
          }
        }
      }
    }
  }
}

bool isSquareFigure() {
  GameContext_t *context = getCurrentContext();
  bool result = false;
  if (context && context->currentFigure) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        if (context->currentFigure[i][j] == 2) result = true;
      }
    }
  }
  return result;
}

bool collision() {
  GameContext_t *context = getCurrentContext();
  bool hasCollision = false;
  if (context && context->currentFigure && context->gameStateInfo.field) {
    int **currentFigure = context->currentFigure;

    for (int i = 0; i < FIGURE_SIZE && !hasCollision; i++) {
      for (int j = 0; j < FIGURE_SIZE && !hasCollision; j++) {
        if (currentFigure[i][j] != 0) {
          int boardX = context->figureX + j;
          int boardY = context->figureY + i;

          if (boardY >= FIELD_HEIGHT) hasCollision = true;

          if ((boardX < 0 || boardX >= FIELD_WIDTH) &&
              !context->goodMode)  // god mode
            hasCollision = true;

          if (pixelInField(boardX, boardY) &&
              context->gameStateInfo.field[boardY][boardX] != 0) {
            int fieldValue = context->gameStateInfo.field[boardY][boardX];

            if (fieldValue != 0 && fieldValue != currentFigure[i][j]) {
              hasCollision = true;
            }
          }
        }
      }
    }
  }
  return hasCollision;
}

bool pixelInField(const int x, const int y) {
  return (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT);
}

void countScore(const int lines) {
  GameContext_t *context = getCurrentContext();
  if (context) {
    static const int scores[] = {0, 100, 300, 700, 1500};

    int scoreIndex = (lines >= 0 && lines <= 4) ? lines : 0;

    context->gameStateInfo.score += scores[scoreIndex];
    context->gameStateInfo.level = 1 + (context->gameStateInfo.score / 600);

    if (context->gameStateInfo.level > MAX_LEVEL) {
      context->gameStateInfo.level = MAX_LEVEL;
    }

    countSpeed();

    if (context->gameStateInfo.score > context->gameStateInfo.high_score) {
      context->gameStateInfo.high_score = context->gameStateInfo.score;

      if (!updateScore(context->gameStateInfo.high_score)) {
        // For debugging: high score writing failed
        // In production code, error logging could be added here
      }
    }
  }
}

void countSpeed() {
  GameContext_t *context = getCurrentContext();
  if (context) {
    int level = context->gameStateInfo.level;

    if (level <= 1) {
      context->gameStateInfo.speed = START_DELAY;
    } else if (level >= MAX_LEVEL) {
      context->gameStateInfo.speed = MIN_DELAY;
    } else {
      int levelRange = MAX_LEVEL - 1;
      int delayRange = START_DELAY - MIN_DELAY;
      int levelStep = (level - 1);

      context->gameStateInfo.speed =
          START_DELAY - (levelStep * delayRange / levelRange);
    }
  }
}

int clearLines() {
  int cleared = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    if (fullLine(i)) {
      removeLine(i);
      cleared += 1;
    }
  }
  return cleared;
}

bool fullLine(const int numLine) {
  GameContext_t *context = getCurrentContext();
  bool isFullLine = true;
  if (context) {
    for (int i = 0; i < FIELD_WIDTH && isFullLine; i++) {
      if (context->gameStateInfo.field[numLine][i] == 0) isFullLine = false;
    }
  }
  return isFullLine;
}

void removeLine(const int numLine) {
  GameContext_t *context = getCurrentContext();
  if (context) {
    for (int i = numLine; i > 0; i--) {
      for (int j = 0; j < FIELD_WIDTH; j++) {
        context->gameStateInfo.field[i][j] =
            context->gameStateInfo.field[i - 1][j];
      }
    }
    for (int i = 0; i < FIELD_WIDTH; i++) {
      context->gameStateInfo.field[0][i] = 0;
    }
  }
}

void moveFigureRight() {
  GameContext_t *context = getCurrentContext();
  if (context) {
    context->figureX++;
    if (collision()) context->figureX--;
  }
}

void moveFigureLeft() {
  GameContext_t *context = getCurrentContext();
  if (context) {
    context->figureX--;
    if (collision()) context->figureX++;
  }
}

void moveFigureDown() {
  GameContext_t *context = getCurrentContext();
  if (context) {
    context->figureY++;
    if (collision()) context->figureY--;
  }
}

void moveFigureUp() {
  GameContext_t *context = getCurrentContext();
  if (context) {
    context->figureY--;
    if (collision()) context->figureY++;
  }
}

void rotationFigure() {
  GameContext_t *context = getCurrentContext();
  if (context && context->currentFigure) {
    int **rotatedFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
    int **currentFigure = context->currentFigure;

    if (rotatedFigure) {
      clearCurrentFigureFromField();

      for (int i = 0; i < FIGURE_SIZE; i++) {
        for (int j = 0; j < FIGURE_SIZE; j++) {
          rotatedFigure[j][FIGURE_SIZE - i - 1] = currentFigure[i][j];
        }
      }

      context->currentFigure = rotatedFigure;

      if (collision()) {
        context->currentFigure = currentFigure;
        freeMatrix(rotatedFigure, FIGURE_SIZE);
      } else {
        freeMatrix(currentFigure, FIGURE_SIZE);
      }
    }
  }
}