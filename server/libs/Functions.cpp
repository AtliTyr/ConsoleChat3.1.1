#include "Functions.h"

void prefixDetection(string& pref, string& tmp)
{
    int i = 0;
    if (tmp.at(i) == '/')
    {
        while (tmp.at(i) != ' ')
        {
            pref.push_back(tmp.at(i));
            i++;
        }
        i++;
    }
    tmp = tmp.substr(tmp.find(' ') + 1, tmp.length());
}


#if defined _WIN32 || _WIN64
void commandProcessing(string pref, string tmp, bool& success, SOCKET ClientSocket)
{
    int i = 0;
    if (pref == "/reg")
    {
        string name = "";
        string log = "";
        string psw = "";

        i = 0;
        while (tmp.at(i) != ' ')
        {
            name.push_back(tmp.at(i));
            i++;
        }
        i++;
        while (tmp.at(i) != ' ')
        {
            log.push_back(tmp.at(i));
            i++;
        }
        i++;
        while (i != tmp.length())
        {
            psw.push_back(tmp.at(i));
            i++;
        }

        if (psw == " " || log == " " || name == " ")
            success = false;
        else
            success = chat1.Registration(name, log, psw);
    }
    else if (pref == "/auth")
    {
        string log = "";
        string psw = "";

        i = 0;
        while (tmp.at(i) != ' ')
        {
            log.push_back(tmp.at(i));
            i++;
        }
        i++;
        while (i != tmp.length())
        {
            psw.push_back(tmp.at(i));
            i++;
        }

        success = chat1.authorization(log, psw);
    }
    else if (pref == "/m")
    {
        string sender = "";
        string recepient = "";
        string text = "";

        i = 0;
        while (tmp.at(i) != ' ')
        {
            sender.push_back(tmp.at(i));
            i++;
        }
        i++;
        while (tmp.at(i) != ' ')
        {
            recepient.push_back(tmp.at(i));
            i++;
        }
        i++;
        while (i != tmp.length())
        {
            text.push_back(tmp.at(i));
            i++;
        }

        success = chat1.WriteMessage(sender, recepient, text);
    }
    else if (pref == "/del")
    {
        success = chat1.DeleteUser(tmp);
    }
    else if (pref == "/rul")
    {
        chat1.SendUsersList(ClientSocket);
    }
    else if (pref == "/rpm")
    {
        chat1.SendPrivateMessages(ClientSocket, tmp);
    }
    else if (pref == "/rgm")
    {
        chat1.SendGeneralMessages(ClientSocket);
    }
}
#elif defined __linux__
void commandProcessing(string pref, string tmp, bool& success, int connection)
{
    int i = 0;
    if (pref == "/reg")
    {
        string name = "";
        string log = "";
        string psw = "";

        i = 0;
        while (tmp.at(i) != ' ')
        {
            name.push_back(tmp.at(i));
            i++;
        }
        i++;
        while (tmp.at(i) != ' ')
        {
            log.push_back(tmp.at(i));
            i++;
        }
        i++;
        while (i != tmp.length())
        {
            psw.push_back(tmp.at(i));
            i++;
        }

        if (psw == " " || log == " " || name == " ")
            success = false;
        else
            success = chat1.Registration(name, log, psw);
    }
    else if (pref == "/auth")
    {
        string log = "";
        string psw = "";

        i = 0;
        while (tmp.at(i) != ' ')
        {
            log.push_back(tmp.at(i));
            i++;
        }
        i++;
        while (i != tmp.length())
        {
            psw.push_back(tmp.at(i));
            i++;
        }

        success = chat1.authorization(log, psw);
    }
    else if (pref == "/m")
    {
        string sender = "";
        string recepient = "";
        string text = "";

        i = 0;
        while (tmp.at(i) != ' ')
        {
            sender.push_back(tmp.at(i));
            i++;
        }
        i++;
        while (tmp.at(i) != ' ')
        {
            recepient.push_back(tmp.at(i));
            i++;
        }
        i++;
        while (i != tmp.length())
        {
            text.push_back(tmp.at(i));
            i++;
        }

        success = chat1.WriteMessage(sender, recepient, text);
    }
    else if (pref == "/del")
    {
        success = chat1.DeleteUser(tmp);
    }
    else if (pref == "/rul")
    {
        chat1.SendUsersList(connection);
    }
    else if (pref == "/rpm")
    {
        chat1.SendPrivateMessages(connection, tmp);
    }
    else if (pref == "/rgm")
    {
        chat1.SendGeneralMessages(connection);
    }
}
#endif
