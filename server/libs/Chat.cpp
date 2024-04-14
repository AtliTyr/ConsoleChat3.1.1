#include "Chat.h"

//int iSendResult;
//SOCKET ClientSocket = INVALID_SOCKET;

Chat::Chat()
{
	//Registration("admin", "admin", "admin");
	//Registration("A", "A", "A");

 	//WriteTestMessages();
}
Chat::~Chat() = default;

#if defined _WIN32 || _WIN64
	void Chat::SendUsersList(SOCKET& clientSocket)
	{
		int iSendResult;
		char message[MESSAGE_LENGTH];

		memset(message, 0, sizeof(message));

		strcpy(message, "$");

		iSendResult = send(clientSocket, message, sizeof(message), 0);

		for (int i{ 0 }; i < base.getUsersCount(); i++)
		{
			strcpy(message, base.getUsersNameNLoginByIndex(i).c_str());
			iSendResult = send(clientSocket, message, sizeof(message), 0);
		}

		strcpy(message, "$");
		iSendResult = send(clientSocket, message, sizeof(message), 0);
	}

	void Chat::SendGeneralMessages(SOCKET& clientSocket)
	{
		int iSendResult;
		char message[MESSAGE_LENGTH];
		memset(message, 0, sizeof(message));

		Message tmp;

		strcpy(message, "$");
		iSendResult = send(clientSocket, message, sizeof(message), 0);
		//ssize_t bytes = write(con, message, sizeof(message));

		for (int i{ 0 }; i < m_base.getMessageCount(); i++)
		{
			tmp = m_base.getMessageByIndex(i);
			if (tmp.getRecepientOfMessage() == "")
			{
				string t = "<" + tmp.getSenderOfMessage() + ">" + tmp.getMessage();
				strcpy(message, t.c_str());
				iSendResult = send(clientSocket, message, sizeof(message), 0);
				//ssize_t bytes = write(con, message, sizeof(message));
			}
		}
		strcpy(message, "$");
		iSendResult = send(clientSocket, message, sizeof(message), 0);
	}

	void Chat::SendPrivateMessages(SOCKET& clientSocket, string login)
	{
		int iSendResult;
		char message[MESSAGE_LENGTH];
		memset(message, 0, sizeof(message));

		Message tmp;

		strcpy(message, "$");
		iSendResult = send(clientSocket, message, sizeof(message), 0);

		for (int i{ 0 }; i < m_base.getMessageCount(); i++)
		{
			tmp = m_base.getMessageByIndex(i);
			if ((tmp.getSenderOfMessage() == login && tmp.getRecepientOfMessage() != "") || (tmp.getRecepientOfMessage() == login))
			{
				string t = "<" + tmp.getSenderOfMessage() + "> <" + tmp.getRecepientOfMessage() + "> " + tmp.getMessage();
				strcpy(message, t.c_str());
				iSendResult = send(clientSocket, message, sizeof(message), 0);
			}
		}

		strcpy(message, "$");
		iSendResult = send(clientSocket, message, sizeof(message), 0);
	}

#elif __linux__
void Chat::SendUsersList(int con)
{
	char message[MESSAGE_LENGTH];
	bzero(message, sizeof(message));

	strcpy(message, "$");

	ssize_t bytes = write(con, message, sizeof(message));

	for (int i{ 0 }; i < base.getUsersCount(); i++)
	{
		strcpy(message, base.getUsersNameNLoginByIndex(i).c_str());
		ssize_t bytes = write(con, message, sizeof(message));
	}

	strcpy(message, "$");
	write(con, message, sizeof(message));

}

void Chat::SendGeneralMessages(int con)
{
	char message[MESSAGE_LENGTH];
	bzero(message, sizeof(message));

	Message tmp;

	strcpy(message, "$");
	ssize_t bytes = write(con, message, sizeof(message));

	for (int i{ 0 }; i < m_base.getMessageCount(); i++)
	{
		tmp = m_base.getMessageByIndex(i);
		if (tmp.getRecepientOfMessage() == "")
		{
			string t = "<" + tmp.getSenderOfMessage() + ">" + tmp.getMessage();
			strcpy(message, t.c_str());
			ssize_t bytes = write(con, message, sizeof(message));
		}
	}
	strcpy(message, "$");
	write(con, message, sizeof(message));

}

