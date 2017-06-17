#include "hash.h"
#include <stdlib.h>

static unsigned int __hash(void *key)
{
	return 0;
}

static unsigned int __str_hash(const char *key)
{
	const char     *ptr;
	unsigned int   val;

	val = 0;
	ptr = key;
	while (*ptr != '\0') {
		unsigned int tmp;
		val = (val << 4) + (*ptr);
		if (tmp = (val & 0xf0000000)) {
			val = val ^(tmp >> 24);
			val = val ^ tmp;
		}
		ptr++;
	}
	
	return val;
}

static unsigned int __int_hash(const int key)
{
	h = capacity * (key * 0.618 mod/*取小数部分*/ 1);

	// such as: 2000 * (6341 * 0.618 mod 1) = 2000 * (3918.738 mod 1) = 2000 * 0.738 = 1476
}

static int __table_size_for(int cap) {
        int n = cap - 1;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
}

hash_t *hash_init()
{
	return hash_init_with_cap_and_fact(DEFAULT_INITIAL_CAPACITY, DEFAULT_LOAD_FACTOR);
}

hash_t *hash_init_with_cap(int capacity)
{
	return hash_init_with_cap_and_fact(capacity, DEFAULT_LOAD_FACTOR);
}

hash_t *hash_init_with_cap_and_fact(int capacity, float load_factor)
{
	if (capacity < 0 || load_factor <= 0)
		return NULL;
	
	hash_t *h = calloc(1, sizeof(hash_t));

	h->capacity = capacity > MAXIMUM_CAPACITY ? MAXIMUM_CAPACITY : __table_size(capacity);
	h->factor = load_factor;
	h->hash = __hash;
	h->bucket = calloc(capacity, sizeof(void *));

	return h;
}
