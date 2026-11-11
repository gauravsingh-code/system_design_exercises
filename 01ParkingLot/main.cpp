#include<iostream>
#include<vector>
using namespace std;

enum class VehicleType{
    MOTORBIKE = 0,
    CAR = 1,
    TRUCK =2
};

enum class SpotSize{
    SMALL = 0,
    MEDIUM = 1,
    LARGE = 2
};


class Vehicle{
    private:
    string registrationNo;
    VehicleType type;

    public:
    Vehicle(string regNo, VehicleType vehType) : registrationNo(regNo) , type(vehType){};

    VehicleType getVehicleType() {
        return type;
    }

    string getRegistratioNo() {
        return registrationNo;
    }
} ;


class ParkingSpot{
    private:
    string parkingId;
    SpotSize size;  //it is because it has fixed value 
    
    //here we have a vehicle - aggregation (HAS - A)
    Vehicle *isParkedVehicle = nullptr;

    public:
    ParkingSpot(string id, SpotSize spotSize) : parkingId(id) , size(spotSize) { };

    bool isAvailable(){
        return isParkedVehicle == nullptr;
    }

    bool isSuitable(Vehicle &vehicle){
        return static_cast<int>(size) == static_cast<int>(vehicle.getVehicleType());
    }

    bool park(Vehicle *vehicle){
        if(vehicle == nullptr || !isAvailable() || !isSuitable(*vehicle)) return false;

        isParkedVehicle = vehicle;
        return true;
    }

    void unpark(){
        isParkedVehicle = nullptr;
    }

    SpotSize getSpotSize(){
        return size;
    }

    string getParkingId(){
        return parkingId;
    }

};


class ParkingFloor{
    private:
    int floorNumber;
    vector<ParkingSpot>spots;

    public:
    ParkingFloor(int floorNo, int small, int medium , int large) : 
        floorNumber(floorNo) {

            //generates the spots for small
            for(int i=1; i<=small; i++){
                spots.emplace_back(to_string(floorNumber) + "-S-" + to_string(i), SpotSize::SMALL);
            }

            //generates the sports for medium spots
            for(int i=1; i<=medium; i++){
                spots.emplace_back(to_string(floorNumber) + "-M-" + to_string(i), SpotSize::MEDIUM);
            }

            //generates the spots for large
            for(int i=1; i<=large; i++){
                spots.emplace_back(to_string(floorNumber) + "-L-" + to_string(i), SpotSize::LARGE);
            }
        }
    

    bool parkFloor(Vehicle *v){
        for(auto &spot : spots){
            if(spot.park(v)) return 1;
        }
        return 0;
    }
    vector<ParkingSpot> getSpots(){
        return spots;
    }

    int getFloorNumber() const{
        return floorNumber;
    }

    size_t getTotalSpots() const {
        return spots.size();
    }    
};

class ParkingLot{
    private:
    //strongly HAS-A relationship (COMPOSITION)
    vector<ParkingFloor> floors;
    
    public:
    //from parking lot we can add a floors dynamically
    void addFloors(ParkingFloor floor){
        floors.push_back(move(floor));
    }

    bool parkVehicle(Vehicle *vehicle){
        //find the valid space
        for(auto &floor : floors){
            if(floor.parkFloor(vehicle)) return true ;
        }
        return false;
    }

    size_t getTotalFloors() const{
        return floors.size();
    }

    int getTotalSpots() const{
        int total = 0;
        for(auto &floor : floors){
            total += floor.getTotalSpots();
        }
        return total;
    }
};

string printStringVehicleType(VehicleType vehicle){
    switch(vehicle){
        case VehicleType::MOTORBIKE:
            cout<<"MOTOR BIKE" <<endl;
            break;
        case VehicleType::CAR:
            cout<<"CAR "<<endl;
            break;
        case VehicleType::TRUCK:
            cout<<"TRUCK"<<endl;
            break;
        default:
            cout<<"INVALID ..."<<endl;
    }
    return "";
}

class ParkingTicket{
    private:
    string ticketId;
    Vehicle *vehicle = nullptr;
    ParkingSpot *spot = nullptr;
    time_t entryTime;
    bool isActive;

    public:
    ParkingTicket(string id , Vehicle *v, ParkingSpot *s) : ticketId(id), vehicle(vehicle), spot(s), isActive(true) {
        entryTime = time(0); 
    }

    string getTicketId() const{  return ticketId;}
    ParkingSpot* getSpot() const{ return spot;;}
    Vehicle * getVehicle() const {return vehicle;}
    time_t getEntryTime() const {return entryTime; }
    bool isActive() const { return isActive; }
    void markComplete() { isActive = false; }
}

