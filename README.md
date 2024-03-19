# Heap Management System

The Heap Management System is a program implemented in C to manage dynamic memory allocation using a custom heap management scheme. It provides functionalities to allocate and free memory blocks, ensuring efficient memory utilization and optimization.

## Overview

Memory management is a critical aspect of software development, especially in systems programming where efficient utilization of resources is essential. The Heap Management System offers a custom solution for managing memory allocation and deallocation, with a focus on optimizing memory usage and minimizing fragmentation.

## Key Features

### 1. Memory Allocation (`myAlloc`)

- **Function:** `void *myAlloc(size_t ReqSize)`
  - **Description:** Allocates a memory block of the specified size from the heap. The function searches for a free block that can accommodate the requested size. If a suitable block is found, it allocates the block and returns a pointer to the allocated memory. If necessary, it splits larger blocks to fulfill the allocation request, ensuring efficient memory utilization.

### 2. Memory Deallocation (`myFree`)

- **Function:** `void myFree(void *toFree)`
  - **Description:** Frees the memory block pointed to by the given pointer. The function merges adjacent free blocks to prevent fragmentation and optimize memory usage. If the freed block is adjacent to the free list, it merges the blocks to form larger contiguous free space, improving memory allocation efficiency.

### 3. Heap Initialization (`Initialize_Heap`)

- **Function:** `void Initialize_Heap()`
  - **Description:** Initializes the heap by setting up the free list and allocating the initial heap space. The function ensures that the heap is ready for memory allocation and deallocation operations. It initializes the free list with the entire heap space, indicating that initially, the entire heap is available for allocation.

### 4. Block Splitting (`splitBlock`)

- **Function:** `MetaData *splitBlock(MetaData *ptr, size_t ReqSize)`
  - **Description:** Splits a memory block into two blocks, with one block allocated and the other remaining as free space. The function is invoked when the requested memory size is smaller than the available block size. It splits the block into two parts, allocating one part for the requested memory and keeping the remaining part as a free block for future allocations.

### 5. Free List Management

- **Function:** `void printFreeList()`
  - **Description:** Prints the current state of the free list, displaying the sizes of free memory blocks. The function provides visibility into the available memory space and helps in understanding memory utilization. By examining the free list, developers can identify patterns of memory allocation and fragmentation, allowing for optimization strategies.

## Usage

1. **Initialization**: Call the `Initialize_Heap` function to initialize the heap before performing memory allocation or deallocation operations. This step ensures that the heap is properly set up for memory management.

2. **Memory Allocation**: Use the `myAlloc` function to dynamically allocate memory blocks as needed. Specify the size of the memory block required as an argument to the function. The function will allocate a suitable block from the heap and return a pointer to the allocated memory.

3. **Memory Deallocation**: When memory blocks are no longer needed, call the `myFree` function to release the allocated memory. Pass the pointer to the memory block to be freed as an argument to the function. The function will merge adjacent free blocks to optimize memory usage and prevent fragmentation.

4. **Monitoring**: Utilize the `printFreeList` function to monitor the state of the free list and track memory fragmentation. By examining the free list periodically, developers can identify opportunities for optimization and improve memory management efficiency.

## Example

```c
#include <stdio.h>

int main() {
    // Initialize the heap
    Initialize_Heap();

    // Allocate memory blocks
    int *a = (int *)myAlloc(sizeof(int));
    int *b = (int *)myAlloc(sizeof(int));
    printFreeList();

    // Free memory block 'a'
    myFree(a);

    // Allocate a character array
    char *s = (char *)myAlloc(sizeof(char) * 20);
    printFreeList();

    // Free memory block 's'
    myFree(s);
    printFreeList();

    return 0;
}
```

## Dependencies

- This project requires a compatible C compiler to build and execute.

## Contributions

Contributions to the Flight Management System project are welcome! Whether it's bug fixes, feature enhancements, or documentation improvements, feel free to contribute to make this project even better.
