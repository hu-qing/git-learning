#include "hash.h"
#include <stdlib.h>

static unsigned int __hash(void *in)
{
	return 0;
}

hash_t *hash_init()
{
	hash_t *h = calloc(1, sizeof(hash_t));

	h->bucket_size = DEFAULT_HASH_BUCKET_SIZE;
	h->bucket = calloc(DEFAULT_HASH_BUCKET_SIZE, sizeof(void *));
	h->hash = __hash;

	return h;
}
