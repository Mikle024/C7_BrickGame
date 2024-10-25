#include "tetris.h"

TetFiguresT *createTetFiguresT(int count, int figuresSize,
                               TetBlock *figuresTemplate) {
  TetFiguresT *tetFiguresT = (TetFiguresT *)malloc(sizeof(TetFiguresT));
  tetFiguresT->count = count;
  tetFiguresT->size = figuresSize;
  tetFiguresT->blocks = figuresTemplate;

  return tetFiguresT;
}

void freeTetFiguresT(TetFiguresT *tetFiguresT) {
  if (tetFiguresT) free(tetFiguresT);
}

TetFiled *createTetField(int width, int height) {
  TetFiled *tetField = (TetFiled *)malloc(sizeof(TetFiled));
  tetField->width = width;
  tetField->height = height;
  tetField->blocks = (TetBlock *)malloc(sizeof(TetBlock) * width * height);
  for (int i = 0; i < width * height; i++) {
    tetField->blocks[i].b = 0;
  }

  return tetField;
}

void freeTetField(TetFiled *tetField) {
  if (tetField) {
    if (tetField->blocks) free(tetField->blocks);
    free(tetField);
  }
}

TetGame *createTetGame(int fieldWidth, int fieldHeight, int figureSize,
                       int count, TetBlock *figuresTemplate) {
  TetGame *context = (TetGame *)malloc(sizeof(TetGame));
  context->field = createTetField(fieldWidth, fieldHeight);
  context->figuresT = createTetFiguresT(count, figureSize, figuresTemplate);

  return context;
}

void freeTetGame(TetGame *context) {
  if (context) {
    freeTetField(context->field);
    freeTetFiguresT(context->figuresT);
    free(context);
  }
}

void moveFigureDown(TetGame *context) { context->figure->y--; }

void moveFigureUp(TetGame *context) { context->figure->y--; }

void moveFigureLeft(TetGame *context) { context->figure->x--; }

void moveFigureRight(TetGame *context) { context->figure->x++; }

void plantFigure(TetGame *context) {
  TetFigure *currentFigure = context->figure;
  for (int i = 0; i < currentFigure->size; i++) {
    for (int j = 0; j < currentFigure->size; j++) {
      if (currentFigure->blocks[i * currentFigure->size + j].b != 0) {
        int fx = currentFigure->x + j;
        int fy = currentFigure->y + i;
        context->field->blocks[fy * context->field->width + fx].b =
            currentFigure->blocks[i * currentFigure->size + j].b;
      }
    }
  }
}

int collisionTet(TetGame *context) {
  int collision = 0;
  TetFigure *currentFigure = context->figure;
  TetFiled *field = context->field;
  for (int i = 0; i < currentFigure->size; i++) {
    for (int j = 0; j < currentFigure->size; j++) {
      if (currentFigure->blocks[i * currentFigure->size + j].b != 0) {
        int fx = currentFigure->x + j;
        int fy = currentFigure->y + i;
        if (currentFigure->blocks[fy * field->width + fx].b != 0) collision = 1;
        if (fx < 0 || fx >= field->width || fy < 0 || fy >= field->height)
          collision = 1;
      }
    }
  }
  return collision;
}

int lineFilledTet(int i, TetFiled *field) {
  int emptyBlock = 1;
  for (int j = 0; j < field->width; j++) {
    if (field->blocks[i * field->width + j].b == 0) emptyBlock = 0;
  }
  return emptyBlock;
}

void dropLineTet(int i, TetFiled *field) {
  if (i == 0) {
    for (int j = 0; j < field->width; j++) field->blocks[j].b = 0;
  } else {
    for (int k = i; k > 0; k--)
      for (int j = 0; j < field->width; j++)
        field->blocks[k * field->width + j].b =
            field->blocks[(k - 1) * field->width + j].b;
  }
}

int eraseLinesTet(TetGame *context) {
  int countLines = 0;
  TetFiled *field = context->field;
  for (int i = field->height; i >= 0; i--) {
    while (lineFilledTet(i, field)) {
      dropLineTet(i, field);
      countLines++;
    }
  }
  return countLines;
}

void dropNewFigure(TetGame *context) {}

void calculateTet(TetGame *context) {
  if (context->ticksLeft <= 0) {
    context->ticksLeft = context->ticks;
    moveFigureDown(context);
    if (collisionTet(context)) {
      moveFigureUp(context);
      plantFigure(context);
      context->score += eraseLinesTet(context);
      dropNewFigure(context);
      if (collisionTet(context)) {
        context->playing = GAME_OVER;
        return;
      }
    }
  }

  switch (context->player->action) {
    case TET_PLAYER_RIGHT:
      moveFigureRight(context);
      if (collisionTet(context)) moveFigureLeft(context);
      break;
    case TET_PLAYER_LEFT:
      moveFigureLeft(context);
      if (collisionTet(context)) moveFigureRight(context);
      break;
    case TET_PLAYER_DOWN:
      moveFigureDown(context);
      if (collisionTet(context)) moveFigureUp(context);
      break;
    case TET_PLAYER_UP:
      TetFigure *shiftFigure = rotFigure(context);
      TetFigure *tmp = context->figure;
      context->figure = shiftFigure;
      if (collisionTet(context)) {
        context->figure = tmp;
        freeTetFigure(shiftFigure);
      } else {
        freeTetFigure(tmp);
      }
      break;
    case TET_PLAYER_NOP:
    default:
      break;
  }
  context->ticksLeft--;
}