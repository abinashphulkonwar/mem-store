#include <iostream>
#include <string>
#include <sstream>
#include "Client.h"

using namespace std;

client::client(/* args */)
{
    string command;

    while (true)
    {
        cout << "> ";
        getline(cin, command);
        if (command == "exit")
        {
            break;
        }

        cout << command << endl;

        size_t pos = 0;

        while ((pos = command.find(' ')) != string::npos)
        {

            string token = command.substr(0, pos);
            cout << "Token: " << token << "val" << endl;

            command.erase(0, pos + 1);

            if (token == "exit")
            {
                return;
            }
        }
    }
}

client::~client()
{
    cout << "exit the process";
}
