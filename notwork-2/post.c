#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "post.h"

post_t *create_post(char *text) {
    if (strlen(text) <= MAX_POST_LENGTH) {
        post_t *post = malloc(sizeof(post_t));
        strcpy(post->text, text);
        post->like_count = 0;
        return post;
    } else {
        return NULL;
    }
}

void destroy_post(post_t *post) {
    free(post);
}

void like_post(post_t *post) {
    post->like_count++;
}

void dislike_post(post_t *post) {
    if (post->like_count > 0)
        post->like_count--;
}

/*
 * Returns a text representing the number of likes of the post, taking
 * singular/plural forms into account.
 * 
 * post - the post of interest
 * buf - a buffer at least LIKE_COUNT_BUFFER_SIZE bytes long
 * 
 * This function is intentionally awful - it is a candidate for refactoring.
 */
char *like_count_text(post_t *post, char *buf) {
    int var1 = post->like_count;
    int var2 = (var1 == 1);
    sprintf(buf, "%d likes", var1);
    int len = strlen(buf);
    if (var2) {
        sprintf(buf, "%d like", var1);
    }
    return buf;
}
