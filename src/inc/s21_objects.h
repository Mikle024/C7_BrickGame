#ifndef S21_OBJECT_H
#define S21_OBJECT_H

// Действия игрока
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

// Определение состояний игры
typedef enum {
  GameState_Start,     // Начало игры
  GameState_Spawn,     // Появление новой фигуры
  GameState_Moving,    // Перемещение фигуры
  GameState_Shifting,  // Изменение положения
  GameState_Attaching,  // Прикрепление фигуры к игровому полю
  GameState_GameOver  // Конец игры
} GameState;

// Информация об игре
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

// из GameState_Start только в GameState_Spawn
// из GameState_Spawn только в GameState_Moving
// из GameState_Moving в GameState_Attaching и в GameState_Shifting
// из GameState_Shifting в GameState_Moving  и в GameState_Attaching
// из GameState_Attaching в GameState_Spawn и GameState_GameOver
// из GameState_GameOver только в GameState_Start

// Игра
typedef struct {
  GameState currentState;    // Текущее состояние игры
  GameInfo_t gameStateInfo;  // Информация о текущей игре
  int **currentFigure;       // Текущая фигура
  int figureX, figureY;      // Координаты фигуры
  int oldFigureX, oldFigureY;  // Предыдущая позиция фигуры
  int ticksSinceLastMove;  // Количество тактов с последнего движения фигуры
  int collision;
  int gameOver;
} GameContext_t;

#endif