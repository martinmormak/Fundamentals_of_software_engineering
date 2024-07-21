#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

#include "ui.h"
#include "view.h"
#include "str_utils.h"

#define HOF_FILENAME "score.txt"

/* private functions */
void game_loop(Game *game);
void print_play_field(Game *game, int input_row, int input_column);
void print_score(Player *list_of_players, int number_of_all_players);
void print_input_rules();


/**
 * Ask a player for his name and store in the game.
 */
void read_player_name(Game *game) {
    assert(game != NULL);
    printf("Zadajte vaše meno prosím: \n");
    char name_of_player[MAX_PLAYER_LENGTH];
    fgets(name_of_player, MAX_PLAYER_LENGTH, stdin);
    str_remove_spaces(name_of_player);
    strcpy(game->player->name, name_of_player);
}


/**
 * Handle whole process of the Game
 */
void play_game(Game *game) {
    assert(game != NULL);

    Player list_of_players[PLAYERS_LIMIT];
    int size_of_list = read_scores(HOF_FILENAME, list_of_players);
    if (size_of_list > 0) {
        print_score(list_of_players, size_of_list);
    }
    game_loop(game);

    if (game->game_state == SOLVED) {
        printf("Gratulujem %s. Riešenie je správne!\n", game->player->name);
    } else {
        printf("Ľutujem %s. Riešenie je nesprávne!\n", game->player->name);
    }
    printf("Vaše skóre je: %d\n", game->player->score);

    bool is_player_added_to_list =
            add_player_to_list(list_of_players, &size_of_list, *game->player);

    if (is_player_added_to_list) {
        save_scores(HOF_FILENAME, list_of_players, size_of_list);
    }
}

/**
 * Function to return how many mines user did mark
 */
int count_of_marked_mines(Game *game)
{
    int count_of_marked=0;
    for(int i=0;i<game->board->mine_count;i++)
    {
        for(int x=0;x<game->board->row_count;x++)
        {
            if(game->board->tiles[i][x]->tile_state==MARKED)
            {
                count_of_marked++;
            }
        }
    }
    return count_of_marked;
}

/**
 * Handles players input process
 * Loops until game state is playing
 */
void game_loop(Game *game) {
    assert(game != NULL);
    int input, input_row = -1, input_column = -1;
    char input_data;
    
    do {
        print_play_field(game, input_row, input_column);

        print_input_rules();
        while (((input = scanf("%c %d %d", &input_data, &input_row, &input_column)) == 0)) {
            scanf("%*[^\n] %*[^\n] %*[^\n]");
            print_input_rules();
        }
        while ((getchar()) != '\n');

        if (input != EOF) {
            if(count_of_marked_mines(game)<game->board->mine_count||input_data=='o'||game->board->tiles[input_row-1][input_column-1]->tile_state == MARKED)
            {
                // if input is not empty or is not correct then open or mark tile and user marked less mines than is their count
                open_or_mark_tile(game, input_row - 1, input_column - 1, input_data);
            }
            else
            {
                printf("You marked all mines\n");
            }
        }

    } while (game->game_state == PLAYING);
    print_play_field(game, input_row, input_column);
}


void print_score(Player *list_of_players, int number_of_all_players) {
    char *text = view_hof(list_of_players, number_of_all_players);
    printf("%s", text);
    free(text);
}


void print_play_field(Game *game, int input_row, int input_column) {
    char *field = view_play_field(game->board, input_row, input_column);
    printf("\n%s\n", field);
    free(field);
}


void print_input_rules() {
    printf("Zadajte úlohu (o = open, m = mine), medzeru číslo riadka, medzeru a číslo stĺpca. Napr. m 2 3, o 5 9\n");
}


int run_again(){
    char input[20];    
    do{
        printf("Chcete hrať znova? (yes/no)\n");
        scanf("%s", input);
    }
    while(run_again_valid(input)==0); //while input isn't valid
    if(run_again_valid(input)==1)return 1; //if yes/ye/y, return 1
    else return 0; //if no/n, return 0
}
