#include "queue.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

queue *q;

void *routine_1(void *param)
{
	void *m = calloc(1024, 1);
	queue_push(q, m);
	while (1) {
		sleep(1);	
	}
	return NULL;
}

void *routine_2(void *param)
{

	void *m;

	while (1) {
		if (queue_pop(q, &m)) {
			printf("noting in queue.\n");
		} else {
			printf("get something from queue, free it.\n");
			free(m);	
		}
		sleep(1);
	}

}

int main()
{
	if ((q = queue_init()) == NULL)
		return -1;

	pthread_t t1, t2;

	pthread_create(&t1, NULL, routine_1, NULL);
	pthread_create(&t2, NULL, routine_2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}
