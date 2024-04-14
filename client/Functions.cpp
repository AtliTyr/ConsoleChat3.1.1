#include "Functions.h"

bool Registration(string& command)
{
	cout << "Register" << endl;
	char ch = ' ';

	/*do
	{*/
	cout << "To exit, enter '0': ";
	//ch = getch();
	(cin >> ch).ignore();
	if (ch == '0')
	{
		command = "";
		return 0;
	}
	cout << "\033[2J\033[1;1H";

	/*user.setUserData();*/
	string name, login, password;
	cout << "Name: "; cin >> name;
	cout << "Login: "; cin >> login;
	cout << "Password: "; cin >> password;

	command = command + " " + name + " " + login + " " + password;

	return 1;
}
bool Authorization(string& command, string& login)
{
	std::string password;
	//std::string login;
	char ch;

	cout << "Log in" << endl;
	cout << "To exit, enter '0': ";

	(cin >> ch).ignore();
	if (ch == '0')
	{
		command = "";
		return 0;
	}

	cout << "\033[2J\033[1;1H";

	cout << "Enter login: ";
	cin >> login;
	cout << "Enter password: ";
	cin >> password;

	command = command + " " + login + " " + password;
	return 1;
}

void DisplayValidUsers()
{
	cout << "Available users: " << endl
		<< "login: admin		login: A" << endl
		<< "password: admin		password: A" << endl;
}
string loginRequest()
{
	string login;
	cout << "Recipient's login: ";
	getline(cin, login);
	return login;
}

void Menu1()
{

	cout << "#####################" << endl
		<< "1: Register" << endl
		<< "2: Enter the chat" << endl
		<< "3: Exit" << endl
		<< "#####################" << endl
		<< ">";

}
void Menu2()
{
	cout << "\n 1 - Write a message to the general chat " << endl
		<< " 2 - Write a private message " << endl
		<< " 3 - Read general messages " << endl
		<< " 4 - Read private messages " << endl
		<< " 5 - View users " << endl
		<< " 6 - Delete account " << endl
		<< " 7 - Leave chat " << endl
		<< " >";
}

void printSystemInfo()
{
#if defined _WIN32 || _WIN64
	system("chcp 1251 > nul & systeminfo > systeminfo.txt");
	std::fstream OCinfo("systeminfo.txt", std::ios::in);

	string OCname, OCversion;

	getline(OCinfo, OCname); // Just for moving file pointer
	getline(OCinfo, OCname);

	getline(OCinfo, OCname);
	getline(OCinfo, OCversion);

	cout << OCname << endl
		<< OCversion << endl;

	OCinfo.close();
#elif defined __linux__
	struct utsname utsname; // объект для структуры типа utsname

	uname(&utsname); // передаем объект по ссылке

	// распечатаем на экране информацию об операционной системе
	// эту информацию нам вернуло ядро Linux в объекте utsname
	cout << "OS name: " << utsname.sysname << endl;
	cout << "Host name: " << utsname.nodename << endl;
	cout << "OS release: " << utsname.release << endl;
	cout << "OS version: " << utsname.version << endl;
	cout << "Architecture: " << utsname.machine << endl;
#elif
	cout << "OS is not identified" << endl;
#endif
}