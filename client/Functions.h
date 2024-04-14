#pragma once
#if defined _WIN32 || _WIN64
#include <Windows.h>
#elif defined __linux__
#include <unistd.h>
#include <sys/utsname.h>
#endif

#include <string>
#include <iostream>
#include <fstream>


using namespace std;

bool Registration(string& command);
bool Authorization(string& command, string& login);

void DisplayValidUsers();
string loginRequest();

void Menu1();
void Menu2();

void printSystemInfo();
