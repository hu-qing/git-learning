#include "hash.h"
#include <stdlib.h>

hash_t *hash_init()
{
	hash_t *h = calloc(1, sizeof(hash_t));


	return h;
}
