#include "Tank.h"

using namespace std;

class Vehicle {
    private:
        vector<Tank> _tanks;

    public:
        vector<Tank> GetTanks( ) { return _tanks; }
        void AddTank(Tank tank){
            _tanks.push_back(tank);
        }
        float GetTotalCapacity(){
            float totalCapacity = 0;
            for (Tank tank : _tanks){
                totalCapacity = totalCapacity + tank.GetMaxCapacity();
            }
            return totalCapacity;
        }
};
