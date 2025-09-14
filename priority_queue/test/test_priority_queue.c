#include "unity.h"
#include "priority_queue.h"
#include "stdio.h"
#include "string.h"

void test_enqueue_dequeue(void); 

DECLARE_PRIORITY_QUEUE(my_queue, 256);

void test_enqueue_dequeue(void) {
    // This is a very basic test/demo
    pq_enqueue(&my_queue, "a", 9);
    pq_enqueue(&my_queue, "b", 9);
    pq_enqueue(&my_queue, "goodbye", 2);
    pq_enqueue(&my_queue, "test", 11);
    pq_enqueue(&my_queue, "world", 1000);
    pq_enqueue(&my_queue, "hello", 10000);
    pq_enqueue(&my_queue, "c", 9);
    pq_enqueue(&my_queue, "d", 9);

    printf("Now dequeueing and printing each item one by one\n\n"); 
    pq_item prev_item = {.priority = ~0, .insertCount = 0};
    pq_item test_item;
    TEST_ASSERT_TRUE(0);
    while(my_queue.size >0) {
        pq_dequeue(&my_queue, &test_item);
        pq_item_print(&test_item); 

        TEST_ASSERT_GREATER_OR_EQUAL(test_item.priority, prev_item.priority);
        if(prev_item.priority == test_item.priority) {

            TEST_ASSERT_LESS_THAN(test_item.insertCount, prev_item.insertCount);
        }

        memcpy(&prev_item, &test_item, sizeof(prev_item));
    }
}

