#ifndef INTROINTER_H_
#define INTROINTER_H_
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <mysql/mysql.h>
#include <nlohmann/json.hpp>
#include "mainInter.h"
#include "mconnector.h"
#include "user.h"
#include "introRepository.h"
using namespace std;

using nlohmann::json;

class MainInterface;


class IntroInterface{
public:
	User u;
	IntroRepository ir;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MainInterface* mi;
public:


	void hello();

	void singIn();

	void singUp();
	User getUser() const;
	IntroInterface& setMainInterface(MainInterface& mi);
	string loginReg();
	string passwordReg();
	string fnameReg();
	string snameReg();
	string genreReg(Information& info);
	string skillsReg(Information& info);
	string infReg();
	void Registration(string choice);
};
#endif
