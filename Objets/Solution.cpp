#include "Solution.h"


using namespace std;

float Solution::CheckFactibility(Node node){
    return (_loadingTime - node.GetLoadingTime());
}
