# queue

## queue_arr.c (circular queue):
```bash
gcc queue_arr.c && ./a.out
```
#### testing function:
```c
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
``` 

#### output:
```
initializing a int queue with capacity 4
enQueue 1
enQueue 2
enQueue 3
deQueue: 1, queue length: 2
enQueue 4
-
current elements in queue (from front to rear):
2
3
4
```

## queue_ll.c:
```bash
gcc queue_ll.c && ./a.out
```
#### testing function:
```c
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
   printf("len: %d\n", get_length(myQueue));
 }
 ``` 
#### output:
```
initializng a queue with linked-list structure, string element:

enQueue string element:  "hello"

enQueue string element:  "apple"

enQueue string element:  "grape"

deQueue a element from front

-
all element in queue, from rear to front:

grape
apple
-
myQueue points to NULL
len: -1
```
