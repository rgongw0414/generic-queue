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
```bash
