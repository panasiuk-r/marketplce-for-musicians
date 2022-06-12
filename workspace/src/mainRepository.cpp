#include "mainRepository.h"

MYSQL_RES* MainRepository::viewMusician(const User& u){
	string str="SELECT id, first_name, second_name, information, date_of_creation, rating, baned FROM user_list ul INNER JOIN user_role ur ON ul.id=ur.user_list_id AND ur.role_id=3 AND ul.id!="+to_string(u.getId())+";";
	res=d.result(str);
	return res;
}

MYSQL_RES* MainRepository::viewUsers(){
	string str="SELECT * FROM users_v";
	res=d.result(str);
	return res;
}

MYSQL_RES* MainRepository::viewHistoryRequest(const User& u){
	string str="SELECT s.status, title, description, usl.id, usl.first_name, usl.second_name,price, comment, review, rl.rating, hrl.date_of_update, rl.id, rl.status_id FROM history_request_list hrl INNER JOIN request_list rl ON rl.id=hrl.request_list_id INNER JOIN statuses s ON s.id=hrl.status_id INNER JOIN user_list ul ON ul.id=rl.author_id AND ul.id="+to_string(u.getId())+" INNER JOIN user_list usl ON usl.id=musician_id ORDER BY ul.date_of_creation DESC;";
	res=d.result(str);
	return res;
}

MYSQL_RES* MainRepository::viewRequests(const User& u){
	string str="SELECT rl.id, s.status, title, description, usl.id, usl.first_name, usl.second_name,price, rl.close, rl.rating,rl.review, rl.comment FROM request_list rl  INNER JOIN statuses s ON s.id=rl.status_id INNER JOIN user_list ul ON ul.id=rl.musician_id AND ul.id="+to_string(u.getId())+" INNER JOIN user_list usl ON usl.id=author_id ORDER BY ul.date_of_creation DESC;";
	res=d.result(str);
	return res;
}

MYSQL_RES* MainRepository::viewProfile(const User& u){
	string str="SELECT * FROM user_list WHERE id="+to_string(u.getId())+";";
	res=d.result(str);
	return res;
}

void MainRepository::updateUser(const User& u){
	string str="UPDATE user_list SET login='"+u.getLogin()+"',password='"+u.getPassword()+"',first_name='"+u.getFname()+"',second_name='"+u.getSname()+"',information='"+u.getJson().dump()+"' WHERE id="+to_string(u.getId())+";";
	d.result(str);
}

void MainRepository::updateRequestStatus(const long long int id,const int status){
	string str="UPDATE request_list SET status_id="+to_string(status)+" WHERE id="+to_string(id)+";";
	d.result(str);
}

void MainRepository::insertComment(const long long int id,const string comment){
	string str="UPDATE request_list SET comment='"+comment+"' WHERE id="+to_string(id)+";";
	d.result(str);
}

void MainRepository::insertReview(const long long int id,const string review,const int rating){
	string str="UPDATE request_list SET review='"+review+"', rating="+to_string(rating)+" WHERE id="+to_string(id)+";";
	d.result(str);
}

void MainRepository::closeRequest(const long long int id){
	string str="UPDATE request_list SET close=1 WHERE id="+to_string(id)+";";
	d.result(str);
}

MYSQL_RES* MainRepository::checkUser(const long long int id){
	string str="SELECT id from user_list WHERE id="+to_string(id)+";";
	res=d.result(str);
	return res;
}

MYSQL_RES* MainRepository::checkMusician(const Request& r){
	string str="SELECT user_list_id FROM user_role ur INNER JOIN user_list ul ON ul.id="+to_string(r.getMusicianId())+" AND role_id=3 AND ul.id=ur.user_list_id AND ul.id!="+to_string(r.getUserId())+";";
	res=d.result(str);
	return res;
}

MYSQL_RES* MainRepository::checkRequest(const long long int id, const long long int musicianId){
	string str="SELECT s.status FROM request_list rl INNER JOIN statuses s ON s.id=status_id AND rl.id="+to_string(id)+" AND musician_id="+to_string(musicianId)+";";
	res=d.result(str);
	return res;
}

void MainRepository::createRequest(const Request& r){
	string str="INSERT INTO request_list(title,description,price,author_id,musician_id, status_id) VALUES ('"+r.getTitle()+"','"+r.getDescription()+"',"+to_string(r.getPrice())+","+to_string(r.getUserId())+","+to_string(r.getMusicianId())+",1);";
	res=d.result(str);
	mysql_free_result(res);
}




