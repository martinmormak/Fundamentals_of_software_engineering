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

TEST like_count_text_should_use_correct_plurals() {
    char buf[LIKE_COUNT_BUFFER_SIZE];
    post_t *post = create_post("new post");
 
    ASSERT_STR_EQ("0 likes", like_count_text(post, buf));
 
    like_post(post);
    ASSERT_STR_EQ("1 like", like_count_text(post, buf));
 
    like_post(post);
    ASSERT_STR_EQ("2 likes", like_count_text(post, buf));
 
    destroy_post(post);
    PASS();
}

TEST created_post_should_have_correct_text() {
    char *text = "my testing post";
    post_t *post = create_post(text);
 
    ASSERT_STR_EQ(text, post->text);
 
    destroy_post(post);
    PASS();
}
 
TEST created_post_should_have_zero_likes() {
    post_t *post = create_post("test");
 
    ASSERT_EQ(0, post->like_count);
 
    destroy_post(post);
    PASS();
}

TEST created_post_with_a_large_size_then_return_null(){
    post_t *post=create_post("This si test for testing when user give longest text then is maximum length size.");
 
    ASSERT_EQ(NULL,post);
 
    destroy_post(post);
    PASS();
}

TEST created_post_should_have_zero_dislikes() {
    post_t *post = create_post("test");
 
    ASSERT_EQ(0, post->dislike_count);
 
    destroy_post(post);
    PASS();
}

TEST dislike_post_increments_dislike_count() {
    post_t *post = create_post("test");
    dislike_post(post);

    ASSERT_EQ(1, post->dislike_count);

    destroy_post(post);
    PASS();
}

TEST dislike_count_text_should_use_correct_plurals() {
    char buf[LIKE_COUNT_BUFFER_SIZE];
    post_t *post = create_post("new post");
 
    ASSERT_STR_EQ("", dislike_count_text(post, buf));
 
    dislike_post(post);
    ASSERT_STR_EQ("1 dislike", dislike_count_text(post, buf));
 
    dislike_post(post);
    ASSERT_STR_EQ("2 dislikes", dislike_count_text(post, buf));
 
    destroy_post(post);
    PASS();
}

SUITE(test_post) {
    RUN_TEST(like_post_increments_like_count);
    RUN_TEST(like_count_text_should_use_correct_plurals);
    RUN_TEST(created_post_should_have_correct_text);
    RUN_TEST(created_post_should_have_zero_likes);
    RUN_TEST(created_post_with_a_large_size_then_return_null);
    RUN_TEST(created_post_should_have_zero_dislikes);
    RUN_TEST(dislike_post_increments_dislike_count);
    RUN_TEST(dislike_count_text_should_use_correct_plurals);
}
