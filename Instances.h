#include "Objets/Node.cpp"
#include "Objets/Solution.h"
#include "Objets/Vehicle.h"

using namespace std;

class Instances {
    private:
        vector<Terminal> _listOfTerminals;
        vector<Node> _listOfNodes;
        vector<Vehicle> _listOfVehicles;

    public:
        void PrintInstances();
        void LoadInstances(string instance);

        vector<Terminal> GetTerminals(){ return _listOfTerminals; }
        vector<Node> GetNodes(){ return _listOfNodes; }
        vector<Vehicle> GetVehicles(){ return _listOfVehicles; }
        Solution GenerateInitialSolution(vector<Node> nodes);
};
