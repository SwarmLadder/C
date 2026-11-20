CC ?= cc
CFLAGS ?= -O2
FLAGS = -std=c17 -Wall -Wextra -Werror -pedantic -Iinclude
STARTERS := $(wildcard */starter/*.c)
SOLUTIONS := $(wildcard */solutions/*.c)

.PHONY: check reference
check: build/student
	./build/student "$(TASK)" "$(LEVEL)"

reference: build/reference
	./build/reference "$(TASK)" "$(LEVEL)"

build/student: $(STARTERS) include/course.h tests/course.c Makefile
	@mkdir -p build
	$(CC) $(FLAGS) $(CFLAGS) $(STARTERS) tests/course.c -o $@

build/reference: $(SOLUTIONS) include/course.h tests/course.c Makefile
	@mkdir -p build
	$(CC) $(FLAGS) $(CFLAGS) $(SOLUTIONS) tests/course.c -o $@
