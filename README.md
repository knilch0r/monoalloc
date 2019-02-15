# monoalloc
monotonic allocator replacement for `malloc()`.

"monotonic allocator" means that this is the most space-conserving, real-time malloc you'll
get, because it's using exactly 32 bytes for bookkeeping (on a 64 bit system), no matter how
many chucks you'll get, and all functions are perfectly linear, without any loops.

On the other hand, you'll probably notice that `free()` is a no-op, and `realloc()` always
will get you a new chunk, so applications using these two often might need more memory than
when using other allocators.
# caveats
not thread-safe. probably broken. for educational purposes only. NO WARRANTY. 'AS-IS'.
assumes 16 bytes alignment will be enough for anybody, and that `sbrk()` only returns
aligned pointers.
# how to use
- set `LD_LIBRARY_PATH` to the location of `libmonoalloc.so`, and either
  - link your applications against `libmonoalloc.so`, see `Makefile` or
  - use `LD_PRELOAD=libmonoalloc.so` for an existing application that has `malloc` linked
    in dynamically.
- alternatively, just statically compile and link `monoalloc.c` to your code before linking
  in the C library.
- set `monoalloc_size` to the maximum size you want to allocate - either by changing the code, or
  by setting it at runtime *before your first call to malloc, which might be in some C/C++
  library function*.
- have fun.
- to see debug output, define `DEBUG` - see `Makefile`. this will print tracing information
  for every `*alloc` call except the ones that are happening inside the tracing `printf`s.
- see source for details.
# recommended reading
the competition: https://sourceware.org/git/?p=glibc.git;a=blob;f=malloc/malloc.c;hb=HEAD
