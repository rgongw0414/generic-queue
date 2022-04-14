#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef unsigned char byte;


typedef struct node{
    byte* data;
    struct node* next;
}node;


typedef struct queue{
    node* front;
    node* rear;
    size_t elemSize;
}queue;

node* nodeCreate(size_t elemSize){
    node* newNode = malloc(sizeof(struct node));
    if (newNode == NULL){
        printf("failed to allocate memory to newNode\n");
        exit(1);
    }
    newNode->data = malloc(sizeof(elemSize));
    if (newNode->data == NULL){
        printf("failed to allocate memory to newNode->data\n");
        exit(1);
    }
    newNode->next = NULL;
    return newNode;
}

void enqueue(queue* myQueue, void* data){
    node* newNode = nodeCreate(myQueue->elemSize);
    memcpy((void*)newNode->data, data, myQueue->elemSize);
    if (myQueue->rear == NULL){
        // rear(front)->NULL
        newNode->next = NULL;
        myQueue->rear = myQueue->front = newNode;
    }
    else{ 
        // newNode(new_rear)->(original)rear->front->NULL
        // ...
        // newNode(new_rear)->(original)rear->...->front->NULL
        newNode->next = myQueue->rear;
        myQueue->rear = newNode;
    }
}

void dequeue(queue* myQueue){
    if (myQueue->rear == myQueue->front){
        printf("queue is empty\n");
        return;
    }
    if (myQueue == NULL){
        printf("myQueue points to NULL\n");
        exit(1);
    }
    node* Node = myQueue->rear;
    while(Node->next != myQueue->front){
        Node = Node->next;
    }
    free(Node->next->data);
    Node->next->next = NULL;
    free(Node->next);
    myQueue->front = Node;
}

queue* queueCreate(size_t elemSize){
   queue* myQueue = malloc(sizeof(queue));
   if (myQueue == NULL){
       printf("failed to allocate memory to myQueue\n");
       exit(1);
   }
   myQueue->front = NULL;
   myQueue->rear = NULL;
   myQueue->elemSize = elemSize;
   return myQueue;
}

int main(int argc, char* argv[]){
   queue* myQueue = queueCreate(sizeof(int));
   int* n = malloc(sizeof(int));
   for (int i = 0; i < 3; i++){      
       *n = i + 1;
       enqueue(myQueue, n);
   }
   printf("front: %d\n", *((int*)myQueue->front->data));
   dequeue(myQueue);
   printf("front: %d\n", *((int*)myQueue->front->data));
   dequeue(myQueue);
   printf("front: %d\n", *((int*)myQueue->front->data));
   dequeue(myQueue);
   printf("front: %d\n", *((int*)myQueue->front->data));
}

