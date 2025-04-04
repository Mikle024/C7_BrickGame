#ifndef S21_TYPES_H
#define S21_TYPES_H

/**
 * @brief Enumeration of user actions.
 */
typedef enum {
  Start,     /**< Start the game. */
  Pause,     /**< Pause the game. */
  Terminate, /**< Terminate the game. */
  Left,      /**< Move the figure to the left. */
  Right,     /**< Move the figure to the right. */
  Up,        /**< Not used in this game. */
  Down,      /**< Move the figure down. */
  Action,    /**< Perform an action. */
} UserAction_t;

/**
 * @brief Structure representing game information for the frontend.
 */
typedef struct {
  int **field;    /**< The game field. */
  int **next;     /**< The next figure. */
  int score;      /**< The current score. */
  int high_score; /**< The high score. */
  int level;      /**< The current level. */
  int speed;      /**< The current speed. */
  int pause;      /**< Indicates if the game is paused. */
} GameInfo_t;

typedef enum {
  GameState_Start,
  GameState_Spawn,
  GameState_Moving,
  GameState_Shifting,
  GameState_Attaching,
  GameState_GameOver
} GameState;

typedef struct {
  GameState currentState;
  GameInfo_t gameStateInfo;
  UserAction_t userInput;
  int **currentFigure;
  int figureX, figureY;
  int oldFigureX, oldFigureY;
  bool shiftRequested;
  long long lastTime;
} GameContext_t;

#endif