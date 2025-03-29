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

/**
 * @brief Добавляет текущую фигуру на игровое поле.
 */
void addCurrentFigureToField() {
  GameContext_t *context = getCurrentContext();
  if (!context || !context->currentFigure || !context->gameStateInfo.field) {
    return;
  }
  
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] != 0) {
        int fieldX = context->figureX + j;
        int fieldY = context->figureY + i;

        if (pixelInField(fieldX, fieldY)) {
          context->gameStateInfo.field[fieldY][fieldX] = context->currentFigure[i][j];
        }
      }
    }
  }
}

/**
 * @brief Очищает текущую фигуру с игрового поля (в старой позиции).
 */
void clearCurrentFigureFromField() {
  GameContext_t *context = getCurrentContext();
  if (!context || !context->currentFigure || !context->gameStateInfo.field) {
    return;
  }
  
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      int fieldX = context->oldFigureX + j;
      int fieldY = context->oldFigureY + i;

      if (pixelInField(fieldX, fieldY)) {
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

bool isSquareFigure() {
  GameContext_t *context = getCurrentContext();
  
  if (!context || !context->currentFigure) {
    return false;
  }

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] == 2) {
        return true;  // Если найден хотя бы один элемент со значением 2, это квадратная фигура
      }
    }
  }

  return false;
}

/**
 * @brief Проверяет наличие коллизий для текущей фигуры.
 *
 * @return true Если есть коллизия.
 * @return false Если нет коллизии.
 */
bool collision() {
  GameContext_t *context = getCurrentContext();
  if (!context || !context->currentFigure || !context->gameStateInfo.field) {
    return true;  // Если данные недоступны, считаем что коллизия произошла
  }
  
  int **currentFigure = context->currentFigure;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (currentFigure[i][j] != 0) {
        int boardX = context->figureX + j;
        int boardY = context->figureY + i;

        // Коллизия с нижней, левой или правой границей
        if (boardY >= FIELD_HEIGHT || boardX < 0 || boardX >= FIELD_WIDTH) {
          return true;
        }

        // Коллизия с другими блоками на поле (только если точка находится на поле)
        if (pixelInField(boardX, boardY) && 
            context->gameStateInfo.field[boardY][boardX] != 0 &&
            context->gameStateInfo.field[boardY][boardX] != currentFigure[i][j]) {
          return true;
        }
      }
    }
  }

  return false;
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
    if (!isSquareFigure()) rotationFigure();
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

/**
 * @brief Подсчитывает очки на основе удаленных линий и обновляет уровень и скорость игры.
 *
 * @param lines Количество удаленных линий.
 */
void countScore(int lines) {
  GameContext_t *context = getCurrentContext();
  if (!context) {
    return;
  }
  
  // Таблица очков в зависимости от количества удаленных линий
  static const int scores[] = {0, 100, 300, 700, 1500};
  
  // Безопасная проверка индекса
  int scoreIndex = (lines >= 0 && lines <= 4) ? lines : 0;

  context->gameStateInfo.score += scores[scoreIndex];
  context->gameStateInfo.level = 1 + (context->gameStateInfo.score / 600);

  // Обновляем скорость в зависимости от уровня
  countSpeed();

  // Проверяем, не побили ли рекорд
  if (context->gameStateInfo.score > context->gameStateInfo.high_score) {
    context->gameStateInfo.high_score = context->gameStateInfo.score;
    updateScore(context->gameStateInfo.score);
  }
}

/**
 * @brief Вычисляет скорость падения фигур в зависимости от уровня.
 */
void countSpeed() {
  GameContext_t *context = getCurrentContext();
  if (!context) {
    return;
  }
  
  int delay = START_DELAY;
  int min_delay = MIN_DELAY;
  int max_level = MAX_LEVEL;

  // Ограничиваем уровень
  int level = context->gameStateInfo.level;
  if (level > max_level) {
    level = max_level;
  }

  // Линейно уменьшаем задержку с увеличением уровня
  if (level <= max_level) {
    context->gameStateInfo.speed = delay - (level - 1) * ((delay - min_delay) / (max_level - 1));
  } else {
    context->gameStateInfo.speed = min_delay;
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
  
  if (!context) {
    return true;  // Если данные недоступны, считаем что прикрепление должно произойти
  }
  
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

/**
 * @brief Вращает текущую фигуру (кроме квадрата).
 */
void rotationFigure() {
  GameContext_t *context = getCurrentContext();
  if (!context || !context->currentFigure) {
    return;
  }
  
  // Создаем временную матрицу для повернутой фигуры
  int **rotatedFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  if (!rotatedFigure) {
    return; // Не удалось выделить память
  }
  
  int **currentFigure = context->currentFigure;

  // Очищаем текущую фигуру с поля перед вращением
  clearCurrentFigureFromField();
  
  // Вращаем фигуру на 90 градусов (по часовой стрелке)
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      rotatedFigure[j][FIGURE_SIZE - i - 1] = currentFigure[i][j];
    }
  }

  // Временно заменяем фигуру на повернутую для проверки коллизий
  context->currentFigure = rotatedFigure;

  // Проверяем, возможно ли такое вращение
  if (collision()) {
    // Вращение невозможно, возвращаем старую фигуру
    context->currentFigure = currentFigure;
    freeMatrix(rotatedFigure, FIGURE_SIZE);
  } else {
    // Вращение возможно, используем новую фигуру
    freeMatrix(currentFigure, FIGURE_SIZE);
  }
}