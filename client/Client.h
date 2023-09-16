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
    client(/* args */);
    ~client();
    bool Validate(CommandsStruch *CommandStruch);
    void CommandHandler(CommandsStruch *CommandStruch);
    int data = 10;
};

#endif
