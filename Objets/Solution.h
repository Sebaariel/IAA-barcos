#include "AssignedNode.h"

using namespace std;

class Solution {
    private:
        vector<AssignedNode> _assignedNodes;
        vector<Node> _noAssignedNodes;
        int _totalNodes;
        float _initialCargo;
        float _currentCargo;
        Vehicle _vehicle;


    public:
        Solution(vector<Node> nodes);
        void SetVehicle( Vehicle vehicle) { _vehicle = vehicle; }
        Vehicle GetVehicle(){ return _vehicle; }
        vector<AssignedNode> GetAssignedNodes( ) { return _assignedNodes; }
        vector<Node> GetNoAssignedNodes( ) { return _noAssignedNodes; }
        int GetTotalNodes( ) { return _totalNodes; }
        float GetCurrentCargo( ) { return _currentCargo; }
        float GetInitialCargo(){ return _initialCargo; }
        bool CheckFactibility(Node nextNode);
        void PrintAssignedNodesLine();
        void PrintAssignedNodes();
        void PrintNoAssignedNodesLine();

        void RemoveCandidate(Node node);
        void SetCandidates(vector<tuple<Node, float>> candidates){ _assignedNodes.back().SetCandidates(candidates); };
        void AddAssignedNode(AssignedNode assignedNode);
        void AddNoAssignedNode(Node noAssignedNode);
        void SetNoAssignedNodes(vector<Node> noAssignedNode);
        void RemoveFromAssignedNodes(AssignedNode assignedNode);
        void RemoveFromNoAssignedNodes(Node noAssignedNode);
        bool CheckTimeWindow(Node nextNode);
        bool CheckShipCapacity(Node nextNode);
        bool CheckDraftLimit(Node nextNode);
};
