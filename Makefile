# SPDX-FileCopyrightText: 2019 knilch <knilch0r@cwde.de>
#
# SPDX-License-Identifier: GPL-2.0-only

.PHONY: all test clean

all: cpptest ctest libmonoalloc.so threadtest

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

threadtest: threadtest.cpp monoalloc.c
	g++ -Wall -DTHREADS $(EXTRAFLAGS) $^ -lpthread -o $@


test: ctest cpptest threadtest
	LD_LIBRARY_PATH=. ./ctest -------------------------------
	./ctest-glibc -------------------------------------------
	LD_LIBRARY_PATH=. ./cpptest -----------------------------
	./cpptest-glibc -----------------------------------------
	./threadtest > threadtest.out

clean:
	rm -f cpptest ctest libmonoalloc.so cpptest-glibc ctest-glibc threadtest threadtest.out
