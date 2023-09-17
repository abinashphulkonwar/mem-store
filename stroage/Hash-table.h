#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <unordered_map>
#include <iostream>

using namespace std;

struct Hash_Table_Records
{
    string text;
    int number;
    int type; // 0 to text, 1 to number, 2 to list
};

class HTable
{
private:
    unordered_map<string, Hash_Table_Records> HMap;

public:
    HTable(/* args */);
    void SetText(string Key, string value);
    tuple<bool, int, string> SetNumber(string Key, string value);
    pair<bool, int> GetNumber(string Key);
    string GetText(string Key);
    ~HTable();
};

#endif
