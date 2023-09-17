#include <string>
#include <sstream>
#include <cstring>
#include "Client.h"

const string SET_COMMAND = "SET";
const string GET_COMMAND = "GET";

client::client(bool isEnable)
{
    HTable *hTable = new HTable();
    this->s = hTable;

    if (isEnable != true)
    {
        return;
    }

    string command;

    CommandsStruch CommandStruch;

    while (true)
    {

        CommandStruch.Command = "";
        CommandStruch.Key = "";
        CommandStruch.Value = "";
        cout << "> ";
        getline(cin, command);
        this->mainHandler(command, &CommandStruch);
    }
}

void client::mainHandler(string command, CommandsStruch *CommandStruch)
{
    if (command == "exit")
    {
        return;
    }

    if (this->S_Tolower_Case(command) == "help")
    {
        this->HelpHandler();
        return;
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
            return;
        }
        if (count == 0)
        {
            CommandStruch->Command = this->S_Toupper_Case(token);
        }
        if (count == 1)
        {
            CommandStruch->Key = token;
        }
        if (count == 2)
        {
            CommandStruch->Value = token;
        }
        if (count >= 3)
        {
            CommandStruch->Value = CommandStruch->Value + " " + token;
        }
        count++;
        if (token == "exit")
        {
            return;
        }
    }
    bool isValid = this->Validate(CommandStruch);
    if (isValid == false)
    {
        return;
    }
    this->CommandHandler(CommandStruch);
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
            cout << "Recored not found \nstatus: 'NULL'" << endl;
        }
    }
    else
    {
        cout << "Enable to Process \nstatus: 'NOT_OK'" << endl;
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

string client::S_Tolower_Case(string val)
{

    for (int i = 0; i < val.length(); i++)
    {
        val[i] = tolower(val[i]);
    }
    return val;
}
string client::S_Toupper_Case(string val)
{

    for (int i = 0; i < val.length(); i++)
    {
        val[i] = toupper(val[i]);
    }
    return val;
}

void client::HelpHandler()
{
    cout << "Commands: " << endl;
    cout << "SET: use to set a value (Type of STRING) with a Key. \n [SET Key1 value1] " << endl;
    cout << "GET: use to query any data associated with a key. \n [GET Key1] " << endl;
}

void client::API_Client()
{
}

client::~client()
{
    cout << "exit the process";
}
