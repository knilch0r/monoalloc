# SPDX-FileCopyrightText: 2019 knilch <knilch0r@cwde.de>
#
# SPDX-License-Identifier: GPL-2.0-only

.PHONY: all test clean

all: cpptest ctest libmonoalloc.so threadtest

ifneq ($(D),)
EXTRAFLAGS:=-DDEBUG -g
endif

libmonoalloc.so: monoalloc.c
	gcc -Wall -Wextra -fPIC $(CFLAGS) $(EXTRAFLAGS) $^ -shared -o $@ -lc

cpptest: test.cpp libmonoalloc.so
	g++ -Wall $(CFLAGS) $(EXTRAFLAGS) $^ -o $@
	g++ -Wall $(CFLAGS) $(EXTRAFLAGS) $< -o $@-glibc

ctest: test.c libmonoalloc.so
	gcc -Wall $(CFLAGS) $(EXTRAFLAGS) $^ -o $@
	gcc -Wall $(CFLAGS) $(EXTRAFLAGS) $< -o $@-glibc

threadtest: threadtest.cpp monoalloc.c
	g++ -Wall -DTHREADS $(CFLAGS) $(EXTRAFLAGS) $^ -lpthread -o $@


test: ctest cpptest threadtest
	./threadtest > threadtest.out
	LD_LIBRARY_PATH=. ./cpptest -----------------------------
	./cpptest-glibc -----------------------------------------
	LD_LIBRARY_PATH=. ./ctest -------------------------------
	./ctest-glibc -------------------------------------------

clean:
	rm -f cpptest ctest libmonoalloc.so cpptest-glibc ctest-glibc threadtest threadtest.out
