#include "frame.h"
#include "handler.h"
#include "net.h"
#include "thread.h"
#include "protocol.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

svr_t  *g_svr;

static int __svr_cfg_struct(const char *key, const char *val)
{

	printf("TRACE: [%s][%d] in cfg key[%s] val[%s].\n", __FL__, key, val);
	if (!strcmp(key, "listen_port")) {
		int port = atoi(val);
		if (port < 1024)
			return -1;
		g_svr->cfg->listen_port = atoi(val);
		printf("TRACE: [%s][%d] listen port[%d] from config file.\n", __FL__, g_svr->cfg->listen_port);
	} else {
		printf("TRACE: [%s][%d] key[%s] val[%s] error.\n", __FL__, key, val);
		return -1;		
	}
	

	return 0;
}

static int __read_svr_cfg(const char *cfg_file)
{
	g_svr->cfg = calloc(1, sizeof(svr_cfg));

	int fd;
	if ((fd = open(cfg_file, O_RDONLY)) == -1) {
		printf("ERROR: [%s][%d] open config file [%s] error.\n", __FL__, cfg_file);	
		return -1;
	}

	char buff[256] = {0};
	char c;
	int  i = 0;
	char key[256];
	char val[256];
	int  ret;
	while (read(fd, &c, 1)) {
		if (c != '\n') {
			buff[i++] = c;
		} else {
			buff[i] = '\0';
			printf("ERROR: [%s][%d] buff[%s] read from config file.\n", __FL__, buff);	
			memset(key, 0, sizeof(key));
			memset(val, 0, sizeof(val));
			sscanf(buff, "%[^=]=%s", key, val);
			ret = __svr_cfg_struct(key, val);
			if (ret)
				goto error;

			i = 0;
		}
	}
	close(fd);
	return 0;
error:
	close(fd);
	return -1;
}


int server_init(char *cfg_file)
{
	g_svr = calloc(1, sizeof(svr_t));

	if (__read_svr_cfg(cfg_file) < 0) {
		printf("ERROR: [%s][%d] read cfg file[%s] error.\n", __FL__, cfg_file);
		return -1;
	}

	int listenfd;
	listenfd = init_net();
	if (listenfd < 0) {
		printf("ERROR: [%s][%d] initialize net error.\n", __FL__);
		return -1;
	}

	g_svr->listenfd = listenfd;

	thread_pool_t *tp = thread_pool_init();
	if (tp == NULL) {
		printf("ERROR: [%s][%d] initialize threads pool error.\n", __FL__);
		return -1;
	}

	tp->sse_protocol = init_protocol();
	if (tp->sse_protocol == NULL) {
		printf("ERROR: [%s][%d] initialize protocol error.\n", __FL__);
		return -1;
	}

	g_svr->tp = tp;

	g_svr->middle = calloc(1, sizeof(middle_handler));
	g_svr->core = calloc(1, sizeof(core_handler));
	g_svr->persistent = calloc(1, sizeof(persistent_handler));

	g_svr->middle_handler_init = init_middle_handler;
	g_svr->core_handler_init = init_core_handler;
	g_svr->persistent_handler_init = init_persistent_handler;

	g_svr->running = 1;

	return 0;
}

int server_set_core_init(int (*init)(void *p))
{
	g_svr->core->init = init;
	return 0;
}

int server_start()
{
	g_svr->tp->run();
	return 0;
}

void server_join()
{
	g_svr->tp->join();
}

void server_free()
{
	if (g_svr != NULL) {
		if (g_svr->tp != NULL)
			free(g_svr->tp);
		free(g_svr);
	}
}
