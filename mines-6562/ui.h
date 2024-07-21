#ifndef MINES_UI_H
#define MINES_UI_H

#include "game.h"

void read_player_name(Game *game);
int count_of_marked_mines(Game *game);
void play_game(Game *game);
int run_again();
#endif //MINES_UI_H