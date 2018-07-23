#include <tuple>

using namespace std;

class Solution {
    private:
        vector<tuple<Node, float>> _assignedNodes;
        vector<Node> _noAssignedNodes;


    public:
        Solution(vector<Node> nodes);
        // void AddAssignedNode( tuple<Node, float> assignedNode ) {
        //     _assignedNodes.push_back(assignedNode);
        //     _noAssignedNodes.erase(remove(_noAssignedNodes.begin(), _noAssignedNodes.end(), get<0>(assignedNode)), _noAssignedNodes.end());
        // }

        vector<tuple<Node, float>> GetAssignedNodes( ) { return _assignedNodes; }
        vector<Node> GetNoAssignedNodes( ) { return _noAssignedNodes; }
        bool CheckFactibility( );
};


Solution::Solution( vector<Node> nodes ) {
    for(Node node : nodes){
        _noAssignedNodes.push_back(node);
    }
}
