#include <stdio.h>
#include <stdlib.h>

#include "piskvorky.h"

int main() {
    printf("Enter the size of field: ");
    int size;
    scanf("%d", &size);

    char field[size];
    for (int i = 0; i < size; i++) {
        field[i] = ' ';
    }
    draw(field, size);

    char player = 'B';
    while (!isSolved(field, size)) {
        player = (player == 'A') ? 'B' : 'A';
        printf("Player %c: ", player);

        int position;
        scanf("%d", &position);

        int cross = addCross(field, size, position);

        if ( cross == -1 ) {
            printf("Wrong position!\n");
            continue;
        } else if ( cross == 0 ) {
            printf("X is already there!\n");
            continue;
        }

        draw(field, size);
    }

    printf("Player %c wins!\n", player);

    return EXIT_SUCCESS;
}

void draw(char field[], int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf(" %d", i+1);
    }
    printf("\n");

    printf("+");
    for (int i = 0; i <size; i++) {
        printf("-+");
    }
    printf("\n");

    printf("|");
    for (int i = 0; i < size; i++) {
        printf("%c|", field[i]);
    }
    printf("\n");

    printf("+");
    for (int i = 0; i < size; i++) {
        printf("-+");
    }
    printf("\n");
}

int addCross(char field[], int size, int position) {
    if(position < 0 || position > size){
        return -1;
    }

    if(field[position-1] == 'X'){
        return 0;
    }

    field[position-1] = 'X';
    return 1;
}

int isSolved(char field[], int size) {
    for(int i = 0; i < size-2; i++){
        if(field[i] == 'X' && field[i+1] == 'X' && field[i+2] == 'X'){
            return 1;
        }
    }

    return 0;
}
