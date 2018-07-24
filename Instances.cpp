#include "Instances.h"

using namespace std;

void Instances::LoadInstances(string instance){
    string line;
    char str[512];
    int numOfNodes = stoi(instance.substr(0,1));
    ifstream myfile ("instancesTxt/"+instance);
    char * pch;
    const char * cmpStr = "-\r";
    int skip = 0;
    int sheetNumber = 0;
    if (myfile.is_open()){
        int terminalNumber = 0;
        while ( getline (myfile,line) ){
            strcpy(str, line.c_str());
            if (strcmp(str, cmpStr) == 0){
                skip = 1;
            } else if(skip == 1){
                skip = 0;
                sheetNumber++;
            }else{

                pch = strtok(str, ",");

              while (pch != NULL){
                  switch (sheetNumber) {
                    case 1:
                    {
                        Vehicle vehicle;
                        vehicle.SetId(atoi(pch));
                        pch = strtok(NULL, ",");
                        vehicle.SetMinCapacity(atof(pch));
                        pch = strtok(NULL, ",");
                        vehicle.SetMaxCapacity(atof(pch));
                        pch = strtok(NULL, ",");
                        vehicle.SetType(atoi(pch));
                        _listOfVehicles.push_back(vehicle);
                        break;
                    }
                    case 2:
                    {
                        Terminal terminal;
                        terminal.SetName(pch);
                        pch = strtok(NULL, ",");
                        terminal.SetId(atoi(pch));
                        pch = strtok(NULL, ",");
                        terminal.SetDraftLimit(atof(pch));
                        pch = strtok(NULL, ",");
                        terminal.SetWaitingTime(atof(pch));
                        pch = strtok(NULL, ",");
                        terminal.SetEnteringTime(atof(pch));
                        _listOfTerminals.push_back(terminal);
                        break;
                        }
                    case 3:
                    {
                        for(int i = 0; i < (int)_listOfTerminals.size(); i = i + 1)
                        {
                            _listOfTerminals.at(terminalNumber).AddTerminalDistance(atof(pch));
                            pch = strtok(NULL, ",");
                        }
                        terminalNumber = terminalNumber + 1;
                        break;
                    }
                    case 4:
                    {
                        Node node;
                        node.SetNumber(atoi(pch));
                        pch = strtok(NULL, ",");

                        auto it = find_if(_listOfTerminals.begin(), _listOfTerminals.end(), [pch](Terminal& obj) {return (strcmp(obj.GetName(), pch) == 0);});

                        if (it != _listOfTerminals.end()){
                          auto index = distance(_listOfTerminals.begin(), it);
                          node.SetTerminal(_listOfTerminals.at(index));
                        }

                        pch = strtok(NULL, ",");
                        node.SetPickupOrDelivery(atoi(pch));
                        pch = strtok(NULL, ",");
                        node.SetWashingTime(atof(pch));
                        pch = strtok(NULL, ",");
                        node.SetCargoLoad(atof(pch));
                        pch = strtok(NULL, ",");
                        node.SetLoadingTime(atof(pch));
                        pch = strtok(NULL, ",");
                        node.SetLowerTimeWindow(atof(pch));
                        pch = strtok(NULL, ",");
                        node.SetUpperTimeWindow(atof(pch));
                        pch = strtok(NULL, ",");
                        node.SetDensity(atof(pch));
                        pch = strtok(NULL, ",");
                        node.SetCargoType(atoi(pch));
                        node.SetTotalNodes(numOfNodes);
                        _listOfNodes.push_back(node);
                        break;
                    }
                  }
                  pch = strtok(NULL, ",");
              }
            }
        }
        myfile.close();
    }
}

void Instances::PrintInstances(){
  int cont = 1;
  for (vector<Vehicle>::iterator it = _listOfVehicles.begin(); it != _listOfVehicles.end(); ++it){

      cout << "Vehicle " << cont << endl;
      cout << "ID: " << it->GetId() << endl;
      cout << "Min Capacity: " << it->GetMinCapacity() << endl;
      cout << "Max Capacity: " << it->GetMaxCapacity() << endl;
      cout << "Type: " << it->GetType() << endl;
      cout << endl;
      cont++;
  }
  cout << "----" << endl;
  for (vector<Terminal>::iterator it = _listOfTerminals.begin(); it != _listOfTerminals.end(); ++it){

      cout << "Terminal " << it->GetName() << endl;
      cout << "ID: " << it->GetId() << endl;
      cout << "Waiting Time: " << it->GetWaitingTime() << endl;
      cout << "Entering Time: " << it->GetEnteringTime() << endl;
      cout << "Distancias" << endl;
      for(size_t i=0; i<it->GetDistances().size(); ++i){
          cout << it->GetDistances()[i] << endl;
      }
      cont++;
  }

  cout << "----" << endl;
  for (vector<Node>::iterator it = _listOfNodes.begin(); it != _listOfNodes.end(); ++it){

      cout << "Node Number " << it->GetNumber() << endl;
      cout << "Pickup or Delivery: " << it->GetPickupOrDelivery() << endl;
      cout << "Waiting Time: " << it->GetWashingTime() << endl;
      cout << "Cargo load: " << it->GetCargoLoad() << endl;
      cout << "Loading time: " << it->GetLoadingTime() << endl;
      cout << "Lower Time Window: " << it->GetLowerTimeWindow() << endl;
      cout << "Upper Time Window: " << it->GetUpperTimeWindow() << endl;
      cout << "Cargo Type: " << it->GetCargoType() << endl;
      cout << "Terminal: " << it->GetTerminal().GetName() << endl;
      cout << endl;
      cont++;
  }
}

Solution Instances::GenerateInitialSolution(vector<Node> nodes){
    Solution solution(nodes);
    float currentTime = 0;
    solution.AddAssignedNode(make_tuple(nodes.at(0), currentTime));
    Node bestNode;


    for (vector<Node>::iterator node = nodes.begin(); node != nodes.end(); ++node){
        float bestTime = 100000;

        float timeRequired;
        bool addNode = false;
        vector<Node> noAssignedNodes(solution.GetNoAssignedNodes());
        for (vector<Node>::iterator otherNode = nodes.begin(); otherNode != nodes.end(); ++otherNode){

            int nodeNumber = (*otherNode).GetNumber();
            auto it = find_if(noAssignedNodes.begin(),
                                noAssignedNodes.end(),
                                [nodeNumber](Node& obj) {
                                    return (obj.GetNumber() == nodeNumber);
                                });

            bool noAssignedNodeFlag = (it != noAssignedNodes.end());

            if ((node->GetNumber() != nodeNumber) && noAssignedNodeFlag && (*otherNode).GetNumber() != solution.GetTotalNodes()-1){
                timeRequired = node->GetTotalMovementTime((*otherNode));

                if (timeRequired < bestTime){
                    bestTime = timeRequired;
                    bestNode = (*otherNode);
                    addNode = true;
                }
            }
        }
        if (addNode){
            currentTime = currentTime + bestTime;
            solution.AddAssignedNode(make_tuple(bestNode, currentTime));
        }


    }
    float timeRequiredLast = bestNode.GetTotalMovementTime(nodes.at(solution.GetTotalNodes()-1));

    currentTime = currentTime + timeRequiredLast;
    solution.AddAssignedNode(make_tuple(nodes.at(solution.GetTotalNodes()-1), currentTime));
    return solution;
}
