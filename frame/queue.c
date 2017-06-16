#include "frame.h"
#include "queue.h"
#include <stdio.h>

#define __FL__ __FILE__, __LINE__

queue *queue_init()
{
	queue *q = calloc(1, sizeof(queue));
	return q;
}

int queue_push(queue *q, void *item)
{
	if ((q->tail + 1) % QUEUE_SIZE == q->head) {
		return -1;
	}
	q->q[q->tail] = item;
	q->tail = (q->tail + 1) % QUEUE_SIZE; 
	return 0;
}

int queue_pop(queue *q, void **item)
{
	if (q->tail == q->head) {
		return -1;
	}

	*item = q->q[q->head];
	q->head = (q->head + 1) % QUEUE_SIZE;
	return 0;
}

void queue_destroy(queue *q)
{
	free(q);
}
