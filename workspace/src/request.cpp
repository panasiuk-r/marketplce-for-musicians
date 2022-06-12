#include "request.h"

Request& Request::setTitle(const string& title){
	this->title=title;
	return* this;
}

Request& Request::setDescription(const string& description){
	this->description=description;
	return* this;
}

Request& Request::setMusicianId(const long long int& musicianId){
	this->musicianId=musicianId;
	return* this;
}

Request& Request::setUserId(const long long int& userId){
	this->userId=userId;
	return* this;
}

Request& Request::setPrice(const double& price){
	this->price=price;
	return* this;
}

Request& Request::setRating(const int& rating){
	this->rating=rating;
	return* this;
}

Request& Request::setReview(const string& review){
	this->review=review;
	return* this;
}

Request& Request::setComment(const string& comment){
	this->comment=comment;
	return* this;
}

string Request::getTitle()const{
	return title;
}

string Request::getDescription()const{
	return description;
}

long long int Request::getMusicianId() const{
	return musicianId;
}

long long int Request::getUserId() const{
	return userId;
}

double Request::getPrice() const{
	return price;
}

int Request::getRating() const{
	return rating;
}

string Request::getComment() const{
	return comment;
}

