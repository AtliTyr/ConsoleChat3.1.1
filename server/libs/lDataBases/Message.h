#pragma once
#include <string>
#include <iostream>

using namespace std;

class Message
{
private:
	string FROM; //Sender's login
	string TO; // Recipient's login
	string MESSAGE; // Message to be sent
public:
	Message() = default;
	~Message() = default;
	Message(string from, string to, string message);
	void senderOfMessage(string sender_l); // Set the sender's login 
	void recipientOfMessage(string recipient_l); // Set the recipient's login
	void setMessage(string message); // Set message text
	string getSenderOfMessage() const; // Get the sender's login
	string getRecepientOfMessage() const; // Get the recipient's login
	string getMessage() const; // Get message text


	friend ostream& operator<< (ostream& os, Message& message);
	friend istream& operator>> (istream& is, Message& message);
};
