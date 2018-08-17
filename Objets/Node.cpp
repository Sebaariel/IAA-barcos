#include "Node.h"


using namespace std;

//T_ij
float Node::GetTotalMovementTime(Node nextNode){
    float totalRequiredTime = 0;
    if (_number == 0 ||  nextNode.GetNumber() == _totalNodes + 1){
        totalRequiredTime =   CalculateSailingTime(nextNode)
                            + CalculateEnteringTime(nextNode);
        if (_number == 0){
            //cout << "totalRequiredTime from ANCH to node (" << nextNode.GetNumber() << ") " << totalRequiredTime << endl;
        }

    } else if (_terminal.GetId() != nextNode.GetTerminal().GetId()){
        cout << " Washing Time: " << _washingTime << endl;
        cout << " Loading Time: " << _loadingTime << endl;
        totalRequiredTime =   _washingTime
                            + _loadingTime
                            + CalculateSailingTime(nextNode)
                            + CalculateEnteringTime(nextNode);
    } else{
        cout << " Washing Time: " << _washingTime << endl;
        cout << " Loading Time: " << _loadingTime << endl;
        totalRequiredTime =   _washingTime
                            + _loadingTime;
        //cout << "Mismo terminal" << endl;
    }
    //cout << "totalRequiredTime: " << totalRequiredTime << endl;
    return totalRequiredTime;
}

//I_ij
float Node::CalculateSailingTime(Node nextNode){
    float distance = _terminal.GetTerminalDistance(nextNode.GetTerminal().GetId());
    float knots = 4.3; //velocidad del barco
    cout << " Sailing Time: " << distance/knots << endl;
    return distance/knots;
}

//E_j
float Node::CalculateEnteringTime(Node nextNode){
    cout << " Entering Time: " << nextNode.GetTerminal().GetEnteringTime() << endl;
    return nextNode.GetTerminal().GetEnteringTime();
}

//W_i
// float Node::CalculateWashingTime(){
//     return _node.GetWashingTime();
// }

//L_i
// float Node::CalculateLoadingUnloadingTime(){
//     return _node.GetLoadingTime();
// }
