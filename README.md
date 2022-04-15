# queue

#### how to use:
```bash
gcc queue_ll.c && ./a.out
```

#### testing input:
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
enQueue string element:  "hello"
enQueue string element:  "apple"
enQueue string element:  "grape"
deQueue a element from front
all element in queue, from rear to front:
grape
apple
myQueue points to NULL
len: -1
```
