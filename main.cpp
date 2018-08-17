#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include <tuple>
#include <algorithm>
#include <vector>
#include "Instances.cpp"
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
    clock_t tStart = clock();
    Instances instances;
    instances.LoadInstances(argv[1]);

    //vector<int> solution(instances.GenerateInitialSolution(instances.GetNodes()));
    Solution solution(instances.GenerateInitialSolution(instances.GetNodes(), instances.GetVehicle()));

    solution.PrintAssignedNodes();
    cout << "Carga Inicial: " << solution.GetInitialCargo() << endl;
    cout << "Carga Final: " << solution.GetCurrentCargo() << endl;

    cout << "Carga màxima: " << solution.GetVehicle().GetTotalCapacity() << endl;
    //instances.PrintInstances();
    printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
