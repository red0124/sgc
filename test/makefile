CC=gcc
CFLAGS=-Wall -Wextra
LDLIBS= ./Unity/src/unity.c
TESTS=test_algorithm test_deque test_forward_list test_list test_map \
      test_priority_queue test_queue test_set test_stack test_static_deque \
      test_static_priority_queue test_static_queue test_static_stack \
      test_static_unordered_map test_static_unordered_set test_static_vector \
      test_string test_unordered_map test_unordered_set test_vector

all: $(TESTS)

# ----

# pattern rule, replacing built-in implicit .c-suffix rule
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

debug: CFLAGS += -g
debug: all

clean:
	@$(RM) -fv $(TESTS)

run: 
	@for i in $(TESTS); do \
		./$$i; \
	done

# don't use any implicit rules
.SUFFIXES:
# these rules won't actually build the targets they're named after
.PHONY: all clean run debug
