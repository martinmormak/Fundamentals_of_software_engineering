#include "greatest.h"
#include "../hof.h"

TEST load_file_number_of_players() {
    char hof_file[] = "tests/score/optimal_size";
    Player list_of_players[PLAYERS_LIMIT];

    ASSERT_EQ(5, read_scores(hof_file, list_of_players));
    PASS();
}

TEST load_file_over_limit() {
    char hof_file[] = "tests/score/over_size";
    int high_size_of_list = PLAYERS_LIMIT + 5;
    Player list_of_players[high_size_of_list];

    ASSERT_EQ(PLAYERS_LIMIT, read_scores(hof_file, list_of_players));
    PASS();
}

TEST load_nonexistent_file() {
    char hof_file[] = "tests/score/nonexistent";
    Player list_of_players[PLAYERS_LIMIT];
    ASSERT_EQ(0, read_scores(hof_file, list_of_players));
    PASS();
}

TEST compare_loaded_and_saved_players() {
    Player list_of_players[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
    };
    int size_of_input_list = 3;
    char hof_file[] = "tests/score/for_saving";

    save_scores(hof_file, list_of_players, size_of_input_list);
    Player test_list_of_players[size_of_input_list];
    int size_of_test_list = read_scores(hof_file, test_list_of_players);

    ASSERT_EQ(size_of_input_list, size_of_test_list);
    for (int i = 0; i < size_of_test_list; i++) {
        ASSERT_EQ(list_of_players[i].score, test_list_of_players[i].score);
        ASSERT_STR_EQ(list_of_players[i].name, test_list_of_players[i].name);
    }
    remove(hof_file);
    PASS();
}

TEST save_player_over_limit() {
    Player list_of_players[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };
    int size = PLAYERS_LIMIT + 1;
    char hof_file[] = "tests/score/for_saving";
    Player *player = (Player *) calloc(1, sizeof(Player));
    strcpy(player->name, "lucia");
    player->score = 26;

    ASSERT_FALSE(add_player_to_list(list_of_players, &size, *player));
    free(player);
    remove(hof_file);
    PASS();
}

TEST add_player_to_optimal_list() {
    Player list_of_players[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"alex",  18},
            {"lubo",  2}
    };
    int size = 3;
    Player *player = (Player *) calloc(1, sizeof(Player));
    strcpy(player->name, "lucia");
    player->score = 26;

    int size_before_adding = size;
    add_player_to_list(list_of_players, &size, *player);
    ASSERT_EQ(size_before_adding + 1, size);
    free(player);
    PASS();
}

/**
 * Having a list of player, we add new player to it
 * Need to check if the position of new added player is right
 *
 * @return
 */
TEST add_player_to_optimal_list_check_order() {
    Player original_list_of_players[3] = {
            {"peter", 99},
            {"alex",  18},
            {"lubo",  2}
    };


    Player list_of_players[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"alex",  18},
            {"lubo",  2}
    };
    int size = 3;

    // create new player
    Player *player = (Player *) calloc(1, sizeof(Player));
    strcpy(player->name, "lucia");
    player->score = 26;

    // add him to the list
    add_player_to_list(list_of_players, &size, *player);
    // this player should be at index 1
    const int newPlayerIndex = 1;

    // test order
    int originalIndexCount = 0;
    for (int newIndexCount = 0; newIndexCount < size; newIndexCount++) {
        Player originalPlayer = original_list_of_players[originalIndexCount];
        Player newListPlayer = list_of_players[newIndexCount];

        // if we get to index where new player was inserted
        if (newPlayerIndex == newIndexCount) {
            // compare new player at index with inserted player
            ASSERT_EQ(newListPlayer.score, player->score);
            ASSERT_STR_EQ(newListPlayer.name, player->name);
            continue;
        }

        // compare original player with new player
        ASSERT_EQ(originalPlayer.score, newListPlayer.score);
        ASSERT_STR_EQ(originalPlayer.name, newListPlayer.name);
        originalIndexCount++;
    }

    free(player);
    PASS();
}

/**
 * Having a list full of players, add new player to it and check order
 *
 * @return
 */
