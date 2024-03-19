/* Write a program to implement heap management scheme.
Implement the ‘allocate’ and ‘free’ functions.
Ensure that adjacent free blocks are merged together. */

#include <stdio.h>
#define HEAPSIZE 1048576 // 1 MB data of heap

typedef struct MetaData
{
    size_t size;           // Available in the stdio.h, size_t is typdef unsigned int
    struct MetaData *next; // A next pointer to refer to the next Free block
} MetaData;

char Heap[HEAPSIZE];

MetaData *FreeList = (void *)Heap;

void Initialize_Heap()
{
    FreeList->size = HEAPSIZE - sizeof(MetaData);
    FreeList->next = NULL;
}

MetaData *splitBlock(MetaData *ptr, size_t ReqSize)
{
    MetaData *newBlock = (void *)((void *)ptr + sizeof(MetaData) + ReqSize);
    newBlock->size = ptr->size - ReqSize - sizeof(MetaData);
    return newBlock;
}

void *myAlloc(size_t ReqSize)
{
    MetaData *fit, *prev;
    fit = FreeList;
    prev = NULL;
    void *block;

    // traversing the FreeList until we find a block is >= the required size that is to be allocated according to the order request
    while (fit->size < ReqSize && fit->next != NULL)
    {
        prev = fit;
        fit = fit->next;
    }

    // if fit block's size is equal to the required size then allocate the block completely
    if ((fit->size >= ReqSize) && (fit->size <= ReqSize + sizeof(MetaData)))
    {
        if (fit == FreeList)
            FreeList = fit->next;
        else
            prev->next = fit->next;
        fit->next = NULL;
        fit++;
        block = (void *)fit;
    }
    // else if the fir block size is > req size then  we have to split the block into fit block and a new block
    else if (fit->size > (ReqSize + sizeof(MetaData)))
    {
        MetaData *newBlock = splitBlock(fit, ReqSize);
        newBlock->next = fit->next;
        if (fit == FreeList)
            FreeList = newBlock;
        else
            prev->next = newBlock;
        fit->next = NULL;
        fit->size = ReqSize;
        fit++;
        block = (void *)fit;
    }
    // else it implies that the heap is full and we need to return NULL as nothing can be assigned to it
    else
    {
        block = NULL;
    }
    return block;
}

void myFree(void *toFree)
{
    if (((void *)Heap <= toFree) && (toFree <= (void *)Heap + HEAPSIZE))
    {
        MetaData *block = toFree;
        block--;
        if (toFree < (void *)FreeList)
        {
            // If the block is right before the FreeList then we merge it with the FreeList and set FreeList to the block
            if (toFree + block->size == (void *)FreeList)
            {
                block->next = FreeList->next;
                block->size += sizeof(MetaData) + FreeList->size;
            }
            // else if the block is not right before the FreeList but prior to it then we create a link from block to FreeList and set FreeList to the block
            else
            {
                block->next = FreeList;
            }
            FreeList = block;
        }
        else
        {
            MetaData *ptr, *prev;
            ptr = FreeList;
            prev = NULL;

            while ((ptr != NULL) && ((void *)ptr < (void *)block))
            {
                prev = ptr;
                ptr = ptr->next;
            }

            // If the toFree block lies perfect between the prev and ptr blocks then we merge all 3 to form a single block and we update the MetaData of prev
            if (((void *)prev + sizeof(MetaData) + prev->size == (void *)block) && (toFree + block->size == (void *)ptr))
            {
                prev->next = ptr->next;
                prev->size += (2 * sizeof(MetaData)) + block->size + ptr->size;
            }
            // If the toFree block lies right after the prev but not right before the ptr then we merge the prev and block and update the data of prev
            else if ((void *)prev + sizeof(MetaData) + prev->size == (void *)block)
            {
                prev->size += sizeof(MetaData) + block->size;
            }
            // If the toFree block lies right before the ptr but not right after the prev then we merge the block and ptr and update the data of block
            else if (toFree + block->size == (void *)ptr)
            {
                block->next = ptr->next;
                block->size += sizeof(MetaData) + ptr->size;
                prev->next = block;
            }
            // Lastly if the block is neither right after prev nor right before ptr the we simply adjust the links of prev and block to make a space for block in between prev and ptr
            else
            {
                prev->next = block;
                block->next = ptr;
            }
        }
    }
    else
    {
        printf("Give a valid pointer which is a part of the Heap");
    }
}

void printFreeList()
{
    MetaData *ptr;
    int i = 1;
    ptr = FreeList;
    while (ptr != NULL)
    {
        printf("[Size %d: %d] ", i, ptr->size);
        i++;
        ptr = ptr->next;
    }
    printf("End\n");
}

void main()
{
    Initialize_Heap();
    int *a, *b, *c, *d;
    a = (int *)myAlloc(sizeof(int));
    b = (int *)myAlloc(sizeof(int));
    c = (int *)myAlloc(sizeof(int));
    d = (int *)myAlloc(sizeof(int));
    printf("abcd allocated: ");
    printFreeList();

    myFree(a);
    printf("a freed: ");
    printFreeList();

    myFree(d);
    printf("Freed: ");
    printFreeList();

    char *s;
    s = (char *)myAlloc(sizeof(char) * 20);
    printf("char allocated: ");
    printFreeList();
    myFree(s);
    printf("s freed: ");
    printFreeList();
}