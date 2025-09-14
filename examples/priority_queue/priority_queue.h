#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <time.h>
#include <stdint.h>

typedef struct {
    uint64_t insertCount; 
    uint32_t priority;
    char *data;
} pq_item;

typedef struct {
    pq_item * buffer;
    size_t size;
    size_t capacity;
    uint64_t insertCount; 
} priority_queue;

#define DECLARE_PRIORITY_QUEUE(q_name, q_size) \
    static pq_item q_name##_buffer[q_size] = {0}; \
    priority_queue q_name = { \
        .buffer = q_name##_buffer,  \
        .size = 0, \
        .capacity = q_size, \
    }

void pq_enqueue(priority_queue *q, void *data, uint32_t priority); 
void pq_dequeue(priority_queue *q, pq_item *item);
void pq_print(priority_queue *q); 
void pq_item_print(pq_item *item); 

#endif
