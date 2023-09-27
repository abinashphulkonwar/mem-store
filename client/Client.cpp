#include <string>
#include <sstream>
#include <cstring>
#include "Client.h"

const string GET_COMMAND = "GET";
const string SET_COMMAND_S = "SET";
const string GET_COMMAND_S = "SGET";
const string SET_COMMAND_N = "NSET";
const string GET_COMMAND_N = "NGET";
const string SET_COMMAND_L = "LSET";
const string GET_COMMAND_L = "LGET";
const string GET_COMMAND_R = "RGET";
const string LPUSH_COMMAND = "LPUSH";
const string RPUSH_COMMAND = "RPUSH";
const string LREMOVE_COMMAND = "LREMOVE";
const string RREMOVE_COMMAND = "RREMOVE";

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
        if (command == "exit")
        {
            return;
        }
        this->mainHandler(command, &CommandStruch);
    }
}

void client::mainHandler(string command, CommandsStruch *CommandStruch)
{

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

        if (count <= 1 && token == "")
        {
            continue;
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
    }
    cout << CommandStruch->Value.length() << endl;
    if (CommandStruch->Value.length() > 0)
    {
        CommandStruch->Value.erase(0, CommandStruch->Value.find_first_not_of(" \t\r\n"));
    }
    if (CommandStruch->Value.length() > 0)
    {
        CommandStruch->Value.erase(CommandStruch->Value.find_last_not_of(" \t\r\n") + 1);
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
    string command = CommandStruch->Command;

    if (command == GET_COMMAND)
    {
        pair<int, variant<int, string>> data = this->s->GetHandler(CommandStruch->Key);

        if (data.first == STATUS_FOUND_CODE_T)
        {
            cout << "Recored: " << get<string>(data.second) << "\n"
                 << "status: 'OK'"
                 << endl;
            return;
        }
        if (data.first == STATUS_FOUND_CODE_N)
        {
            cout << "Recored: " << get<int>(data.second) << "\n"
                 << "status: 'OK'"
                 << endl;
            return;
        }

        if (data.first == STATUS_NOT_FOUND_CODE || data.first == STATUS_ERROR_CODE)
        {
            cout << "Recored not found \nstatus: 'NULL'" << endl;
            return;
        }
    }

    if (command == GET_COMMAND_S)
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
        return;
    }

    if (command == GET_COMMAND_N)
    {
        pair<bool, int> data = this->s->GetNumber(CommandStruch->Key);
        if (data.first == true)
        {
            cout << "Recored: " << data.second << "\n"
                 << "status: 'OK'"
                 << endl;
        }
        else
        {
            cout << "Recored not found \nstatus: 'NULL'" << endl;
        }
        return;
    }
    if (command == SET_COMMAND_N)
    {
        tuple<bool, int, string> res = this->s->SetNumber(CommandStruch->Key, CommandStruch->Value);

        if (get<0>(res) == true)
        {

            cout << "Recored: "
                 << get<1>(res)
                 << "\nstatus: 'OK'"
                 << endl;
        }
        else
        {
            cout << "Error: " << get<2>(res) << "\nstatus: 'NULL'" << endl;
        }
        return;
    }

    if (command == SET_COMMAND_S)
    {
        this->s->SetText(CommandStruch->Key, CommandStruch->Value);
        cout << "Recored Added status: 'OK'" << endl;
        return;
    }

    if (command == SET_COMMAND_L)
    {
        this->s->SetListKey(CommandStruch->Key);
        cout << "Recored Added status: 'OK'" << endl;
        return;
    }

    if (command == GET_COMMAND_L || command == GET_COMMAND_R)
    {
        bool isLeft = false;
        if (command == GET_COMMAND_L)
            isLeft = true;
        pair<int, std::string> res = this->s->GetListLR(CommandStruch->Key, isLeft);
        if (res.first == STATUS_FOUND_CODE_L)
        {
            cout << "Recored Added status: 'OK'\nvalue: " << res.second << endl;
            return;
        }
        else
        {
            cout << "Recored not Added status: 'NOT_OF'\nvalue: " << res.second << endl;
            return;
        }
    }
    if (command == LPUSH_COMMAND || command == RPUSH_COMMAND)
    {
        bool isLeft = false;
        if (command == LPUSH_COMMAND)
            isLeft = true;
        bool res = this->s->PushListLR(CommandStruch->Key, CommandStruch->Value, isLeft);
        if (res == true)
        {
            cout << "Recored Added status: 'OK'" << endl;
            return;
        }
        else
        {
            cout << "Recored not Added status: 'NOT_OF'" << endl;
            return;
        }
    }

    if (command == LREMOVE_COMMAND || command == RREMOVE_COMMAND)
    {
        bool isLeft = false;
        if (command == LPUSH_COMMAND)
            isLeft = true;

        bool res = this->s->RemoveListLR(CommandStruch->Key, isLeft);
        if (res == true)
        {
            cout << "Recored Removed status: 'OK' " << endl;
            return;
        }
        else
        {
            cout << "Recored not removed status: 'NOT_OF'" << endl;
            return;
        }
    }

    cout << "Enable to Process \nstatus: 'NOT_OK'" << endl;
    return;
}

