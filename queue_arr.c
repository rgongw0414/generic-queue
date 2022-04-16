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
        // enqueue succeed
        memcpy((void*)(myQueue->data + (myQueue->rear*myQueue->typeSize)), (void*)data, myQueue->typeSize);
        myQueue->rear = (myQueue->rear+1) % myQueue->capacity;
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
        void* front_data = (void*)(myQueue->data + myQueue->typeSize*myQueue->front);
        myQueue->front = (myQueue->front+1) % myQueue->capacity;
        return front_data;
    }
}

int getLength(queue* myQueue){
    if (myQueue == NULL){
        printf("the queue points to NULL\n");
        return -1;
    }
    // (a + b) % c = ((a%c) + (b%c)) % c
    return ((myQueue->rear - myQueue->front) + myQueue->capacity) % myQueue->capacity;
}

void traverse(queue* myQueue, void(*func)(queue* myQueue, int index)){
    if (myQueue == NULL){
        printf("the queue points to NULL\n");
        return;
    }
    int index = myQueue->front;
    while (index != myQueue->rear){
        func(myQueue, index);
        index = (index + 1) % myQueue->capacity;
    }
}

void queueClear(queue* myQueue){
    if (myQueue == NULL){
        printf("the queue points to NULL\n");
        return;
    }
    myQueue->rear = myQueue->front = 0;
    free(myQueue->data);
    myQueue->data = NULL;
}

queue* queueDestroy(queue* myQueue){
    if (myQueue == NULL){
        printf("the queue points to NULL\n");
        return NULL;
    }
    queueClear(myQueue);
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

void print_int(queue* myQueue, int index){
    printf("%d\n", ((int*)myQueue->data)[index]);
}

void print_char(queue* myQueue, int index){
    printf("%c\n", ((char*)myQueue->data)[index]);
}

void print_float(queue* myQueue, int index){
    printf("%f\n", ((float*)myQueue->data)[index]);
}

void print_double(queue* myQueue, int index){
    printf("%lf\n", ((double*)myQueue->data)[index]);
}

void print_string(queue* myQueue, int index){
    printf("%s\n", (char*)myQueue->data + myQueue->typeSize * (size_t)index);
}

int main(int argc, char* argv[]){
    int capacity = 3 + 1;
    queue* myQueue = queueCreate(capacity, sizeof(int));
    printf("initializing an int queue with capacity %d\n", capacity);
    int* n = malloc(sizeof(int));
    *n = 1;
    enqueue(myQueue, n);
    printf("enQueue %d\n", *n);

    *n = 2;
    enqueue(myQueue, n);
    printf("enQueue %d\n", *n);

    *n = 3;
    enqueue(myQueue, n);
    printf("enQueue %d\n", *n);

    int* front;
    front = dequeue(myQueue);
    printf("deQueue: %d, queue length: %d\n", *front, getLength(myQueue));

    *n = 4;
    enqueue(myQueue, n);
    printf("enQueue %d\n", *n);

    printf("-\ncurrent elements in queue (from front to rear):\n");
    traverse(myQueue, print_int);
}
