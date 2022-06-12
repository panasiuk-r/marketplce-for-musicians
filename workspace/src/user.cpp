#include "user.h"

Information& Information::operator =(const Information& info){
	this->genres=info.genres;
	this->skills=info.skills;
	this->inf=info.inf;
	return* this;
}

vector<string> Information::getGenres() const{
	return genres;
}

vector<string> Information::getSkills() const{
	return skills;
}

string Information::getInf() const{
	return inf;
}
Information& Information::pushGenre(string genre){
	genres.push_back(genre);
	return* this;
}
Information& Information::pushSkill(string skill){
	skills.push_back(skill);
	return* this;
}
Information& Information::setInf(string inf){
	this->inf=inf;
	return* this;
}

Information& Information::setGenres(vector<string> genres){
	this->genres=genres;
	return* this;
}

Information& Information::setSkills(vector<string> skills){
	this->skills=skills;
	return* this;
}
Information& Information::to_json(json& j){
	j={
		{"genres",genres},
		{"skills",skills},
		{"information",inf}
	};
	return* this;
}

Information& Information::from_json(const json& j){
	j.at("genres").get_to(genres);
	j.at("skills").get_to(skills);
	j.at("information").get_to(inf);
	return *this;
}

Information& Information::clear(){
	genres.clear();
	skills.clear();
	inf.clear();
	return *this;
}

User& User::operator = (const User& u) {
	id = u.id;
	login = u.login;
	password = u.password;
	fname = u.fname;
	sname = u.sname;
	creationd = u.creationd;
	updated = u.updated;
	role=u.role;
	baned=u.baned;
	info=u.info;
	j=u.j;
	return* this;
}
User& User::clear(){
	id = 0;
	login.clear();
	password.clear();
	fname.clear();
	sname.clear();
	creationd.clear();
	updated.clear();
	role.clear();
	baned=NULL;
	info.clear();
	j.clear();
	return* this;
}


User& User::pushRole(int role){
	this->role.push_back(role);
	return* this;
}

long long int User::getId() const{
	return id;
}

bool User::getBaned() const{
	return baned;
}

string User::getLogin() const{
	return login;
}

string User::getPassword() const{
	return password;
}

string User::getFname() const{
	return fname;
}

string User::getSname() const{
	return sname;
}

Information User::getInfo() const{
	return info;
}

json User::getJson() const{
	return j;
}

vector<int> User::getRole() const{
	return role;
}

User& User::setId(const long long int& id){
	this->id=id;
	return* this;
}

User& User::setJson(json j){
	this->j=j;
	return* this;
}

User& User::setJsonRow(char*& r){
	if(r!=NULL)
		j=json::parse(r);
	return* this;
}

User& User::setLogin(const string& login){
	this->login=login;
	return* this;
}

User& User::setBaned(bool baned){
	this->baned=baned;
	return* this;
}

User& User::setPassword(const string& password){
	this->password=password;
	return* this;
}

User& User::setFname(const string& fname){
	this->fname=fname;
	return* this;
}

User& User::setSname(const string& sname){
	this->sname=sname;
	return* this;
}

User& User::setCretiond(const string& creationd){
	this->creationd=creationd;
	return* this;
}

User& User::setUpdated(const string& updated){
	this->updated=updated;
	return* this;
}

User& User::setInfo(const Information& info){
	this->info=info;
	return* this;
}
User& User::setRole(const vector<int>& role){
	this->role=role;
	return* this;
}
