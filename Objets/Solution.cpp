#include "Solution.h"


using namespace std;

Solution::Solution( vector<Node> nodes ) {
    for (Node node : nodes){
        _noAssignedNodes.push_back(node);
        if (node.GetCargoLoad() < 0){
            _currentCargo = _currentCargo - node.GetCargoLoad();
            _initialCargo = _initialCargo - node.GetCargoLoad();
        }
    }
    //_initialCargo = _currentCargo;
    _totalNodes = _noAssignedNodes.size();
}

void Solution::AddAssignedNode(AssignedNode assignedNode){
    float prevTime = 0;
    float bestTime = assignedNode.GetBestTime();
    if (_assignedNodes.size() != 0){
        prevTime = _assignedNodes.back().GetBestTime();
        bestTime = assignedNode.GetNode().GetTotalMovementTime(_assignedNodes.back().GetNode()); //TODO: verificar
    }
    assignedNode.SetBestTime(prevTime + bestTime);
    _assignedNodes.push_back(assignedNode);
    _currentCargo = _currentCargo + assignedNode.GetNode().GetCargoLoad();
    RemoveFromNoAssignedNodes(assignedNode.GetNode());
};

void Solution::AddNoAssignedNode(Node noAssignedNode){
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

bool Solution::CheckFactibility(Node nextNode){
    bool factibleCapacity = CheckShipCapacity(nextNode);
    bool factibleTimeWindow = CheckTimeWindow(nextNode);
    bool factibleDraftLimit = CheckDraftLimit(nextNode);

    return (factibleCapacity && factibleTimeWindow && factibleDraftLimit);
}

bool Solution::CheckTimeWindow(Node nextNode){
    Node lastNode = _assignedNodes.back().GetNode();
    float t_i = _assignedNodes.back().GetBestTime();
    float T_ij = lastNode.GetTotalMovementTime(nextNode);
    float t_j = t_i + T_ij;
    return (nextNode.GetLowerTimeWindow() <= t_j && t_j <= nextNode.GetUpperTimeWindow());
}

bool Solution::CheckShipCapacity(Node nextNode){
    if (nextNode.GetCargoType() == 1){
        //cout << "Verificaciòn de carga: " << ((_currentCargo + nextNode.GetCargoLoad()) < _vehicle.GetTotalCapacity()) << endl;
        return ((_currentCargo + nextNode.GetCargoLoad()) < _vehicle.GetTotalCapacity());
    } else {
        return true;
    }

}

bool Solution::CheckDraftLimit(Node nextNode){
    return (_currentCargo < nextNode.GetTerminal().GetDraftLimit());
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
    _currentCargo = _currentCargo - assignedNode.GetNode().GetCargoLoad();
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
    float cargoOnBoard = _initialCargo;
    Node prevNode;
    int cont = 0;
    float timef = 0;
    float totalTime = 0;
    for (AssignedNode assignedNode : _assignedNodes){
        cout << "---------" << endl;
        if (cont != 0){
            cout << "Tiempo para moverse desde " << prevNode.GetNumber() << " a " << assignedNode.GetNode().GetNumber() << endl;
            timef = prevNode.GetTotalMovementTime(assignedNode.GetNode());
            totalTime = totalTime + timef;
            cout << " Total: " << timef << endl;
        }

        cargoOnBoard = cargoOnBoard + assignedNode.GetNode().GetCargoLoad();
        cout << "Nodo: " << assignedNode.GetNode().GetNumber();
        cout << " Terminal: " << assignedNode.GetNode().GetTerminal().GetName();
        cout << " Tiempo: " << totalTime << endl;

        cout << "Carga a bordo: " << cargoOnBoard << endl << endl;

        // cout << "------" << endl;
        // assignedNode.PrintCandidates();
        // cout << "------" << endl;
        prevNode = assignedNode.GetNode();
        cont++;
    }
    cout << endl;
}
