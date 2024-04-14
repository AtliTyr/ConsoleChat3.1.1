#include "Message.h"

Message::Message(std::string from, std::string to, std::string message) : FROM(from), TO(to), MESSAGE(message)
{}
void Message::senderOfMessage(std::string sender_l)
{
	FROM = sender_l;
}
void Message::recipientOfMessage(std::string recipient_l)
{
	TO = recipient_l;
}
void Message::setMessage(std::string message)
{
	MESSAGE = message;
}
std::string Message::getSenderOfMessage() const
{
	return FROM;
}
std::string Message::getRecepientOfMessage() const
{
	return TO;
}
std::string Message::getMessage() const
{
	return MESSAGE;
}
ostream& operator<<(ostream& os, Message& message)
{
	string msg = message.FROM + "/" + message.TO + "/" + message.MESSAGE + "\n";
	return os << msg;
}

istream& operator>>(istream& is, Message& message)
{
	string s;

	getline(is, s, '/');
	message.senderOfMessage(s);

	getline(is, s, '/');
	message.recipientOfMessage(s);

	getline(is, s);
	message.setMessage(s);

	return is;
}
