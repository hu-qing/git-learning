#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>

#define DEFAULT_INITIAL_CAPACITY (1 << 4)
#define MAXIMUM_CAPACITY         (1 << 30)

#define DEBUG
#include <stdio.h>

typedef struct hash_pair_s {
    void               *key;
    void               *val;
	unsigned int       hash;
    struct hash_pair_s *next;
} hash_pair_t;

typedef struct hash_s {
    int     key_type;
    int     val_type;
	size_t  init_capacity;
    size_t  threshold;
	size_t  size;
	int     (*match)(const void *a, const void *b);
	unsigned int  (*hash)(const void *s);
	hash_pair_t   **buckets;
} hash_t;

enum item_type{LL, INT, L, DOUBLE, STR, POINTER};

hash_t *hash_init(int key_type, int val_type);
hash_t *hash_init_with_cap(int key_type, int val_type, size_t capacity);

void hash_destroy(hash_t *h);
int  hash_put(hash_t *h, void *key, void *val);
int  hash_get(hash_t *h, void *key, void **val);
void **hash_keys(hash_t *h, size_t *size);
int  hash_replace(hash_t *h, void *key, void *val);
size_t  hash_count(hash_t *h);
void hash_destroy_keys(void **keys);

#endif
