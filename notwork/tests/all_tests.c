#include "greatest.h"

extern SUITE(test_post);
extern SUITE(test_wall);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(test_post);
    RUN_SUITE(test_wall);
    GREATEST_MAIN_END();
}
