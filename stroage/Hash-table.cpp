#include <string>
#include <sstream>
#include "Hash-table.h"
#include "List.h"

HTable::HTable()
{
}

HTable::~HTable()
{
}

void HTable::SetText(string key, string value)
{
    this->CleareKey(key);
    Hash_Table_Records record;
    record.text = value;
    record.number = 0;
    record.type = 0;
    this->HMap[key] = record;
}
tuple<bool, int, string> HTable::SetNumber(string key, string value)
{
    this->CleareKey(key);

    int num;
    try
    {
        num = stoi(value);
        std::cout << "The converted integer value: " << num << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        cerr << "Invalid argument: " << e.what() << endl;
        tuple<bool, int, string> res(false, 0, "unable to convert " + value + " to number");
        return res;
    }
    catch (const std::out_of_range &e)
    {
        cerr << "Out of range: " << e.what() << endl;

        tuple<bool, int, string> res(false, 0, "unable to convert " + value + " to number");
        return res;
    }
    Hash_Table_Records record;
    record.text = "";
    record.number = num;
    record.type = 1;
    this->HMap[key] = record;
    tuple<bool, int, string> res(true, num, "");

    return res;
}

string HTable::GetText(string key)
{
    auto it = this->HMap.find(key);
    if (it != this->HMap.end())
    {
        if (it->second.number != 0)
        {
            return "";
        }
        return it->second.text;
    }
    else
    {
        return "";
    }
}
pair<bool, int> HTable::GetNumber(string key)
{
    auto it = this->HMap.find(key);
    if (it != this->HMap.end())
    {
        cout << it->second.number << " " << it->second.type << endl;
        if (it->second.type == 1)
        {
            return pair(true, it->second.number);
        }
    }

    return pair(false, 0);
}

pair<int, variant<int, string>> HTable::GetHandler(string key)
{
    variant<int, string> res;
    auto it = this->HMap.find(key);
    if (it != this->HMap.end())
    {
        int status = 0;
        Hash_Table_Records val = it->second;
        if (val.type == 0)
        {
            res = val.text;
            status = STATUS_FOUND_CODE_T;
        }
        else if (val.type == 1)
        {
            res = val.number;
            status = STATUS_FOUND_CODE_N;
        }

        return pair(status, res);
    }
    res = 0;
    return pair(STATUS_NOT_FOUND_CODE, res);
}

void HTable::CleareKey(string Key)
{
    auto it = this->HMap.find(Key);
    if (it != this->HMap.end())
    {
        if (it->second.type == 2)
        {
            delete it->second.List;
        }

        if (it->second.type == 0)
        {
            it->second.text = "";
        }
        if (it->second.type == 1)
        {
            it->second.number = 0;
        }
    }
}

bool HTable::SetListKey(string key)
{
    this->CleareKey(key);
    Hash_Table_Records record;
    record.type = 2;
    LinkedList *list = new LinkedList();
    record.List = list;

    this->HMap[key] = record;
    cout << this->HMap[key].type << key << "data" << endl;
    return true;
}

pair<int, string> HTable::GetListLR(string key, bool isLeft)
{
    auto it = this->HMap.find(key);
    if (it != this->HMap.end())
    {
        if (it->second.type == 2)
        {
            if (isLeft == true)
            {
                pair<std::string, std::string> res = it->second.List->lGet();

                return make_pair(STATUS_FOUND_CODE_L, res.second);
            }
            else
            {
                pair<std::string, std::string> res = it->second.List->rGet();
                return make_pair(STATUS_FOUND_CODE_L, res.second);
            }
        }
        else
        {
            cout << "list not set" << endl;
        }
    }

    return make_pair(STATUS_NOT_FOUND_CODE, "");
}
bool HTable::RemoveListLR(string key, bool isLeft)
{
    auto it = this->HMap.find(key);
    if (it != this->HMap.end())
    {
        if (it->second.type == 2)
        {
            if (isLeft == true)
            {
                it->second.List->lRemove();
                return true;
            }
            else
            {

                it->second.List->rRemove();

                return true;
            }
        }
        else
        {
            cout << "list not set" << endl;
        }
    }

    return false;
}

bool HTable::PushListLR(string key, string value, bool isLeft)

{
    cout
        << "push list start" << isLeft << key << value << endl;
    auto it = this->HMap.find(key);
    if (it != this->HMap.end())
    {
        cout << "list found" << endl;
        if (it->second.type == 2)
        {
            cout << "push list" << isLeft << key << value << endl;
            if (isLeft == true)
            {
                it->second.List->lPush(value);

                return true;
            }
            else
            {
                it->second.List->rPush(value);
                return true;
            }
        }
        else
        {
            cout << "list not set" << endl;
        }
    }

    return false;
}
