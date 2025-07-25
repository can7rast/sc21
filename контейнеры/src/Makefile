CXX=g++
CXXFLAGS=-std=c++20 -Wall -Wextra -Werror
TST_LIBS=-lgtest -lgtest_main -lpthread
TESTS=$(wildcard ./tests/*.cpp)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	TST_LIBS += -L/opt/homebrew/lib
	CXXFLAGS += -I/opt/homebrew/include 
endif

all: test

clean:
	rm -rf *.o *.a *.out *.log $(TEST_TARGET)

test: clean
	$(CXX) $(CXXFLAGS) $(TESTS) -o tests.out $(TST_LIBS)
	./tests.out