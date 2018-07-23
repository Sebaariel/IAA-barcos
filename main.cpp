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

    vector<int> solution(instances.GenerateInitialSolution(instances.GetNodes()));
    //Solution solution(instances.GetNodes());

    for(int i : solution)
        cout << "Node = " << i << endl;
    //instances.PrintInstances();

    return 0;
}
