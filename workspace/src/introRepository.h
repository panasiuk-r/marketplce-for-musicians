#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <mysql/mysql.h>
#include "mconnector.h"
#include "user.h"
#ifndef INTROREPOSITORY_H_
#define INTROREPOSITORY_H_


class IntroRepository{
private:
	Dialog d;
	MYSQL_RES *res;
public:
	MYSQL_RES *check_user(const User& u);
	MYSQL_RES *get_role(const User& u);
	void user_registration(string choice, const User& u);
};


#endif /* INTROREPOSITORY_H_ */
