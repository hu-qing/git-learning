#include "hash.h"
#include <stdlib.h>
#include <string.h>

static int __int_match(const void *a, const void *b)
{
    return *(long long *)a == *(long long *)b;
}

static int __str_match(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b);
}

static unsigned int __str_hash(const void *key)
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

static unsigned int __int_hash(const void *key)
{
	return *(int *)key;
}

static unsigned int __ll_hash(const void *key)
{
    long long k = *(long long *)key;
	return k ^ (k >> 32);
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

static void __resize(hash_t *h)
{
    
}

hash_t *hash_init(int key_type, int val_type)
{
	return hash_init_with_cap_and_fact(key_type, val_type, DEFAULT_INITIAL_CAPACITY, DEFAULT_LOAD_FACTOR);
}

hash_t *hash_init_with_cap(int key_type, int val_type, int capacity)
{
	return hash_init_with_cap_and_fact(key_type, val_type, capacity, DEFAULT_LOAD_FACTOR);
}

hash_t *hash_init_with_cap_and_fact(int key_type, int val_type, int capacity, float load_factor)
{
	if (capacity < 0 || load_factor <= 0)
		return NULL;
	
	hash_t *h = NULL;
    if ((h = calloc(1, sizeof(hash_t))) == NULL)
        return NULL;
    

    switch (key_type) {
    case L:
    case LL:
	    h->hash = __ll_hash;
        h->match = __int_match;
        break;
    case INT:
	    h->hash = __int_hash;
        h->match = __int_match;
        break;
    case STR:
	    h->hash = __str_hash;
        h->match = __str_match;
        break;
    default:
        free(h);
        return NULL;
    }

    switch (val_type) { /* check if the val_type in enum */
    case L:
    case LL:
    case INT:
    case STR:
    case DOUBLE:
    case POINTER:
        break;
    default:
        free(h);
        return NULL;
    }

    h->key_type = key_type;
    h->val_type = val_type;
    h->init_capacity = capacity > MAXIMUM_CAPACITY ? MAXIMUM_CAPACITY : capacity;
	h->threshold = __table_size(capacity);
	h->load_factor = load_factor;
    h->size = 0;
	h->buckets = calloc(h->threshold, sizeof(hash_item_t *));

	return h;
}

void list_destroy(hash_item_t *l)
{
    hash_item_t *p1, *p2;
    p1 = l;
    while (p1) {
        free(p1->key);
        free(p1->val);

        p2 = p1->next;
        free(p1);
        p1 = p2; 
    }
}

void hash_destroy(hash_t *h)
{
    int i;
    for (i = 0; i < h->threshold; ++i) {
        if (h->buckets[i] != NULL) 
            list_destroy(h->buckets[i]);
    }
    free(h->buckets);
    free(h);
}

hash_item_t *__find(void *key, hash_item_t *head, int (*match)(void *a, void *b))
{
    hash_item_t *p = head;
    while (p) {
        if (!match(key, p->key))
            return p;
        p = p->next;
    }
    return NULL;
}

void *__calloc_for(int type, void *k)
{
    void *r;

    switch (type) {
    case INT: 
        r = calloc(1, sizeof(int));
        *(int *)r = *(int *)k;
        return r;
    case L: 
        r = calloc(1, sizeof(long));
        *(long *)r = *(long *)k;
        return r;
    case LL: 
        r = calloc(1, sizeof(long long));
        *(long long *)r = *(long long *)k;
        return r;
    case STR: 
        r = calloc(1, strlen((char *)k) + 1);
        strcpy((char *)r, (char *)k);
        return r;
    case DOUBLE: 
        r = calloc(1, sizeof(double));
        *(double *)r = *(double *)k;
        return r;
    case POINTER:
        return r;
    }
    return NULL;
}

int  hash_put(hash_t *h, void *key, void *val)
{
    unsigned int hash = h->hash(key);
    pos = hash & (h->threshold - 1);

    if (__find(key, h->buckets[pos], h->match) != NULL)
        return -1;

    hash_item_t *hi = calloc(1, sizeof(hash_item_t));
    void *newkey = __calloc_for(h->key_type, key);
    void *newval = __calloc_for(h->val_type, val);
    hi->key = newkey;
    hi->val = newval;
    hi->next = h->buckets[pos];
    h->buckets[pos] = hi;

    if (++(h->size) > threshold)
        __resize(h);

    return 0;
}

int  hash_replace(hash_t *h, void *key, void *val)
{
    return 0;
}

int  hash_get(hash_t *h, void *key, void **val)
{
    return 0;
}
