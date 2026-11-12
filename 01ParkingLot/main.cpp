#include<iostream>
#include<vector>
#include<ctime>
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
    time_t parkedAt = 0;  // record entry time here 

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
        parkedAt = time(0) - 120 ; //saved upon entry
        return true;
    }

    void unpark(){
        isParkedVehicle = nullptr;
        parkedAt = 0;
    }

    SpotSize getSpotSize(){
        return size;
    }

    string getParkingId(){
        return parkingId;
    }

    time_t getParkedTime() const {return parkedAt ;}

    Vehicle * getParkedVehicle() const { return isParkedVehicle; }

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
    

    ParkingSpot* parkFloor(Vehicle *v){
        for(auto &spot : spots){
            if(spot.park(v)) return &spot;
        }
        return nullptr;
    }
    vector<ParkingSpot>& getSpots(){
        return spots;
    }

    int getFloorNumber() const{
        return floorNumber;
    }

    size_t getTotalSpots() const {
        return spots.size();
    }    
};

class ParkingTicket{
    private:
    string ticketId;
    Vehicle *vehicle = nullptr;
    ParkingSpot *spot = nullptr;
    time_t entryTime;
    time_t exitTime;  // 0 while still parked
    bool isActive;
    double amountPaid = 0.0;
    string paymentMethod = "NONE"; 

    public:
    ParkingTicket(string id, Vehicle *v, ParkingSpot *s, time_t enTime) 
        : ticketId(id), vehicle(v), spot(s), isActive(true), entryTime(enTime), exitTime(0) {}

    void closeTicket(double amount, string method){
        isActive = false;
        exitTime = time(0); // current time at the time of exiting
        amountPaid = amount;
        paymentMethod = method;
    }

    int getDurationInSeconds() const{
        if(exitTime == 0) return 0; // vehicle is still parked
        return static_cast<int>(exitTime - entryTime);
    }

    // getters 
    string getTicketId() const { return ticketId; }
    ParkingSpot* getSpot() const { return spot; }
    Vehicle* getVehicle() const { return vehicle; }
    time_t getEntryTime() const { return entryTime; }
    bool getIsActive() const { return isActive; }


    double getAmountPaid() const{ return amountPaid; }

    string getPaymentMethod() const{ return paymentMethod; }
};

class PaymentStrategy{
    public:
    virtual bool processPayment(double amount) = 0;
    virtual string getMethodName() const = 0;
    virtual ~PaymentStrategy() = default;
};

//Concreate strategies
class UPIPayment : public PaymentStrategy{
    public:
    bool processPayment(double amount) override{
        cout << "💳 Paid $" << amount << " via UPI." << endl;
        return true;
    }

    string getMethodName() const override {return "UPI"; }
};

class CardPayment : public PaymentStrategy{
    public:
    bool processPayment(double amount){
        cout << "💳 Paid $" << amount << " via Credit/Debit Card." << endl;
        return true;
    }

    string getMethodName() const override{ return "CARD" ;}

};

class CashPayment : public PaymentStrategy {
public:
    bool processPayment(double amount) override {
        cout << "💵 Paid $" << amount << " via Cash." << endl;
        return true;
    }

    string getMethodName() const override{return "CASH"; }
};

class ParkingLot{
    private:
    //strongly HAS-A relationship (COMPOSITION)
    vector<ParkingFloor> floors;
    vector<ParkingTicket> tickets;
    int ticketCounter = 101; 
    
    public:
    //from parking lot we can add a floors dynamically
    void addFloors(ParkingFloor floor){
        floors.push_back(move(floor));
    }

    /*
    ParkingTicket* parkVehicle(Vehicle *vehicle){
        //find the valid space across all floors if we get we exit this loop
        for(auto &floor : floors){
            ParkingSpot * spot = floor.parkFloor(vehicle);
            //we successfully allocated the spot
            if(spot != nullptr){
                string id ="TKT-" + to_string(ticketCounter++);
                tickets.emplace_back(id, vehicle, spot);
                return &tickets.back();
            }
        }
        return nullptr;
    }

    //unpark using the vehicle
    bool unparkVehicle(ParkingTicket *ticket){
        if(ticket == nullptr || !ticket->getIsActive()){
            return false;
        }

        //1. free the spot
        ticket->getSpot()->unpark();
        ticket->closeTicket();

        return true;
    }
    */

    bool parkVehicle(Vehicle *vehicle){
        for(auto &floor : floors){
            ParkingSpot *spot = floor.parkFloor(vehicle);
            if(spot != nullptr) return true;  //at park no ticket needed 
        }
        return false;
    }

    double calculateFee(VehicleType vehicle, int duration){
        double ratePerSecond = 1.0; // default for bike

        if(vehicle == VehicleType :: CAR) ratePerSecond = 2.0; 
        if(vehicle == VehicleType :: TRUCK) ratePerSecond = 3.0;

        //minimum base charge is 10
        return max(10.0, duration * ratePerSecond);
    }


