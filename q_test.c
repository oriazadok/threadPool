#include <stdio.h>
#include "queue.h"


int main() {
    pQueue queue = createQueue();

    deQueue(queue);
    printf("is wmpty %d\n", isEmpyt(queue)); 

    enQueue(queue, "hello");
    enQueue(queue, "name");
    enQueue(queue, "is");
    enQueue(queue, "zadok");

    printf("Size of Queue is %d\n", size(queue)); 
    printQueue(queue);
    
    free(deQueue(queue));
    free(deQueue(queue));
    free(deQueue(queue));

    enQueue(queue, "walla");
    enQueue(queue, "cosomo");
    enQueue(queue, "blat");
    enQueue(queue, "hoder");
    printQueue(queue);

    printf("Size of Queue is 1 %d\n", size(queue)); 
    free(deQueue(queue));
    printf("Size of Queue is 2 %d\n", size(queue)); 
    free(deQueue(queue));
    printf("Size of Queue is 3 %d\n", size(queue)); 
    printf("is wmpty %d\n", isEmpyt(queue)); 
    free(deQueue(queue));
    printf("Size of Queue is 4 %d\n", size(queue)); 
    free(deQueue(queue));
    printf("Size of Queue is 5 %d\n", size(queue)); 
    free(deQueue(queue));
    printf("Size of Queue is 6 %d\n", size(queue)); 
    printQueue(queue);
    printf("Size of Queue is 7 %d\n", size(queue)); 

    printf("is wmpty %d\n", isEmpyt(queue)); 


    enQueue(queue, "wo");
    enQueue(queue, "ni");
    enQueue(queue, "ta");
    enQueue(queue, "men");

    printf("Size of Queue is %d\n", size(queue)); 
    printQueue(queue);

    printf("is wmpty %d\n", isEmpyt(queue)); 
    
    free(deQueue(queue));

    freeQueue(queue);

    return 0;
}