bool client::Validate(CommandsStruch *CommandStruch)
{

    string command = CommandStruch->Command;
    if (command != GET_COMMAND && command != SET_COMMAND_S &&
        command != GET_COMMAND_S && command != SET_COMMAND_N && command != GET_COMMAND_N && command != SET_COMMAND_L && command != GET_COMMAND_L && command != GET_COMMAND_R && command != LPUSH_COMMAND && command != RPUSH_COMMAND && command != LREMOVE_COMMAND && command != RREMOVE_COMMAND)
    {
        cout << "error: Command need to be SET or GET or NSET or NGET or LIST commands" << endl;
        return false;
    }

    if ((command == SET_COMMAND_S || command == SET_COMMAND_N || command == LPUSH_COMMAND || command == RPUSH_COMMAND) && (CommandStruch->Key == "" || CommandStruch->Value == ""))
    {
        cout << "error: Command SET or NSET need both key and value [SET key1 value1]" << endl;
        return false;
    }

    if ((command == SET_COMMAND_L || command == LREMOVE_COMMAND || command == RREMOVE_COMMAND) && CommandStruch->Key == "")
    {
        cout << "error: Command LSET need key [SET key1]" << endl;
        return false;
    }

    if ((command == GET_COMMAND || command == GET_COMMAND_S || command == GET_COMMAND_N || command == GET_COMMAND_L || command == GET_COMMAND_R) && CommandStruch->Key == "")
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
    cout << "Available Commands: \n"
         << endl;
    cout << "STRINGS: \n"
         << endl;
    // Document the SET command
    cout << "SET: Set a value associated with a key." << endl;
    cout << "Usage: SET <Key> <Value>" << endl;
    cout << "Example: SET Key1 Value1" << endl;
    cout << "Description: Use the SET command to store a STRING value with a specific key.\n"
         << endl;

    // Document the GET command
    cout << "GET: Retrieve data associated with a key." << endl;
    cout << "Usage: GET <Key>" << endl;
    cout << "Example: GET Key1" << endl;
    cout << "Description: Use the GET command to retrieve the data associated with a specific key.\n"
         << endl;

    cout << "NUMBERS: \n"
         << endl;

    // Document the SET command
    cout << "NSET: Set a value associated with a key." << endl;
    cout << "Usage: NSET <Key> <Value>" << endl;
    cout << "Example: NSET Key1 892" << endl;
    cout << "Description: Use the NSET command to store a INT value with a specific key.\n"
         << endl;

    // Document the GET command
    cout << "NGET: Retrieve data associated with a key." << endl;
    cout << "Usage: NGET <Key>" << endl;
    cout << "Example: NGET Key1" << endl;
    cout << "Description: Use the NGET command to retrieve the data associated with a specific key.\n"
         << endl;

    cout << "Note: Key should not contain spaces." << endl;
}

void client::API_Client()
{
}

client::~client()
{
    cout << "exit the process";
}
