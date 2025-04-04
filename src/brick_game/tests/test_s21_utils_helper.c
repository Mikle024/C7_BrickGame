#include "s21_tests.h"

static GameContext_t *originalContext = NULL;

void setupTest(void) {
  GameContext_t *context = getCurrentContext();
  originalContext = context;

  if (context->currentFigure) {
    freeMatrix(context->currentFigure, FIGURE_SIZE);
    context->currentFigure = NULL;
  }

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
    context->gameStateInfo.field = NULL;
  }

  if (context->gameStateInfo.next) {
    freeMatrix(context->gameStateInfo.next, FIGURE_SIZE);
    context->gameStateInfo.next = NULL;
  }

  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  context->gameStateInfo.next = createFigure(0);
  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);

  context->figureX = START_COORD_F_X;
  context->figureY = START_COORD_F_Y;
  context->oldFigureX = START_COORD_F_X;
  context->oldFigureY = START_COORD_F_Y;
  context->lastTime = 0;
  context->currentState = GameState_Start;

  context->gameStateInfo.score = 0;
  context->gameStateInfo.high_score = 0;
  context->gameStateInfo.level = START_LEVEL;
  context->gameStateInfo.speed = START_DELAY;
  context->gameStateInfo.pause = 1;
}

void cleanupTest(void) {
  if (originalContext) {
    if (originalContext->currentFigure) {
      freeMatrix(originalContext->currentFigure, FIGURE_SIZE);
      originalContext->currentFigure = NULL;
    }

    if (originalContext->gameStateInfo.field) {
      freeMatrix(originalContext->gameStateInfo.field, FIELD_HEIGHT);
      originalContext->gameStateInfo.field = NULL;
    }

    if (originalContext->gameStateInfo.next) {
      freeMatrix(originalContext->gameStateInfo.next, FIGURE_SIZE);
      originalContext->gameStateInfo.next = NULL;
    }

    originalContext->figureX = 0;
    originalContext->figureY = 0;
    originalContext->oldFigureX = 0;
    originalContext->oldFigureY = 0;
    originalContext->lastTime = 0;
    originalContext->currentState = GameState_Start;

    originalContext->gameStateInfo.score = 0;
    originalContext->gameStateInfo.high_score = 0;
    originalContext->gameStateInfo.level = 0;
    originalContext->gameStateInfo.speed = 0;
    originalContext->gameStateInfo.pause = 0;

    originalContext = NULL;
  }
}

void cleanupAfterTest(void) {
  GameContext_t *context = getCurrentContext();

  if (context) {
    if (context->currentFigure) {
      freeMatrix(context->currentFigure, FIGURE_SIZE);
      context->currentFigure = NULL;
    }

    if (context->gameStateInfo.field) {
      freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
      context->gameStateInfo.field = NULL;
    }

    if (context->gameStateInfo.next) {
      freeMatrix(context->gameStateInfo.next, FIGURE_SIZE);
      context->gameStateInfo.next = NULL;
    }

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

    context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
    context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    context->gameStateInfo.next = createFigure(0);

    freeMatrix(context->currentFigure, FIGURE_SIZE);
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
    freeMatrix(context->gameStateInfo.next, FIGURE_SIZE);

    context->currentFigure = NULL;
    context->gameStateInfo.field = NULL;
    context->gameStateInfo.next = NULL;
  }

  originalContext = NULL;
}

int **createTestField(int pattern[FIELD_HEIGHT][FIELD_WIDTH]) {
  int **field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  if (field) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
      for (int j = 0; j < FIELD_WIDTH; j++) {
        field[i][j] = pattern[i][j];
      }
    }
  }
  return field;
}

int **createTestFigure(int pattern[FIGURE_SIZE][FIGURE_SIZE]) {
  int **figure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  if (figure) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        figure[i][j] = pattern[i][j];
      }
    }
  }
  return figure;
}

void setupGameWithCustomValues(int fieldPattern[FIELD_HEIGHT][FIELD_WIDTH],
                               int figurePattern[FIGURE_SIZE][FIGURE_SIZE],
                               int posX, int posY) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->currentFigure) {
    freeMatrix(context->currentFigure, FIGURE_SIZE);
    context->currentFigure = NULL;
  }

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
    context->gameStateInfo.field = NULL;
  }

  if (fieldPattern) {
    context->gameStateInfo.field = createTestField(fieldPattern);
  } else {
    context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  }

  if (figurePattern) {
    context->currentFigure = createTestFigure(figurePattern);
  } else {
    context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  }

  context->figureX = posX;
  context->figureY = posY;
  context->oldFigureX = posX;
  context->oldFigureY = posY;
}

int collisionWithContext(GameContext_t *context) {
  int result = 0;
  if (!context || !context->currentFigure || !context->gameStateInfo.field) {
    result = 1;
  } else {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        if (context->currentFigure[i][j] != 0) {
          int fieldX = context->figureX + j;
          int fieldY = context->figureY + i;

          if (!pixelInField(fieldX, fieldY)) {
            result = 1;
          }

          if (fieldY >= 0 &&
              context->gameStateInfo.field[fieldY][fieldX] != 0 &&
              context->gameStateInfo.field[fieldY][fieldX] !=
                  context->currentFigure[i][j]) {
            result = 1;
          }
        }
      }
    }
  }
  return result;
}