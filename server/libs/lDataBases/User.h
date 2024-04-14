#pragma once
#include <string>
#include "../lHash/sha1.h"
#include <iostream>

using namespace std;

class User
{
private:
	string _name;
	string _login;
	uint* _password;
public:
	User();
	User(string name, string password, string login);
	User(const User& user);
	User& operator=(const User& user);
	~User();
	
	void setName(string name); // Set a name
	void setPassword(string password); // Set a password
	void setLogin(string login); // Set login

	string getName() const; // Get the name
	uint* getPassword() const; // Get password
	string getLogin() const; // Get login
	
	void setUserData(); // Set login, password, name
	
	friend istream& operator>> (istream& is, User& user); // ...
	friend ostream& operator<< (ostream& os, User& user); // outdated 
};
