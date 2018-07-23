#include "Node.h"


using namespace std;

float Node::GetMovementTime(Node node){
    return (_loadingTime - node.GetLoadingTime());
}
