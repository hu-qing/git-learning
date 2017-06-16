#include "thread.h"
#include <stdlib.h>

int main()
{
	thread_pool *tp = thread_pool_init();	

	tp->run();
	tp->join();

	free(tp);

	return 0;
}
