#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *heap_base = NULL;

typedef struct heap_block_t {
    size_t size;
    struct heap_block_t *next;
    int free;
} heap_block;

typedef struct point_t {
    int x;
    int y;
} point; 

void *balloc(size_t size);
heap_block *find_free_block(heap_block **last, size_t size);

int main() {
    point *p1 = balloc(sizeof(point));

    p1->x = 5;
    p1->y = -5;

    printf("(%d, %d)\n", p1->x, p1->y);

    return 0;
}

heap_block *find_free_block(heap_block **last, size_t size) {
    heap_block *current = heap_base;
    
    while (current != NULL && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    
    return current;
}

heap_block *request_space(heap_block* last, size_t size) {
    heap_block *block = sbrk(0);
    block = sbrk(2000);
    void *request = (void *) sbrk(size + sizeof(heap_block) );
    
    if (request == (void*) -1) {
        return NULL;
    }

    if(last != NULL) {
        last->next = block;
    }
    
    block->size = size;
    block->next = NULL;
    block->free = 0;
    
    return block;
}

void *balloc(size_t size) {
    heap_block *block;

    if(size <= 0) {
        return NULL;
    }

    if(heap_base == NULL) {
        block = request_space(NULL, size);

        if(block == NULL) {
            return NULL;
        }

        heap_base = block;
    } else {
        
    }
}

