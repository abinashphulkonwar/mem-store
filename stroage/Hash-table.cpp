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

string HTable::GetText(string key)
{
    auto it = this->HMap.find(key);
    if (it != this->HMap.end())
    {
        return it->second.text;
    }
    else
    {
        return "";
    }
}