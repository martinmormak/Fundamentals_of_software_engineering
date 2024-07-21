CC = gcc
CFLAGS = -std=c11 -Wall -pedantic -g
LDFLAGS =

TARGET = notwork
MODULES = wall.o post.o
TEST_TARGET = tests/all_tests
TEST_MODULES = tests/test_post.o tests/test_wall.o

# Main tasks
.PHONY: all test clean

all: $(TARGET) $(TEST_TARGET)

test: $(TEST_TARGET)
	$<

clean:
	rm *.o tests/*.o $(TARGET) $(TEST_TARGET)

# Dependencies
$(TARGET): notwork.o $(MODULES)
notwork.o: notwork.c wall.h post.h
wall.o: wall.c wall.h post.h
post.o: post.c post.h

$(TEST_TARGET): tests/all_tests.o $(TEST_MODULES) $(MODULES)
tests/test_post.o: tests/test_post.c post.h
tests/test_wall.o: tests/test_wall.c wall.h

# Machinery
%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $<
%: %.o
	$(CC) -o $@ $(LDFLAGS) $^
