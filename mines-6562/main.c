#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "ui.h"
#include "board.h"


int main() {
    int row_count, column_count, mine_count = 0;
    Game *game = create_game();
    read_player_name(game);
    do{
        do{
            printf("Zadajte počet riadkov, stĺpcov a mín. Napr. 5 5 1, 8 9 3\n");
            scanf("%d %d %d", &row_count, &column_count, &mine_count);
            int vstup;
            //clearing buffer
            while((vstup = getchar()) != '\n' && vstup != EOF);
        //loading custom parameters in loop until they are correct
        }
        while(check_custom_parameters(row_count, column_count, mine_count) == 1);
        Board *board = create_board(row_count, column_count, mine_count);
        game->board = board;
        game->player->score=1;
        game->game_state=PLAYING;
        play_game(game);
    }
    while(run_again()==1); //repeat if player wants to play again
    destroy_game(game);
    exit(EXIT_SUCCESS);
}
