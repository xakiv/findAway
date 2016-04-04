#include <stdlib.h>
#include <stdio.h>
#include "minpriorityqueue.h"

heap_t *create_heap(int n) {
    heap_t *h = calloc(1, sizeof (heap_t));
    h->data = calloc(n + 1, sizeof (int));
    h->prio = calloc(n + 1, sizeof (float));
    h->index = calloc(n, sizeof (int));
	h->size = n;
    return h;
}

int min(heap_t *h, int i, int j, int k) {
    int m = i;
    if (j <= h->len && h->prio[j] < h->prio[m])
        m = j;
    if (k <= h->len && h->prio[k] < h->prio[m])
        m = k;
    return m;
}

float get_priority(heap_t *h, int v)
{
	if(h->index[v] && h->data[h->index[v]] == v)
		return h->prio[h->index[v]];
	else
		return -1.0f;
}

bool is_in(heap_t *h, int v)
{
	return h->index[v] && h->data[h->index[v]] == v;
}
 
void push_heap(heap_t *h, int v, float p) {
	
	int i = 0;
	if(h->index[v])
		i = h->index[v];
	else
		i = ++h->len;

    int j = i / 2;
    while (i > 1) {
        if (h->prio[j] < p)
            break;
        h->data[i] = h->data[j];
        h->prio[i] = h->prio[j];
        h->index[h->data[i]] = i;
        i = j;
        j = j / 2;
    }
    h->data[i] = v;
    h->prio[i] = p;
    h->index[v] = i;
}
 
int extract_min(heap_t *h) {
    int v = h->data[1];
    h->data[1] = h->data[h->len];
    h->prio[1] = h->prio[h->len];
    h->index[h->data[1]] = 1;
    h->len--;
    int i = 1;
    while (1) {
        int j = min(h, i, 2 * i, 2 * i + 1);
        if (j == i)
            break;
        h->data[i] = h->data[j];
        h->prio[i] = h->prio[j];
        h->index[h->data[i]] = i;
        i = j;
    }
    h->data[i] = h->data[h->len + 1];
    h->prio[i] = h->prio[h->len + 1];
    h->index[h->data[i]] = i;
	if (h->len <= 0)
	{
		int k = 0;
		for(k=0;k < h->size;k++)
		{
			h->index[k] = 0;
		}
	}	
    return v;
}

bool isEmpty(heap_t *h)
{
	return h->len <= 0;
}
