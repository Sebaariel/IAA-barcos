using namespace std;
class Tank {
    private:
        int _id;
        float _minCapacity;
        float _maxCapacity;
        int _tankType;

    public:
        void SetId( int id ) { _id = id; }
        void SetMinCapacity( float minCapacity ) { _minCapacity = minCapacity; }
        void SetMaxCapacity( float maxCapacity ) { _maxCapacity = maxCapacity; }
        void SetTankType( int tankType ) { _tankType = tankType; }

        int GetId( ) { return _id; }
        float GetMinCapacity( ) { return _minCapacity; }
        float GetMaxCapacity( ) { return _maxCapacity; }
        int GetTankType( ) { return _tankType; }
};
