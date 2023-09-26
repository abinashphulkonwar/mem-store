#include "List.h"

Node::Node(string val)
{
    this->value = val;
    this->next = nullptr;
    this->prev = nullptr;
}

LinkedList::LinkedList(/* args */)
{
    this->length = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

void LinkedList::rPush(string val)
{
    Node *node = new Node(val);
    if (this->length == 0)
    {
        this->head = node;
        this->tail = node;
        this->length++;
        return;
    }
    // 1,  2
    this->length++;

    this->tail->next = node;
    node->prev = this->tail;
    this->tail = node;
    return;
}
void LinkedList::rRemove()
{
    if (this->length == 0)
    {
        return;
    }

    this->length--;
    Node *node = this->tail;

    if (this->head == this->tail)
    {
        this->head = nullptr;
        this->tail = nullptr;
        delete node;
        return;
    }

    this->tail = node->prev;

    delete node;
}

void LinkedList::lPush(string val)
{
    Node *node = new Node(val);
    if (this->length == 0)
    {
        this->head = node;
        this->tail = node;
        this->length++;
        return;
    }
    // 1,  2
    this->length++;

    this->head->prev = node;
    node->next = this->head;
    this->head = node;
    return;
}

void LinkedList::lRemove()
{
    if (this->length == 0)
    {
        return;
    }

    this->length--;
    Node *node = this->head;
    if (this->head == this->tail)
    {
        delete node;

        this->head = nullptr;
        this->tail = nullptr;
        return;
    }

    this->head = node->next;

    delete node;
}

pair<string, string> LinkedList::rGet()
{
    if (this->length == 0)
    {
        return pair(NOT_FOUND_LIST, "");
    }
    cout << this->tail->value << endl;
    return pair(FOUND_LIST, this->tail->value);
}
pair<string, string> LinkedList::lGet()
{
    if (this->length == 0)
    {
        return pair(NOT_FOUND_LIST, "");
    }
    cout << this->head->value << endl;
    return pair(FOUND_LIST, this->head->value);
}

bool LinkedList::insertAt(int idx, string val)
{
    if (idx > this->length)
    {
        return false;
    }
    else if (idx == 0)
    {
        this->lPush(val);
        return true;
    }
    else if (idx == this->length)
    {
        this->rPush(val);
        return true;
    }

    this->length++;
    Node *node = new Node(val);

    Node *current = this->head;
    cout << "data " << current->value << endl;

    for (int i = 0; i < idx; i++)
    {
        current = current->next;
    }
    cout << "data " << current->value << endl;
    current->prev->next = node;
    node->prev = current->prev;
    node->next = current;
    current->prev = node;
    return true;
}
bool LinkedList::removeAt(int idx)
{
    if (idx > this->length)
    {
        return false;
    }
    else if (idx == 0)
    {
        this->lRemove();
        return true;
    }
    else if (idx == this->length)
    {
        this->rRemove();
        return true;
    }

    this->length--;

    Node *current = this->head;
    //  cout << "data remove " << current->value << endl;

    for (int i = 0; i < idx; i++)
    {
        current = current->next;
    }
    //  cout << "data remove " << current->prev->value << " " << current->value << " " << current->next->value << endl;
    current->prev->next = current->next;
    current->next->prev = current->prev;

    delete current;

    return true;
}

void LinkedList::travers(int val)
{

    if (val == 1)
    {
        Node *current = this->tail;
        cout << "from tail :" << endl;

        for (int i = 0; i < this->length; i++)
        {
            cout << current->value << endl;
            current = current->prev;
        }
    }
    else
    {
        Node *current = this->head;
        cout << "from head :" << endl;

        for (int i = 0; i < this->length; i++)
        {
            cout << current->value << endl;
            current = current->next;
        }
    }
}

vector<string> LinkedList::lMap(int length)
{
    if (length > 50)
    {
        length = 50;
    }
    if (length > this->length)
    {
        length = this->length;
    }
    vector<string> vec(length);
    if (this->length == 0)
    {
        return vec;
    }

    Node *current = this->head;

    for (int i = 0; i < length; i++)
    {
        vec[i] = current->value;
        cout << "count " << i << " " << current->value << endl;

        current = current->next;
    }

    return vec;
}
vector<string> LinkedList::rMap(int length)
{
    if (length > 50)
    {
        length = 50;
    }
    if (length > this->length)
    {
        length = this->length;
    }
    vector<string> vec(length);
    if (this->length == 0)
    {
        return vec;
    }

    Node *current = this->tail;

    for (int i = 0; i < length; i++)
    {
        vec[i] = current->value;
        cout << "count " << i << " " << current->value << endl;

        current = current->prev;
    }

    return vec;
}

LinkedList::~LinkedList()
{
    Node *current = this->head;

    while (current)
    {
        Node *next = current->next;

        delete current;

        current = next;
    }
    this->head = nullptr;
    this->tail = nullptr;
}
