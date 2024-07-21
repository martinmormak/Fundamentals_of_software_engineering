#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "game.h"


/**
 * Change players score.
 * Adds value of opened tile to the score.
 * If game is solved/failed then multiples/divide the score by 2.
 */
void update_player_score(Game *game, int input_row, int input_column) {

    if (game->game_state == FAILED) {
        game->player->score /= 2;
    } else {
        game->player->score +=
                game->board->tiles[input_row][input_column]->value;
    }
    if (game->game_state == SOLVED) {
        game->player->score *= 2;
    }
}


/**
 * Open neighbour Tile if value of the clue is 0.
 * Checks main and mixed directions of the opened Tile.
 */
void open_neighbour_tiles(Game *game, int row, int column) {
    assert(game != NULL);
    // iterates every possible direction of opened Tile
    for (int d_row = -1; d_row <= 1; d_row++) {
        for (int d_column = -1; d_column <= 1; d_column++) {
            int a_row = row + d_row;
            int a_column = column + d_column;
            if (a_row >= 0 && a_row < game->board->row_count && a_column >= 0
                && a_column < game->board->column_count) {
                open_or_mark_tile(game, a_row, a_column,'o');
            }
        }
    }
}


/**
 * Create and allocate pointers of a Board, Player and Game.
 * Sets Game state to PLAYING.
 * @return pointer to the Game
 */
Game *create_game() {
    Game *game = (Game *) calloc(1, sizeof(Game));
    Player *player = (Player *) calloc(1, sizeof(Player));
    game->player = player;
    game->player->score = 1;
    game->game_state = PLAYING;
    return game;
}


/**
 * Close all marked Tile(s)
 */
void close_all_marked_tiles(Game *game)
{
    for(int i=0;i<game->board->row_count;i++)
    {
        for(int x=0;x<game->board->column_count;x++)
        {
            if(game->board->tiles[i][x]->tile_state==MARKED)
            {
                game->board->tiles[i][x]->tile_state=CLOSED;
            }
        }
    }
}

/**
 * Open or mark selected Tile(s) according to input coordinates.
 * Checks if input coordinates are in the correct range if Game state is playing.
 * Can change Game state to solved or failed.
 */
void open_or_mark_tile(Game *game, int input_row, int input_column, char input_data) {

    if (game->game_state != PLAYING
        || !is_input_data_correct(game->board, input_row, input_column,input_data)) {
        return;
    }

    if(input_data=='o')     //open selected tile
    {
        if (game->board->tiles[input_row][input_column]->tile_state == CLOSED||game->board->tiles[input_row][input_column]->tile_state == MARKED) {
            game->board->tiles[input_row][input_column]->tile_state = OPEN;

            if (game->board->tiles[input_row][input_column]->is_mine && game->player->score==0) {
            int x=0;
            int y=0;
            game->board->tiles[input_row][input_column]->is_mine = false;
            if (!game->board->tiles[x][y]->is_mine){
                game->board->tiles[x][y]->is_mine = true;
            }
            else {
                if (y>game->board->column_count){
                    y=0;
                    x=x+1;
                }
                while ((game->board->tiles[x][y]->is_mine)&& y<=game->board->column_count){
                    y=y+1;
                }
                if (!game->board->tiles[x][y]->is_mine){
                    game->board->tiles[x][y]->is_mine = true;
                }
            }

        }if (game->board->tiles[input_row][input_column]->is_mine) {
                game->game_state = FAILED;
                close_all_marked_tiles(game);
                open_all_mines(game->board);
            }

            if (!game->board->tiles[input_row][input_column]->is_mine
                && game->board->tiles[input_row][input_column]->value == 0) {
                open_neighbour_tiles(game, input_row, input_column);
            }
            if (is_game_solved(game->board)) {
                game->game_state = SOLVED;
            }
            update_player_score(game, input_row, input_column);
        }
    }
    else if(input_data=='m')    //mark selected tile
    {
        //if the field on the entered coordinates is marked, then the mark is canceled, othetwise if the field isn't marked, then mark field
        if (game->board->tiles[input_row][input_column]->tile_state == MARKED) {
            game->board->tiles[input_row][input_column]->tile_state = CLOSED;
        }
        else if (game->board->tiles[input_row][input_column]->tile_state == CLOSED) {
            game->board->tiles[input_row][input_column]->tile_state = MARKED;
        }
    }
}

/**
 * Free pointers of the Player and Game.
 */
void destroy_game(Game *game) {
    assert(game != NULL);
    destroy_board(game->board);
    free(game->player);
    free(game);
}

int run_again_valid(char input[4]){
    if(strcmp(input,"y")!=0&&strcmp(input,"ye")!=0&&strcmp(input,"yes")!=0&&strcmp(input,"n")!=0&&strcmp(input,"no")!=0)return 0;//if invalid, return 0
    if(strcmp(input,"y")==0||strcmp(input,"ye")==0||strcmp(input,"yes")==0)return 1; //if yes/ye/y, return 1
    else return 2; //else no/n, return 2
}
