#ifndef LIST_APPLICATION_H
#define LIST_APPLICATION_H
#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    Node *next;
    Node *prev;
    int value;
    Node(int val);
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
    void rPush(int val);
    void lPush(int val);
    void rRemove();
    void lRemove();
    pair<int, int> rGet();
    pair<int, int> lGet();
    // pair<int, int> getIndex(int idx);
    int insertAt(int idx, int value);
    int removeAt(int idx);
    void travers(int val);
    vector<int> lMap(int length);
    vector<int> rMap(int length);
};

#endif
