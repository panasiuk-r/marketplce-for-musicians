#include "mainInter.h"

MainInterface& MainInterface::setIntroInterface(IntroInterface& ii){
	this->ii=&ii;
	return* this;
}

MainInterface& MainInterface::setUser(const User& u){
	this->u=u;
	return *this;
}

void MainRepository::giveAdmin(const long long int id){
	string str="CALL give_admin_tr("+to_string(id)+");";
	d.result(str);
}

void MainRepository::banUser(const long long int id, int ban){
	string str="UPDATE user_list SET baned="+to_string(ban)+" WHERE id="+to_string(id)+";";
	d.result(str);
}

void MainRepository::musicianRating(const long long int id){
	string str="UPDATE user_list SET rating=avg_rating("+to_string(id)+") WHERE id="+to_string(id)+";";
	d.result(str);
}


void MainInterface::mainMenu(){
	string choice;
	if(!u.getBaned())
		{
		if (u.getRole()[0]==1 && u.getRole().size()==1){
			cout<<"1.View musician"<<endl;
			cout<<"2.View history request"<<endl;
			cout<<"3.View profile"<<endl;
			cout<<"4.Log out"<<endl;
			getline(cin,choice);
			while(choice!="1" && choice!="2" && choice!="3" && choice!="4"){
				cout<<"Incorrect input. Please, try again"<<endl;
				cout<<"1.View musician"<<endl;
				cout<<"2.History request"<<endl;
				cout<<"3.View profile"<<endl;
				cout<<"4.Log out"<<endl;
				getline(cin,choice);
			}
			cout<<endl;
			if(choice=="1")
				viewMusician();
			if(choice=="2")
				viewHistoryRequest();
			if(choice=="3")
				viewProfile();
			if(choice=="4")
				logOut();
		}
		if(u.getRole()[0]==3 && u.getRole().size()==1){
			cout<<"1.View requests"<<endl;
			cout<<"2.View closed requests"<<endl;
			cout<<"3.View profile"<<endl;
			cout<<"4.Log out"<<endl;
			getline(cin,choice);
			while(choice!="1" && choice!="2" && choice!="3" && choice!="4"){
				cout<<"Incorrect input. Please, try again"<<endl;
				cout<<"1.View requests"<<endl;
				cout<<"2.View closed requests"<<endl;
				cout<<"3.View profile"<<endl;
				cout<<"4.Log out"<<endl;
				getline(cin,choice);
			}
			cout<<endl;
			if(choice=="1")
				viewRequests();
			if(choice=="2")
				viewClosed();
			if(choice=="3")
				viewProfile();
			if(choice=="4")
				ii->hello();
		}
		if(u.getRole()[0]==2 && u.getRole().size()==1){
			cout<<"1.View users statuses"<<endl;
			cout<<"2.View profile"<<endl;
			cout<<"3.Log out"<<endl;
			getline(cin,choice);
			while(choice!="1" && choice!="2" && choice!="3"){
				cout<<"Incorrect input. Please, try again"<<endl;
				cout<<"1.View users statuses"<<endl;
				cout<<"2.View profile"<<endl;
				cout<<"3.Log out"<<endl;
				getline(cin,choice);
			}
			cout<<endl;
			if(choice=="1")
				viewUsers();
			if(choice=="2")
				viewProfile();
			if(choice=="3")
				ii->hello();
		}
		if(u.getRole().size()>1){
			cout<<"1.View musician"<<endl;
			cout<<"2.View history request"<<endl;
			cout<<"3.View profile"<<endl;
			cout<<"4.View requests"<<endl;
			cout<<"5.View closed"<<endl;
			cout<<"6.Log out"<<endl;
			getline(cin,choice);
			while(choice!="1" && choice!="2" && choice!="3" && choice!="4" && choice!="5" && choice!="6"){
				cout<<"1.View musician"<<endl;
				cout<<"2.View history request"<<endl;
				cout<<"3.View profile"<<endl;
				cout<<"4.View requests"<<endl;
				cout<<"5.View closed requests"<<endl;
				cout<<"6.Log out"<<endl;
				getline(cin,choice);
			}
			cout<<endl;
			if(choice=="1")
				viewMusician();
			if(choice=="2")
				viewHistoryRequest();
			if(choice=="3")
				viewProfile();
			if(choice=="4")
				viewRequests();
			if(choice=="5")
				viewClosed();
			if(choice=="6")
				logOut();
		}
	}
	else{
		cout<<"You have been baned"<<endl<<endl;
		ii->hello();
	}
}

