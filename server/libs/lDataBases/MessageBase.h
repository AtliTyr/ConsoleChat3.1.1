#pragma once
#include <vector>
#include "Message.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include "User.h"
#include <string>

namespace fs = std::filesystem;

const char MessageFilePath[] = "Logs/MessageBase.txt";

class MessageBase
{
private:
	std::vector <Message> chat; // Массив сообщений чата
	std::fstream mFile;
public:
	MessageBase();
	~MessageBase();
	
	int getMessageCount() const;
	Message getMessageByIndex(int ind);

	void AddMessageToChat(const Message& message);

	void DisplayChat();
	void DisplayChat(User& user);

	void LoadMessagebaseFromFile();
};

