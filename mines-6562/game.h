#ifndef MINES_GAME_H
#define MINES_GAME_H
#include "hof.h"
#include "board.h"

typedef enum  {
    FAILED,
    PLAYING,
    SOLVED,
} GameState;

typedef struct {
    Board *board;          /* Struct of the play field */
    Player *player;        /* Struct of user who is playing the Game */
    GameState game_state;  /* Enum for status of the Game */
} Game;

Game *create_game();
void close_all_marked_tiles(Game *game);
void open_or_mark_tile(Game *game, int input_row, int input_column, char input_data);
void destroy_game(Game *game);
int run_again_valid();
#endif //MINES_GAME_H