#ifndef TETRIS_H
#define TETRIS_H

#include <stdlib.h>

typedef struct {
  int b;
} TetBlock;

typedef struct {
  int x;
  int y;
  int size;
  TetBlock *blocks;
} TetFigure;

typedef struct {
  int count;
  int size;
  TetBlock *blocks;
} TetFiguresT;

typedef struct {
  int width;
  int height;
  TetBlock *blocks;
} TetFiled;

enum { GAME_OVER = 0, PLAYING };

enum {
  TET_PLAYER_NOP = 0,
  TET_PLAYER_UP,
  TET_PLAYER_DOWN,
  TET_PLAYER_LEFT,
  TET_PLAYER_RIGHT
};

typedef struct {
  int action;
} TetPlayer;

typedef struct {
  TetFiled *field;
  TetFigure *figure;
  TetFiguresT *figuresT;
  TetPlayer *player;
  int ticks;
  int ticksLeft;
  int playing;
  int score;
} TetGame;

TetFiguresT *createTetFiguresT(int count, int figuresSize,
                               TetBlock *figuresTemplate);
void freeTetFiguresT(TetFiguresT *tetFiguresT);
TetFiled *createTetField(int width, int height);
void freeTetField(TetFiled *tetField);
TetGame *createTetGame(int fieldWidth, int fieldHeight, int figureSize,
                       int count, TetBlock *figuresTemplate);
void freeTetGame(TetGame *context);

int lineFilledTet(int i, TetFiled *field);
void dropLineTet(int i, TetFiled *field);
int eraseLinesTet(TetGame *context);
void dropNewFigure(TetGame *context);
void plantFigure(TetGame *context);
int collisionTet(TetGame *context);
void calculateTet(TetGame *context);

void moveFigureDown(TetGame *context);
void moveFigureUp(TetGame *context);
void moveFigureRight(TetGame *context);
void moveFigureLeft(TetGame *context);

#endif