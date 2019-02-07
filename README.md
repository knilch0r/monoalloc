# monoalloc
monotonic allocator replacement for `malloc()`.
# caveats
not thread-safe. probably broken. for educational purposes only. NO WARRANTY. 'AS-IS'.
# how to use
- set `LD_LIBRARY_PATH` to the location of `libmonoalloc.so`, and either
  - link your applications against `libmonoalloc.so`, see `Makefile` or
  - use `LD_PRELOAD=libmonoalloc.so` for an existing application that has `malloc` linked
    in dynamically.
- set `monoalloc_size` to the size you want to allocate - either by changing the code, or
  by setting it at runtime *before your first call to malloc, which might be in some C/C++
  library function*.
- have fun.
- to see debug output, define `DEBUG` - see `Makefile`. this will print tracing information
  for every `\*alloc` call except the ones that are happening inside the tracing `printf`s.
- see source for details.
