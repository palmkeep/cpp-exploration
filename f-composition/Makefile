EXE=a.out
CC=clang++
DEBUG?=0
CFLAGS=-O2 -std=c++20 -Wall -Wextra -D DEBUG=$(DEBUG)

.PHONY: all clean test
test:
	- @rm $(EXE)
	$(CC) $(CFLAGS) -o $(EXE) main.cpp
	./$(EXE)

all: $(EXE)

clean:
	rm -rf $(EXE) ./*.out ./*.gch


$(EXE): main.cpp pretty_print.hpp.gch functional.hpp.gch
	$(CC) $(CFLAGS) -o $(EXE) main.cpp

functional.hpp.gch: functional.hpp
	$(CC) $(CFLAGS) -c functional.hpp

pretty_print.hpp.gch: pretty_print.hpp
	$(CC) $(CFLAGS) -c pretty_print.hpp

