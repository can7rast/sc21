CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
TST_LIBS=-lcheck -lrt -lm -lsubunit -pthread
TST_LIBS_MAC= -lcheck -lm -pthread
TESTS=$(wildcard ./tests/*.c)
OBJECTS := $(patsubst ./tests/%.c, ./tests/%.o, $(TESTS))

all: clean gcov_report

s21_string.a: s21_string.o 
	ar rc s21_string.a s21_string.o
	ranlib s21_string.a

s21_string.o: s21_string.c
	$(CC) $(CFLAGS) -c $< -o $@

./tests/%.o: ./tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.a *.o test.out *.gcda *.gcno *.out
	rm -f ./tests/*.o ./tests/*.gcda ./tests/*.gcno
	rm -rf ./report

test: s21_string.a $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) s21_string.a -o test.out $(TST_LIBS)
	./test.out
	rm -f $(OBJECTS)

test_mac: s21_string.a $(OBJECTS)
	$(CC) $(CFLAGS) $(shell pkg-config --libs check) $(OBJECTS) s21_string.a -o test.out
	./test.out
	rm -f $(OBJECTS)

gcov_report_mac: s21_string.a $(OBJECTS)
	$(CC) $(CFLAGS) $(shell pkg-config --libs check) --coverage $(TESTS) s21_string.a $(TST_LIBS_MAC) -o test.out 
	./test.out
	@lcov -t "Report" -c -d ./ --output-file coverage.info
	genhtml ./coverage.info --output-directory ./report/
	open ./report/index.html
	rm -f $(OBJECTS) *.o *.a *.gcno *.gcda *.info *.out *.gcov

gcov_report: s21_string.a $(OBJECTS)
	$(CC) $(CFLAGS) $(shell pkg-config --libs check) --coverage $(TESTS) s21_string.a $(TST_LIBS) -o test.out 
	./test.out
	@lcov -t "Report" -c -d ./ --output-file coverage.info
	genhtml ./coverage.info --output-directory ./report/
	open ./report/index.html
	rm -f $(OBJECTS) *.o *.a *.gcno *.gcda *.info *.out *.gcov