TEST add_player_over_limit_check_order() {
    Player originalListOfPlayers[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };

    int size = PLAYERS_LIMIT;
    Player newListOfPlayers[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };

    // prepare new player to insert
    Player *player = (Player *) calloc(1, sizeof(Player));
    strcpy(player->name, "lucia");
    player->score = 26;

    // add him to the list
    add_player_to_list(newListOfPlayers, &size, *player);
    const int newPlayerIndex = 4;

    // check the order
    // test order
    int originalIndexCount = 0;
    for (int newIndexCount = 0; newIndexCount < size; newIndexCount++) {
        Player originalPlayer = originalListOfPlayers[originalIndexCount];
        Player newListPlayer = newListOfPlayers[newIndexCount];

        if (newPlayerIndex == newIndexCount) {
            // compare new player at index with inserted player
            ASSERT_EQ(newListPlayer.score, player->score);
            ASSERT_STR_EQ(newListPlayer.name, player->name);
            continue;
        }

        // compare original player with new player
        ASSERT_EQ(originalPlayer.score, newListPlayer.score);
        ASSERT_STR_EQ(originalPlayer.name, newListPlayer.name);
        originalIndexCount++;
    }

    free(player);
    PASS();
}

/**
 * Having full list of players hall of fame, add player that
 * does not have enough score to be saved
 *
 * @return
 */
TEST add_player_with_not_enough_score_to_full_list() {
    int size = PLAYERS_LIMIT;
    Player currentHallOfFame[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };

    Player hallOfFameAfterAdd[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };

    // prepare new player to insert
    Player *player = (Player *) calloc(1, sizeof(Player));
    strcpy(player->name, "lucia");
    player->score = 1;

    add_player_to_list(hallOfFameAfterAdd, &size, *player);

    for (int i = 0; i < size; i++) {
        ASSERT_STR_EQ(currentHallOfFame[i].name, hallOfFameAfterAdd[i].name);
        ASSERT_EQ(currentHallOfFame[i].score, hallOfFameAfterAdd[i].score);
    }

    free(player);
    PASS();
}

/**
 * Having a file, where players are in bad order,
 * check if the function reads it in good order
 *
 * @return
 */
TEST read_players_bad_order_check_order() {
    Player goodOrderPlayers[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };

    Player readFromBadFile[PLAYERS_LIMIT];
    int readSize = read_scores("tests/score/bad_order", readFromBadFile);

    for (int i = 0; i < readSize; i++) {
        Player good = goodOrderPlayers[i];
        Player read = readFromBadFile[i];

        ASSERT_EQ(good.score, read.score);
        ASSERT_STR_EQ(good.name, read.name);
    }

    PASS();
}

/**
 * Having unsorted list of hall of fame, save it in order
 *
 * @return
 */
TEST compare_saved_unsorted_and_sorted_players() {
    int size = PLAYERS_LIMIT;
    Player goodOrderPlayers[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };

    Player badOrderPlayers[PLAYERS_LIMIT] = {
            {"jozo",  55},
            {"lubo",  2},
            {"alex",  18},
            {"alena", 43},
            {"peter", 99},
            {"roman", 32},
            {"dano",  9},
            {"lubo",  21},
            {"milan", 20},
            {"kiko",  4},
    };

    char hof_file[] = "tests/score/for_saving";
    save_scores(hof_file, badOrderPlayers, size);

    Player readPlayersFromFile[PLAYERS_LIMIT];
    read_scores(hof_file, readPlayersFromFile);

    for (int i = 0; i < size; i++) {
        Player good = goodOrderPlayers[i];
        Player read = readPlayersFromFile[i];
        ASSERT_EQ(good.score, read.score);
        ASSERT_STR_EQ(good.name, read.name);
    }

    remove(hof_file);
    PASS();
}

/**
 * Test if value is not in array
 */
TEST is_value_in_array() {
    int array[] = {1, 2, 3, 4};
    ASSERT_FALSE(isValueInArray(array, 4, 5));
    ASSERT(isValueInArray(array, 4, 4));
    PASS();
}

TEST check_alphabet_order_basic() {
    char *first = "abcd";
    char *second = "efgh";

    ASSERT(isFirstBeforeSecondInAlphabet(first, second));
    ASSERT_FALSE(isFirstBeforeSecondInAlphabet(second, first));
    PASS();
}

TEST check_alphabet_order_null() {
    char *first = "abcd";
    char *second = NULL;

    ASSERT_FALSE(isFirstBeforeSecondInAlphabet(first, second));
    PASS();
}

