#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	queue *q = queue_init();
	if (q == NULL)
		return -1;

	char a = 'a';
	char b = 'b';
	queue_push(q, (void *)&a);
	queue_push(q, (void *)&b);

	printf("head[%d] tail[%d].\n", q->head, q->tail);
	char *c;
	char *d;
	queue_pop(q, (void **)&c);
	queue_pop(q, (void **)&d);

	printf("head[%d] tail[%d] c[%c] d[%c].\n", q->head, q->tail, *c, *d);

	queue_destroy(q);

	return 0;
	
}
