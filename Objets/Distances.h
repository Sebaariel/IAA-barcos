class Distances {
    private:
        int _id;
        float _minCapacity;
        float _maxCapacity;
        int _type;

    public:
        void SetId( int id ) { _id = id; }
        void SetMinCapacity( float minCapacity ) { _minCapacity = minCapacity; }
        void SetMaxCapacity( float maxCapacity ) { _maxCapacity = maxCapacity; }
        void SetType( int type ) { _type = type; }

        int GetId( ) { return _id; }
        float GetMinCapacity( ) { return _minCapacity; }
        float GetMaxCapacity( ) { return _maxCapacity; }
        int GetType( ) { return _type; }
};
