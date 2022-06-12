
#ifndef REQUEST_H_
#define REQUEST_H_

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;
class Request{
	string title;
	string description;
	long long int musicianId;
	long long int userId;
	double price;
	int rating;
	string review;
	string comment;
public:

	Request& setTitle(const string& title);

	Request& setDescription(const string& description);

	Request& setMusicianId(const long long int& musicianId);

	Request& setUserId(const long long int& userId);

	Request& setPrice(const double& price);

	Request& setRating(const int& rating);

	Request& setReview(const string& review);

	Request& setComment(const string& comment);

	string getTitle()const;

	string getDescription()const;

	long long int getMusicianId() const;

	long long int getUserId() const;

	double getPrice() const;

	int getRating() const;

	string getReview() const;

	string getComment() const;
};



#endif /* REQUEST_H_ */
