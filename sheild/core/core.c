#include "core.h"
#include <string.h>

int  g_send_trans_no;
char g_data_date[16];

int core_init()
{
	g_send_trans_no = 0;
	strcpy(g_data_date, "20170613");

	return 0;
}
