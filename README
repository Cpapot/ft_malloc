# ft_malloc

A custom implementation of memory allocation functions (`malloc`, `realloc`, `free`) with debugging features.

## Core Functions

### `void *malloc(size_t size)`

Allocates memory of the specified size.

- Returns a pointer to the allocated memory
- Memory is not initialized (contains garbage values)
- If size is 0, returns NULL
- Memory is allocated in different zones based on size:
  - TINY: For allocations <= n bytes
  - SMALL: For allocations <= m bytes
  - LARGE: For allocations > m bytes

### `void free(void *ptr)`

Releases memory previously allocated by `malloc` or `realloc`.

- If ptr is NULL, no operation is performed
- Ensures proper cleanup of memory blocks based on zone type
- Can automatically clean freed memory when `MALLOC_CLEAN_FREED_MEMORY` is enabled

### `void *realloc(void *ptr, size_t size)`

Changes the size of a previously allocated memory block.

- If ptr is NULL, behaves like `malloc(size)`
- If size is 0, behaves like `free(ptr)` and returns NULL
- If the new size fits in the current allocation zone, may reuse the same memory block
- Otherwise, allocates new memory, copies data from the old block, and frees the old block
- Returns a pointer to the new memory block, or NULL if the allocation fails

## Memory Visualization Functions

### `void show_alloc_mem()`

Displays information about allocated memory blocks:
- Location (memory address)
- Size
- Zone type (TINY, SMALL, LARGE)
- Total bytes allocated

### `void show_alloc_mem_ex()`

Extended version of `show_alloc_mem()` that additionally shows a hexadecimal dump of the memory content.

## Debug Environment Variables

Set these environment variables to enable various debugging features:

### `MALLOC_SHOW_LEAKS`

Displays information about memory leaks at program exit, showing memory blocks that haven't been freed.

```bash
export MALLOC_SHOW_LEAKS=1
```

### `MALLOC_FREE_LEAKS`

Automatically frees all memory leaks at program exit.

```bash
export MALLOC_SHOW_LEAKS=1
```

### `MALLOC_SHOW_ALLOCATE`

Displays a message each time memory is allocated, showing:
- Zone type
- Memory address
- Block size

```bash
export MALLOC_SHOW_ALLOCATE=1
```

### `MALLOC_SHOW_FREE`

Displays a message each time memory is freed, showing:
- Zone type
- Memory address
- Size of freed memory

```bash
export MALLOC_SHOW_FREE=1
```

### `MALLOC_SHOW_MUNMAP`

Displays a message when a memory block is unmapped (returned to the system).

```bash
export MALLOC_SHOW_MUNMAP=1
```

### `MALLOC_SHOW_HEXADUMP`

Enables hexadecimal display of memory content in debug outputs.

```bash
export MALLOC_SHOW_HEXADUMP=1
```

### `MALLOC_CLEAN_FREED_MEMORY`

Zeroes out memory blocks when they are freed. This can help detect use-after-free bugs.

```bash
export MALLOC_CLEAN_FREED_MEMORY=1
```

## Running Tests

The project includes several test files that verify the functionality of the implementation:

- `tiny_and_small_tests.c`: Tests for TINY and SMALL allocations
- `large_tests.c`: Tests for LARGE allocations
- `libft_tests.c`: Tests for library functions using the malloc implementation
You can run the tests using the provided Makefile.

### Building Tests

```bash
make test
```

## Usage

After building, link your program with the custom malloc library:

```bash
gcc -o your_program your_program.c -L. -lft_malloc
```

Or use `LD_PRELOAD` to use the custom malloc with any program:

```bash
LD_PRELOAD=./libft_malloc.so your_program
```

To enable debugging:

```bash
MALLOC_SHOW_LEAKS=1 MALLOC_SHOW_ALLOCATE=1 ./your_program
```