void MainInterface::viewMusician(){
	User u;
	json j;
	long long int id;
	int size;
	string choice;
	string ban;
	res=mr.viewMusician(this->u);
	while((row = mysql_fetch_row(res))!=NULL){
		ban=row[6];
		if(ban!="1"){
			id=atoll(row[0]);
			mr.musicianRating(id);
		}
	}
	mysql_free_result(res);
	res=mr.viewMusician(this->u);
	while ((row = mysql_fetch_row(res))!=NULL){
		ban=row[6];
		if(ban!="1"){
			j=json::parse(row[3]);
			u.setInfo(u.getInfo().from_json(j));
			cout<<"------------------"<<endl;
			cout<<"id number:"<<row[0]<<endl;
			cout<<"First name: "<<row[1]<<endl;
			cout<<"Second name: "<<row[2]<<endl;
			cout<<"Skills: ";
			size=u.getInfo().getSkills().size();
			for(string str: u.getInfo().getSkills()){
				if(str==u.getInfo().getSkills()[size-1])
					cout<<str;
				else
					cout<<str<<", ";
			}
			cout<<"\nGenres: ";
			size=u.getInfo().getGenres().size();
			for(string str: u.getInfo().getGenres()){
				if(str==u.getInfo().getGenres()[size-1])
					cout<<str;
				else
					cout<<str<<", ";
			}
			cout<<endl;
			cout<<"Information: ";
			cout<<u.getInfo().getInf()<<endl;
			if(row[5]!=NULL)
				cout<<"Rating: "<<row[5]<<endl;
			else
				cout<<"Rating: "<<endl;
			cout<<"With us since: "<<row[4]<<endl;
			cout<<"------------------"<<endl;
		}
	}
	mysql_free_result(res);
	cout<<"1.Create request"<<endl;
	cout<<"2.Go Back"<<endl;
	getline(cin,choice);
	while(choice!="1" && choice!="2"){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"1.Create request"<<endl;
		cout<<"2.Go Back"<<endl;
		getline(cin,choice);
	}
	cout<<endl;
	if (choice=="1")
		createRequest();
	if (choice=="2")
		mainMenu();
}

void MainInterface::viewHistoryRequest(){
	string status;
	string rstatus;
	long long int id;
	string choice;
	string comment;
	string rating;
	string review;
	res=mr.viewHistoryRequest(u);
	row = mysql_fetch_row(res);
	if(row!=NULL){
		while(row!=NULL){
			if(row[9]!=NULL)
				rating=row[9];
			if(row[8]!=NULL)
				review=row[8];
			if(row[7]!=NULL)
				comment=row[7];
			status=row[0];
			rstatus=row[12];
			cout<<"------------------"<<endl;
			cout<<"Time: "<<row[10]<<endl;
			cout<<"Status: "<<row[0]<<endl;
			cout<<"Title: "<<row[1]<<endl;
			cout<<"Description: "<<row[2]<<endl;
			cout<<"Musician id: "<<row[3]<<endl;
			cout<<"First name: "<<row[4]<<endl;
			cout<<"Second name: "<<row[5]<<endl;
			cout<<"Price: "<<row[6]<<endl;
			cout<<"Final comment: "<<comment<<endl;
			cout<<"Final Rating: "<<rating<<endl;
			cout<<"Final Review: "<<review<<endl;
			cout<<"------------------"<<endl;
			if(rstatus=="4" && status=="DONE"){
				while(choice!="Yes"){
					cout<<"Rate completed work from 0 to 5"<<endl;
					getline(cin,rating);
					while(atoi(rating.c_str())>5 ||  atoi(rating.c_str())<0 ){
						cout<<"Incorrect input. Please, try again"<<endl;
						cout<<"Rate completed work from 0 to 5"<<endl;
						getline(cin,rating);
					}
					cout<<"You can add review:"<<endl;
					getline(cin,review);
					cout<<"Confirm changes? Yes/No"<<endl;
					getline(cin,choice);
				}
				id=atoll(row[11]);
				mr.insertReview(id, review, atoi(rating.c_str()));
				mr.updateRequestStatus(id, 5);
				mr.closeRequest(id);
				cout<<endl;
				viewRequests();
			}
			cout<<endl;
			row = mysql_fetch_row(res);
		}
	}
	else
		cout<<"You do not have requests"<<endl;
	cout<<endl;
	mainMenu();
}

