#include "hof.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

bool isValueInArray(const int array[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) return true;
    }
    return false;
}

bool isFirstBeforeSecondInAlphabet(const char *first, const char *second) {
    if (first == NULL || second == NULL) return false;
    return strcmp(first, second) < 0;
}

int getIndexWhereToInsertPlayer(Player list[], int size, Player newPlayer, enum Sort sort, bool sortWithAlphabet) {
    int count = 0;

    while (count < size) {
        if (sort == Descending
            ? list[count].score <= newPlayer.score
            : list[count].score >= newPlayer.score) {
            // if two have same score and want sorting with alphabet, sort them according to alphabet
            if (sortWithAlphabet && list[count].score == newPlayer.score) {
                int isBefore = isFirstBeforeSecondInAlphabet(list[count].name, newPlayer.name);
                // if element in list is before in alphabet
                return count + (sort == Descending ? isBefore : -isBefore);
            }
            return count;
        }
        count++;
    }

    return count;
}

Player *sortListOfPlayers(const Player list[], int size, enum Sort sortType) {
    if (size == 0) return NULL;

    Player *sorted = (Player*) calloc(size + 1, sizeof(Player));
    int alreadyUsedIndexes[size];

    for (int i = 0; i < size; i++) {

        // find current index of minimal player
        int indexOfMinimalPlayer;
        bool isFirstLoop = true;
        for (int j = 0; j < size; j++) {
            // skip already found indexes
            if (isValueInArray(alreadyUsedIndexes, i, j)) continue;

            if (isFirstLoop) {
                indexOfMinimalPlayer = j;
                isFirstLoop = false;
                continue;
            }

            Player current = list[j];
            Player minimal = list[indexOfMinimalPlayer];

            if (current.score < minimal.score) indexOfMinimalPlayer = j;
        }

        // add minimal player to sorted list and his index to already used indexes
        sorted[sortType == Ascending ? i : size - 1 - i] = list[indexOfMinimalPlayer];
        alreadyUsedIndexes[i] = indexOfMinimalPlayer;
    }

    return sorted;
}

/**
 * Load hall of fame from the file
 * @return the number of loaded entries or 0, if there was error in loading
 */
int read_scores(char *filename, Player *list_of_players) {
    assert(filename != NULL);
    assert(list_of_players != NULL);
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return 0;
    }
    int index_of_player = 0;
    while (fscanf(file, "%s %d", list_of_players[index_of_player].name,
                  &list_of_players[index_of_player].score) != EOF
           && index_of_player < PLAYERS_LIMIT) {

        index_of_player++;
    }

    fclose(file);

    Player *sorted = sortListOfPlayers(list_of_players, index_of_player, Descending);
    // copy sorted into list of players
    for (int i = 0; i < index_of_player; i++) {
        list_of_players[i] = sorted[i];
    }
    free(sorted);

    return index_of_player;
}


/**
 * Save the hall of fame array to the file
 */
void save_scores(char *filename, Player *list_of_players, const int size) {
    assert(filename != NULL);
    assert(list_of_players != NULL);

    if (size == 0) return;
    // first sort the players
    Player *sorted = sortListOfPlayers(list_of_players, size, Descending);

    FILE *file = fopen(filename, "w");

    if (file == NULL) { return; }
    for (int i = 0; i < size; i++) {
        if (i < PLAYERS_LIMIT) {
            fprintf(file, "%s %d\n", sorted[i].name, sorted[i].score);
        }
    }
    fclose(file);
    free(sorted);
}


/**
 * Add Player to the hall of fame array
 * @return true, if Player (entry) was added to the list, false otherwise
 */
bool add_player_to_list(Player list_of_players[], int *size_of_list, const Player player) {
    assert(list_of_players != NULL && size_of_list != NULL);

    // invalid list size
    if (*size_of_list > PLAYERS_LIMIT) return false;

    // when the list is full and player did not get the smaller score, not adding
    if (*size_of_list != 0 && *size_of_list == PLAYERS_LIMIT && list_of_players[*size_of_list - 1].score > player.score) return false;

    // find out the index where the new player will be inserted in list
    const int index = getIndexWhereToInsertPlayer(list_of_players, *size_of_list, player, Descending, false);

    // if list is full and we are adding new player
    if (*size_of_list == PLAYERS_LIMIT) {
        // will need to delete the last one to insert new
        for (int i = *size_of_list - 1; i > index; i--) {
            list_of_players[i] = list_of_players[i - 1];
        }
        list_of_players[index] = player;
    }
    // if list is not full yet
    else {
        // just insert and push the others
        for (int i = *size_of_list; i > index; i--) {
            list_of_players[i] = list_of_players[i - 1];
        }
        list_of_players[index] = player;
        // size increases
        *size_of_list += 1;
    }

    return true;
}
