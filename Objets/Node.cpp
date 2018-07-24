#include "Node.h"


using namespace std;

float Node::GetTotalMovementTime(Node nextNode){
    float totalRequiredTime = 0;
    if (_number == 0 ||  nextNode.GetNumber() == 6){ //TODO: corregir por size() de nùmero de terminales
        totalRequiredTime =   CalculateSailingTime(nextNode)
                            + CalculateEnteringTime(nextNode);
    } else if (_terminal.GetId() != nextNode.GetTerminal().GetId()){
        totalRequiredTime =   _washingTime
                            + _loadingTime
                            + CalculateSailingTime(nextNode)
                            + CalculateEnteringTime(nextNode);
    } else{
        totalRequiredTime =   _washingTime
                            + _loadingTime;
    }
    return totalRequiredTime;
}

//I_ij
float Node::CalculateSailingTime(Node nextNode){
    return _terminal.GetTerminalDistance(nextNode.GetTerminal().GetId());
}

//E_j
float Node::CalculateEnteringTime(Node nextNode){
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
