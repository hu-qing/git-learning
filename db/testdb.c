#include "sqlite3.h"
#include <stdio.h>
#include <unistd.h>

#define DB_NAME "SHIELD.DB"

#define CREATE_T_USER        "create table t_user(user_name varchar(40) primary key, password varchar(512), is_active integer);"
#define CREATE_T_CLIENT      "create table t_client(acc_no varchar(15) primary key, vol integer, pbu varchar(10), is_active integer);"
#define CREATE_T_TRADE_DATE  "create table t_trade_date(trade_date varchar(8));"
#define CREATE_T_TRADE       "create table t_trade(seq integer, trade_date varchar(8), sge_trans_no integer, " \
                             "sge_instruction varchar(16), instrument_id varchar(6), acc_no varchar(15), " \
                             "pbu varhchar(10), quantity integer, is_succeed integer, );"
#define CREATE_T_HIS_TRADE   "create table t_his_trade(seq integer varchar(8));"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(int argc, char *argv[]){
	sqlite3 *db;
	char *zErrMsg = 0;
	int ret;

	ret = sqlite3_open("test.db", &db);
	if (ret) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	char *sql = "select one as o, two as t from tbl1;";
	ret = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( ret!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
	return 0;
}