void MainInterface::viewProfile(){
	string choice;
	int size;
	json j;
	res=mr.viewProfile(u);
	row = mysql_fetch_row(res);
	cout<<"Your profile:"<<endl;
	cout<<"------------------"<<endl;
	cout<<"Login: "<<row[1]<<endl;
	cout<<"Password: "<<row[2]<<endl;
	cout<<"First name: "<<row[3]<<endl;
	cout<<"Second name: "<<row[4]<<endl;
	cout<<"With us since: "<<row[5]<<endl;
	cout<<"Last update: "<<row[6]<<endl;
	if(u.getRole()[0]==3){
		j=json::parse(row[7]);
		u.setInfo(u.getInfo().from_json(j));
		cout<<"Skills: ";
		size=u.getInfo().getSkills().size();
		for(string str: u.getInfo().getSkills()){
			if(str==u.getInfo().getSkills()[size-1])
				cout<<str;
			else
				cout<<str<<", ";
		}
		cout<<"\nGenres: ";
		size=u.getInfo().getGenres().size();
		for(string str: u.getInfo().getGenres()){
			if(str==u.getInfo().getGenres()[size-1])
				cout<<str;
			else
				cout<<str<<", ";
		}
		cout<<endl;
		cout<<"Information: ";
		cout<<u.getInfo().getInf()<<endl;
	}
	cout<<"------------------"<<endl;
	cout<<"1.Edit profile"<<endl;
	cout<<"2.Go back"<<endl;
	getline(cin,choice);
	if(choice=="1"){
		cout<<endl;
		editProfile();
		return;
	}
	if(choice=="2"){
		cout<<endl;
		mainMenu();
		return;
	}
	while(choice!="1" && choice !="2"){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"1.Edit profile"<<endl;
		cout<<"2.Go back"<<endl;
		getline(cin,choice);
		cout<<endl;
		if(choice=="1"){
			cout<<endl;
			editProfile();
			break;
		}
		if(choice=="2"){
			cout<<endl;
			mainMenu();
			break;
		}
	}
	mysql_free_result(res);
}

