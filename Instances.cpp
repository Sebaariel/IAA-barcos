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
    vector<tuple<Node, float>> firstNodeDomain;
    solution.AddAssignedNode(AssignedNode(nodes.at(0), currentTime, firstNodeDomain ));
    vector<tuple<Node, float>> firstCandidates;
    bool flagDelete = true;
    int contador = 0;
    Node bestNode;
    while (solution.GetNoAssignedNodes().size() != 1){
        float bestTime = 100000;
        int noFactNodes = 0;
        vector<tuple<Node, float>> candidates;
        for (Node node : solution.GetNoAssignedNodes()){
            cout << "timeRequired from (" << solution.GetAssignedNodes().back().GetNode().GetNumber() << ") to (" << node.GetNumber() << "): " << solution.GetAssignedNodes().back().GetNode().GetTotalMovementTime(node) << endl;
            if (solution.CheckFactibility(node) && node.GetNumber() != solution.GetTotalNodes()-1){
                float timeRequired = solution.GetAssignedNodes().back().GetNode().GetTotalMovementTime(node);

                if (timeRequired < bestTime){
                    bestTime = timeRequired;
                    bestNode = node;
                } else {
                    candidates.push_back(make_tuple(node, timeRequired));
                }

            } else {
                noFactNodes = noFactNodes + 1;
            }
        }

        if (true){//if (solution.GetAssignedNodes().size() == 2 ){
            cout << ">>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            solution.PrintAssignedNodesLine();
            solution.PrintNoAssignedNodesLine();
            solution.GetAssignedNodes().back().PrintCandidates();
        }


        //cout << endl;
        if (noFactNodes != (int)solution.GetNoAssignedNodes().size()){

            currentTime = bestTime;
            cout << "Agreguè nodo (" << bestNode.GetNumber() << ") con tiempo: " << currentTime << endl;
            solution.AddAssignedNode(AssignedNode(bestNode, currentTime, candidates));
            // solution.GetAssignedNodes().back().PrintCandidatesLine();
            // cout << "---" << endl;
        } else {
            AssignedNode newAssignedNode;
            AssignedNode removedNode;
            bool newCandidate = false;
            if (solution.GetAssignedNodes().back().GetCandidates().size() != 0){ //Si no agregò ninguno pero al ùltimo nodo le quedan candidatos
                removedNode = solution.GetAssignedNodes().back();
                solution.RemoveFromAssignedNodes(removedNode);                  //Remuevo nodo obtenido
                solution.AddNoAssignedNode(removedNode.GetNode());           //Obtengo nodo a eliminar (ùltimo)
                //Agrego nodo obtenido a los nodos no asignados
                newAssignedNode.SetNode(get<0>(removedNode.GetBestCandidate())); //Si los tiene, lo guardo para asignarlo posteriormente
                newAssignedNode.SetBestTime(get<1>(removedNode.GetBestCandidate())); //Seteo tiempo de mejor candidato
                newAssignedNode.SetCandidates(removedNode.GetCandidates());  //Seteo candidatos a este mejor candidato
                newAssignedNode.RemoveFromCandidate(newAssignedNode.GetNode()); //Le elimino a si mismo de los candidatos

            }
            while (solution.GetAssignedNodes().back().GetCandidates().size() == 0){
                removedNode = solution.GetAssignedNodes().back();  //Obtengo nodo a eliminar (ùltimo)
                solution.RemoveFromAssignedNodes(removedNode);                  //Remuevo nodo obtenido
                solution.AddNoAssignedNode(removedNode.GetNode());              //Agrego nodo obtenido a los nodos no asignados
                if (solution.GetAssignedNodes().back().GetCandidates().size() != 0){  //Si el nodo siguiente tiene candidatos:
                    //cout << "Num of candidates node " << solution.GetAssignedNodes().back().GetNode().GetNumber() << ": " << solution.GetAssignedNodes().back().GetCandidates().size() << endl;
                    //solution.RemoveCandidate(removedNode.GetNode());                  //Le remuevo de sus candidatos el eliminado anteriormente
                    //cout << "Num of candidates node " << solution.GetAssignedNodes().back().GetNode().GetNumber() << ": " << solution.GetAssignedNodes().back().GetCandidates().size() << endl;
                    if (solution.GetAssignedNodes().back().GetCandidates().size() != 0){ //Verifico si nuevamente tiene màs candidatos
                        newAssignedNode.SetNode(get<0>(solution.GetAssignedNodes().back().GetBestCandidate())); //Si los tiene, lo guardo para asignarlo posteriormente
                        newAssignedNode.SetBestTime(get<1>(solution.GetAssignedNodes().back().GetBestCandidate())); //Seteo tiempo de mejor candidato
                        newAssignedNode.SetCandidates(solution.GetAssignedNodes().back().GetCandidates());  //Seteo candidatos a este mejor candidato
                        newAssignedNode.RemoveFromCandidate(newAssignedNode.GetNode()); //Le elimino a si mismo de los candidatos
                    }
                }
                solution.PrintAssignedNodesLine();
            }
            solution.AddNoAssignedNode(solution.GetAssignedNodes().back().GetNode());
            solution.RemoveFromAssignedNodes(solution.GetAssignedNodes().back());                  //Remuevo nodo obtenido

            solution.AddAssignedNode(newAssignedNode); //Agrego candidato
            // if (true){ //Si hay nuevo candidato
            //     solution.AddAssignedNode(newAssignedNode); //Agrego candidato
            //     //solution.Remove(newAssignedNode.GetNode()); //Lo saco de los nodos no asignados
            // } else { // Si no hay nuevo candidato
            //     cout << "No solution" << endl;
            // }

        }
        // } else {
        //     AssignedNode removedNode = solution.GetAssignedNodes().back();
        //     // solution.RemoveCandidate(removedNode.GetNode());
        //     // solution.RemoveFromAssignedNodes(removedNode);
        //     // solution.AddNoAssignedNode(removedNode.GetNode());
        //
        //
        //     while (removedNode.GetCandidates().size() == 0){
        //         removedNode = solution.GetAssignedNodes().back();
        //         solution.RemoveCandidate(removedNode.GetNode());
        //         solution.RemoveFromAssignedNodes(removedNode);
        //         solution.AddNoAssignedNode(removedNode.GetNode());
        //     }
        //
        //     if (removedNode.GetCandidates().size() != 0){
        //         //solution.GetAssignedNodes().back().PrintCandidates();
        //         Node bestNodeCandidate = get<0>(removedNode.GetBestCandidate());
        //         float bestTimeCandidate = get<1>(removedNode.GetBestCandidate());
        //         vector<tuple<Node, float>> bestCandidates = removedNode.GetCandidates();
        //
        //         AssignedNode newAssignedNode(bestNodeCandidate, bestTimeCandidate, bestCandidates);
        //         solution.AddAssignedNode(newAssignedNode);
        //         solution.AddNoAssignedNode(removedNode.GetNode());
        //         solution.RemoveCandidate(newAssignedNode.GetNode());
        //     } else {
        //         solution.RemoveFromAssignedNodes(removedNode);
        //         //solution.AddNoAssignedNode(removedNode.GetNode());
        //
        //         //solution.SetNoAssignedNodes(removedNode.GetCandidatesNodes());
        //     }
        //
        //
        //
        //     // if (solution.GetAssignedNodes().back().GetCandidates().size() != 0){
        //     //     solution.RemoveCandidate(removedNode.GetNode());
        //     // }
        //     //
        //     // AssignedNode newAssignedNode;
        //     //
        //     // cout << "asd" <<
        //     // if (solution.GetAssignedNodes().back().GetCandidates().size() != 0){
        //     //     solution.RemoveCandidate(bestNodeCandidate);
        //     // }
        //
        //
        //     //solution.SetNoAssignedNodes(solution.GetAssignedNodes().back().GetCandidates());
        //
        //     // while(removedNode.GetCandidates().size() == 0){
        //     //     removedNode = solution.GetAssignedNodes().back();
        //     //     solution.RemoveFromAssignedNodes(removedNode);
        //     //     solution.AddNoAssignedNode(removedNode.GetNode());
        //     //     //AssignedNode removedAssignedNod = solution.GetAssignedNodes().back();
        //     //     // solution.RemoveFromAssignedNodes(solution.GetAssignedNodes().back());
        //     //     // solution.AddNoAssignedNode(solution.GetAssignedNodes().back().GetNode());
        //     //     if (solution.GetAssignedNodes().back().GetCandidates().size() != 0){
        //     //         solution.RemoveCandidate(removedAssignedNod.GetNode());
        //     //     }
        //     //     solution.GetAssignedNodes().back().PrintCandidates();
        //     // } else {
        //     //
        //     // }
        //     // AssignedNode removedAssignedNode = solution.GetAssignedNodes().back();
        //     // AssignedNode newAssignedNode;
        //     // Node bestNodeCandidate = get<0>(removedAssignedNode.GetBestCandidate());
        //     // float bestTimeCandidate = get<1>(removedAssignedNode.GetBestCandidate());
        //     // vector<tuple<Node, float>> bestCandidates = removedAssignedNode.GetCandidates();
        //     // if (solution.GetAssignedNodes().back().GetCandidates().size() != 0){
        //     //     solution.RemoveCandidate(bestNodeCandidate);
        //     // }
        //     // cout << "---" << endl;
        //     // solution.RemoveFromAssignedNodes(solution.GetAssignedNodes().back());
        //     // solution.AddNoAssignedNode(solution.GetAssignedNodes().back().GetNode());
        //     // cout << "---" << endl;
        //     // solution.AddAssignedNode(AssignedNode(bestNodeCandidate, bestTimeCandidate, bestCandidates));
        //     //
        //     //
        //     // cout << "---" << endl;
        //     // cout << "bestNodeCandidate: " << bestNodeCandidate.GetNumber() << endl;
        //     // cout << "bestTimeCandidate: " << bestTimeCandidate << endl;
        //     // solution.GetAssignedNodes().back().PrintCandidates();
        //
        //     //solution.RemoveFromAssignedNodes(solution.GetAssignedNodes().back());
        //
        //
        // }
        contador = contador +1;
    }

    cout << "Iteraciones: " << contador << endl;

    float timeRequiredLast = bestNode.GetTotalMovementTime(nodes.at(solution.GetTotalNodes()-1));

    currentTime = currentTime + timeRequiredLast;
    solution.AddAssignedNode(AssignedNode(nodes.at(solution.GetTotalNodes()-1), currentTime, firstNodeDomain));


    // while (index <= totalNodes - 2){
    //
    //     float bestTime = 100000;
    //     float timeRequired;
    //     solution.PrintAssignedNodesLine();
    //     vector<Node> nodeDomain(solution.GetAssignedNodeDomain());
    //     bool resetNodesFlag = true;
    //     for (vector<Node>::iterator otherNode = nodeDomain.begin(); otherNode != nodeDomain.end(); ++otherNode){
    //
    //         int otherNodeNumber = (*otherNode).GetNumber();
    //         int nodeNumber = get<0>(solution.GetAssignedNodes().back()).GetNumber();
    //
    //         //cout << "Is factible: " << solution.CheckFactibility((*otherNode)) << "Nodo: " << otherNodeNumber << endl;
    //         deleteNodeFlag = deleteNodeFlag && !(solution.CheckFactibility((*otherNode)) && (*otherNode).GetNumber() != solution.GetTotalNodes()-1);
    //         //cout << "DeleteNode: " << deleteNodeFlag << endl;
    //
    //         if (solution.CheckFactibility((*otherNode)) && (*otherNode).GetNumber() != solution.GetTotalNodes()-1){
    //             solution.AddCurrentDomain((*otherNode));
    //
    //
    //             timeRequired = get<0>(solution.GetAssignedNodes().back()).GetTotalMovementTime((*otherNode));
    //             if (timeRequired < bestTime){
    //                 bestTime = timeRequired;
    //                 bestNode = (*otherNode);
    //                 addNode = true;
    //                 deleteNodeFlag = false;
    //             }
    //         }
    //     }
    //     if (addNode){
    //         currentTime = currentTime + bestTime;
    //         solution.AddAssignedNode(make_tuple(bestNode, currentTime));
    //         index = index + 1;
    //         deleteNodeFlag = true;
    //     } else {
    //         cout << "Eliminè" << endl;
    //         tuple<Node, float> deleteNode = solution.GetAssignedNodes().back();
    //         solution.AddNoAssignedNode(get<0>(deleteNode));
    //         solution.RemoveFromAssignedNodes(deleteNode);
    //         solution.RemoveFromAssignedNodeDomain(get<0>(deleteNode));
    //
    //         if (resetNodesFlag && ){
    //             cout << "Resetiè" << endl;
    //             solution.ClearAssignedNodesDomain();
    //             for (int i=0; i<solution.GetNoAssignedNodes().size(); i++){
    //                 solution.AddAssignedNodeDomain(solution.GetNoAssignedNodes()[i]);
    //             }
    //         }
    //
    //
    //         //currentTime = currentTime - node->GetTotalMovementTime(bestNode);
    //         currentTime = get<1>(solution.GetAssignedNodes().back());
    //         index = index - 1;
    //
    //         // tuple<Node, float> deleteNode = solution.GetAssignedNodes().back();
    //         //
    //         // if (deleteNodeFlag){
    //         //     solution.RemoveFromAssignedNodes(deleteNode);
    //         // }
    //         //
    //         º
    //         // index = index - 1;
    //         solution.PrintNoAssignedNodes();
    //         solution.PrintAssignedNodesLine();
    //         solution.PrintAssignedNodesDomain();
    //
    //     }
    //     cout << "AssignedNodesDomain size: " << solution.GetAssignedNodeDomain().size() << endl;
    //     solution.PrintAssignedNodes();
    // }
    //
    // float timeRequiredLast = bestNode.GetTotalMovementTime(nodes.at(solution.GetTotalNodes()-1));
    //
    // currentTime = currentTime + timeRequiredLast;
    // solution.AddAssignedNode(make_tuple(nodes.at(solution.GetTotalNodes()-1), currentTime));
    return solution;
}
