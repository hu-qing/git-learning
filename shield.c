#include "frame/frame.h"
#include "core/core.h"
#include "middle/middle.h"
/*
 * #include "persistent/persistent.h"
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

handler_map_t g_hp[];

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage: %s -f <config file>\n", argv[0]);	
		return -1;
	}

	char f[256] = {0};
	int opt;
	if ((opt = getopt(argc, argv, "f:abc")) != -1) {
		strncpy(f, optarg, sizeof(f));	
	} else {
		printf("ERROR: [%s][%d] get args error.\n", __FL__);
		return -1;
	}

	if (server_init(f) != 0) {
		printf("ERROR: [%s][%d] initialize server error.\n", __FL__);
		return -1;
	}

	g_svr->core_handler_init(g_svr->core, g_hp);
	g_svr->middle_handler_init(g_svr->middle, resolve_msg, package_msg);
	g_svr->persistent_handler_init(g_svr->persistent, NULL);

	server_set_core_init(core_init);

	if (server_start() != 0) {
		printf("ERROR: [%s][%d] start server error.\n", __FL__);
		server_free();
		return -1;
	}
	server_join();
	return 0;
}
