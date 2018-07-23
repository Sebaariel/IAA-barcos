#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
    private:
        vector<tuple<Node, float>> _assignedNodes;
        vector<Node> _noAssignedNodes;


    public:
        Solution(vector<Node> nodes);
        void AddAssignedNode( tuple<Node, float> assignedNode ) {
            _assignedNodes.push_back(assignedNode);
            int nodeNumber = (get<0>(assignedNode)).GetNumber();
            auto it = find_if(_noAssignedNodes.begin(), _noAssignedNodes.end(), [nodeNumber](Node& obj) {return (obj.GetNumber() == nodeNumber);});

            if (it != _noAssignedNodes.end()){
              auto index = std::distance(_noAssignedNodes.begin(), it);
              _noAssignedNodes.erase(_noAssignedNodes.begin() + index);
            }
        }

        vector<tuple<Node, float>> GetAssignedNodes( ) { return _assignedNodes; }
        vector<Node> GetNoAssignedNodes( ) { return _noAssignedNodes; }
        bool CheckFactibility( );
        void PrintNoAssignedNodes(){
            cout << "No Assigned Nodes = ";
            for (Node node : _noAssignedNodes){
                cout << node.GetNumber();
            }
            cout << endl;
        }
        void PrintAssignedNodes(){
            cout << "Assigned Nodes = ";
            for (tuple<Node, float> node : _assignedNodes){
                cout << (get<0>(node)).GetNumber();
            }
            cout << endl;
        }
};


Solution::Solution( vector<Node> nodes ) {
    for(Node node : nodes){
        _noAssignedNodes.push_back(node);
    }
}
