#ifndef LIST_APPLICATION_H
#define LIST_APPLICATION_H
#include <iostream>
#include <vector>

using namespace std;

const string NOT_FOUND_LIST = "NOT_FOUND_LIST";
const string FOUND_LIST = "FOUND_LIST";

class Node
{
public:
    Node *next;
    Node *prev;
    string value;
    Node(string val);
};

class LinkedList
{
private:
    Node *head;
    Node *tail;

public:
    int length;
    LinkedList(/* args */);
    ~LinkedList();
    void rPush(string val);
    void lPush(string val);
    void rRemove();
    void lRemove();
    pair<string, string> rGet();
    pair<string, string> lGet();
    // pair<int, int> getIndex(int idx);
    bool insertAt(int idx, string value);
    bool removeAt(int idx);
    void travers(int val);
    vector<string> lMap(int length);
    vector<string> rMap(int length);
};

#endif
