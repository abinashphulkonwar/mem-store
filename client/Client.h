#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include "../stroage/Hash-table.h"
using namespace std;

struct CommandsStruch
{
    string Command;
    string Key;
    string Value;
};

class client
{
private:
    HTable *s;

public:
    client(bool isEnable);
    void API_Client();
    ~client();
    void mainHandler(string command, CommandsStruch *CommandStruch);
    bool Validate(CommandsStruch *CommandStruch);
    void CommandHandler(CommandsStruch *CommandStruch);
    string S_Tolower_Case(string val);
    string S_Toupper_Case(string val);
    void HelpHandler();
};

#endif
