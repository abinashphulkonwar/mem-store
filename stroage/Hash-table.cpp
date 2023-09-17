#include <string>
#include <sstream>
#include "Hash-table.h"

HTable::HTable()
{
}

HTable::~HTable()
{
}

void HTable::SetText(string key, string value)
{

    Hash_Table_Records record;
    record.text = value;
    record.number = 0;
    record.type = 0;
    this->HMap[key] = record;
}
tuple<bool, int, string> HTable::SetNumber(string key, string value)
{

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