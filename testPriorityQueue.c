#include <stdio.h>
#include <stdlib.h>
#include "minpriorityqueue.h"

int main () {
    heap_t *h = create_heap(5);
    push_heap(h, 1, 3.4);
    push_heap(h, 1, 1.2);
    push_heap(h, 0, 6.02);
    push_heap(h, 3, 8.9);
    push_heap(h, 4, 0.1);
	push_heap(h, 3, 1.1);
	push_heap(h, 2, 0.0);
	
    int i;
    for (i = 0; i < 6; i++) {
		printf("\nprio [%d]:%f",i , get_priority(h, i));
    }
	i = 0;
	printf("\n");
	while (!isEmpty(h)) {
        printf("[%d]%d", i, extract_min(h));
		if (i++ != 4)
			printf(", ");
    }
	/*
	expected output :
	prio [0]:6.020000
	prio [1]:1.200000
	prio [2]:0.000000
	prio [3]:1.100000
	prio [4]:0.100000
	prio [5]:-1.000000
	[0]2, [1]4, [2]3, [3]1, [4]0
	*/
	
    return 0;
}