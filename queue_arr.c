#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*** implement a circular, generic-dataType queue with array. ***//

typedef unsigned char byte;

typedef struct queue{
    byte* data;
    int capacity; // to achieve circular queue, (capacity-1) is the actual capacity. 
    size_t typeSize;
    int front;
    int rear;
}queue;

int isEmpty(queue* myQueue){
    if (myQueue == NULL){
        printf("the queue points to NULL\n");
        exit(1);
    }
    if (myQueue->front == myQueue->rear)
        return 1;
    else
        return 0;
}

int isFull(queue* myQueue){
    if (myQueue == NULL){
        printf("the queue points to NULL\n");
        exit(1);
    }
    if ((myQueue->rear+1) % myQueue->capacity == myQueue->front)
        return 1;
    else
        return 0;
}

void enqueue(queue* myQueue, void* data){
    if (myQueue == NULL){
        printf("the queue points to NULL\n");
        exit(1);
    }
    if (isFull(myQueue))
        printf("the queue is full\n"); // enqueue failed
    else{
        memcpy((void*)(myQueue->data + (myQueue->rear*myQueue->typeSize)), (void*)data, myQueue->typeSize);
        myQueue->rear = (myQueue->rear+1) % myQueue->capacity;
        return; // enqueue succeed
    }
}

void* dequeue(queue* myQueue){
    // return front (index)
    if (myQueue == NULL){
        printf("the queue points to NULL\n");
        return NULL;
    }
    if (isEmpty(myQueue)){
        printf("the queue is empty\n");
        return NULL;
    }
    else{
        byte* front_data = malloc(sizeof(myQueue->typeSize));
        memcpy((void*)front_data, (void*)(myQueue->data + myQueue->typeSize*myQueue->front), myQueue->typeSize);
        myQueue->front = (myQueue->front+1) % myQueue->capacity;
        return front_data;
    }
}

int getLength(queue* myQueue){
    if (myQueue == NULL){
        printf("the queue points to NULL\n");
        return -1;
    }
    return ((myQueue->rear - myQueue->front + myQueue->capacity) % myQueue->capacity);
}

queue* queueDestroy(queue* myQueue){
    if (myQueue == NULL){
        printf("the queue points to NULL\n");
        return NULL;
    }
    free(myQueue->data);
    free(myQueue);
    return NULL;
}

queue* queueCreate(int capacity, size_t typeSize){
    queue* myQueue = malloc(sizeof(queue));
    if (myQueue == NULL){
        printf("failed to allocate memory to myQueue\n");
        return NULL;
    }
    myQueue->data = malloc(typeSize * (size_t)capacity);
    if (myQueue->data == NULL){
        printf("failed to allocate memory to myQueue->data\n");
        return NULL;
    }
    myQueue->capacity = capacity;
    myQueue->typeSize = typeSize;
    myQueue->front = 0;
    myQueue->rear = 0;
    return myQueue;
}

int main(int argc, char* argv[]){
    queue* myQueue = queueCreate(3, sizeof(int));
    int* n = malloc(sizeof(int));
    *n = 1;
    enqueue(myQueue, n);
    *n = 2;
    enqueue(myQueue, n);
    *n = 3;
    enqueue(myQueue, n);

    int* front;
    front = dequeue(myQueue);
    printf("deQueue: %d, len: %d\n", *front, getLength(myQueue));

    *n = 3;
    enqueue(myQueue, n);
    printf("len: %d\n", getLength(myQueue));
}
