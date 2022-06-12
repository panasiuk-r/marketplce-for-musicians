#include "introInter.h"

void IntroInterface::hello(){
	string choice;
	u.clear();
	cout<<"1.Sing in\n2.Sing up\n3.Exit"<<endl;
	getline(cin,choice);
	while(choice!="2" and choice!="1" and choice!="3"){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"1.Sing in\n2.Sing up"<<endl;
		getline(cin,choice);
	}
	cout<<endl;
	if(choice=="1")
		singIn();
	if(choice=="2")
		singUp();
	if(choice=="3")
		exit(1);
}
User IntroInterface::getUser()const{
	return u;
}
void IntroInterface::singIn(){
	string login;
	string pas;
	cout<<"Press 1 to go back"<<endl;
	cout<<"Enter login. Login must contain at least 8 characters and does not include spaces:"<<endl;
	getline(cin,login);
	while(login.find(" ")!=string::npos){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"Enter login. Login must contain at least 8 characters and does not include spaces:"<<endl;
		getline(cin,login);
	}
	if(login=="1")
		hello();
	else{
		cout<<"Enter password. password must contain at least 8 characters and does not include spaces:"<<endl;
		getline(cin,pas);
		while(login.find(" ")!=string::npos){
			cout<<"Incorrect input. Please, try again"<<endl;
			cout<<"Enter password. password must contain at least 8 characters and does not include spaces:"<<endl;
			getline(cin,pas);
		}
		if (pas=="1")
			hello();
		else{
			u.setLogin(login).setPassword(pas);
			res=ir.check_user(u);
			row = mysql_fetch_row(res);
			if(row==NULL){
				cout<<"Incorrect login or password. Please, try again"<<endl;
				mysql_free_result(res);
				singIn();
			}
			else{
				u.setId(atoll(row[0])).setFname(row[3]).setSname(row[4]).setCretiond(row[5]).setUpdated(row[6]).setJsonRow(row[7]).setBaned(atoi(row[8]));
				res=ir.get_role(u);
				while((row = mysql_fetch_row(res))!=NULL){
					u.pushRole(atoi(row[1]));
				}
				cout<<endl;
				mi->setUser(getUser());
				mi->mainMenu();
			}
		}
	}
}

IntroInterface& IntroInterface::setMainInterface(MainInterface& mi){
	this->mi=&mi;
	return* this;
}

void IntroInterface::singUp(){
	cout<<"What are you looking for?"<<endl;
	cout<<"1.I am a musician, and i am looking for clients"<<endl;
	cout<<"2.I am looking for someone who can make music and beyond"<<endl;
	cout<<"3.Both"<<endl;
	cout<<"4.Go back"<<endl;
	string choice;
	getline(cin,choice);
	while(choice!="2" and choice!="1" and choice!="3" and choice!="4	"){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"1.I am a musican, and i am looking for clients"<<endl;
		cout<<"2.I am looking for a musician"<<endl;
		cout<<"3.Both"<<endl;
		cout<<"4.Go back"<<endl;
		getline(cin,choice);
	}
	cout<<endl;
	if(choice=="4")
		hello();
	else{
		Registration(choice);
	}
}
string IntroInterface::loginReg(){
	string login;
	cout<<"Enter login. Login must contain at least 8 characters and does not include spaces:"<<endl;
	getline(cin,login);
	cout<<endl;
	while(login.length() < 8 && login!="1" && login.find(" ")!=string::npos){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"Enter login(must contain at least 8 characters): ";
		getline(cin,login);
		cout<<endl;
	}
	return login;
}

string IntroInterface::passwordReg(){
	string password;
	cout<<"Enter password. Password must contain at least 8 characters and does not include spaces:"<<endl;
	getline(cin,password);
	cout<<endl;
	while(password.length() < 8 && password!="1" && password.find(" ")!=string::npos){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"Enter password. Password must contain at least 8 characters and does not include spaces:"<<endl;
		getline(cin,password);
		cout<<endl;
	}
	return password;
}

string IntroInterface::fnameReg(){
	string fname;
	cout<<"Enter your first name: "<<endl;
	getline(cin,fname);
	cout<<endl;
	return fname;
}

string IntroInterface::snameReg(){
	string sname;
	cout<<"Enter your second name: "<<endl;
	getline(cin,sname);
	cout<<endl;
	return sname;
}

string IntroInterface::genreReg(Information& info){
	string genre;
	cout<<"Enter genres in which you think you are good at"<<endl;
	cout<<"Enter them one by one and separate them by pressing 'Enter' button"<<endl;
	cout<<"When you are done, write 'Enough':"<<endl;
	cout<<"for example:"<<endl;
	cout<<"----------"<<endl;
	cout<<"Pop\nJazz\nDeath metal\nEnough"<<endl;
	cout<<"----------"<<endl;
	getline(cin,genre);
	while(genre=="Enough"){
		cout<<"This is required filed. You must write at least one genre"<<endl;
		getline(cin,genre);
	}
	while(true){
		if(genre=="0" || genre=="Enough")
			break;
		info.pushGenre(genre);
		getline(cin, genre);
	}
	return genre;
}

string IntroInterface::skillsReg(Information& info){
	string skill;
	cout<<"Enter music skills in which you think you are good at."<<endl;
	cout<<"Enter them one by one and separate them by pressing 'Enter' button."<<endl;
	cout<<"When you are done, write 'Enough'."<<endl;
	cout<<"For instance:"<<endl;
	cout<<"----------"<<endl;
	cout<<"Bass guitar playing\nBeatmaking\nEnough"<<endl;
	cout<<"----------"<<endl;
	getline(cin,skill);
	while(skill=="Enough"){
		cout<<"This is required filed. You must write at least one skill"<<endl;
		getline(cin,skill);
	}
	while(true){
		if(skill=="0" || skill=="Enough")
			break;
		info.pushSkill(skill);
		getline(cin,skill);
	}
	return skill;
}

string IntroInterface::infReg(){
	string inf;
	cout<<"Here you can tell about yourself. When done, press 'Enter'"<<endl;
	getline(cin,inf);
	while(inf=="Enough" && inf=="0"){
		cout<<"This is required filed. You must write some information about you"<<endl;
		getline(cin,inf);
	}
	return inf;
}

void IntroInterface::Registration(string choice){
	cout<<"\nPress 0 at any time to go back"<<endl;
	Information info;
	u.setLogin(loginReg());
	if(u.getLogin()=="0"){
		singUp();
		return;
	}
	u.setPassword(passwordReg());
	if(u.getPassword()=="0"){
		return;
	}
	u.setFname(fnameReg());
	if(u.getFname()=="0"){
		singUp();
		return;
	}
	u.setSname(snameReg());
	if(u.getSname()=="0"){
		singUp();
		return;
	}
	if(choice == "1" || choice=="3"){
		string genre;
		string skill;
		string cont;
		genre=genreReg(info);
		if(genre=="0"){
			singUp();
			return;
		}
		cout<<endl;
		skill=skillsReg(info);
		if(skill=="0"){
			singUp();
			return;
		}
		cout<<endl;
		string inf;
		inf=infReg();
		if(inf=="0"){
			singUp();
			return;
		}
		cout<<endl;
		info.setInf(inf);
		json j;
		info.to_json(j);
		u.setJson(j);
	}
	ir.user_registration(choice,u);
	hello();
}
