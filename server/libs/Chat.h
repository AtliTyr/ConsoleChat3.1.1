#pragma once
#if defined _WIN32 || _WIN64
//#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#elif __linux__
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#endif


#include "lDataBases/UserBase.h"
//#include "UserBase.h"
#include <vector>
#include "lDataBases/Message.h"
//#include "Message.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include "lExceptions/ExceptionHandling.h"
//#include "ExceptionHandling.h"
#include "lDataBases/MessageBase.h"
//#include "MessageBase.h"

#define MESSAGE_LENGTH 1024

using namespace std;

class Chat
{
private:
	MessageBase m_base;
	UserBase base;  // Chat user base
	User authorized; // Currently authorized user
public:
	Chat();
	~Chat();

#if defined _WIN32 || _WIN64
	void SendUsersList(SOCKET& clientSocket);

	void SendGeneralMessages(SOCKET& clientSocket);

	void SendPrivateMessages(SOCKET& clientSocket, string log);
#elif __linux__
	void SendUsersList(int con);
	
	void SendGeneralMessages(int con);

	void SendPrivateMessages(int con, string log);
#endif
	bool DeleteUser(std::string);
	// Authorization in chat, returns true if the entered login and password match in the user database
	bool EnterChat(); 

	// Registration taking into account the uniqueness of the login in the user database
	void Registration();
	
	bool WriteMessage(std::string, std::string, std::string);

	bool Registration(std::string name, std::string login, std::string password);

	bool authorization(std::string login, std::string password);
	// Accelerated registration option, without checks for the uniqueness of the login, for quick Debugging
	//void Registration(std::string name, std::string login, std::string password);
	
	// Allows you to write a public message
	void WriteMessageToAll();
	
	// Allows you to write a message that is accessible only to a user with a given login
	void WritePrivateMessage(std::string login);
	
	// Adds several public messages to the chat. Needed to check functionality. Can be deleted
	void WriteTestMessages();
	
	// Output messages
	void CheckGeneralMessages();

	void CheckPrivateMessages();

	// Removes the current authorized user from the chat user database
	void DeleteUserFromChat();
 
	// Output chat users
	void DisplayUserList();	
};
