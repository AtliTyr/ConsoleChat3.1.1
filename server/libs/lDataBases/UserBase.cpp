#include "UserBase.h"

UserBase::UserBase()
{
	DataFile.open(FilePath, std::ios::in | std::ios::out);
	if(!DataFile.is_open())
	{
		DataFile.open(FilePath, std::ios::in | std::ios::out | std::ios::trunc);
		fs::permissions(FilePath, fs::perms::owner_exec | fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);
		
		User reserved_user("A", "A", "A");
		User reserved_user2("admin", "admin", "admin");
		DataFile << reserved_user;
		DataFile << reserved_user2;
	}
	
	LoadDatabaseFromFile();
}

UserBase::~UserBase()
{
	if(!List.empty())
	{
		DataFile.close();
		DataFile.open(FilePath, std::ios::out | std::ios::trunc);

		LoadDatabaseToFile();
		DataFile.close();
	}
}

User& UserBase::operator[](int index)
{
	if (index >= 0 && index <= List.size())
	{
		int i = 0;
		for (vector<User>::iterator it = List.begin(); it != List.end(); it++, i++)
			if (i == index)
				return *it;
	}
}

int UserBase::getUsersCount() const
{
	return List.size();
}

string UserBase::getUsersNameNLoginByIndex(int ind)
{
	string tmp = List.at(ind).getName() + " " + List.at(ind).getLogin();
	return string(tmp);
}

void UserBase::LoadDatabaseToFile()
{
	DataFile.clear();
	DataFile.seekg(0, std::ios::end);
	
	for (vector<User>::iterator it = List.begin(); it != List.end(); it++)
	{
		DataFile << *it;
	}
}

void UserBase::LoadDatabaseFromFile()
{
	DataFile.clear();
	DataFile.seekg(0, std::ios::beg);

	while (!DataFile.eof())
	{
		User tmp;
		DataFile >> tmp;
		if (tmp.getLogin() == "")
			break;

		List.push_back(tmp);
	}
}

void UserBase::addUserToUserBase(const User& user)
{

	List.push_back(user);
}
void UserBase::deleteUserFromUserBase(std::string login)
{
	for (vector<User>::iterator it = List.begin(); it != List.end();it++)
		if ((*it).getLogin() == login)
		{
			List.erase(it);
			break;
		}
}
void UserBase::displayUserBase()
{
	for (vector<User>::iterator it = List.begin(); it != List.end(); it++)
	{
		cout << "Name: " << (*it).getName() << endl
		     << "Login: " << (*it).getLogin() << endl << endl;
	}
}
int UserBase::findUserIndex(std::string login)
{
	int i = 0;
	for (vector<User>::iterator it = List.begin(); it != List.end(); it++, i++)
	{
		if ((*it).getLogin() == login)
		{
			return i;
		}
	}
	return -1;
}
bool UserBase::authorization(std::string login, std::string password)
{
	int index = findUserIndex(login);
	if (index != -1)
	{
		vector<User>::iterator it = List.begin();
		for (int i = 0; i < index; i++)
		{
			it++;
		}

				
		char* tmp = new char[password.length() + 1];
		strcpy(tmp, password.c_str());

		uint* digest = sha1(tmp, password.length());
		
		bool cmpHashes = !memcmp(
			(*it).getPassword(),
			digest,
			SHA1HASHLENGTHBYTES);
		
		delete[] digest;
		delete[] tmp;

		return cmpHashes;
	}
	return false;
}
