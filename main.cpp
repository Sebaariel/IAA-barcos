#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include "Instances.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    Instances instances;
    instances.LoadInstances(argv[1]);
    instances.PrintInstances();

    return 0;
}
