class Solution {
    private:
        Terminal _terminal;
        int _number;
        int _pickupOrDelivery;
        float _washingTime;
        float _cargoLoad;
        float _loadingTime;
        float _lowerTimeWindow;
        float _upperTimeWindow;
        float _density;
        int _cargoType;

    public:
        void SetNumber( int number ) { _number = number; }
        void SetPickupOrDelivery( int pickupOrDelivery ) { _pickupOrDelivery = pickupOrDelivery; }
        void SetWashingTime( float washingTime ) { _washingTime = washingTime; }
        void SetCargoLoad( float cargoLoad ) { _cargoLoad = cargoLoad; }
        void SetLoadingTime( float loadingTime ) { _loadingTime = loadingTime; }
        void SetLowerTimeWindow( float lowerTimeWindow ) { _lowerTimeWindow = lowerTimeWindow; }
        void SetUpperTimeWindow( float upperTimeWindow ) { _upperTimeWindow = upperTimeWindow; }
        void SetDensity( float density ) { _density = density; }
        void SetCargoType( int cargoType ) { _cargoType = cargoType; }
        void SetTerminal( Terminal terminal) { _terminal = terminal; }

        int GetNumber( ) { return _number; }
        int GetPickupOrDelivery( ) { return _pickupOrDelivery; }
        float GetWashingTime( ) { return _washingTime; }
        float GetCargoLoad( ) { return _cargoLoad; }
        float GetLoadingTime( ) { return _loadingTime; }
        float GetLowerTimeWindow( ) { return _lowerTimeWindow; }
        float GetUpperTimeWindow( ) { return _upperTimeWindow; }
        float GetDensity( ) { return _density; }
        int GetCargoType( ) { return _cargoType; }
        Terminal GetTerminal( ) { return _terminal; }
};
