#ifndef _FRAME_H_
#define _FRAME_H_


#include <stdlib.h>
#include "thread.h"

#define MAX_TYPE 0x80

#define __FL__ __FILE__, __LINE__

#define MAGIC_NUM 980234


typedef struct shield_head_s {
	unsigned int magic_num;
	size_t       len;
	int          fd;
	long long    trade_type;
} shield_head;


typedef struct handler_map_s {
	int  type;
	int  (*handler)(shield_head *h);
} handler_map_t;


typedef struct config {
	int  listen_port;
} svr_cfg;

typedef struct core_s {
	int (*init)(void *p);
	int (*push_to_middle)(shield_head *h);
	int (*push_to_persistent)(shield_head *h);
	int (*handler)(shield_head *h);
	int (*handlers[MAX_TYPE])(shield_head *h);
} core_handler;

typedef struct middle_s {
	int  (*handle_in)(shield_head *h);
	int  (*handle_out)(shield_head *h);
	int  (*push_in)(shield_head *h);
	int  (*push_out)(shield_head *h);
} middle_handler;

typedef struct persistent_s {
	int  (*handler)(shield_head *h);
} persistent_handler;

typedef struct svr_s {
	int                listenfd;

	int                running;

	svr_cfg            *cfg;

	thread_pool_t      *tp;

	core_handler       *core;
	middle_handler     *middle;
	persistent_handler *persistent;

	int  (*core_handler_init)(core_handler *core, handler_map_t *m);
	int  (*middle_handler_init)(middle_handler *middle,
	                            int (*fin)(shield_head *),
								int (*fout)(shield_head *));
	int  (*persistent_handler_init)(persistent_handler *persistent,
	                                int (*handler)(shield_head *));

} svr_t;

extern svr_t *g_svr;

int  server_init(char *cfg_file);
int  server_start();
void server_join();
void server_free();

int server_set_core_init(int (*init)(void *p));

#endif
