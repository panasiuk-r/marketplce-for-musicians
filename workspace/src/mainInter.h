
#ifndef MAININTER_H_
#define MAININTER_H_
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <mysql/mysql.h>
#include "mconnector.h"
#include "user.h"
#include "introInter.h"
#include "request.h"
#include "mainRepository.h"
class IntroInterface;

class MainInterface{
private:
	Request r;
	User u;
	MainRepository mr;
	MYSQL_RES *res;
	MYSQL_ROW row;
	IntroInterface* ii;
public:
	MainInterface& setIntroInterface(IntroInterface& ii);
	MainInterface& setUser(const User& u);
	void mainMenu();
	void viewMusician();
	void viewHistoryRequest();
	void viewProfile();
	void logOut() const;
	void viewRequests();
	void viewClosed();
	void viewUsers();
	void createRequest();
	void editRequest();
	void editProfile();
	void banUser();
	void giveAdmin();
	string idReq();
	string titleReq();
	string descriptionReq();
	string priceReq();
};




#endif /* MAININTERFACE_H_ */
