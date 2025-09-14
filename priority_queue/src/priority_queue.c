#include "priority_queue.h" 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static size_t getParent(size_t i) {
    return (i==0) ? 0 : (i - 1) / 2;
}

// returns the index of the left child
static size_t getChildLeft(size_t i) {
    return 2 * i + 1;
}

// returns the index of the right child
static size_t getChildRight(size_t i) {
    return 2 * i + 2;
}

static bool isPositionCorrect(priority_queue *q, size_t itemIndex) {
    if(itemIndex == 0) {
        return true; // If this is not the case, we've messed up somewhere else
    }
    size_t parentIndex = getParent(itemIndex);
    uint32_t parentPriority = q->buffer[parentIndex].priority;
    uint32_t childPriority = q->buffer[itemIndex].priority;
    if(parentPriority < childPriority) {
        return false;
    }
    if(parentPriority == childPriority) {
        return q->buffer[parentIndex].insertCount <=  q->buffer[itemIndex].insertCount;
    }
    return true;
}

static void swapWithParent(priority_queue *q, size_t i) {
    pq_item temp; 
    size_t parentIndex = getParent(i);
    memcpy(&temp, &q->buffer[i], sizeof(pq_item));
    memcpy(&q->buffer[i], &q->buffer[parentIndex], sizeof(pq_item));
    memcpy(&q->buffer[parentIndex], &temp, sizeof(pq_item));
}

static bool is_swap_required(priority_queue *q, size_t child, size_t parent) {
    if(child >= q->size) {
        return false;
    }
    if(q->buffer[child].priority == q->buffer[parent].priority) {
        return q->buffer[parent].insertCount > q->buffer[child].insertCount; 
    }

    return q->buffer[parent].priority < q->buffer[child].priority; 
}


static void max_heapify(priority_queue *q, size_t i) {
    size_t left = getChildLeft(i);
    size_t right = getChildRight(i);
    size_t swap = i;
    if(is_swap_required(q, left, swap)) {
        swap = left;
    }
    if(is_swap_required(q, right, swap)) {
        swap = right;
    }
    if(swap != i) {
        swapWithParent(q, swap);
        max_heapify(q, swap);
    }
}

void pq_enqueue(priority_queue *q, void *data, uint32_t priority) {
    if(q == NULL) {
        printf("Whoops, null pointer passed to pq_enqueue"); 
        return;
    }

    pq_item item = {
        .data = data, 
        .priority = priority, 
        .insertCount = ++q->insertCount
    };
    
    if(q->size == q->capacity) {
        printf("Queue has reached capacity.");
        return;
    }

    q->size++; 
    size_t insert_index = q->size - 1;
    memcpy(&q->buffer[insert_index], &item, sizeof(pq_item));

    while(is_swap_required(q, insert_index, getParent(insert_index))) {
        printf("insert swapping\n");
        swapWithParent(q, insert_index);
        insert_index = getParent(insert_index);
    }
}


void pq_dequeue(priority_queue *q, pq_item *item) {
    if(q->size <= 0) {
        printf("tried to dequeue from empty queue");
        return;
    }
    memcpy(item, &q->buffer[0], sizeof(pq_item));
    memcpy(&q->buffer[0], &q->buffer[q->size - 1], sizeof(pq_item));
    q->size--; 
    max_heapify(q, 0);
}


void pq_item_print(pq_item *item) {
    printf("priority: %u, insert precedence: %lu, %s\n", item->priority, item->insertCount, item->data);
}

void pq_print(priority_queue *q) {
    pq_item *item;
    // This function assumes that the data in the queue is a pointer to a string 
    for(size_t i = 0; i < q->size; i++) {
        item = &q->buffer[i];
        pq_item_print(&q->buffer[i]);
    }
}