void MainInterface::viewRequests(){
	string status;
	string choice;
	string close;
	bool newReq=false;
	bool empty=false;
	res=mr.viewRequests(u);
	row=mysql_fetch_row(res);
	if(row!=NULL){
		while(row!=NULL){
			close=row[8];
			if(close!="1"){
				empty=true;
				status=row[1];
				if(status=="REGISTERED")
					newReq=true;
				cout<<"------------------"<<endl;
				cout<<"Request id: "<<row[0]<<endl;
				cout<<"Status: "<<row[1]<<endl;
				cout<<"Title: "<<row[2]<<endl;
				cout<<"Description: "<<row[3]<<endl;
				cout<<"Author id: "<<row[4]<<endl;
				cout<<"First name: "<<row[5]<<endl;
				cout<<"Second name: "<<row[6]<<endl;
				cout<<"Price: "<<row[7]<<endl;
				cout<<"------------------"<<endl;
			}
			row=mysql_fetch_row(res);
		}
		if(newReq==true)
			cout<<"You have a new request!"<<endl;
		if(empty){
			cout<<"1.Edit request"<<endl;
			cout<<"2.Go back"<<endl;
			getline(cin,choice);
			while(choice!="1" && choice!="2"){
				cout<<"Incorrect input. Please, try again"<<endl;
				cout<<"1.Edit request"<<endl;
				cout<<"2.Go back"<<endl;
				getline(cin, choice);
			}
			if(choice=="1")
				editRequest();
			if(choice=="2")
				mainMenu();
		}
		else{
			cout<<"You do not have requests"<<endl<<endl;
			mainMenu();
		}
	}
	else{
		cout<<"You do not have requests"<<endl<<endl;
		mainMenu();
	}
}

void MainInterface::viewClosed(){
	string close;
	res=mr.viewRequests(u);
	row=mysql_fetch_row(res);
	if(row!=NULL){
		while(row!=NULL){
			close=row[8];
			if(close=="1"){
				cout<<"------------------"<<endl;
				cout<<"Request id: "<<row[0]<<endl;
				cout<<"Status: "<<row[1]<<endl;
				cout<<"Title: "<<row[2]<<endl;
				cout<<"Description: "<<row[3]<<endl;
				cout<<"Author id: "<<row[4]<<endl;
				cout<<"First name: "<<row[5]<<endl;
				cout<<"Second name: "<<row[6]<<endl;
				cout<<"Price: "<<row[7]<<endl;
				if(row[11]!=NULL)
					cout<<"Comment: "<<row[11]<<endl;
				if(row[9]!=NULL)
					cout<<"Rating: "<<row[9]<<endl;
				if(row[10]!=NULL)
					cout<<"Review: "<<row[10]<<endl;
				cout<<"------------------"<<endl;
			}
			row=mysql_fetch_row(res);
		}
	}
	else
		cout<<"you do not have closed requests"<<endl;
	cout<<endl;
	mainMenu();
}


