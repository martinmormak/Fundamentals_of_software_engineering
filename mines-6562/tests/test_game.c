#include "greatest.h"
#include "../board.h"
#include "../game.h"

TEST open_mine() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if(game->board->tiles[row][column]->is_mine){
                open_or_mark_tile(game, row, column,'o');
            }
        }
    }
    ASSERT_EQ(FAILED, game->game_state);
    destroy_game(game);
    PASS();
}

TEST open_tile_with_bad_coordinates() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    open_or_mark_tile(game, -1, -1,'o');
    open_or_mark_tile(game, game->board->row_count, game->board->column_count,'o');

    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
                    ASSERT_EQ(CLOSED, game->board->tiles[row][column]->tile_state);
        }
    }
    destroy_game(game);
    PASS();
}

TEST first_turn() {
    Game *game = create_game();
    Board *board = create_board(3, 3, 4);
    game->board = board;
    game->board->tiles[1][0]->is_mine = false;
    game->board->tiles[1][1]->is_mine = false;
    game->board->tiles[1][2]->is_mine = false;
    game->board->tiles[2][0]->is_mine = false;
    game->board->tiles[2][1]->is_mine = false;
    game->board->tiles[0][0]->is_mine = true;
    game->board->tiles[0][1]->is_mine = true;
    game->board->tiles[0][2]->is_mine = true;
    game->board->tiles[2][2]->is_mine = true;
    open_or_mark_tile(game, 2, 2, 'o');
    open_or_mark_tile(game, game->board->row_count, game->board->column_count, 'o');
    ASSERT_EQ(1, game->board->tiles[2][2]->is_mine);
        
    
    
    destroy_game(game);
    PASS();
}

TEST first_turn2() {
    Game *game = create_game();
    Board *board = create_board(3, 3, 4);
    game->board = board;
    game->board->tiles[1][0]->is_mine = true;
    game->board->tiles[1][1]->is_mine = true;
    game->board->tiles[1][2]->is_mine = true;
    game->board->tiles[2][0]->is_mine = true;
    game->board->tiles[2][1]->is_mine = true;
    game->board->tiles[0][0]->is_mine = false;
    game->board->tiles[0][1]->is_mine = false;
    game->board->tiles[0][2]->is_mine = false;
    game->board->tiles[2][2]->is_mine = false;
    open_or_mark_tile(game, 2, 1, 'o');
    open_or_mark_tile(game, game->board->row_count, game->board->column_count, 'o');
    ASSERT_EQ(1, game->board->tiles[2][1]->is_mine);
        
    
    
    destroy_game(game);
    PASS();
}

TEST count_score_after_move() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 70);
    game->board = board;
    bool is_closed_tile_open = false;
    int score = 1;
    while (!is_closed_tile_open) {
        int row = rand() % game->board->row_count;
        int column = rand() % game->board->column_count;
        if (!game->board->tiles[row][column]->is_mine) {
            open_or_mark_tile(game, row, column,'o');
            score += game->board->tiles[row][column]->value;
            ASSERT_EQ(score, game->player->score);
            is_closed_tile_open = true;
        }
    }

    destroy_game(game);
    PASS();
}

TEST count_score_when_game_failed() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 30);
    game->board = board;
    game->player->score = 30;
    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if (game->board->tiles[row][column]->is_mine) {
                open_or_mark_tile(game, row, column,'o');
                ASSERT_EQ(15, game->player->score);
                break;
            }
        }
    }

    destroy_game(game);
    PASS();
}

TEST test_valid_input_run_again_valid(){
    ASSERT_EQ(1, run_again_valid("yes"));
    ASSERT_EQ(1, run_again_valid("ye"));
    ASSERT_EQ(1, run_again_valid("y"));
    ASSERT_EQ(2, run_again_valid("n"));
    ASSERT_EQ(2, run_again_valid("no"));
    PASS();
}

TEST test_invalid_input_run_again_valid(){
    ASSERT_EQ(0, run_again_valid("hello"));
    ASSERT_EQ(0, run_again_valid(""));
    ASSERT_EQ(0, run_again_valid("tuke"));
    ASSERT_EQ(0, run_again_valid("nie"));
    ASSERT_EQ(0, run_again_valid("ano"));
    ASSERT_EQ(0, run_again_valid("yesano"));
    PASS();
}

TEST mark_mine_once_then_return_MARKED() {
    srand(time(NULL));
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    int row=rand()%10+0;
    int column=rand()%10+0;
    open_or_mark_tile(game, row, column,'m');
    ASSERT_EQ(MARKED, board->tiles[row][column]->tile_state);
    destroy_game(game);
    PASS();
}

TEST mark_mine_twice_then_return_CLOSED() {
    srand(time(NULL));
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    int row=rand()%10+0;
    int column=rand()%10+0;
    open_or_mark_tile(game, row, column,'m');
    open_or_mark_tile(game, row, column,'m');
    ASSERT_EQ(CLOSED, board->tiles[row][column]->tile_state);
    destroy_game(game);
    PASS();
}

TEST open_mine_then_return_OPENED() {
    srand(time(NULL));
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    int row=rand()%10+0;
    int column=rand()%10+0;
    open_or_mark_tile(game, row, column,'o');
    ASSERT_EQ(OPEN, board->tiles[row][column]->tile_state);
    destroy_game(game);
    PASS();
}

TEST close_all_MARKED_tiles_then_return_CLOSED()
{
    srand(time(NULL));
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    int row=rand()%10+0;
    int column=rand()%10+0;
    open_or_mark_tile(game, row, column,'m');
    close_all_marked_tiles(game);
    ASSERT_EQ(CLOSED, board->tiles[row][column]->tile_state);
    destroy_game(game);
    PASS();
}

SUITE (test_game) {
    RUN_TEST(open_mine);
    RUN_TEST(open_tile_with_bad_coordinates);
    RUN_TEST(first_turn);
    RUN_TEST(first_turn2);
    RUN_TEST(count_score_after_move);
    RUN_TEST(count_score_when_game_failed);
    RUN_TEST(test_valid_input_run_again_valid);
    RUN_TEST(test_invalid_input_run_again_valid);
    RUN_TEST(mark_mine_once_then_return_MARKED);
    RUN_TEST(mark_mine_twice_then_return_CLOSED);
    RUN_TEST(open_mine_then_return_OPENED);
    RUN_TEST(close_all_MARKED_tiles_then_return_CLOSED);
}
