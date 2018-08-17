#include "Objets/Node.cpp"
#include "Objets/Vehicle.h"
#include "Objets/Solution.cpp"


using namespace std;

class Instances {
    private:
        vector<Terminal> _listOfTerminals;
        vector<Node> _listOfNodes;
        Vehicle _vehicle;

    public:
        void PrintInstances();
        void LoadInstances(string instance);

        vector<Terminal> GetTerminals(){ return _listOfTerminals; }
        vector<Node> GetNodes(){ return _listOfNodes; }
        Vehicle GetVehicle(){ return _vehicle; }
        Solution GenerateInitialSolution(vector<Node> nodes, Vehicle vehicle);
};