void MainInterface::viewUsers(){
	res=mr.viewUsers();
	string choice;
	cout<<"------------------"<<endl;
	while ((row = mysql_fetch_row(res)) !=NULL){
		cout<<"user id: "<<row[0]<<endl;
		cout<<"role: "<<row[1]<<endl;
		cout<<"ban status: "<<row[2]<<endl;
		cout<<endl;
	}
	cout<<"------------------"<<endl;
	cout<<"1.Give admin status"<<endl;
	cout<<"2.Ban/unban user"<<endl;
	cout<<"3.Go back"<<endl;
	getline(cin, choice);
	while(choice!="1" && choice!="2" && choice!="3"){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"1.Change user status"<<endl;
		cout<<"2.Ban/unban user"<<endl;
		cout<<"3.Go back"<<endl;
		getline(cin, choice);
	}
	cout<<endl;
	if(choice=="1")
		giveAdmin();
	if(choice=="2")
		banUser();
	if(choice=="3")
		mainMenu();
}
void MainInterface::editRequest(){
	string id;
	string choice;
	string status;
	string comment;
	cout<<"Enter 0 at any time to go back"<<endl;
	cout<<"Enter id of the request you want to edit:"<<endl;
	getline(cin,id);
	if(id=="0"){
		cout<<endl;
		viewRequests();
		return;
	}
	res=mr.checkRequest(atoll(id.c_str()),u.getId());
	row=mysql_fetch_row(res);
	if(row==NULL){
		cout<<"Incorrect input. Please, try again"<<endl<<endl;
		viewRequests();
	}
	else{
		status=row[0];
		if(status=="REGISTERED"){
			cout<<"Confirm request? Yes/No"<<endl;
			getline(cin,choice);
			while(choice!="Yes" && choice!="No" && choice!="0"){
				cout<<"Incorrect input. Please, try again"<<endl;
				cout<<"Confirm request? Yes/No"<<endl;
				getline(cin,choice);
			}
			if(choice=="0"){
				cout<<endl;
				viewRequests();
				return;
			}
			if(choice=="Yes")
				mr.updateRequestStatus(atoll(id.c_str()),3);
			if(choice=="No"){
				cout<<"Write the reason why you reject it:"<<endl;
				getline(cin,comment);
				cout<<"Confirm comment? Yes/No"<<endl;
				getline(cin,choice);
				while(choice!="Yes" && choice!="No" && choice!="0"){
					cout<<"Incorrect input. Please, try again"<<endl;
					cout<<"Confirm comment? Yes/No"<<endl;
					getline(cin,choice);
				}
				if(choice=="0" || choice=="No"){
					cout<<endl;
					viewRequests();
					return;
				}
				if(choice=="Yes"){
					mr.insertComment(atoll(id.c_str()), comment);
					mr.updateRequestStatus(atoll(id.c_str()), 2);
					mr.closeRequest(atoll(id.c_str()));
					cout<<endl;
					viewRequests();
				}
			}
		}
		if(status=="ACCEPTED"){
			cout<<"Do you confirm that the task has been completed? Yes/No"<<endl;
			getline(cin,choice);
			while(choice!="Yes" && choice!="No" && choice!="0"){
				cout<<"Incorrect input. Please, try again"<<endl;
				cout<<"Do you confirm that the task is completion? Yes/No"<<endl;
				getline(cin,choice);
			}
			if(choice=="0" || choice=="No"){
				viewRequests();
				return;
			}
			if(choice=="Yes"){
				cout<<"You can add comment:"<<endl;
				getline(cin,comment);
				cout<<"Confirm comment? Yes/No"<<endl;
				getline(cin,choice);
				while(choice!="Yes" && choice!="No" && choice!="0"){
					cout<<"Incorrect input. Please, try again"<<endl;
					cout<<"Confirm comment? Yes/No"<<endl;
					getline(cin,choice);
				}
				if(choice=="0" || choice=="No"){
					cout<<endl;
					viewRequests();
					return;
				}
				if(choice=="Yes"){
					mr.insertComment(atoll(id.c_str()), comment);
					mr.updateRequestStatus(atoll(id.c_str()), 4);
					cout<<endl;
					viewRequests();
				}
			}
		}
		else{
			cout<<"You can not change this request"<<endl<<endl;
			viewRequests();
		}
	}
}
void MainInterface::createRequest(){
	string conf;
	cout<<"Press 0 at any time to go back"<<endl;
	r.setMusicianId(atoll(idReq().c_str()));
	if(r.getMusicianId()==0){
		cout<<endl;
		viewMusician();
		return;
	}
	r.setTitle(titleReq());
	if(r.getTitle()=="0"){
		cout<<endl;
		viewMusician();
		return;
	}
	r.setDescription(descriptionReq());
	if(r.getDescription()=="0"){
		cout<<endl;
		viewMusician();
		return;
	}
	r.setPrice(atof(priceReq().c_str()));
	if(r.getPrice()==0){
		cout<<endl;
		viewMusician();
		return;
	}
	cout<<"Your request:"<<endl;
	cout<<"-----------------"<<endl;
	cout<<"Musician id:"<<endl<<r.getMusicianId()<<endl;
	cout<<"Title:"<<endl<<r.getTitle()<<endl;
	cout<<"Description:"<<endl<<r.getDescription()<<endl;
	cout<<"Price:"<<endl<<r.getPrice()<<endl;
	cout<<"-----------------"<<endl;
	cout<<"Do you confirm it? Yes/No"<<endl;
	getline(cin,conf);
	while(conf!="Yes" && conf!="No"){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"Your request:"<<endl;
		cout<<"-----------------"<<endl;
		cout<<"Musician id:"<<endl<<r.getMusicianId()<<endl;
		cout<<"Title:"<<endl<<r.getTitle()<<endl;
		cout<<"Description:"<<endl<<r.getDescription()<<endl;
		cout<<"Price:"<<endl<<r.getPrice()<<endl;
		cout<<"-----------------"<<endl;
		cout<<"Do you confirm it? Yes/No"<<endl;;
		getline(cin,conf);
	}
	if(conf=="No"){
		viewMusician();
		return;
	}
	r.setUserId(u.getId());
	res=mr.checkMusician(r);
	if((row = mysql_fetch_row(res))==NULL){
		cout<<endl;
		cout<<"Incorrect input. Please, try again"<<endl;
		viewMusician();
		return;
	}
	mysql_free_result(res);
	mr.createRequest(r);
	mainMenu();
}

