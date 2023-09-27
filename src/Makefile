CC = gcc
TEST_DIR = ./tests
TEST = tests/test_main
BUILD_DIR = obj
BUILD_TEST_DIR = obj_test

SRC  := $(shell find ./arithmetic ./conversion ./comparison ./helpers ./others -name "s21*.c")
OBJS := $(SRC:%.c=$(BUILD_DIR)/%.o)

TEST_SRC := $(shell find $(TEST_DIR) -name "*.c")
TEST_OBJS := $(TEST_SRC:%.c=$(BUILD_TEST_DIR)/%.o)

FLAGS = -std=c11 -Wall -Werror -Wextra
TEST_FLAGS = -lcheck -lpthread -pthread -lm 

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS += -lsubunit -lgcov -lrt
endif

all: clean s21_decimal.a test gcov_report

s21_decimal.a: $(OBJS) s21_decimal.h 
	@mkdir -p $(BUILD_DIR)
	ar rc s21_decimal.a $(OBJS)
	ranlib s21_decimal.a
	
testim: s21_decimal.a 
	$(CC) -c main.c
	$(CC)  main.o s21_decimal.a -o DEBUG.out

test.a: $(TEST_OBJS)
	ar r test.a $^

test: s21_decimal.a test.a 
	$(CC) $(TEST_OBJS) test.a  s21_decimal.a $(TEST_FLAGS) -o test.out 
	./test.out

gcov_report: clean
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage $(TEST_SRC) $(SRC) -o test $(TEST_FLAGS)
	./test
	lcov -t "s21_decimal.a" -o s21_decimal.info -c -d .
	genhtml -o gcov_report s21_decimal.info

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@ 

$(BUILD_TEST_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $^ -o $@

$(GCOV_OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(TEST_FLAGS) -c $< -o $@

testforleaks: s21_decimal.a test.a 
	$(CC) $(TEST_OBJS) test.a  s21_decimal.a $(TEST_FLAGS) -o test.out 

leaks: testforleaks
ifeq ($(shell uname -s), Linux)
	valgrind --leak-check=yes  ./test.out
else
	leaks --atExit -- ./test.out
endif

style_fix:
	clang-format -style=Google -i *.c *.h

style:
	clang-format -style=Google -n $(SRC) *.h


rebuild: clean all

clean:
	rm -rf *.gcda *.gcov *.o *.gcno *.out *.a ./tests/coverage_report.* *.gcda *.gcno *.gcov *.info *.html $(TEST)*.gcda $(TEST)*.gcno $(TEST)*.o $(TEST)*.a $(TEST) gcov_report test
	rm -rf $(BUILD_DIR) $(BUILD_TEST_DIR) $(GCOV_OBJ_DIR) *.dSYM

