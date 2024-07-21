#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "post.h"

post_t *create_post(char *text) {
    if (strlen(text) <= MAX_POST_LENGTH) {
        post_t *post = malloc(sizeof(post_t));
        strcpy(post->text, text);
        post->like_count = 0;
        post->dislike_count = 0;
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
    post->dislike_count++;
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
    if (post->like_count == 1) {
        strcpy(buf, "1 like");
    } else {
        sprintf(buf, "%d likes", post->like_count);
    }
    return buf;
}

char *dislike_count_text(post_t *post, char *buf) {
    if(post->dislike_count==0)
    {
        strcpy(buf, "");
    }
    else if (post->dislike_count == 1) {
        strcpy(buf, "1 dislike");
    } else {
        sprintf(buf, "%d dislikes", post->dislike_count);
    }
    return buf;
}
