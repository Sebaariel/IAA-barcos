#include "Objets/Node.h"
#include "Objets/Vehicle.h"
#include "Objets/Terminal.h"
#include <vector>


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
};
