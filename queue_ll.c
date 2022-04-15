#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*** implement a generic-dataType queue, with linked-list structure. ***//

typedef unsigned char byte; // assumption: unsigned char takes 1 byte.

typedef struct node{
    byte* data;
    struct node* next;
}node;

typedef struct queue{
    node* front;
    node* rear;
    size_t elemSize;
}queue;

int is_empty(queue* myQueue){
    if (myQueue->front == NULL){
        //printf("the queue is empty\n");
        return 1;
    }
    else
        return 0;
}

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
    if (is_empty(myQueue)){
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

node* get_front(queue* myQueue){
    if (is_empty(myQueue)){
        //printf("the queue is empty\n");
        return NULL;
    }
    else{
        return myQueue->front;
    }
}

node* get_rear(queue* myQueue){
    if (is_empty(myQueue)){
        //printf("the queue is empty\n");
        return NULL;
    }
    else{
        return myQueue->rear;
    }
}

void print_int(node* myNode){
    printf("%d\n", *(int*)myNode->data);
}

void print_float(node* myNode){
    printf("%f\n", *(float*)myNode->data);
}

void print_double(node* myNode){
    printf("%lf\n", *(double*)myNode->data);
}

void print_char(node* myNode){
    printf("%c\n", *(char*)myNode->data);
}

void print_string(node* myNode){
    printf("%s\n", (char*)myNode->data);
}

void traverse(queue* myQueue, void(*func)(node* myNode)){
    // for each node, from rear to front, visit it with func.
    if (is_empty(myQueue)){
        printf("queue is empty\n");
        return;
    }
    node* myNode = myQueue->rear;
    if (myQueue->front == NULL) return;
    node* next;
    while (myNode != NULL){
        next = myNode->next;
        func(myNode);
        myNode = next;
    }
}

void nodeDestroy(node* myNode){ // if just want to destroy one node, when function returned, remember to set the node to NULL, or realloc() mem space to it.
    if (myNode == NULL || myNode->data == NULL) return;
    free(myNode->data);
    free(myNode);
    myNode->data = NULL; // *** always remember to set pointer to NULL, after free it's memory space; ***
    myNode->next = NULL; // *** since after free'ing it, the pointed content would be set to some default value, ***
    myNode = NULL;       // *** otherwise, it may lead to ERROR. ***
}

void queueClear(queue* myQueue){
    // destroy (free) each node in myQueue
    if (myQueue == NULL) return;
    if (is_empty(myQueue)) return;
    // destroy node from rear to front (rear->...->front->NULL)
    traverse(myQueue, nodeDestroy);
}

queue* queueDestroy(queue* myQueue){
    // destroy (free) myQueue
    if (myQueue == NULL) return NULL;
    queueClear(myQueue);
    free(myQueue);
    myQueue->rear = myQueue->front = NULL; // this does modify rear's & front's pointer value, because this line does reach myQueue's actual value;
    myQueue = NULL; // instead, in this line, since myQueue is merely a local variable, this line would not change myQueue in original scope,
    return myQueue; // so it should be returned to caller's scope.
}

void dequeue(queue* myQueue){
    if (is_empty(myQueue)){
        printf("queue is empty\n");
        return;
    }
    if (myQueue == NULL){
        printf("myQueue points to NULL\n");
        return;
    }
    if (myQueue->rear == myQueue->front){
        // only one node left in queue
        free(myQueue->rear->data);
        myQueue->rear = myQueue->front = NULL;
    }
    else{
        node* Node = myQueue->rear; 
        while (Node->next != myQueue->front) // traverse to the 2nd last node
            Node = Node->next;
        nodeDestroy(Node->next); // destroy front
        myQueue->front = Node; // point rear to the 2nd last node
        myQueue->front->next = NULL;
    }
}

int get_length(queue* myQueue){
    if (myQueue == NULL){
        printf("myQueue points to NULL\n");
        return -1;
    }
    node* myNode = myQueue->rear;
    if (myNode == NULL){ 
        printf("myQueue->rear points to NULL\n");
        return -1;
    }
    int len = 0;
    while (myNode != NULL){
        len++;
        myNode = myNode->next;
    }
    return len;
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
    // queue of string
   queue* myQueue = queueCreate(sizeof(char*));
   char* n = malloc(sizeof(char) * 10);
   enqueue(myQueue, "hello");
   n = "apple";
   enqueue(myQueue, n);
   n = "grape";
   enqueue(myQueue, n);
   dequeue(myQueue);
   traverse(myQueue, print_string);

   myQueue = queueDestroy(myQueue); // return NULL to the destroyed queue, so as to disable it's all function.
   /*if (myQueue == NULL) 
       printf("ffffffffffffffffff\n");*/
   printf("len: %d\n", get_length(myQueue));
/*
   // queue of char
   queue* myQueue = queueCreate(sizeof(char));
   char* n = malloc(sizeof(char));
   for (int i = 0; i < 5; i++){      
       *n = 'a' + i;
       enqueue(myQueue, n);
   }
   traverse(myQueue, print_char);*/
/*
   // queue of double
   queue* myQueue = queueCreate(sizeof(double));
   double* n = malloc(sizeof(double));
   for (int i = 0; i < 5; i++){      
       *n = (double)(i + 1);
       enqueue(myQueue, n);
   }
   traverse(myQueue, print_double);*/
}

