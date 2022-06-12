#include "mconnector.h"

MYSQL* mysql_connection_setup(struct ConnectionDetails mysql_details) {

    MYSQL *connection = mysql_init(NULL);

    if (!mysql_real_connect(connection,mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0)) {
      cout<<"Conection error : "<< mysql_error(connection)<<endl;
      exit(1);
    }

    return connection;
}

MYSQL_RES* mysql_perform_query(MYSQL *connection, char const *sql_query) {

   if (mysql_query(connection, sql_query)) {
      cout<<"MySQL query error : "<< mysql_error(connection)<<endl;
      return NULL;
   }
   return mysql_use_result(connection);
}

MYSQL_RES* Dialog::result(string str){
	DBdetails.server = "localhost";
	DBdetails.user = "root";
	DBdetails.password = "VEPbrfyn!24";
	DBdetails.database = "workspace";
	conn = mysql_connection_setup(DBdetails);
	res = mysql_perform_query(conn, str.c_str());
	if(res==NULL)
		mysql_close(conn);
	return res;
}
