#include "MessageBase.h"

MessageBase::MessageBase()
{
	mFile.open(MessageFilePath, std::ios::in | std::ios::out);
	if(!mFile.is_open())
	{
		mFile.open(MessageFilePath, std::ios::in | std::ios::out | std::ios::trunc);
		fs::permissions(MessageFilePath, fs::perms::owner_exec | fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);
		Message testM1 ("","","Test Message");
		Message testM2 ("","","Test Message2");
		Message testM3 ("","","Test Message3");
		mFile << testM1;
		mFile << testM2;
		mFile << testM3;
	}

	LoadMessagebaseFromFile();
}

MessageBase::~MessageBase()
{
	mFile.close();
}

int MessageBase::getMessageCount() const
{
	return chat.size();
}

Message MessageBase::getMessageByIndex(int ind)
{
//	std::string tmp = chat.at(ind).getSenderOfMessage() + " " chat.at(ind).getRecepientOfMessage() + " " + chat.at(ind).getMessage();
//	return tmp;

	return chat.at(ind);
}

void MessageBase::AddMessageToChat(const Message& message)
{
	chat.emplace_back(message.getSenderOfMessage(), message.getRecepientOfMessage(), message.getMessage());

	Message msg;
	msg.senderOfMessage(message.getSenderOfMessage());
	msg.recipientOfMessage(message.getRecepientOfMessage());
	msg.setMessage(message.getMessage());

	mFile.clear();
	mFile.seekp(0, std::ios::end);
	mFile << msg;
}

void MessageBase::DisplayChat()
{
	for (vector<Message>::iterator it = chat.begin(); it != chat.end(); it++)
	{
		if( (*it).getRecepientOfMessage() == "")
			std::cout << "<" << (*it).getSenderOfMessage() << "> : " << (*it).getMessage() << endl;
	}
}

void MessageBase::DisplayChat(User& user)
{
	for (int i{ 0 }; i < chat.size(); i++)
	{
		if ( (chat.at(i).getRecepientOfMessage() == user.getLogin()) || (chat.at(i).getSenderOfMessage() == user.getLogin() && chat.at(i).getRecepientOfMessage() != ""))
			std::cout << "<" << chat.at(i).getSenderOfMessage() << "> to <" << chat.at(i).getRecepientOfMessage() << ">: " << chat.at(i).getMessage() << endl;

	}
}

void MessageBase::LoadMessagebaseFromFile()
{
	mFile.clear();
	mFile.seekg(0, std::ios::beg);

	while (!mFile.eof())
	{
		Message tmp;
		mFile >> tmp;

		if (tmp.getMessage() == "")
		{
			break;
		}
		
		chat.emplace_back(tmp);
	}
}
