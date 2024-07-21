#ifndef POST_H
#define	POST_H

#define MAX_POST_LENGTH 30
/* Space for two 64-bit integers and additional text */
#define LIKE_COUNT_BUFFER_SIZE 60

typedef struct {
    char text[MAX_POST_LENGTH + 1];
    int like_count;
    int dislike_count;
} post_t;

post_t *create_post(char *text);
void destroy_post(post_t *post);
void like_post(post_t *post);
void dislike_post(post_t *post);
char *like_count_text(post_t *post, char *buf);
char *dislike_count_text(post_t *post, char *buf);

#endif	/* POST_H */

