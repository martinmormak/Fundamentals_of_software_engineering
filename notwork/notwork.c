#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wall.h"

void empty_input_buffer() {
    int buf;
    while ((buf = getchar()) != '\n') { }
}

void show_wall_ui(wall_t *wall) {
    char buf[LIKE_COUNT_BUFFER_SIZE];
    post_t *post;
    
    for (int i = 1; i <= wall->num_posts; i++) {
        post = get_post(wall, i);
        printf("%d\t%s (%s)\n", i, post->text,like_count_text(post, buf));
    }
}

void write_post_ui(wall_t *wall) {
    char text[MAX_POST_LENGTH + 2]; // leave space for newline and 0
    size_t newline_pos = 0;

    printf("Enter your post:\n");
    fgets(text, MAX_POST_LENGTH + 2, stdin);

    newline_pos = strcspn(text, "\n");
    if (newline_pos <= MAX_POST_LENGTH) {
        text[newline_pos] = '\0'; // remove the trailing newline
    } else { // Newline not found, so input must be longer then the limit
        printf("Post longer then %d characters. It would be truncated.\n",
            MAX_POST_LENGTH);
        text[MAX_POST_LENGTH] = 0;
        empty_input_buffer();
    }
    post_t *post = create_post(text);
    add_post(wall, post);
}

post_t *select_post_ui(wall_t *wall, char *question) {
    show_wall_ui(wall);
    printf("%s Enter number: ", question);
    int number;
    scanf("%d", &number);
    empty_input_buffer();
    post_t *post = get_post(wall, number);
    if (post == NULL) {
        printf("Invalid post number.\n");
    }
    return post;
}

void like_post_ui(wall_t *wall) {
    post_t *post = select_post_ui(wall, "Which post would you like to like?");
    if (post != NULL) {
        like_post(post);
    }
}

void dislike_post_ui(wall_t *wall) {
    post_t *post = select_post_ui(wall, "Which post would you like to dislike?");
    if (post != NULL) {
        dislike_post(post);
    }
}

void main_ui(wall_t *wall) {
    int input;
    
    do {
        printf("(S)how wall / (W)rite post / (L)ike post / (D)islike post / (E)xit: ");
        input = getchar();
        empty_input_buffer();
        input = toupper(input);
        
        switch (input) {
            case 'S':
                show_wall_ui(wall);
                break;
            case 'W':
                write_post_ui(wall);
                break;
            case 'L':
                like_post_ui(wall);
                break;
            case 'D':
                dislike_post_ui(wall);
                break;
        }
    } while (input != 'E');
}

int main(int argc, char** argv) {
    printf("Notwork - An offline social network\n");
    wall_t *wall = create_wall();
    main_ui(wall);
    destroy_wall(wall);
    return (EXIT_SUCCESS);
}

