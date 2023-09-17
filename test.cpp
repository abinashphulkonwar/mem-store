#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

int main()
{
    string val = "Engineering Discipline.";

    for (int i = 0; i < val.length(); i++)
    {
        val[i] = toupper(val[i]);
    }
    cout << val << endl;
    return 1;
}