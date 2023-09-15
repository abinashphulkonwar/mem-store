#include <iostream>
#include <vector>
#include "./client/Client.h"

int main()
{
    client *new_client = new client();
    delete new_client;
    return 1;
}