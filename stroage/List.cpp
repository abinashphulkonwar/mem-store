#include "List.h"

Node::Node(int val)
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

void LinkedList::rPush(int val)
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

    if (this->head == this->tail)
    {
        this->head = nullptr;
        this->tail = nullptr;
    }

    Node *node = this->tail;
    this->tail = node->prev;

    delete node;
}

void LinkedList::lPush(int val)
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

    if (this->head == this->tail)
    {
        this->head = nullptr;
        this->tail = nullptr;
    }

    Node *node = this->head;
    this->head = node->next;

    delete node;
}

pair<int, int> LinkedList::rGet()
{
    if (this->length == 0)
    {
        return pair(-1, -1);
    }
    cout << this->tail->value << endl;
    return pair(1, this->tail->value);
}
pair<int, int> LinkedList::lGet()
{
    if (this->length == 0)
    {
        return pair(-1, -1);
    }
    cout << this->head->value << endl;
    return pair(1, this->head->value);
}

int LinkedList::insertAt(int idx, int val)
{
    if (idx > this->length)
    {
        return -1;
    }
    else if (idx == 0)
    {
        this->lPush(val);
        return 1;
    }
    else if (idx == this->length)
    {
        this->rPush(val);
        return 1;
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
    return 1;
}
int LinkedList::removeAt(int idx)
{
    if (idx > this->length)
    {
        return -1;
    }
    else if (idx == 0)
    {
        this->lRemove();
        return 1;
    }
    else if (idx == this->length)
    {
        this->rRemove();
        return 1;
    }

    this->length--;

    Node *current = this->head;
    cout << "data remove " << current->value << endl;

    for (int i = 0; i < idx; i++)
    {
        current = current->next;
    }
    cout << "data remove " << current->prev->value << " " << current->value << " " << current->next->value << endl;
    current->prev->next = current->next;
    current->next->prev = current->prev;

    delete current;

    return 1;
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

vector<int> LinkedList::lMap(int length)
{
    if (length > 50)
    {
        length = 50;
    }
    if (length > this->length)
    {
        length = this->length;
    }
    vector<int> vec(length);
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
vector<int> LinkedList::rMap(int length)
{
    if (length > 50)
    {
        length = 50;
    }
    if (length > this->length)
    {
        length = this->length;
    }
    vector<int> vec(length);
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
