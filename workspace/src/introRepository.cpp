#include "introRepository.h"
MYSQL_RES* IntroRepository::check_user(const User& u){
	string str="SELECT * FROM user_list WHERE login='"+ u.getLogin() +"' AND password='"+ u.getPassword() +"';";
	res = d.result(str);
	return res;
}
MYSQL_RES *IntroRepository::get_role(const User& u){
	string str = "SELECT * FROM user_role WHERE user_list_id="+to_string(u.getId())+" ORDER BY role_id DESC;";
	res=d.result(str);
	return res;
}
void IntroRepository::	user_registration(string choice, const User& u){
	string str;
	if(choice=="2")
		str="CALL insert_user_tr('"+u.getLogin()+"','"+u.getPassword()+"','"+u.getFname()+"','"+u.getSname()+"',NULL,'"+choice+"');";
	else
		str="CALL insert_user_tr('"+u.getLogin()+"','"+u.getPassword()+"','"+u.getFname()+"','"+u.getSname()+"','"+u.getJson().dump()+"','"+choice+"');";
	d.result(str);
}




