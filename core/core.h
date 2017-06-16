#ifndef __CORE_H__
#define __CORE_H__

#include "frame/frame.h"

#define CALLOC_MSG(s, ifd, type) \
	shield_head *__##s = calloc(1, sizeof(shield_head) + sizeof(s##_t)); \
	__##s->magic_num = MAGIC_NUM; \
	__##s->fd = ifd; \
	__##s->trade_type = type; \
	s##_t *s = (s##_t *)(__##s + 1);

#define PUSH_MSG(s) \
	g_svr->core->push_to_middle(__##s);


extern handler_map_t g_hp[];

extern int  g_send_trans_no;
extern char g_data_date[16];

int  core_init();

int  login_req_handler(shield_head *h);
int  biz_over_req_handler(shield_head *h);
int  logout_req_handler(shield_head *h);
int  ping_req_handler(shield_head *h);
int  ping_rsp_handler(shield_head *h);
int  add_vol_req_handler(shield_head *h);
int  cut_vol_req_handler(shield_head *h);
int  trade_qry_req_handler(shield_head *h);

#endif
