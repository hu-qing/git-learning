#ifndef __HASH_H__
#define __HASH_H__

#define DEFAULT_HASH_BUCKET_SIZE 1024

typedef struct hash_s {
	size_t  bucket_size;
	int     (*cmp)(void *a, void *b);
	unsigned int hash(void *s);
	void    *bucket;
} hash_t;

hash_t *hash_init();

#endif
