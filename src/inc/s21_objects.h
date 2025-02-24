#ifndef S21_OBJECT_H
#define S21_OBJECT_H

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

typedef enum {
  GameState_Start,
  GameState_Spawn,
  GameState_Moving,
  GameState_Shifting,
  GameState_Attaching,
  GameState_GameOver
} GameState;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  GameState currentState;
  GameInfo_t gameStateInfo;
  UserAction_t userInput;
  bool holdAction;
  int **currentFigure;
  int figureX, figureY;
  int oldFigureX, oldFigureY;
  int gameOver;
  bool shiftRequested;
  long long lastTime;
} GameContext_t;

#endif