#include "core.h"
#include "middle/middle.h"
#include "include/trade_msg.h"
#include "include/trade_type.h"
#include <stdio.h>
#include <string.h>

static int __package_head(msg_head_t *h)
{
	h->msg_len = LOGOUT_RSP_LEN; 
	h->fix_length = NONFIX; 
	h->rec_length = LOGOUT_RSP_BODY_LEN; 
	h->rec_no = 1; 
	strncpy(h->msg_type, A302, sizeof(h->msg_type));
	h->trans_no = 0; 
	h->signature_flag = NONSIGNATURED; 
	h->encrypted = NONENCRYTED; 
	h->resend_flag = 0; 
	strncpy(h->reserved, "123", sizeof(h->reserved)); 
	strncpy(h->signature_data, "123", sizeof(h->signature_data)); 
	return 0;
}

int add_vol_handler(shield_head *h)
{
	printf("TRACE: [%s][%d] add vol handler called.\n", __FL__);
		
	CALLOC_MSG(add_vol_rsp, h->fd, ADD_VOL_RSP);

	__package_head(&add_vol_rsp->msg_head);
	
	printf("TRACE: [%s][%d] add vol head package ok.\n", __FL__);

	strncpy(add_vol_rsp->processingResult, "00001", sizeof(add_vol_rsp->processingResult));
	strncpy(add_vol_rsp->description, "add vol success!", sizeof(add_vol_rsp->description));
	strncpy(add_vol_rsp->orgInstructionId, "", sizeof(add_vol_rsp->orgInstructionId));
	strncpy(add_vol_rsp->instrumentId, "", sizeof(add_vol_rsp->instrumentId));
	strncpy(add_vol_rsp->accountId, "", sizeof(add_vol_rsp->accountId));
	strncpy(add_vol_rsp->PBU, "", sizeof(add_vol_rsp->PBU));
	strncpy(add_vol_rsp->quantity, "", sizeof(add_vol_rsp->quantity));
	printf("TRACE: [%s][%d]add vol rsp body package ok.\n", __FL__);
	printf("TRACE: [%s][%d] push to middle[%p].\n", __FL__, g_svr->core->push_to_middle);
	PUSH_MSG(add_vol_rsp);

	return 0;
}

