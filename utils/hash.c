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
		if ((tmp = (val & 0xf0000000))) {
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

static void __list_destroy(hash_pair_t *l)
{
    hash_pair_t *p1, *p2;
    p1 = l;
    while (p1) {
        free(p1->key);
        free(p1->val);

        p2 = p1->next;
        free(p1);
        p1 = p2; 
    }
}

static void __buckets_destroy(hash_pair_t **b, size_t thr)
{
	size_t i;

    for (i = 0; i < thr; ++i) {
        if (b[i] != NULL) 
            __list_destroy(b[i]);
    }

    free(b);
}

hash_pair_t *__find(void *key, hash_pair_t *head, int (*match)(const void *a, const void *b))
{
    hash_pair_t *p = head;
    while (p) {
        if (!match(key, p->key))
            return p;
        p = p->next;
    }
    return NULL;
}

static void __resize(hash_t *h)
{
    if (h->threshold >= MAXIMUM_CAPACITY)
        return;

    size_t old_threshold = h->threshold;
    size_t new_threshold = h->threshold << 1;

    hash_pair_t **new_buckets = (hash_pair_t **)calloc(new_threshold, sizeof(hash_pair_t *));

    size_t i;
    hash_pair_t *p;
    for (i = 0; i < old_threshold; ++i) {
        if ((p = h->buckets[i]) != NULL) {

            if (p->next == NULL) {
                new_buckets[p->hash & (new_threshold - 1)] = p;
            } else {
                hash_pair_t *next;
                hash_pair_t *low_head = NULL, *low_tail = NULL;
                hash_pair_t *high_head = NULL, *high_tail = NULL;

                do {
                    next = p->next;

                    if ((p->hash & old_threshold) == 0) {
                        if (low_tail == NULL)
                            low_head = p;
                        else
                            low_tail->next = p;
                        low_tail = p;
                    } else {
                        if (high_tail == NULL) 
                                high_head = p;
                        else
                            high_tail->next = p;
                        high_tail = p;
                    }
                } while ((p = next) != NULL);
                if (low_tail != NULL) {
                    low_tail->next = NULL; 
                    new_buckets[i] = low_head;
                }
                if (high_tail != NULL) {
                    high_tail->next = NULL; 
                    new_buckets[i + old_threshold] = high_head;
                }
            }
        }
    }
    free(h->buckets);
    h->buckets = new_buckets;
    h->threshold = new_threshold;
}

hash_t *hash_init(int key_type, int val_type)
{
	return hash_init_with_cap(key_type, val_type, DEFAULT_INITIAL_CAPACITY);
}

hash_t *hash_init_with_cap(int key_type, int val_type, size_t capacity)
{
	if (capacity < 0)
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
	h->threshold = __table_size_for(h->init_capacity);
    h->size = 0;
	h->buckets = (hash_pair_t **)calloc(h->threshold, sizeof(hash_pair_t *));

	return h;
}

void hash_destroy(hash_t *h)
{
	__buckets_destroy(h->buckets, h->threshold);

    free(h);
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
        return k;
    }
    return NULL;
}

unsigned int __hash(unsigned int hash)
{
    return hash ^ (hash >> 16);
}

int  hash_put(hash_t *h, void *key, void *val)
{
    unsigned int hash = key == NULL ? 0 : __hash(h->hash(key));
    unsigned int pos = hash & (h->threshold - 1);

#ifdef DEBUG
    if (h->key_type == STR) 
        printf("key[%s] threshold[%ld] hash[%d] pos[%d]\n", (char *)key, h->threshold, hash, pos);
#endif

    if (__find(key, h->buckets[pos], h->match) != NULL)
        return -1;

    hash_pair_t *hi = calloc(1, sizeof(hash_pair_t));
    void *newkey = __calloc_for(h->key_type, key);
    void *newval = __calloc_for(h->val_type, val);
    hi->key = newkey;
    hi->val = newval;
	hi->hash = hash;
    hi->next = h->buckets[pos];
    h->buckets[pos] = hi;

    if (++(h->size) > h->threshold)
        __resize(h);

    return 0;
}

int hash_replace(hash_t *h, void *key, void *val)
{
    return 0;
}

int hash_get(hash_t *h, void *key, void **val)
{
    unsigned int hash = key == NULL ? 0 : __hash(h->hash(key));
    int pos = hash & (h->threshold - 1);

#ifdef DEBUG
    if (h->key_type == STR) 
        printf("key[%s] threshold[%ld] hash[%d] pos[%d]\n", (char *)key, h->threshold, hash, pos);
#endif

    hash_pair_t *hi = __find(key, h->buckets[pos], h->match);
    if (hi == NULL)
        return -1;
    *val = hi->val;

    return 0;
}
