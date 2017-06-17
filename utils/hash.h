#ifndef __HASH_H__
#define __HASH_H__

#define DEFAULT_INITIAL_CAPACITY (1 << 4)
#define MAXIMUM_CAPACITY         (1 << 30)
#define DEFAULT_LOAD_FACTOR      0.75

typedef struct hash_s {
	int     capacity;
	int     size;
	float   load_factor;
	int     (*cmp)(void *a, void *b);
	int     hash(void *s);
	void    *bucket;
} hash_t;

hash_t *hash_init();
hash_t *hash_init_with_cap(int capacity);
hash_t *hash_init_with_cap_and_fact(int capacity, float load_factor);

#endif
