# Priority queue
In a typical queue follows the FIFO principle. First item in, first item out.
In a priority queue, the first value out of the queue depends on its 
'priority'. Elements with higher priority are retrieved/removed before elements 
with lower priority. Some priority queue's also maintain FIFO order for 
elements of the same priority (my priority queue implementation does that).

Priority queue's are often implemented as a binary heaps. 

Binary heaps are specific implementations of a binary tree, which follow the 
heap principle.   
    - Heap principle: Parent is always greater than or equal to child (max heap)
    OR parent is always less than or equal to child (min heap)  
    - Binary heaps are often implemented using an array. The root is the first 
    element of the array. To calculate the child of a given node, you can use 
    the following equations: 
        - left_node = 2 * i + 1
        - right_node = 2 * i + 2
        - parent = (i-1)/2