void Chat::SendPrivateMessages(int con, string login)
{
	char message[MESSAGE_LENGTH];
	bzero(message, sizeof(message));

	Message tmp;

	strcpy(message, "$");
	ssize_t bytes = write(con, message, sizeof(message));

	for (int i{ 0 }; i < m_base.getMessageCount(); i++)
	{
		tmp = m_base.getMessageByIndex(i);
		if ((tmp.getSenderOfMessage() == login && tmp.getRecepientOfMessage() != "") || (tmp.getRecepientOfMessage() == login))
		{
			string t = "<" + tmp.getSenderOfMessage() + "> <" + tmp.getRecepientOfMessage() + "> " + tmp.getMessage();
			strcpy(message, t.c_str());
			ssize_t bytes = write(con, message, sizeof(message));
		}
	}

	strcpy(message, "$");
	write(con, message, sizeof(message));
}
#endif


bool Chat::WriteMessage(string snd, string rec, string text)
{
	
	if(rec == "")
	{
		m_base.AddMessageToChat(Message(snd, "", text));
	}
	else
	{
		if(base.findUserIndex(rec) == -1)
			return false;
		else
		{
			m_base.AddMessageToChat(Message(snd, rec, text));
			return true;
		}	
	}

}

bool Chat::DeleteUser(string login)
{
	if(login == "admin" || login == "A")
	{
		return false;
	}
	
	base.deleteUserFromUserBase(login);
	return true;
}

void Chat::Registration()
{
			cout << "Register" << endl;
			User user;
			char ch = ' ';
			do
			{
				cout << "To exit, enter '0': ";
				//ch = getch();
				(cin>>ch).ignore();
				if (ch == '0')
					throw bad_Registration();

				cout << "\033[2J\033[1;1H";

				user.setUserData();
				if (base.findUserIndex(user.getLogin()) != -1)
				{
					cout << "The entered login is busy" << endl;
				}

			} while (base.findUserIndex(user.getLogin()) != -1);
				

				cout << "User successfully registered" << endl;
				base.addUserToUserBase(user);
				
}

bool Chat::Registration(std::string name, std::string login, std::string password)
{
	if( base.findUserIndex(login) != -1 )
		return false;

	base.addUserToUserBase(User(name, password, login));
		return true;

}

bool Chat::authorization(std::string login, std::string password)
{

	return base.authorization(login, password);
}



/*
void Chat::Registration(std::string name, std::string login, std::string password)
{
	User user(name, password, login);
	base.addUserToUserBase(user);
	
}

*/

bool Chat::EnterChat()
{
				
				std::string password;
				std::string login;
				char ch;
				do
				{
					cout << "Log in" << endl;

					cout << "To exit, enter '0': ";
					//ch = getch();
					(cin >> ch).ignore();
					if (ch == '0')
						throw bad_Authorization();

					//	system("cls");
					cout << "\033[2J\033[1;1H";

					cout << "Enter login: ";
					cin >> login;

					cout << "Enter password: ";
					std::cin >> password;
				} while (!base.authorization(login, password));

					//system("cls");
					cout << "\033[2J\033[1;1H";
					cout << "Authorization successful" << endl;
					authorized = base[base.findUserIndex(login)];
					return true;
}

void Chat::DisplayUserList() // For testing. Then delete
{

	base.displayUserBase();
}

void Chat::DeleteUserFromChat()
{
	if (authorized.getLogin() == "admin" || authorized.getLogin() == "A")
	{
		throw bad_Delete();
	}
	else
	{
		base.deleteUserFromUserBase(authorized.getLogin());
		cout << "Account deleted" << endl;
	}
}

void Chat::WriteMessageToAll()
{
	cout << "<" << authorized.getLogin() << "> : ";
	string msg="";
	getline(cin,msg,'\n');

	m_base.AddMessageToChat(Message(authorized.getLogin(), "", msg));
	//	chat.emplace_back(Message(authorized.getLogin(), "", msg));
}
void Chat::WritePrivateMessage(std::string login)
{
	if (authorized.getLogin() == login)
	{
		throw bad_Recepient();
	}

	if (base.findUserIndex(login) != -1)
	{
		cout << "<" << authorized.getLogin() << "> to <" << login << "> :";
		string msg;
		getline(cin, msg);
	
		m_base.AddMessageToChat(Message(authorized.getLogin(), login, msg));	
	//	chat.emplace_back(Message(authorized.getLogin(),login, msg));
	}
	else
	{
		throw bad_Recepient();
	}
}
void Chat::CheckGeneralMessages()
{
	m_base.DisplayChat();
}
void Chat::CheckPrivateMessages()
{
	m_base.DisplayChat(authorized);
}


void Chat::WriteTestMessages()
{
	m_base.AddMessageToChat(Message("", "", "Test Message"));
	m_base.AddMessageToChat(Message("", "", "Test Message1"));
	m_base.AddMessageToChat(Message("", "", "Test Message2"));
}