TEST check_alphabet_order_special_cases() {
    char *first_same = "abcd";
    char *second_same = "abcd";

    ASSERT_FALSE(isFirstBeforeSecondInAlphabet(first_same, second_same));

    char *first_special_chars = "1*&#@";
    char *second_special_chars = "*&@#*&#@";

    ASSERT_FALSE(isFirstBeforeSecondInAlphabet(first_special_chars, second_special_chars));

    char *first_empty = "";
    char *second_empty = "";

    ASSERT_FALSE(isFirstBeforeSecondInAlphabet(first_empty, second_empty));

    PASS();
}

/**
 * Test to sort players descending
 * @return
 */
TEST check_sort_players_desc() {
    int size = PLAYERS_LIMIT;
    Player players[PLAYERS_LIMIT] = {
            {"kiko",  4},
            {"peter", 99},
            {"roman", 32},
            {"alena", 43},
            {"lubo",  21},
            {"jozo",  55},
            {"milan", 20},
            {"dano",  9},
            {"lubo",  2},
            {"alex",  18}
    };

    Player goodOrderPlayers[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };

    Player *sorted = sortListOfPlayers(players, PLAYERS_LIMIT, Descending);

    for (int i = 0; i < size; i++) {
        Player good = goodOrderPlayers[i];
        Player sortedPlayer = sorted[i];
        ASSERT_EQ(good.score, sortedPlayer.score);
        ASSERT_STR_EQ(good.name, sortedPlayer.name);
    }

    free(sorted);
    PASS();
}

/**
 * Test to sort players ascending
 * @return
 */
TEST check_sort_players_asc() {
    int size = PLAYERS_LIMIT;
    Player players[PLAYERS_LIMIT] = {
            {"kiko",  4},
            {"peter", 99},
            {"roman", 32},
            {"alena", 43},
            {"lubo",  21},
            {"jozo",  55},
            {"milan", 20},
            {"dano",  9},
            {"lubo",  2},
            {"alex",  18}
    };

    Player goodOrderPlayers[PLAYERS_LIMIT] = {
            {"lubo",  2},
            {"kiko",  4},
            {"dano",  9},
            {"alex",  18},
            {"milan", 20},
            {"lubo",  21},
            {"roman", 32},
            {"alena", 43},
            {"jozo",  55},
            {"peter", 99},
    };

    Player *sorted = sortListOfPlayers(players, PLAYERS_LIMIT, Ascending);

    for (int i = 0; i < size; i++) {
        Player good = goodOrderPlayers[i];
        Player sortedPlayer = sorted[i];
        ASSERT_EQ(good.score, sortedPlayer.score);
        ASSERT_STR_EQ(good.name, sortedPlayer.name);
    }

    free(sorted);
    PASS();
}

TEST check_index_where_insert_player_on_beginning() {
    Player playersDescending[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };
    Player insertToFirstIndexDescendingPlayer = {
            .name = "firstPlayer",
            .score = 100
    };
    int insertToFirstIndexDescendingPlayerIndex = getIndexWhereToInsertPlayer(playersDescending, PLAYERS_LIMIT, insertToFirstIndexDescendingPlayer, Descending, false);
    ASSERT_EQ(insertToFirstIndexDescendingPlayerIndex, 0);



    Player playersAscending[PLAYERS_LIMIT] = {
            {"lubo",  2},
            {"kiko",  4},
            {"dano",  9},
            {"alex",  18},
            {"milan", 20},
            {"lubo",  21},
            {"roman", 32},
            {"alena", 43},
            {"jozo",  55},
            {"peter", 99},
    };
    Player insertToFirstIndexAscendingPlayer = {
            .name = "firstPlayer",
            .score = 1
    };
    int insertToFirstIndexAscendingPlayerIndex = getIndexWhereToInsertPlayer(playersAscending, PLAYERS_LIMIT, insertToFirstIndexAscendingPlayer, Ascending, false);
    ASSERT_EQ(insertToFirstIndexAscendingPlayerIndex, 0);

    PASS();
}