void MainInterface::editProfile(){
	string choice;
	Information info;
	json j;
	int size;
	cout<<"Press 0 at any time to go back"<<endl;
	cout<<"1.login"<<endl;
	cout<<"2.password"<<endl;
	cout<<"3.First name"<<endl;
	cout<<"4.Second name"<<endl;
	if(u.getRole()[0]==1 || u.getRole()[0]==2){
		cout<<"Enter number of a row you want to edit:"<<endl;
		getline(cin,choice);
		while(choice!="0" && choice!="1" && choice!="2" && choice!="3" && choice!="4"){
			cout<<"Incorrect input. Please, try again"<<endl;
			getline(cin,choice);
		}
		cout<<endl;
	}
	else{
		cout<<"5.Skills"<<endl;
		cout<<"6.Genres"<<endl;
		cout<<"7.Information"<<endl;
		cout<<"Enter number of a row you want to edit:"<<endl;
		getline(cin,choice);
		while(choice!="0" && choice!="1" && choice!="2" && choice!="3" && choice!="4" && choice!="5" && choice!="6" && choice !="7"){
			cout<<"Incorrect input. Please, try again"<<endl;
			getline(cin,choice);
		}
		cout<<endl;
	}
	cout<<endl;
	if(choice=="0"){
		viewProfile();
		return;
	}
	if(choice=="1"){
		string login;
		login=ii->loginReg();
		if(login=="0"){
			viewProfile();
			return;
		}
		cout<<endl;
		u.setLogin(login);
		mr.updateUser(u);
		viewProfile();
		return;
	}
	if(choice=="2"){
		string password;
		password=ii->passwordReg();
		if(password=="0"){
			viewProfile();
			return;
		}
		cout<<endl;
		u.setPassword(password);
		mr.updateUser(u);
		viewProfile();
		return;
	}
	if(choice=="3"){
		string fname;
		fname=ii->fnameReg();
		if(fname=="0"){
			viewProfile();
			return;
		}
		cout<<endl;
		u.setFname(fname);
		mr.updateUser(u);
		viewProfile();
		return;
	}
	if(choice=="4"){
		string sname;
		sname=ii->snameReg();
		if(sname=="0"){
			viewProfile();
			return;
		}
		cout<<endl;
		u.setSname(sname);
		mr.updateUser(u);
		viewProfile();
		return;
	}
	if(choice=="5"){
		info.setGenres(u.getInfo().getGenres());
		info.setInf(u.getInfo().getInf());
		ii->skillsReg(info);
		size=info.getSkills().size();
		if(info.getSkills()[size-1]=="0"){
			viewProfile();
			return;
		}
		cout<<endl;
		u.setInfo(info);
		info.to_json(j);
		u.setJson(j);
		mr.updateUser(u);
		viewProfile();
		return;
	}
	if(choice=="6"){
		info.setSkills(u.getInfo().getSkills());
		info.setInf(u.getInfo().getInf());
		ii->genreReg(info);
		size=info.getGenres().size();
		if(info.getGenres()[size-1]=="0"){
			viewProfile();
			return;
		}
		cout<<endl;
		u.setInfo(info);
		info.to_json(j);
		u.setJson(j);
		mr.updateUser(u);
		viewProfile();
		return;
	}
	if(choice=="7"){
		string inf;
		info.setSkills(u.getInfo().getSkills());
		info.setGenres(u.getInfo().getGenres());
		inf=ii->infReg();
		if(inf=="0"){
			viewProfile();
			return;
		}
		cout<<endl;
		info.setInf(inf);
		u.setInfo(info);
		u.getInfo().to_json(j);
		u.setJson(j);
		mr.updateUser(u);
		viewProfile();
		return;		info.setInf(inf);
		u.getInfo().setInf(inf);
	}
}

