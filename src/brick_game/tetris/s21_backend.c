#include "inc/s21_backend.h"

GameContext_t *getCurrentContext() {
  static GameContext_t gameContext;
  static bool initGame = false;
  if (!initGame) {
    initRandom();
    initializeGame(&gameContext, &initGame);
  }
  GameContext_t *get = &gameContext;
  return get;
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

int initHighScore() {
  FILE *fp = fopen("highScore.txt", "r");
  int highScore = 0;

  if (fp) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';

      char *endPtr;
      long score = strtol(buffer, &endPtr, 10);

      if (endPtr == buffer || *endPtr != '\0' || score <= 0) {
        highScore = 0;
      } else {
        highScore = (int)score;
      }
    }
    fclose(fp);
  }

  return highScore;
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
  context->exit = 0;
  context->lastTime = 0;

  *checkInit = true;
}

int **createMatrix(int rows, int column) {
  int **newMatrix = (int **)malloc(rows * sizeof(int *));
  if (newMatrix) {
    for (int i = 0; i < rows; i++) {
      newMatrix[i] = (int *)malloc(column * sizeof(int));
      if (newMatrix[i]) {
        for (int j = 0; j < column; j++) {
          newMatrix[i][j] = 0;
        }
      }
    }
    return newMatrix;
  }
}

void freeMatrix(int **matrix, int rows) {
  if (matrix) {
    for (int i = 0; i < rows; i++) {
      free(matrix[i]);
    }
    free(matrix);
  }
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
    context->exit = 0;
    context->lastTime = 0;
    context->currentState = GameState_Start;

    context->gameStateInfo.score = 0;
    context->gameStateInfo.high_score = 0;
    context->gameStateInfo.level = 0;
    context->gameStateInfo.speed = 0;
    context->gameStateInfo.pause = 0;
  }
}

int **createFigure(int figureNum) {
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

void dropNewFigure(int x, int y) {
  GameContext_t *context = getCurrentContext();

  freeMatrix(context->currentFigure, FIGURE_SIZE);
  context->currentFigure = context->gameStateInfo.next;

  context->gameStateInfo.next = createFigure(rand() % FIGURE_COUNT);

  context->figureX = x;
  context->figureY = y;
  context->oldFigureX = x;
  context->oldFigureY = y;
}

void addCurrentFigureToField() {
  GameContext_t *context = getCurrentContext();
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

void clearCurrentFigureFromField() {
  GameContext_t *context = getCurrentContext();
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

bool attachFigureToField() {
  GameContext_t *context = getCurrentContext();
  bool outOfField = false;
  if (context->currentFigure) {
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
    for (int x = 0; x < FIELD_WIDTH && !outOfField; x++) {
      if (field[0][x] != 0) {
        outOfField = true;
      }
    }
  }
  return outOfField;
}

bool ifSquare() {
  bool ifSquare = false;
  GameContext_t *context = getCurrentContext();

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] == 2) ifSquare = true;
    }
  }

  return ifSquare;
}

bool collision() {
  GameContext_t *context = getCurrentContext();
  int **currentFigure = context->currentFigure;

  bool collision = false;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (currentFigure[i][j] != 0) {
        int boardX = context->figureX + j;
        int boardY = context->figureY + i;

        if (boardY >= FIELD_HEIGHT) collision = true;

        if ((boardX < 0 || boardX >= FIELD_WIDTH)) collision = true;

        if (pixelInField(boardX, boardY) &&
            context->gameStateInfo.field[boardY][boardX] != 0) {
          int fieldValue = context->gameStateInfo.field[boardY][boardX];

          if (fieldValue != 0 && fieldValue != currentFigure[i][j]) {
            collision = true;
          }
        }
      }
    }
  }

  return collision;
}

bool pixelInField(int x, int y) {
  return (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT);
}

void processShift() {
  GameContext_t *context = getCurrentContext();
  if (context->userInput == Left) {
    moveFigureLeft();
  } else if (context->userInput == Right) {
    moveFigureRight();
  } else if (context->userInput == Down) {
    moveFigureDown();
  } else if (context->userInput == Action) {
    if (!ifSquare()) rotationFigure();
  }
  context->shiftRequested = false;
}

bool processAttaching() {
  bool attaching = moveFigureDown();
  if (!attaching) {
    moveFigureUp();
  }
  return attaching;
}

void countScore(int lines) {
  GameContext_t *context = getCurrentContext();
  int const scores[] = {0, 100, 300, 700, 1500};

  context->gameStateInfo.score += scores[lines];
  context->gameStateInfo.level = 1 + (context->gameStateInfo.score / 600);

  countSpeed();

  if (context->gameStateInfo.score >= context->gameStateInfo.high_score) {
    context->gameStateInfo.high_score = context->gameStateInfo.score;
    updateScore();
  }
}

void countSpeed() {
  GameContext_t *context = getCurrentContext();
  int delay = START_DELAY;
  int min_delay = MIN_DELAY;
  int max_lvl = MAX_LEVEL;

  if (context->gameStateInfo.level <= max_lvl)
    context->gameStateInfo.speed =
        delay - (context->gameStateInfo.level - 1) *
                    ((delay - min_delay) / (max_lvl - 1));
  else
    context->gameStateInfo.speed = min_delay;
}

void updateScore() {
  GameContext_t *context = getCurrentContext();
  FILE *fp = fopen("highScore.txt", "w");
  if (fp) {
    fprintf(fp, "%d", context->gameStateInfo.score);
    fclose(fp);
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

bool fullLine(int numLine) {
  GameContext_t *context = getCurrentContext();
  for (int i = 0; i < FIELD_WIDTH; i++) {
    if (context->gameStateInfo.field[numLine][i] == 0) {
      return false;
    }
  }
  return true;
}

void removeLine(int numLine) {
  GameContext_t *context = getCurrentContext();
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

void moveFigureRight() {
  GameContext_t *context = getCurrentContext();
  context->figureX++;
  if (collision()) context->figureX--;
}

void moveFigureLeft() {
  GameContext_t *context = getCurrentContext();
  context->figureX--;
  if (collision()) context->figureX++;
}

bool moveFigureDown() {
  bool attaching = false;
  GameContext_t *context = getCurrentContext();
  context->figureY++;
  if (collision()) {
    context->figureY--;
    attaching = true;
  }
  return attaching;
}

bool moveFigureUp() {
  GameContext_t *context = getCurrentContext();
  context->figureY--;
  if (collision()) {
    context->figureY++;
  }
}

void rotationFigure() {
  GameContext_t *context = getCurrentContext();
  int **shiftFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  int **currentFigure = context->currentFigure;

  clearCurrentFigureFromField();
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      shiftFigure[j][FIGURE_SIZE - i - 1] = currentFigure[i][j];
    }
  }

  context->currentFigure = shiftFigure;

  if (collision()) {
    context->currentFigure = currentFigure;
    freeMatrix(shiftFigure, FIGURE_SIZE);
  } else {
    context->currentFigure = shiftFigure;
    freeMatrix(currentFigure, FIGURE_SIZE);
  }
}