TEST check_index_where_insert_player_on_empty_list() {
    Player playersDescending[PLAYERS_LIMIT] = {};
    Player insertToFirstIndexDescendingPlayer = {
            .name = "firstPlayer",
            .score = 100
    };
    int insertToFirstIndexDescendingPlayerIndex = getIndexWhereToInsertPlayer(playersDescending, 0, insertToFirstIndexDescendingPlayer, Descending, false);
    ASSERT_EQ(insertToFirstIndexDescendingPlayerIndex, 0);

    PASS();
}

TEST check_index_where_insert_player_random() {
    Player playersDescending[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            // here goes random player
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };
    Player insertToRandomIndexDescendingPlayer = {
            .name = "randomPlayer",
            .score = 45
    };
    int insertToFirstIndexDescendingPlayerIndex = getIndexWhereToInsertPlayer(playersDescending, PLAYERS_LIMIT, insertToRandomIndexDescendingPlayer, Descending, false);
    ASSERT_EQ(insertToFirstIndexDescendingPlayerIndex, 2);

    Player playersAscending[PLAYERS_LIMIT] = {
            {"lubo",  2},
            {"kiko",  4},
            {"dano",  9},
            // here goes random player
            {"alex",  18},
            {"milan", 20},
            {"lubo",  21},
            {"roman", 32},
            {"alena", 43},
            {"jozo",  55},
            {"peter", 99},
    };
    Player insertToRandomIndexAscendingPlayer = {
            .name = "firstPlayer",
            .score = 10
    };
    int insertToRandomIndexAscendingPlayerIndex = getIndexWhereToInsertPlayer(playersAscending, PLAYERS_LIMIT, insertToRandomIndexAscendingPlayer, Ascending, false);
    ASSERT_EQ(insertToRandomIndexAscendingPlayerIndex, 3);

    PASS();
}

/**
 * If there is a case, where two players have same score, sort them by alphabet test
 * @return
 */
TEST check_index_where_insert_player_alphabet_sorting() {
    Player playersDescending[PLAYERS_LIMIT] = {
            {"peter", 99},
            // here goes random player
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };
    Player insertToRandomIndexDescendingPlayer = {
            .name = "anna",
            .score = 55
    };
    int insertToFirstIndexDescendingPlayerIndex = getIndexWhereToInsertPlayer(playersDescending, PLAYERS_LIMIT, insertToRandomIndexDescendingPlayer, Descending, true);
    ASSERT_EQ(insertToFirstIndexDescendingPlayerIndex, 1);



    Player playersAscending[PLAYERS_LIMIT] = {
            {"lubo",  2},
            {"kiko",  4},
            // here goes random player
            {"dano",  9},
            {"alex",  18},
            {"milan", 20},
            {"lubo",  21},
            {"roman", 32},
            {"alena", 43},
            {"jozo",  55},
            {"peter", 99},
    };
    Player insertToRandomIndexAscendingPlayer = {
            .name = "andrew",
            .score = 9
    };
    int insertToRandomIndexAscendingPlayerIndex = getIndexWhereToInsertPlayer(playersAscending, PLAYERS_LIMIT, insertToRandomIndexAscendingPlayer, Ascending, true);
    ASSERT_EQ(insertToRandomIndexAscendingPlayerIndex, 2);

    PASS();
}


SUITE (test_hall_of_fame) {
    RUN_TEST(load_file_number_of_players);
    RUN_TEST(load_file_over_limit);
    RUN_TEST(load_nonexistent_file);
    RUN_TEST(compare_loaded_and_saved_players);
    RUN_TEST(save_player_over_limit);
    RUN_TEST(add_player_to_optimal_list);
    RUN_TEST(add_player_to_optimal_list_check_order);
    RUN_TEST(add_player_over_limit_check_order);
    RUN_TEST(read_players_bad_order_check_order);
    RUN_TEST(add_player_with_not_enough_score_to_full_list);
    RUN_TEST(compare_saved_unsorted_and_sorted_players);
    RUN_TEST(is_value_in_array);
    RUN_TEST(check_alphabet_order_basic);
    RUN_TEST(check_alphabet_order_null);
    RUN_TEST(check_alphabet_order_special_cases);
    RUN_TEST(check_sort_players_desc);
    RUN_TEST(check_sort_players_asc);
    RUN_TEST(check_index_where_insert_player_on_beginning);
    RUN_TEST(check_index_where_insert_player_random);
    RUN_TEST(check_index_where_insert_player_alphabet_sorting);
    RUN_TEST(check_index_where_insert_player_on_empty_list);
}
