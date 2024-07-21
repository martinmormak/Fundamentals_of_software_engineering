#include <stdio.h>
#include <stdlib.h>
#include "greatest.h"
#include "../post.h"

TEST like_post_increments_like_count() {
    post_t *post = create_post("test");
    like_post(post);

    ASSERT_EQ(1, post->like_count);

    destroy_post(post);
    PASS();
}

SUITE(test_post) {
    RUN_TEST(like_post_increments_like_count);
}