    ParkingTicket* unparkVehicle(Vehicle *vehicle, PaymentStrategy *paymentMethod){
        if(vehicle == nullptr || paymentMethod == nullptr) return nullptr;
        //now i need to find the vehicle in all floors and their spots 
        for(auto &floor : floors){
            for(auto &spot : floor.getSpots()){
                if(spot.getParkedVehicle() == vehicle){
                    time_t entryTime = spot.getParkedTime();
                    int duration = static_cast<int>(time(0) - entryTime);

                    double amt = calculateFee(vehicle->getVehicleType(), duration);

                    //we attempt of payment
                    if(!paymentMethod->processPayment(amt)){
                        cout << "❌ Payment failed! Gate will not open." << endl;
                        return nullptr; // Vehicle stays parked!
                    }

                    //payment succedded
                    string id = "TKT-" + to_string(ticketCounter++);
                    tickets.emplace_back(id, vehicle, &spot, entryTime);
                    ParkingTicket* exitTicket = &tickets.back();
                    exitTicket->closeTicket(amt, paymentMethod->getMethodName()); //sets exiTIme = now()

                    spot.unpark();

                    return exitTicket; //return generated bill 
                }
            }
        }
        return nullptr;
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

//using Abstract(pure virtuual funtion) strategy patternn for followinf open/close principle



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

void printTicket(const ParkingTicket &ticket) {
    cout << "\n===================================" << endl;
    cout << "          PARKING TICKET           " << endl;
    cout << "===================================" << endl;
    cout << "Ticket ID    : " << ticket.getTicketId() << endl;
    cout << "Vehicle Reg  : " << ticket.getVehicle()->getRegistratioNo() << endl;
    cout << "Spot ID      : " << ticket.getSpot()->getParkingId() << endl;
    cout << "Status       : " << (ticket.getIsActive() ? "ACTIVE (PARKED)" : "COMPLETED") << endl;
    cout<<"Payment paid: "<<ticket.getAmountPaid()<<endl;
    cout<<"Paymnet Method: "<<ticket.getPaymentMethod()<<endl;

    // If vehicle has already unparked, show duration
    if (!ticket.getIsActive()) {
        cout << "Duration     : " << ticket.getDurationInSeconds() << " seconds" << endl;
    }
    cout << "===================================\n" << endl;
}

int main(){

    ParkingLot lot;
    lot.addFloors(ParkingFloor(0,2 ,3 , 4));  //0-floor , 2- small , 3 -med, 4-large
    
    // ParkingFloor floor2(0,2 ,3 , 4);
    // vector<ParkingSpot> spots = floor2.getSpots();

    // for(auto spot : spots){
    //     cout<<"Spot Id: "<< spot.getParkingId() << " --- Is Spot Available: "<<spot.isAvailable()<<endl;
    // }

    // Vehicle car("GJ-01-AB-1234", VehicleType::CAR);

    //park and get ticket 
    // ParkingTicket *t = lot.parkVehicle(&car);

    // if(t != nullptr){

    //     printTicket(*t);
    //     // cout<<"----CAR IS PARKED----"<<endl;
    //     // cout<<"TIcket Id: "<<t->getTicketId()<<endl;
    //     // cout<<"Spot Id: "<<t->getSpot()->getParkingId()<<endl;
    //     // cout<<-------------------------------
    // }else{
    //     cout<<"Parking Lot is full !"<<endl;
    // }


    vector<Vehicle>vehicles = {
          Vehicle("GJ-001", VehicleType::MOTORBIKE),
          Vehicle("GJ-002", VehicleType::MOTORBIKE),
          Vehicle("GJ-003", VehicleType::CAR)
    };

  
  
    cout << "=== Parking Batch Vehicles (Entry - No Ticket Needed) ===" << endl;
    for (auto &v : vehicles) {
        if (lot.parkVehicle(&v)) {
            cout << "✅ " << v.getRegistratioNo() << " entered and parked." << endl;
        } else {
            cout << "❌ " << v.getRegistratioNo() << " failed to park! (Lot full)" << endl;
        }
    }

    UPIPayment upi;
    CardPayment card;

    cout << "\n=== Vehicles Exiting with Payment ===" << endl;

    cout << "\n=== Unparking Batch Vehicles (Tickets Generated at Exit) ===" << endl;
    for (auto &v : vehicles) {
        ParkingTicket *receipt = lot.unparkVehicle(&v, &upi);
        if (receipt != nullptr) {
            cout << "🎫 Ticket Generated at Exit for: " << v.getRegistratioNo() << endl;
            printTicket(*receipt);
        } else {
            cout << "❌ Vehicle " << v.getRegistratioNo() << " not found in lot!" << endl;
        }
    }


    // Now you can easily unpark all of them whenever you want:
    // cout << "\n=== Unparking All Vehicles ===" << endl;
    // for (auto *t : issuedTickets) {
    //     lot.unparkVehicle(t);
    //     printTicket(*t); // Prints with status: COMPLETED and duration
    // }



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

    cout<<"\nHello world"<<endl;
    return 0;
}