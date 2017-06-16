#ifndef __DB_H__
#define __DB_H__

#include "sqlite3.h"

int db_init(const char *filename, sqlite3 **conn);
int db_close(sqlite3 *conn);

#endif
