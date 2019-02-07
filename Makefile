.PHONY: all test clean

all: cpptest ctest libmonoalloc.so

ifneq ($(D),)
EXTRAFLAGS:=-DDEBUG -g
endif

libmonoalloc.so: monoalloc.c
	gcc -Wall -Wextra -fPIC $(EXTRAFLAGS) $^ -shared -o $@ -lc

cpptest: test.cpp libmonoalloc.so
	g++ -Wall $(EXTRAFLAGS) $^ -o $@
	g++ -Wall $(EXTRAFLAGS) $< -o $@-glibc

ctest: test.c libmonoalloc.so
	gcc -Wall $(EXTRAFLAGS) $^ -o $@
	gcc -Wall $(EXTRAFLAGS) $< -o $@-glibc

test: ctest cpptest
	LD_LIBRARY_PATH=. ./ctest -------------------------------
	./ctest-glibc -------------------------------------------
	LD_LIBRARY_PATH=. ./cpptest -----------------------------
	./cpptest-glibc -----------------------------------------

clean:
	rm -f cpptest ctest libmonoalloc.so cpptest-glibc ctest-glibc
