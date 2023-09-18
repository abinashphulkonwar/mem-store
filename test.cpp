#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;
union UnionVal
{
    char a;
    float b;
    int c;
};

int main()
{

    union UnionVal valueUnion;

    valueUnion.a = 'a';

    cout << valueUnion.a << " " << endl;
    cout << valueUnion.b << " " << endl;
    cout << valueUnion.t << " " << endl;
    valueUnion.c = 986088876;

    cout << valueUnion.a << " " << endl;
    cout << valueUnion.b << " " << endl;
    cout << valueUnion.c << " " << endl;

    // const char *input = "dd123"; // Input string
    // int intValue = stoi(input);

    // try
    // {
    //     intValue = stoi(input);
    //     cout << "The converted integer value: " << intValue << endl;
    // }
    // catch (const std::invalid_argument &e)
    // {
    //     cerr << "Invalid argument: " << e.what() << endl;
    // }
    // catch (const std::out_of_range &e)
    // {
    //     cerr << "Out of range: " << e.what() << endl;
    // }
    return 1;
}