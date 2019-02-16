/* monoalloc - simple monotonic allocator implementation of malloc()
 * Copyright (C) 2019 knilch - knilch0r@cwde.de
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#ifdef DEBUG
#include <stdio.h>
static int indebug;
#endif
#ifdef THREADS
#include <pthread.h>
static pthread_mutex_t monoalloc_mutex = PTHREAD_MUTEX_INITIALIZER;
#define MUTEX_LOCK()  do { pthread_mutex_lock(&monoalloc_mutex); } while (0)
#define MUTEX_UNLOCK()  do { pthread_mutex_unlock(&monoalloc_mutex); } while (0)
#else
#define MUTEX_LOCK()  do { /* nothing */ } while (0)
#define MUTEX_UNLOCK()  do { /* nothing */ } while (0)
#endif
/* size of initial allocation */
size_t monoalloc_size = 50 * 1042 * 1024;
static int init;

static void *next;
static size_t currsize;

static void check_init(void) {
	if (!init) {
		next = sbrk(monoalloc_size);
		if (next == (void *) -1) next = NULL;
		init = 1;
	}
}

void *malloc(size_t size) {
	void * tmp = NULL;
	MUTEX_LOCK();
	/* we assume that next always points to sufficiently aligned memory,
	 * so further alignment is ensured by increasing size */
	if (size & 0xFu) size = (size + 16) & (~ (size_t) 0xFu);
	if ((SIZE_MAX - size < currsize) || (monoalloc_size < currsize + size)) {
		/* FIXME: errno = ENOMEM; */
		goto out_unlock;
	}
	check_init();
	if (!next) goto out_unlock;
	tmp = next;
	next = (char *)next + size;
	currsize += size;
#ifdef DEBUG
	if (!indebug) {
		/* printf() would call malloc(), resulting in endless recursion... */
		indebug = 1;
		printf("trace: malloc'd %zd bytes, next %p, return %p\n", size, next, tmp);
		indebug = 0;
	}
#endif
out_unlock:
	MUTEX_UNLOCK();
	return tmp;
}

void free(void *ptr) {
	/* do nothing */
#ifdef DEBUG
	printf("trace: free %p\n", ptr);
#endif
	(void) ptr;
}

void *calloc(size_t nmemb, size_t size) {
	void *tmp;
#ifdef DEBUG
	printf("trace: calloc %zd, %zd\n", nmemb, size);
#endif
	/* ensure proper alignment for array members */
	if (size & 0xFu) size = (size + 16) & (~ (size_t) 0xFu);
	tmp = malloc(nmemb*size);
	if (!tmp) return NULL;
	memset(tmp, 0, size);
	return tmp;
}

void *realloc(void *ptr, size_t size) {
	void *tmp;
#ifdef DEBUG
	printf("trace: realloc %p, %zd\n", ptr, size);
#endif
	if (!ptr) return malloc(size);
	if (!size) return NULL;
	tmp = malloc(size);
	memcpy(tmp, ptr, size);
	return tmp;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