void MainInterface::giveAdmin(){
	string id;
	string choice;
	cout<<"Press 0 at any time to go back"<<endl;
	cout<<"Enter user id:"<<endl;
	getline(cin,id);
	if(id=="0"){
		viewUsers();
		return;
	}
	cout<<"You sure you want to add this user ADMIN status? Yes/No"<<endl;
	getline(cin,choice);
	while(choice!="Yes" && choice!="No"){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"You sure you want to add this user ADMIN status? Yes/No"<<endl;
		getline(cin,choice);
	}
	if(choice=="No"){
		viewUsers();
		return;
	}
	if(choice=="Yes"){
		res=mr.checkUser(atoll(id.c_str()));
		row=mysql_fetch_row(res);
		if(row!=NULL){
			mr.giveAdmin(atoll(id.c_str()));
			cout<<endl;
			viewUsers();
			return;
		}
		else{
			cout<<"No such user"<<endl<<endl;
			mysql_free_result(res);
			viewUsers();
			return;
		}
	}
}

void MainInterface::banUser(){
	string id;
	string choice;
	string ban;
	cout<<"Press 0 at any time to go back"<<endl;
	cout<<"Enter user id:"<<endl;
	getline(cin,id);
	if(id=="0"){
		viewUsers();
		return;
	}
	cout<<"1.Unban"<<endl;
	cout<<"2.Ban"<<endl;
	getline(cin,ban);
	while(ban!="1" && ban!="2" && ban!="0"){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"1.Unban"<<endl;
		cout<<"2.Ban"<<endl;
		getline(cin,ban);
	}
	cout<<"You sure you want to ban/unban this user? Yes/No"<<endl;
	getline(cin,choice);
	while(choice!="Yes" && choice!="No"){
		cout<<"Incorrect input. Please, try again"<<endl;
		cout<<"You sure you want to ban/unban this user? Yes/No"<<endl;
		getline(cin,choice);
	}
	if(choice=="No"){
		viewUsers();
		return;
	}
	if(choice=="Yes"){
		res=mr.checkUser(atoll(id.c_str()));
		row=mysql_fetch_row(res);
		string str=row[0];
		if(str.empty()){
			cout<<"No such user"<<endl<<endl;
			mysql_free_result(res);
			viewUsers();
			return;
		}
		else{
			mr.banUser(atoll(id.c_str()), atoi(ban.c_str())-1);
			cout<<endl;
			viewUsers();
			return;
		}
	}

}

string MainInterface::idReq(){
	string id;
	cout<<"Enter musician id to whom you want to make request:"<<endl;
	getline(cin,id);
	return id;
}

string MainInterface::titleReq(){
	string title;
	cout<<"Enter title:"<<endl;
	getline(cin,title);
	return title;
}

string MainInterface::descriptionReq(){
	string description;
	cout<<"Enter description:"<<endl;
	getline(cin,description);
	return description;
}

string MainInterface::priceReq(){
	string price;
	cout<<"Enter price $:"<<endl;
	getline(cin,price);
	if(price.find(",")!=string::npos){
		size_t pos = price.find(",");
		price.replace(pos,1,".");
	}
	return price;
}
void MainInterface::logOut() const{
	ii->hello();
}
