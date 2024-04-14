#pragma once
#include "User.h"
//#include "C:\Users\ACER\Desktop\Projs\IsCrossplatform\IsCrossplatform\lHash\sha1.h"
//#include "..\lHash\sha1.h"
//#include "lHash/sha1.h"
#include "../lHash/sha1.h"
#include <list>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <vector>


const char FilePath[] = "Logs/UserBase.txt";

namespace fs = std::filesystem;

class UserBase
{
private:
	//User* list = nullptr;
	vector<User> List;
	std::fstream DataFile;
public:
	UserBase();
	~UserBase();
	User& operator[](int index);
	
	int getUsersCount() const;

	string getUsersNameNLoginByIndex(int ind);

	// Loads all user's data from file to List
	void LoadDatabaseFromFile();
	
	void LoadDatabaseToFile();

	// Adds a user to the database
	void addUserToUserBase(const User& user);

	// Removes a user from the database
	void deleteUserFromUserBase(std::string login);
	
	// Display logins and usernames
	void displayUserBase();

	// Returns the user's index in the database if there is one
	// And returns -1 if the user is not found
	int findUserIndex(std::string login); 
	
	// Checks the user's login and password from the database, and if the user has
	// exists with the given login and password, then returns true
	// otherwise false
	bool authorization(std::string login, std::string password);

};
