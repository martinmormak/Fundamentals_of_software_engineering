#ifndef WALL_H
#define	WALL_H

#include "post.h"

#define MAX_POSTS 20

typedef struct {
    int num_posts;
    post_t *posts[MAX_POSTS];
} wall_t;

wall_t *create_wall();
void destroy_wall(wall_t *wall);
void add_post(wall_t *wall, post_t *post);
post_t *get_post(wall_t *wall, int number);

#endif	/* WALL_H */
