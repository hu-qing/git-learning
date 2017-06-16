#include "db.h"
#include <stdio.h>


int db_init(const char *filename, sqlite3 **conn)
{
	int ret;

	*conn = NULL;
	ret = sqlite3_open(filename, conn);
	if (ret) {
		if (*conn)
			sqlite3_close(*conn);
		return -1;
	}

	return 0;
}

int db_close(sqlite3 *conn)
{
	return sqlite3_close(conn) == SQLITE_OK ? 0 : -1;
}

int db_exec_dql(sqlites *conn, const char *sql, callback, 0, &zErrMsg)
{
	int ret;

	ret = sqlite3_exec(conn, sql, callback, void *, char **errmsg);
}

int db_exec_dml(sqlites *conn, const char *sql, char **err_msg)
{
	return sqlite3_exec(conn, sql, NULL, NULL, err_msg) == SQLITE_OK ? 0 : -1;
}

int main()
{
	int ret;

	sqlite3 *conn;
	ret = db_init("test.db", &conn);

	return ret;
}
