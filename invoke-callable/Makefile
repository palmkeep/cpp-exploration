EXE=invoker
CC=clang++
CFLAGS=-g -O2 -std=c++20 -Wall -Wextra

.PHONY: test, clean
test: $(EXE)
	./$(EXE)

$(EXE): main.cpp invoke_callable.hpp.gch
	$(CC) $(CFLAGS) -o $(EXE) main.cpp

invoke_callable.hpp.gch: invoke_callable.hpp
	$(CC) $(CFLAGS) -c invoke_callable.hpp

clean:
	rm -rf $(EXE) ./*.o ./*.gch
