#include <string>
#include <sstream>
#include "Client.h"

const string SET_COMMAND = "SET";
const string GET_COMMAND = "GET";

client::client(/* args */)
{
    HTable *hTable = new HTable();
    this->s = hTable;
    string command;

    CommandsStruch CommandStruch;

    while (true)
    {

        CommandStruch.Command = "";
        CommandStruch.Key = "";
        CommandStruch.Value = "";
        cout << "> ";
        getline(cin, command);
        if (command == "exit")
        {
            break;
        }

        //   cout << command << endl;

        size_t pos = 0;

        command = command + " ";
        int count = 0;

        while ((pos = command.find(' ')) != string::npos)
        {

            string token = command.substr(0, pos);
            //   cout << "Token: " << token << endl;
            command.erase(0, pos + 1);

            if (token == "")
            {
                continue;
            }
            if (count == 0)
            {
                CommandStruch.Command = token;
            }
            if (count == 1)
            {
                CommandStruch.Key = token;
            }
            if (count == 2)
            {
                CommandStruch.Value = token + " " + command;
            }
            count++;
            if (token == "exit")
            {
                return;
            }
        }
        cout << CommandStruch.Command << " " << CommandStruch.Key << " " << CommandStruch.Value << endl;
        bool isValid = this->Validate(&CommandStruch);
        if (isValid == false)
        {
            continue;
        }
        this->CommandHandler(&CommandStruch);
    }
}

void client::CommandHandler(CommandsStruch *CommandStruch)
{

    if (CommandStruch->Command == SET_COMMAND)
    {
        this->s->SetText(CommandStruch->Key, CommandStruch->Value);
        cout << "Recored Added status: 'OK'" << endl;
    }
    else if (CommandStruch->Command == GET_COMMAND)
    {
        string data = this->s->GetText(CommandStruch->Key);
        if (data != "")
        {
            cout << "Recored: " << data << "\n"
                 << "status: 'OK'"
                 << endl;
        }
        else
        {
            cout << "Recored not, status: 'OK'" << endl;
        }
    }
    else
    {
        cout << "Enable to Process status: 'NOT_OK'" << endl;
    }
}

bool client::Validate(CommandsStruch *CommandStruch)
{

    if (CommandStruch->Command != SET_COMMAND &&
        CommandStruch->Command != GET_COMMAND)
    {
        cout << "error: Command need to be SET or GET" << endl;
        return false;
    }

    if (CommandStruch->Command == SET_COMMAND && (CommandStruch->Key == "" || CommandStruch->Value == ""))
    {
        cout << "error: Command SET need both key and value [SET key1 value1]" << endl;
        return false;
    }
    if (CommandStruch->Command == GET_COMMAND && CommandStruch->Key == "")
    {
        cout << "error: Command GET need key of the Recored [GET key1]" << endl;
        return false;
    }
    return true;
}

client::~client()
{
    cout << "exit the process";
}
