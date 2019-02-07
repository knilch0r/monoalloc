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

clean:
	rm -f cpptest ctest libmonoalloc.so cpptest-glibc ctest-glibc
