#include "Instances.h"
using namespace std;


void Instances::LoadInstances(std::string instance){
    string line;
    char str[512];
    ifstream myfile (instance);
    char * pch;
    const char * cmpStr = "-\r";
    int skip = 0;
    int sheetNumber = 0;
    if (myfile.is_open()){
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
                    case 2:
                        Terminal terminal;
                        terminal.SetName(pch);
                        pch = strtok(NULL, ",");
                        terminal.SetId(atoi(pch));
                        pch = strtok(NULL, ",");
                        pch = strtok(NULL, ",");
                        terminal.SetWaitingTime(atof(pch));
                        pch = strtok(NULL, ",");
                        terminal.SetEnteringTime(atof(pch));
                        _listOfTerminals.push_back(terminal);
                        break;
                    case 3:
                        Node node;
                        node.SetNumber(atoi(pch));
                        pch = strtok(NULL, ",");
                        node.SetTerminal(pch);
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
                        pch = strtok(NULL, ",");
                        node.SetCargoType(atoi(pch));
                        _listOfNodes.push_back(node);
                        break;
                    case 4:
                        break;

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
      cout << endl;
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
      cout << "Terminal: " << it->GetTerminal() << endl;
      cout << endl;
      cont++;
  }
}
