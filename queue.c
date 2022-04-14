#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

// implement by array
typedef struct queue{
    byte* data;
    int capacity;
    size_t typeSize;
    int front;
    int rear;
}queue;


void enqueue(queue* myQueue, void* data);

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
    myQueue->front = 0;
    myQueue->rear = 0;
    return myQueue;
}

int main(int argc, char* argv[]){
    queue* myQueue = queueCreate(3, sizeof(int));

}
