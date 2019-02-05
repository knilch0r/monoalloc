all: cpptest ctest

libmonoalloc.so: monoalloc.c
	gcc -Wall -Wextra -fPIC $^ -shared -o $@ -lc -ldl

cpptest: test.cpp libmonoalloc.so
	g++ -Wall $^ -o $@
	g++ -Wall $< -o $@-glibc

ctest: test.c libmonoalloc.so
	gcc -Wall $^ -o $@
	gcc -Wall $< -o $@-glibc

