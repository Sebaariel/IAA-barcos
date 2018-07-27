#include "AssignedNode.h"

using namespace std;

class Solution {
    private:
        vector<AssignedNode> _assignedNodes;
        vector<Node> _noAssignedNodes;
        int _totalNodes;


    public:
        Solution(vector<Node> nodes);
        vector<AssignedNode> GetAssignedNodes( ) { return _assignedNodes; }
        vector<Node> GetNoAssignedNodes( ) { return _noAssignedNodes; }
        int GetTotalNodes( ) { return _totalNodes; }
        bool CheckFactibility(Node nextNode);
        void PrintAssignedNodesLine();
        void PrintAssignedNodes();
        void PrintNoAssignedNodesLine();

        void RemoveCandidate(Node node);
        void SetCandidates(vector<tuple<Node, float>> candidates){ _assignedNodes.back().SetCandidates(candidates); };

        //Constructor de soluciòn
        void AddAssignedNode(AssignedNode assignedNode){
            // cout << "@@@" << endl;
            // cout << "@@@Node to asign: " << assignedNode.GetNode().GetNumber() << endl;


            float prevTime = 0;
            float bestTime = assignedNode.GetBestTime();
            if (_assignedNodes.size() != 0){
                // cout << "@@@Node compare node: " << _assignedNodes.back().GetNode().GetNumber() << endl;
                prevTime = _assignedNodes.back().GetBestTime();
                // cout << "@@@@PrevBestTime:" << prevTime << endl;
                bestTime = assignedNode.GetNode().GetTotalMovementTime(_assignedNodes.back().GetNode());
            }

            //float bestTime = assignedNode.GetTotalMovementTime(_assignedNodes.back().GetNode());
            // cout << "@@@@CurrBestTime:" << bestTime << endl;
            // cout << "PrevBestTime:" << prevTime << endl;
            // cout << "CurrBestTime:" << bestTime << endl;
            // cout << "@@@@AddedTime:" << (prevTime + bestTime) << endl;
            assignedNode.SetBestTime(prevTime + bestTime);
            _assignedNodes.push_back(assignedNode);
            RemoveFromNoAssignedNodes(assignedNode.GetNode());
        };
        void AddNoAssignedNode(Node noAssignedNode){
            bool add = true;
            for (Node node : _noAssignedNodes){
                if (node.GetNumber() == noAssignedNode.GetNumber()){
                    add = false;
                    break;
                }
            }
            if (add){
                _noAssignedNodes.push_back(noAssignedNode);
            }

        };
        void SetNoAssignedNodes(vector<Node> noAssignedNode);
        void RemoveFromAssignedNodes(AssignedNode assignedNode);
        void RemoveFromNoAssignedNodes(Node noAssignedNode);
        bool CheckTimeWindow(Node nextNode);
};
