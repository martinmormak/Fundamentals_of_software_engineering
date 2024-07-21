#include "greatest.h"
#include "../board.h"
#include "../game.h"

TEST verify_with_wrong_action() {
    srand(time(NULL));
    Board *board = create_board(10, 10, 5);
    int row=rand()%10+0;
    int column=rand()%10+0;
    ASSERT_FALSE(is_input_data_correct(board, row, column,'a'));
    PASS();
}

TEST verify_with_correct_action() {
    Board *board = create_board(10, 10, 5);
    int row=rand()%10+0;
    int column=rand()%10+0;
    ASSERT(is_input_data_correct(board, row, column,'o'));
    row=rand()%10+0;
    column=rand()%10+0;
    ASSERT(is_input_data_correct(board, row, column,'m'));
    PASS();
}

TEST verify_with_high_coordinates() {
    Board *board = create_board(10, 10, 5);
    ASSERT_FALSE(is_input_data_correct(board, 6, 11,'o'));
    PASS();
}

TEST verify_with_low_coordinates() {
    Board *board = create_board(10, 10, 5);
    ASSERT_FALSE(is_input_data_correct(board, -1, 4,'o'));
    PASS();
}

TEST verify_with_correct_coordinates() {
    Board *board = create_board(10, 10, 5);
    ASSERT(is_input_data_correct(board, 0, 9,'o'));
    PASS();
}

TEST is_game_solved_at_the_start() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;

    bool is_solved = is_game_solved(game->board);
    ASSERT_FALSE(is_solved);
    destroy_game(game);
    PASS();
}

TEST is_game_solved_if_solved() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;

    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if (!game->board->tiles[row][column]->is_mine) {
                open_or_mark_tile(game, row, column,'o');
            }
        }
    }
    ASSERT(is_game_solved(game->board));
    destroy_game(game);
    PASS();
}

TEST open_mines_after_win() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;

    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if (!game->board->tiles[row][column]->is_mine) {
                open_or_mark_tile(game, row, column,'o');
            }
        }
    }
    open_all_mines(game->board);
    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if (game->board->tiles[row][column]->is_mine) {
                ASSERT_EQ(MARKED, game->board->tiles[row][column]->tile_state);
            }
        }
    }
    destroy_game(game);
    PASS();
}

TEST verify_invalid_input_of_custom_parameters(){
   ASSERT_EQ(1, check_custom_parameters(0, 10, 1)); 
   ASSERT_EQ(1, check_custom_parameters(1, 0, 10)); 
   ASSERT_EQ(1, check_custom_parameters(5, 5, 25)); 
   ASSERT_EQ(1, check_custom_parameters(10, 10, 110)); 
   ASSERT_EQ(1, check_custom_parameters(10, 5, 0)); 
   PASS();
}


TEST verify_valid_input_of_custom_parameters(){
   ASSERT_EQ(0, check_custom_parameters(10, 10, 1)); 
   ASSERT_EQ(0, check_custom_parameters(5, 3, 2)); 
   ASSERT_EQ(0, check_custom_parameters(8, 7, 3)); 
   ASSERT_EQ(0, check_custom_parameters(10, 10, 15)); 
   ASSERT_EQ(0, check_custom_parameters(6, 6, 5)); 
   PASS();
}

SUITE (test_board) {
    RUN_TEST(verify_with_wrong_action);
    RUN_TEST(verify_with_correct_action);
    RUN_TEST(verify_with_high_coordinates);
    RUN_TEST(verify_with_low_coordinates);
    RUN_TEST(verify_with_correct_coordinates);
    RUN_TEST(is_game_solved_at_the_start);
    RUN_TEST(is_game_solved_if_solved);
    RUN_TEST(open_mines_after_win);
    RUN_TEST(verify_invalid_input_of_custom_parameters);
    RUN_TEST(verify_valid_input_of_custom_parameters);
}
