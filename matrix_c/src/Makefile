CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -I .
GCOVFLAGS = -fprofile-arcs -ftest-coverage

RESET = \033[0m
GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
CYAN = \033[36m

SHELLNAME := $(shell uname)
ifeq ($(SHELLNAME), Linux)
  TST_LIBS = -lcheck -lrt -lm -lsubunit -pthread
else ifeq ($(SHELLNAME), Darwin)
  TST_LIBS = -L/opt/homebrew/Cellar/check/0.15.2/lib -lcheck -lm -pthread
endif

SRC_FILES = $(wildcard operation/*.c)
OBJECTS = $(patsubst operation/%.c, operation/%.o, $(SRC_FILES))
TESTS = $(wildcard tests/*.c)
TEST_OBJECTS = $(patsubst tests/%.c, tests/%.o, $(TESTS))

all: clean s21_matrix.a test gcov_report

s21_matrix.a: $(OBJECTS)
	@echo "$(YELLOW)Creating static library...$(RESET)"
	@ar rc s21_matrix.a $(OBJECTS)
	@ranlib s21_matrix.a
	@echo "$(GREEN)Static library created: s21_matrix.a$(RESET)"

operation/%.o: operation/%.c
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

tests/%.o: tests/%.c
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

test: s21_matrix.a $(TEST_OBJECTS)
	@echo "$(CYAN)Running tests...$(RESET)"
	@$(CC) $(CFLAGS) $(TEST_OBJECTS) s21_matrix.a -o test.out $(TST_LIBS)
	@./test.out 2>&1 | tee test_output.log
	@echo "$(GREEN)Tests completed$(RESET)"

test_mac: clean s21_matrix.a $(TEST_OBJECTS)
	@echo "$(CYAN)Running tests for macOS...$(RESET)"
	@$(CC) $(CFLAGS) $(TEST_OBJECTS) s21_matrix.a -o test.out $(TST_LIBS)
	@./test.out 2>&1 | tee test_output.log
	@echo "$(GREEN)Tests completed$(RESET)"

gcov_report: clean s21_matrix.a $(TEST_OBJECTS)
	@echo "$(YELLOW)Generating coverage report...$(RESET)"
	@$(CC) $(CFLAGS) $(GCOVFLAGS) $(SRC_FILES) $(TESTS) -o test.out $(TST_LIBS)
	@./test.out
	@lcov --capture --directory . --output-file coverage.info --ignore-errors unsupported,unused > /dev/null 2>&1
	@lcov --remove coverage.info '/usr/*' '/Applications/Xcode.app/Contents/Developer/*' --output-file coverage.info --ignore-errors unused > /dev/null 2>&1
	@rm -rf report
	@mkdir -p report
	@genhtml coverage.info --output-directory report --quiet > /dev/null 2>&1
	@echo "$(GREEN)HTML report generated in report/index.html$(RESET)"
	@open report/index.html

clean:
	@echo "$(RED)Cleaning up...$(RESET)"
	@rm -f *.a *.o test.out *.gcda *.gcno *.out *.gcov coverage.info test_output.log
	@rm -f operation/*.o operation/*.gcda operation/*.gcno
	@rm -f tests/*.o tests/*.gcda tests/*.gcno
	@rm -rf report
	@echo "$(GREEN)Cleanup complete$(RESET)"

style:
	@echo "$(CYAN)Formatting code with clang-format...$(RESET)"
	@cp ../materials/linters/.clang-format .
	@clang-format -i *.h tests/*.c tests/*.h operation/*.c
	@rm .clang-format
	@echo "$(GREEN)Code formatting complete$(RESET)"

html: gcov_report
	@open report/index.html

valgrind: test
	@echo "$(CYAN)Running Valgrind to check for memory leaks...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./test.out
	@echo "$(GREEN)Valgrind check completed. See valgrind-out.txt for details.$(RESET)"