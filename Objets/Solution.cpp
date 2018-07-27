#include "Solution.h"


using namespace std;

Solution::Solution( vector<Node> nodes ) {
    for (Node node : nodes){
        _noAssignedNodes.push_back(node);
    }

    _totalNodes = _noAssignedNodes.size();
}

bool Solution::CheckFactibility(Node nextNode){
    // float zero = 0;
    // Node lastNode = assignedNodes.back().GetNode();
    // float t_i = _assignedNodes.back().GetBestTime();
    // float T_ij = lastNode.GetTotalMovementTime(nextNode);
    // float t_j = t_i + T_ij;
    // float M_ij = max(zero, lastNode.GetUpperTimeWindow() + T_ij - nextNode.GetLowerTimeWindow());
    return CheckTimeWindow(nextNode);
}

bool Solution::CheckTimeWindow(Node nextNode){
    Node lastNode = _assignedNodes.back().GetNode();
    float t_i = _assignedNodes.back().GetBestTime();
    // for (AssignedNode assignedNode : _assignedNodes){
    //     t_i = t_i + assignedNode.GetBestTime();
    // }
    //float t_i = _assignedNodes.back().GetBestTime();
    float T_ij = lastNode.GetTotalMovementTime(nextNode);
    float t_j = t_i + T_ij;
    // if (nextNode.GetLowerTimeWindow() <= t_j && t_j <= nextNode.GetUpperTimeWindow()){
        cout << "t_i: " << t_i << endl;
        cout << "T_ij: " << T_ij << endl;
        cout << "Time to j: " << t_j << endl;
        cout << "Time windows: " << nextNode.GetLowerTimeWindow() << " - " << nextNode.GetUpperTimeWindow() << endl;
    // }

    return (nextNode.GetLowerTimeWindow() <= t_j && t_j <= nextNode.GetUpperTimeWindow());
}

void Solution::RemoveFromAssignedNodes(AssignedNode assignedNode){
    int nodeNumber = assignedNode.GetNode().GetNumber();

    auto it = find_if(_assignedNodes.begin(),
                        _assignedNodes.end(),
                        [nodeNumber](AssignedNode& obj) {
                            return (obj.GetNode().GetNumber() == nodeNumber);
                        });
    if (it != _assignedNodes.end()){
      auto index = distance(_assignedNodes.begin(), it);
      _assignedNodes.erase(_assignedNodes.begin() + index);
    }
}

void Solution::RemoveFromNoAssignedNodes(Node assignedNode){
    int nodeNumber = assignedNode.GetNumber();

    auto it = find_if(_noAssignedNodes.begin(),
                        _noAssignedNodes.end(),
                        [nodeNumber](Node& obj) {
                            return (obj.GetNumber() == nodeNumber);
                        });
    if (it != _noAssignedNodes.end()){
      auto index = distance(_noAssignedNodes.begin(), it);
      _noAssignedNodes.erase(_noAssignedNodes.begin() + index);
    }
}

void Solution::SetNoAssignedNodes(vector<Node> noAssignedNodes){
    _noAssignedNodes.clear();
    for (Node node : noAssignedNodes){
        _noAssignedNodes.push_back(node);
    }
}

void Solution::RemoveCandidate(Node node){
    _assignedNodes.back().RemoveFromCandidate(node);
}

void Solution::PrintAssignedNodesLine(){
    cout << "Assigned Nodes: ";
    for (AssignedNode assignedNode : _assignedNodes){
        cout << assignedNode.GetNode().GetNumber();
    }
    cout << endl;
}


void Solution::PrintNoAssignedNodesLine(){
    cout << "No Assigned Nodes: ";
    for (Node noAssignedNode : _noAssignedNodes){
        cout << noAssignedNode.GetNumber();
    }
    cout << endl;
}

void Solution::PrintAssignedNodes(){
    cout << "Assigned Nodes: " << endl;
    for (AssignedNode assignedNode : _assignedNodes){
        cout << "Node: " << assignedNode.GetNode().GetNumber() << " Terminal: " << assignedNode.GetNode().GetTerminal().GetName() << " Time: " << assignedNode.GetBestTime() << endl;
        // cout << "------" << endl;
        // assignedNode.PrintCandidates();
        // cout << "------" << endl;


    }
    cout << endl;
}
