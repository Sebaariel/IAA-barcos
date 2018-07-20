#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include "Instances.cpp"
#include "Solution.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    Instances instances;
    instances.LoadInstances(argv[1]);

    instances.GetInitialSolution();
    //instances.PrintInstances();

    return 0;
}
