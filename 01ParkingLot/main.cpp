#include<iostream>
using namespace std;

//Enums
enum class VehicleType{
    MOTORCYCLE = 0,
    CAR = 1,
    TRUCK = 2
};

enum class SpotSize{
    SMALL = 0,
    MEDIUM = 1,
    LARGE = 2
};

class Vehicle{
    private:
    string registration_no;
    VehicleType type;

    public:
    Vehicle(string regNo, VehicleType vtype){
        this->registration_no = regNo;
        this->type = vtype;
    }

    //GETTER METHODS 

    VehicleType getVehicleType() const{
        return type;
    }

    string getRegistrationNo() const{
        return registration_no;
    }
};





int main(){

    VehicleType vehicle = VehicleType::MOTORCYCLE;
    SpotSize size = SpotSize::LARGE;

    Vehicle car("GJ01AB1234", VehicleType::CAR);

    cout << car.getRegistrationNo() << endl;
    cout << static_cast<int>(car.getVehicleType()) << endl;

    
    cout << "vehicle" <<": "<<static_cast<int>(vehicle)<<endl;
    cout<< "size" <<": "<<static_cast<int>(size)<<endl;
    


    return 0;
}