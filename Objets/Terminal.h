#include <vector>

class Terminal {
    private:
        char _name[5];
        int _id;
        float _draftLimit;
        float _waitingTime;
        float _enteringTime;
        std::vector<float> _distances;

    public:
        void SetName( char* name ) { strcpy(_name, name); }
        void SetId( int id ) { _id = id; }
        void SetWaitingTime( float waitingTime ) { _waitingTime = waitingTime; }
        void SetDraftLimit( float draftLimit ) { _draftLimit = draftLimit; }
        void SetEnteringTime( float enteringTime ) { _enteringTime = enteringTime; }
        void AddTerminalDistance( float distance ) { _distances.push_back(distance); }

        char* GetName( ) { return _name; }
        int GetId( ) { return _id; }
        float GetWaitingTime( ) { return _waitingTime; }
        float GetEnteringTime( ) { return _enteringTime; }
        std::vector<float> GetDistances( ) { return _distances; }
};
