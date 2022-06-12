
#ifndef MAINREPOSITORY_H_
#define MAINREPOSITORY_H_

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <mysql/mysql.h>
#include "mconnector.h"
#include "user.h"
#include "request.h"

class MainRepository{
private:
	Dialog d;
	MYSQL_RES *res;
public:
	MYSQL_RES* viewMusician(const User& u);
	MYSQL_RES* viewHistoryRequest(const User& u);
	MYSQL_RES* viewRequests(const User& u);;
	MYSQL_RES* checkUser(const long long int id);
	MYSQL_RES* checkMusician(const Request& r);
	MYSQL_RES* checkRequest(const long long int id, const long long int musicianId);
	MYSQL_RES* viewProfile(const User& u);
	MYSQL_RES* viewUsers();
	void updateUser(const User& u);
	void closeRequest(const long long int id);
	void updateRequestStatus(const long long int id,const int status);
	void insertComment(const long long int id,const string comment);
	void insertReview(const long long int id,const string review,const int rating);
	void createRequest(const Request& r);
	void giveAdmin(const long long int id);
	void banUser(const long long int id, int ban);
	void musicianRating(const long long int id);
};


#endif /* MAINREPOSITORY_H_ */