int main(){

    ParkingLot lot;
    lot.addFloors(ParkingFloor(0,2 ,3 , 4));  //0-floor , 2- small , 3 -med, 4-large
    
    // ParkingFloor floor2(0,2 ,3 , 4);
    // vector<ParkingSpot> spots = floor2.getSpots();

    // for(auto spot : spots){
    //     cout<<"Spot Id: "<< spot.getParkingId() << " --- Is Spot Available: "<<spot.isAvailable()<<endl;
    // }




    vector<Vehicle>vehicles = {
          Vehicle("GJ-001", VehicleType::MOTORBIKE),
          Vehicle("GJ-002", VehicleType::MOTORBIKE),
          Vehicle("GJ-003", VehicleType::MOTORBIKE)
    };
  
    cout << "=== Parking Batch Vehicles ===" << endl;
    for (auto &v : vehicles) {
        if (lot.parkVehicle(&v)) {
            cout << "✅ " << v.getRegistratioNo() << " parked!" << endl;
        } else {
            cout << "❌ " << v.getRegistratioNo() << " failed to park! (Lot full)" << endl;
        }
    }



    // bool res = lot.parkVehicle(&bike)
    
    // if (lot.parkVehicle(&bike)) {
    //     cout << "Car parked successfully!" << endl;
    // } else {
    //     cout << "No spot available for this car!" << endl;
    // }


    /*
    // 1. Create a Parking Lot & add a Floor (Floor 0: 2 Small, 2 Medium, 1 Large = 5 spots)
    ParkingLot lot;
    ParkingFloor floor0(0, 2, 2, 1);
    lot.addFloors(floor0);
    cout << "=== 1. Floor & Spot Count Test ===" << endl;
    cout << "Total Floors: " << lot.getTotalFloors() << endl; // Expected: 1
    cout << "Total Spots: "  << lot.getTotalSpots()  << endl; // Expected: 5
    // 2. Create Vehicles
    Vehicle bike("KA-01-1111", VehicleType::MOTORBIKE);
    Vehicle car("MH-02-2222",  VehicleType::CAR);
    Vehicle truck("DL-03-3333", VehicleType::TRUCK);
    // Grab a reference to spots on floor 0 to test spot logic
    // (Note: floor0 inside lot is a copy, so let's inspect spot suitability)
    ParkingSpot smallSpot("0-S-1", SpotSize::SMALL);
    ParkingSpot largeSpot("0-L-1", SpotSize::LARGE);

    cout << "\n=== 2. Suitability & Parking Test ===" << endl;
    // Small spot tests:
    cout << "Bike fits in Small Spot? " 
         << (smallSpot.isSuitable(bike) ? "YES" : "NO") << endl;  // YES (0 <= 0)
    cout << "Truck fits in Small Spot? " 
         << (smallSpot.isSuitable(truck) ? "YES" : "NO") << endl; // NO  (2 > 0)
    // 3. Park Bike in Small Spot
    bool parked = smallSpot.park(&bike);
    cout << "Bike Parked successfully? " << (parked ? "YES" : "NO") << endl; // YES
    cout << "Is Small Spot still available? " 
         << (smallSpot.isAvailable() ? "YES" : "NO") << endl;        // NO
    // Try parking another vehicle in the same spot (should fail)
    bool doublePark = smallSpot.park(&car);
    cout << "Can Car park in occupied spot? " 
         << (doublePark ? "YES" : "NO") << endl;                     // NO
    // 4. Unpark Test
    cout << "\n=== 3. Unpark Test ===" << endl;
    smallSpot.unpark();
    cout << "Spot available after unpark? " 
         << (smallSpot.isAvailable() ? "YES" : "NO") << endl;        // YES

    */

    // Vehicle vehicle1("GJ_011", VehicleType::MOTORBIKE);
    // ParkingSpot spot("PARK-001" , SpotSize::LARGE);

    // bool isParked = spot.park(&vehicle1);

    // cout<<"Is parked: "<<isParked<<endl; 

    // ParkingLot lot ;
    // ParkingFloor floor(0 , 3 , 4, 5);
    // ParkingFloor floor2(1, 3,2, 5);

    // ParkingLot p1();


    // lot.addFloors(floor);
    // lot.addFloors(floor2);
    // size_t floors = lot.getTotalFloors();
    // cout<<"Floors: "<<floors<<endl;

    
    
    // VehicleType type = VehicleType::MOTORBIKE;
    // Vehicle vehicle("GJ-001", type);


//    type = vehicle.getVehicleType();
//    printStringVehicleType(type); 
    // cout<<"LARGe: "<<SpotSize::LARGE<<endl;

    cout<<"Hello world"<<endl;
    return 0;
}