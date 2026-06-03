#include<iostream>
#include<vector>
#include<numeric>
#include<unordered_map>
using namespace std;

// =======================Problem 1======================================================
// Problem: Build a TemperatureSensor class that collects temperature readings and provides statistical access. The sensor should validate that readings fall within a reasonable range and never expose its internal list of readings directly.

// Requirements:

// Private list of readings
// addReading(value): adds a temperature reading, but only if it's between -50 and 150 degrees (inclusive). Reject out-of-range values.
// getAverage(): returns the average of all readings, or 0 if no readings exist
// getReadingCount(): returns how many readings have been recorded
// getReadings(): returns a copy of the readings list (not the original)

enum RANGE{
    Start = -50,
    End = 150
};

class TemperatureSensor{
    private:
    double reading = 0;
    vector<double>readingList;

    public:
    bool addReading(const double val){
        if(val >= RANGE::Start && val <= RANGE::End){
           reading = val;
           readingList.push_back(reading);
           cout<<"Reading added : "<<reading<<endl;
           return 1;
        }
        cerr<<"Reading is out of range.."<<endl;
        return 0;
    }

    double getAverage(){
        if(readingList.empty()){
            cout<<"Reading history is empty.."<<endl;
            return -1;
        }
        double avg = accumulate(readingList.begin() , readingList.end() , 0.0)/readingList.size();
        cout<<"========AVERAGE======: "<<avg<<endl;
        return avg;
    }

    //getter of the reading from the private variable
    double getReading() const{
        return reading;
    }

    //here using the const means the receiver didn't authority to change this variable . means our variable is 100% safe
    int getReadingCount() const{
        return readingList.size() > 0 ? readingList.size() : -1;
    }
};


// =======================Problem 2======================================================
// Design ShoppingCart Class
// Problem: Build a ShoppingCart class that manages items, supports a one-time discount code, and prevents modifications after checkout.

// Requirements:

// Private map/dictionary of items (item name to price)
// Private discount code (can only be applied once)
// Private isCheckedOut flag
// addItem(name, price): adds an item, but only if the cart hasn't been checked out
// applyDiscount(code): if the code is "SAVE10" and no discount has been applied yet, marks the discount as applied and stores it. Returns success/failure.
// getTotal(): returns the sum of all prices, minus 10% if a discount was applied
// checkout(): marks the cart as checked out if it has at least one item. After checkout, no items can be added and no discounts can be applied.


//----------------------My implementation 4/10--------------------------------------
// class ShoppingCart{
//     private:
//     unordered_map<string, int>items;  //this map stores all the card itens of the user
//     bool isCheckout = false;
//     double discountCode = 2.0;

//     public:
//     void addItem(const string itemName , double amount ){
//         //only allow add item if checkoout is pending
//         if(!isCheckout){
//             items[itemName] = amount;
//         }
//         return ; 
//     }

//     double applyDiscount(){
//         double appliedDiscountPrice = 0;
//         if(!isCheckout){
//             int total = 0;
//             for(auto i : items){
//                 total += i.second;
//             }

//            appliedDiscountPrice = (total * discountCode)/100 + total;
//         }
//         return appliedDiscountPrice;
//     }

//     double getTotal(){
//         int total = 0;
//         for(auto i : items){
//             total += i.second;
//         }
//         return total;
//     }

//     void checkOut() {
//         isCheckout = 1;
//     }
// };


class ShoppingCart{
    private:
    unordered_map<string, double>items;
    bool isCheckout = false;
    bool isDiscountApplied = false;

    public:
    void addItem(const string )
}


int main(){


    // ShoppingCart cart;
    // cart.addItem("Shirt" , 400);
    // cart.addItem("Pant" , 786);
    // // cart.addItem("Pant" ,100);


    // int bill = cart.getTotal();
    // cout<<"Total bill is: "<<bill<<endl;
    // cart.checkOut();

    // cart.addItem("Jeans" , 899);
    // bill = cart.getTotal();
    // cout<<"Total bill is: "<<bill<<endl;



    // TemperatureSensor sensor;

    // sensor.addReading(56);
    // sensor.addReading(78);
    // sensor.addReading(200);
    // sensor.getAverage();
    // cout<<"Total readings: "<<sensor.getReadingCount()<<endl;
    // cout<<"Last reading: "<<sensor.getReading()<<endl;
    // sensor.addReading(-60);
    // sensor.addReading(120);


}