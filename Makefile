CC ?= cc
CFLAGS ?= -O2
FLAGS = -std=c17 -Wall -Wextra -Werror -pedantic -Iinclude
LEVELS := basics intermediate advanced
STARTERS := $(foreach level,$(LEVELS),$(wildcard $(level)/starter/*.c))
SOLUTIONS := $(foreach level,$(LEVELS),$(wildcard $(level)/solutions/*.c))
MASTER_STARTERS := $(wildcard mastery/starter/*.c)
MASTER_SOLUTIONS := $(wildcard mastery/reference/*.c)
MASTER_FLAGS = -std=c17 -Wall -Wextra -Werror -pedantic -Imastery/include

.PHONY: check reference mastery-check mastery-reference clean
check: build/student
	./build/student "$(TASK)" "$(LEVEL)"

reference: build/reference
	./build/reference "$(TASK)" "$(LEVEL)"

mastery-check: build/mastery-student
	./build/mastery-student "$(TASK)" "$(LEVEL)"

mastery-reference: build/mastery-reference
	./build/mastery-reference "$(TASK)" "$(LEVEL)"

build/student: $(STARTERS) include/course.h tests/course.c Makefile
	@mkdir -p build
	$(CC) $(FLAGS) $(CFLAGS) $(STARTERS) tests/course.c -o $@

build/reference: $(SOLUTIONS) include/course.h tests/course.c Makefile
	@mkdir -p build
	$(CC) $(FLAGS) $(CFLAGS) $(SOLUTIONS) tests/course.c -o $@

build/mastery-student: $(MASTER_STARTERS) mastery/include/mastery.h tests/mastery.c Makefile
	@mkdir -p build
	$(CC) $(MASTER_FLAGS) $(CFLAGS) $(MASTER_STARTERS) tests/mastery.c -o $@

build/mastery-reference: $(MASTER_SOLUTIONS) mastery/include/mastery.h tests/mastery.c Makefile
	@mkdir -p build
	$(CC) $(MASTER_FLAGS) $(CFLAGS) $(MASTER_SOLUTIONS) tests/mastery.c -o $@

build/telemetry-inspector: examples/telemetry_reader/main.c mastery/reference/frame_header.c mastery/include/mastery.h Makefile
	@mkdir -p build
	$(CC) $(MASTER_FLAGS) $(CFLAGS) examples/telemetry_reader/main.c mastery/reference/frame_header.c -o $@

clean:
	rm -rf build
