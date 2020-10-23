// SPDX-FileCopyrightText: 2019 knilch <knilch0r@cwde.de>
//
// SPDX-License-Identifier: GPL-2.0-only

#include <stdio.h>
#include <stdlib.h>

static void* mallocprint(size_t s) {
	void * p = malloc(s);
	printf("malloc(%zd) = %p\n", s, p);
	return p;
}

int main(int argc, char**argv) {
	void *a, *b, *c;
	a = mallocprint(1024);
	b = mallocprint(1024);
	c = mallocprint(2048);
	free(b);
	puts("free(b)");
	b = mallocprint(512);
	b = realloc(b, 1024);
	printf("realloc(1024) = %p\n", b);
	free(c);
	puts("free(c)");
	b = mallocprint(argc * 1024 * 1024);
	c = mallocprint(argc * 8 * 1024 * 1024);
	free(c);
	puts("free(c)");
	c = mallocprint(argc);
	free(a);
	free(c);
	c = mallocprint(argc * 8 * 1024 * 1024);
	return 0;
}

