class Node {
    private:
        char _terminal[5];
        int _number;
        int _pickupOrDelivery;
        float _washingTime;
        float _cargoLoad;
        float _loadingTime;
        float _lowerTimeWindow;
        float _upperTimeWindow;
        int _cargoType;

    public:
        void SetNumber( int number ) { _number = number; }
        void SetPickupOrDelivery( int pickupOrDelivery ) { _pickupOrDelivery = pickupOrDelivery; }
        void SetWashingTime( float washingTime ) { _washingTime = washingTime; }
        void SetCargoLoad( float cargoLoad ) { _cargoLoad = cargoLoad; }
        void SetLoadingTime( float loadingTime ) { _loadingTime = loadingTime; }
        void SetLowerTimeWindow( float lowerTimeWindow ) { _lowerTimeWindow = lowerTimeWindow; }
        void SetUpperTimeWindow( float upperTimeWindow ) { _upperTimeWindow = upperTimeWindow; }
        void SetCargoType( int cargoType ) { _cargoType = cargoType; }
        void SetTerminal( char* terminal) { strcpy(_terminal, terminal); }

        int GetNumber( ) { return _number; }
        int GetPickupOrDelivery( ) { return _pickupOrDelivery; }
        float GetWashingTime( ) { return _washingTime; }
        float GetCargoLoad( ) { return _cargoLoad; }
        float GetLoadingTime( ) { return _loadingTime; }
        float GetLowerTimeWindow( ) { return _lowerTimeWindow; }
        float GetUpperTimeWindow( ) { return _upperTimeWindow; }
        int GetCargoType( ) { return _cargoType; }
        char* GetTerminal( ) { return _terminal; }
};
