#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <unordered_map>
#include <iostream>
#include <variant>
#include "../status-code/status-code.h"
#include "List.h"

using namespace std;

struct Hash_Table_Records
{
    string text;
    int number;
    LinkedList *List;
    int type; // 0 to text, 1 to number, 2 to list
};

class HTable
{
private:
    unordered_map<string, Hash_Table_Records> HMap;

public:
    HTable(/* args */);
    void SetText(string Key, string value);
    pair<int, variant<int, string>> GetHandler(string key);
    tuple<bool, int, string> SetNumber(string Key, string value);
    pair<bool, int> GetNumber(string Key);
    string GetText(string Key);
    void CleareKey(string key);
    ~HTable();
};

#endif
