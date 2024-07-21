#include <stdlib.h>
#include "wall.h"

wall_t *create_wall() {
    wall_t *wall = malloc(sizeof(wall_t));
    wall->num_posts = 0;
    return wall;
}

void destroy_wall(wall_t *wall) {
    for (int i = 0; i < wall->num_posts; i++)
        destroy_post(wall->posts[i]);
    free(wall);
}

void add_post(wall_t *wall, post_t *post) {
    wall->posts[wall->num_posts] = post;
    wall->num_posts++;
}

post_t *get_post(wall_t *wall, int number) {
    if (number > 0 && number <= wall->num_posts)
        return wall->posts[number - 1];
    else
        return NULL;
}
