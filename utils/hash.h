#ifndef __HASH_H__
#define __HASH_H__

#define DEFAULT_INITIAL_CAPACITY (1 << 4)
#define MAXIMUM_CAPACITY         (1 << 30)
#define DEFAULT_LOAD_FACTOR      0.75

typedef struct hash_item_s {
    void               *key;
    void               *val;
	unsigned int       hash;
    struct hash_item_s *next;
} hash_item_t;

typedef struct hash_s {
    int     key_type;
    int     val_type;
	int     init_capacity;
    int     threshold;
	float   load_factor;
	int     size;
	int     (*match)(const void *a, const void *b);
	unsigned int  (*hash)(const void *s);
	hash_item_t   **buckets;
} hash_t;

enum item_type{LL, INT, L, DOUBLE, STR, POINTER};

hash_t *hash_init(int key_type, int val_type);
hash_t *hash_init_with_cap(int key_type, int val_type, int capacity);
hash_t *hash_init_with_cap_and_fact(int key_type, int val_type, int capacity, float load_factor);

void hash_destroy(hash_t *h);
int  hash_put(hash_t *h, void *key, void *val);
int  hash_replace(hash_t *h, void *key, void *val);
int  hash_get(hash_t *h, void *key, void **val);

#endif
