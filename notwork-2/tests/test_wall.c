#include <stdio.h>
#include <stdlib.h>
#include "greatest.h"
#include "../wall.h"

wall_t *create_wall_with_posts(int num_posts) {
    char buffer[25];
    wall_t *wall = create_wall();
    for (int i = 1; i <= num_posts; i++) {
        sprintf(buffer, "Post %d", i);
        add_post(wall, create_post(buffer));
    }
    return wall;
}

TEST empty_wall_should_have_no_posts() {
    wall_t *wall = create_wall();

    ASSERT_EQ(NULL, get_post(wall, 0));
    ASSERT_EQ(NULL, get_post(wall, 1));

    destroy_wall(wall);
    PASS();
}

TEST get_post_should_return_first_post() {
    wall_t *wall = create_wall();
    post_t *post1 = create_post("Post 1");
    add_post(wall, post1);
    
    ASSERT_EQ(post1, get_post(wall, 1));
    
    destroy_wall(wall);
    PASS();
}

TEST get_post_should_return_last_post() {
    wall_t *wall = create_wall_with_posts(3);
    post_t *post4 = create_post("Post 4");
    add_post(wall, post4);
    
    ASSERT_EQ(post4, get_post(wall, 4));
    
    destroy_wall(wall);
    PASS();
}

SUITE(test_wall) {
    RUN_TEST(empty_wall_should_have_no_posts);
    RUN_TEST(get_post_should_return_first_post);
    RUN_TEST(get_post_should_return_last_post);
}
