CC = g++
CFLAGS = -c -Wall -Werror -Wextra -pedantic -std=c++20
LDFLAGS = -std=c++20
SOURCE = $(wildcard s21_*.cpp)
HEADER = $(wildcard s21_*.h)
OBJECTS = $(patsubst %.cpp,%.o, ${SOURCE})
TESTS_SOURCE = $(wildcard tests/*.cpp)
TESTS_OBJECTS = $(patsubst %.cpp,%.o, ${TESTS_SOURCE})
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  OPEN_CMD = xdg-open
  ADD_LIB = -lgtest -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
  BREW = .
  GTEST_INCLUDE =
  GTEST_LIB = -lgtest -lgtest_main -lsubunit -lm -lrt -lpthread
endif
ifeq ($(UNAME_S),Darwin)
  OPEN_CMD = open
  ADD_LIB =
  BREW := /opt/homebrew
  ARCH := $(shell uname -m)
  ifeq ($(ARCH),arm64)
    GTEST_INCLUDE = -I/opt/homebrew/include
    GTEST_LIB = -L/opt/homebrew/lib -lgtest -lgtest_main
  else
    GTEST_INCLUDE = -I/usr/local/include
    GTEST_LIB = -L/usr/local/lib -lgtest -lgtest_main
  endif
endif

PATH := $(BREW)/bin:$(PATH)

all: s21_matrix_oop.a

s21_matrix_oop.a: ${SOURCE}
	$(CC) $(CFLAGS) $(ADD_LIB) $(SOURCE)
	ar rcs $@ $(OBJECTS)
	ranlib $@
	-rm -rf *.o

test_linux: ${TESTS_SOURCE} s21_matrix_oop.a
	$(CC) $(LDFLAGS) -o test $^ -lgtest -lsubunit -lm -lrt -lpthread
	./test

test_mac: ${TESTS_SOURCE} s21_matrix_oop.a
	$(CC) $(LDFLAGS) $(GTEST_INCLUDE) -o test $^ $(GTEST_LIB)
	./test

test:
ifeq ($(UNAME_S),Linux)
	$(MAKE) test_linux
else ifeq ($(UNAME_S),Darwin)
	$(MAKE) test_mac
else
	@echo "Unsupported OS"
endif

gcov_report: ${SOURCE} ${TESTS_SOURCE}
	$(CC) --coverage $(GTEST_INCLUDE) $(SOURCE) $(TESTS_SOURCE) -o gcov_test $(GTEST_LIB) -std=c++20
	chmod +x gcov_test
	./gcov_test
	lcov -t "gcov_test" --ignore-errors inconsistent,source -o s21_test.info --no-external -c -d . --rc lcov_branch_coverage=1
	lcov --remove s21_test.info '*/tests/*' -o s21_test.info --rc lcov_branch_coverage=1
	genhtml --ignore-errors inconsistent,source -o report s21_test.info --rc genhtml_branch_coverage=1
	$(OPEN_CMD) ./report/index.html

valgrind: clean
ifeq ($(UNAME_S),Linux)
	make s21_matrix_oop.a
	$(CC) -g $(TESTS_SOURCE) -std=c++20 s21_matrix_oop.a -o test -lgtest -lpthread -D_GNU_SOURCE
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt ./test
else
	@echo "Valgrind is not supported on macOS"
endif

leaks: clean
ifeq ($(UNAME_S),Darwin)
	make s21_matrix_oop.a
	$(CC) -g $(GTEST_INCLUDE) $(TESTS_SOURCE) -std=c++20 s21_matrix_oop.a -o test $(GTEST_LIB)
	@echo "Running leaks (sudo may be required for full debugging)"
	MallocStackLogging=1 sudo leaks -atExit -- ./test > leaks_report.txt 2>&1 || true
	@echo "Leaks report saved to leaks_report.txt"
	@grep LEAK: leaks_report.txt || echo "No leaks detected"
	@echo "Note: If 'Process is not debuggable' appears, try running 'sudo make leaks' or use Instruments from Xcode"
else
	@echo "Leaks is not supported on Linux"
endif

style: clean
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cpp *.h
	clang-format -style=Google -n tests/*.cpp tests/*.h
	rm .clang-format

clean:
	-rm -rf *.o *.gcno *.a *.gcda *.info *.gcov ./gcov_test ./report/ ./test s21_test RESULT_VALGRIND.txt leaks_report.txt

rebuild: clean all

.PHONY: all clean test test_linux test_mac gcov_report valgrind leaks style rebuild