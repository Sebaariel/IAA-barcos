
class Terminal {
    private:
        char _name[5];
        int _id;
        float _waitingTime;
        float _enteringTime;
        float _draftLimit;

    public:
        void SetName( char* name ) { strcpy(_name, name); }
        void SetId( int id ) { _id = id; }
        void SetWaitingTime( float waitingTime ) { _waitingTime = waitingTime; }
        void SetEnteringTime( float enteringTime ) { _enteringTime = enteringTime; }
        void setDraftLimit( float draftLimit ) { _draftLimit = draftLimit; }

        char* GetName( ) { return _name; }
        int GetId( ) { return _id; }
        float GetWaitingTime( ) { return _waitingTime; }
        float GetEnteringTime( ) { return _enteringTime; }
        float GetDraftLimit( ) { return _draftLimit; }
};
