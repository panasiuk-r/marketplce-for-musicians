
#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using nlohmann::json;

class Information{
	vector<string> genres;
	vector<string> skills;
	string inf;
public:

	Information& operator =(const Information& info);

	Information& clear();

	vector<string> getGenres() const;

	vector<string> getSkills() const;

	string getInf() const;

	Information& setGenres(vector<string> genres);

	Information& setSkills(vector<string> skills);

	Information& pushGenre(string genre);

	Information& pushSkill(string skill);

	Information& setInf(string  inf);

	Information& to_json(json& j);

	Information& from_json(const json& j);
};

class User{
private:
	long long int id;
	string login;
	string password;
	string fname;
	string sname;
	string creationd;
	string updated;
	bool baned;
	Information info;
	json j;
	vector<int> role;
public:
	User& operator = (const User& u);

	User& clear();

	User& pushRole(int role);

	long long int getId() const;

	bool getBaned() const;

	string getLogin() const;

	string getPassword() const;

	string getFname() const;

	string getSname() const;

	Information getInfo() const;

	json getJson() const;

	vector<int> getRole() const;

	User& setId(const long long int& id);

	User& setJson(json j);

	User& setJsonRow(char*& r);

	User& setLogin(const string& login);

	User& setBaned(bool baned);

	User& setPassword(const string& password);

	User& setFname(const string& fname);

	User& setSname(const string& sname);

	User& setCretiond(const string& creationd);

	User& setUpdated(const string& updated);

	User& setInfo(const Information& info);

	User& setRole(const vector<int>& role);
};



#endif /* USER_H_ */
