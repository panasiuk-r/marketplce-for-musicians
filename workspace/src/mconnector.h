#ifndef MCONNECTOR_H_
#define MCONNECTOR_H_

#include <mysql/mysql.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;


struct ConnectionDetails
{
    char *server;
    char *user;
    char *password;
    char *database;
};

MYSQL* mysql_connection_setup(struct ConnectionDetails mysql_details);

MYSQL_RES* mysql_perform_query(MYSQL *connection, char const *sql_query);

class Dialog{
private:
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	ConnectionDetails DBdetails;

public:
	MYSQL_RES* result(string str);
};

#endif /* MCONNECTOR_H_ */
