#include<iostream>
#include<stdexcept>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

//------------------------- 1. Design Bank Account Class--------------------------------------
// Problem: Create a BankAccount class that manages a simple bank account with deposit, withdrawal, and balance checking functionality.

// Requirements:

// Fields: accountNumber, ownerName, balance
// Constructor that initializes the account with owner name and account number (balance starts at 0)
// deposit(amount): adds money to balance (only positive amounts)
// withdraw(amount): removes money if sufficient balance exists, returns success/failure
// getBalance(): returns current balance

class InsufficientFundsException : public runtime_error {
    public :
     double shortfall;
     InsufficientFundsException(double shortfall) : runtime_error("Insufficient funds"), shortfall(shortfall){}
};

class InvalidAmountException : public invalid_argument{
    public:
    InvalidAmountException(const string &msg): invalid_argument(msg){ }
};



class BankAccount{
    private:
     double balance;
     string accountNumber;
     string ownerName;

     public:
     BankAccount(const string& number,  const string &name) : accountNumber(number) , ownerName(name), balance(0.0){
        if(number.empty()) throw invalid_argument("Account number cannot be empty.");
        if(name.empty()) throw invalid_argument("Owner name cannot be empty.");
     }
     
     void deposit(double amount){
        if(amount <= 0){
            throw InvalidAmountException("Deposit amount must be positive.");
        }

        balance += amount;
        cout<<fixed<<setprecision(2);
        cout<<"Deposited: $"<<amount << " | New balance: $"<<balance<<endl;
     }

     bool withdraw(double amount){
        if(amount <= 0){
            throw InvalidAmountException("Withdraw must be positive");
        }
        if(amount > balance){
            throw InsufficientFundsException(amount - balance);
        }

        balance -= amount;
        cout<<fixed<<setprecision(2);
        cout << "Withdrawn: $" << amount << " | Remaining Balance: $" << balance << "\n";
        return true;
     }

     double getBalance() const{
        return balance;
     }

     //getters for dealing with private variables
     const string& getAccountNumber()  const {return accountNumber;}
     const string& getOwnerName() const {return ownerName;}

};


enum class Coin{
    PENNY,
    NICKEL,
    DIME,
    QUARTER
};

int getValueCoin(Coin coin){
    switch(coin){
        case Coin::PENNY: return 1;
        case Coin::NICKEL: return 5;
        case Coin::DIME: return 10;
        case Coin::QUARTER: return 25;
        default: return 0;

    }
}







///2  @brief---------- Order Management---------------
struct PaymentMethod{
    string displayName;
    double feePercent;

    static const PaymentMethod CREDIT_CARD;
    static const PaymentMethod DEBIT_CARD;
    static const PaymentMethod UPI;
    static const PaymentMethod NET_BANKING;
    static const PaymentMethod customMethod;
};

const PaymentMethod PaymentMethod::CREDIT_CARD{"Credit Card", 2.5};
const PaymentMethod PaymentMethod::DEBIT_CARD{"Debit Card", 1.0};
const PaymentMethod PaymentMethod::UPI{"UPI", 0.0};
const PaymentMethod PaymentMethod::NET_BANKING{"Net Banking", 1.5};

enum class OrderStatus{
    PLACED , CONFIRMED, SHIPPED, DELIVERED, CANCELLED
};

string orderStatusToString(OrderStatus s){
    switch(s){
        case OrderStatus::PLACED: return "PLACED";
        case OrderStatus::CONFIRMED:  return "CONFIRMED";
        case OrderStatus::SHIPPED: return "SHIPPED";
        case OrderStatus::DELIVERED: return "DELIVERED";
        case OrderStatus::CANCELLED: return "CANCELLED";
        default: return "UNKNOWN";
    }
}

class Order{
    private:
        string orderId;
        OrderStatus status;
        PaymentMethod paymentMethod;
        double amount;

        public:
        Order(const string &orderId, const PaymentMethod &paymentMethod , double amount)
        :orderId(orderId), status(OrderStatus::PLACED), paymentMethod(paymentMethod), amount(amount)
        {}
        
        bool advanceStatus(){
            switch(status){
                case OrderStatus::PLACED :
                    status = OrderStatus::CONFIRMED; return true;
                case OrderStatus::CONFIRMED :
                    status = OrderStatus::SHIPPED; return true;
                case OrderStatus::SHIPPED :
                    status = OrderStatus::DELIVERED; return true;
                default:
                    return false;
                }
        }

        bool cancel(){
            if(status == OrderStatus::PLACED || status == OrderStatus::CONFIRMED){
                status =  OrderStatus::CANCELLED;
                return true;
            }
            return false;
        }

        double getTotalWithFees() const {
            return amount + (amount * paymentMethod.feePercent / 100);
        }

       void displayInfo() const {
        printf("Order %s | Status: %s | Payment: %s | Amount: $%.2f (with fees: $%.2f)\n",
            orderId.c_str(), orderStatusToString(status).c_str(),
            paymentMethod.displayName.c_str(), amount, getTotalWithFees());
        }
};
        
enum class daily{
    WAKEUP,
    FRESH,
    GYM,
    BATH,
    METRO,
    OFFICE
};


enum class Statuses{
    RED, GREEN, BLUE
};

string  returnTime(daily s){
    switch(s){
       case daily::WAKEUP:  return "6 AM";
       case daily::FRESH: return "6:30 AM";
       case daily::GYM: return "6:50 AM";
       case daily::BATH: return "8:40 AM";
       case daily::METRO: return "9:30 AM";
       case daily::OFFICE: return "10:30 AM";
       default : return "BUSY IN MY OWN ERA"; 
    }
}



/// 3.  Design Traffic Light Class
// easy
// Problem: Create a TrafficLight enum where each light has a color (RED, YELLOW, GREEN), a duration in seconds, and a next() method that returns 
//the next light in the cycle (RED -> GREEN -> YELLOW -> RED).

// Requirements:

// Each light has a duration property: RED = 30s, YELLOW = 5s, GREEN = 25s
// next() method returns the next TrafficLight in the cycle
// display() method prints the color and duration

enum class TrafficLight{
    RED , YELLOW , GREEN
};



int getDuration(TrafficLight tl){
    switch(tl){
        case TrafficLight::RED : return 30;
        case TrafficLight::YELLOW: return 5; 
        case TrafficLight::GREEN: return 25;
        default: return 0;
    }
};

TrafficLight getNext(TrafficLight tl){
    switch(tl){
        case TrafficLight::RED : return TrafficLight::GREEN;
        case TrafficLight::GREEN: return TrafficLight::YELLOW;
        case TrafficLight::YELLOW: return TrafficLight::RED;
        default: return TrafficLight::RED;
    }
};

void display(TrafficLight tl){
    string color;
    switch(tl){
        case TrafficLight::RED : color = "RED"; break;
        case TrafficLight::GREEN : color = "GREEN"; break;
        case TrafficLight::YELLOW: color = "YELLOW"; break;
        default: color ="Please choose correct option"; 
    }

    cout<<"Color is: "<<color<<" Time: "<<getDuration(tl)<<endl;
}





// 4. Implement HTTP Status Code
// medium
// Problem: Create an HttpStatus enum where each status has a numeric code and a message string.

// Requirements:

// Values: OK(200, "OK"), BAD_REQUEST(400, "Bad Request"), NOT_FOUND(404, "Not Found"), INTERNAL_SERVER_ERROR(500, "Internal Server Error")
// isSuccess() method that returns true if the code is less than 400
// display() method that prints "CODE MESSAGE" (e.g. "200 OK")
// A static fromCode(int) method that returns the HttpStatus for a given code, or null/None if not found

// enum class HttpStatus{
//     OK = 200,
//     BAD_REQUEST = 400,
//     NOT_FOUND = 404,
//     INTERNAL_SERVER_ERROR = 500
// };

// int getStatusCode(HttpStatus st){
//     return static_cast<int>(st);
// }


// bool isSuccess(HttpStatus s){
//     return getStatusCode(s) < 400;
// }

// string getStatusText(HttpStatus s){
//     switch(s){
//         case HttpStatus::OK : return "OK ";
//         case HttpStatus::BAD_REQUEST : return "BAD REQUEST";
//         case HttpStatus::NOT_FOUND : return "NOT FOUND";
//         case HttpStatus::INTERNAL_SERVER_ERROR: return "INTERNAL SERVER ERROR";
//         default: return "UNKNOWN";
//     }
// }


// bool frmCode(int code, HttpStatus &out){
//     switch(code){
//         case 200: out = HttpStatus::OK; return true;
//         case 400: out = HttpStatus::BAD_REQUEST; return true;
//         case 404: out = HttpStatus::NOT_FOUND; return true;
//         case 500: out = HttpStatus::INTERNAL_SERVER_ERROR; return true;
//         default: return false;
//     }
// }


//uaing the struct 
struct HttpStatus{
    string statusName;
    int code;

    static const HttpStatus OK;
    static const HttpStatus BAD_REQUEST;
    static const HttpStatus NOT_FOUND;
    static const HttpStatus INTERNAL_SERVER_ERROR;

    bool isSuccess() const{
        return code < 400;
    }
    
    void dispaly() const{
        cout<<statusName <<" : "<<code<<endl;
    }

    static const HttpStatus* fromCode(int code) {
        for (const auto* status : values()) {
            if (status->code == code) {
                return status;
            }
        }
        return nullptr;
    }

    static const vector<const HttpStatus*>& values() {
        static vector<const HttpStatus*> v = {&OK, &BAD_REQUEST, &NOT_FOUND, &INTERNAL_SERVER_ERROR};
        return v;
    }
};

const HttpStatus HttpStatus::OK{"OK" , 200};
const HttpStatus HttpStatus::BAD_REQUEST{"BAD REQUEST" , 400};
const HttpStatus HttpStatus::NOT_FOUND{"Not Found", 404};
const HttpStatus HttpStatus::INTERNAL_SERVER_ERROR{"Internal Server Error" , 500};

// bool isSuccess(HttpStatus &st){
//     if(st.code < 400) return true;
//     return false;
// }


int main(){

    HttpStatus::OK.dispaly();
    HttpStatus::BAD_REQUEST.dispaly();

    HttpStatus st = HttpStatus::OK;
    cout<<"Is success: "<<st.isSuccess()<<endl;

    const HttpStatus* ht = HttpStatus::fromCode(400);
    ht->dispaly();
     cout<<"Is success: "<<ht->isSuccess()<<endl;
    // HttpStatus st = HttpStatus::OK;


    // bool ans = isSuccess(st);
    // cout<<"SUccess: "<<ans<<endl;





    // HttpStatus st = HttpStatus::OK;
    // string statusName = getStatusText(st);
    // cout<<"Status : "<<statusName<<endl;

    // bool status = isSuccess(st);
    // cout<<"Is < 400: "<<status<<endl;

    // int statusCode = getStatusCode(st);
    // cout<<"Status code: "<<statusCode<<endl;

    // HttpStatus parsed ;
    // status = frmCode(500 , parsed);
    // cout<<"FrmCode status: "<<status<<endl;
    // string frmcode = getStatusText(out);
    // cout<<"Frm code : "<<frmCode<<endl;
    // cout << getStatusCode(parsed) << " " << getStatusText(parsed) << "\n"; // 200 OK



    // TrafficLight tl = TrafficLight::RED;
    // display(tl);
    // TrafficLight tl2 = getNext(tl);
    // display(tl2);
    // cout<<static_cast<int>(tl2)<<endl;
    // for(int i = 0; i<6; i++){
    //     display(tl);
    //     tl = getNext(tl);
    // }




    // daily d = daily::GYM;
    // string time = returnTime(d);

    // cout<<"Time is: "<<time<<endl;


    // Order order("ORD-001", PaymentMethod::CREDIT_CARD, 99.99);
    // order.displayInfo();

    // order.advanceStatus();
    // order.advanceStatus();
    // order.displayInfo();

    // cout << "Cancel after shipping: " << (order.cancel() ? "true" : "false") <<endl;

    // cout<<endl;
    // cout<<"Hello duniya"<<endl;
    // cout<<PaymentMethod::CREDIT_CARD.displayName<<endl;
    // cout<<PaymentMethod::CREDIT_CARD.feePercent<<endl;

    // PaymentMethod PaymentMethod::customMethod;
    // cout<<customMethod<<endl;
    // cout<<customMethod.displayName<<endl;
    // cout<<customMethod.feePercent<<endl;

    // PaymentMethod::customMethod.displayName = "CRYPTO";
    // PaymentMethod::customMethod.feePercent = 5;

    // cout<<customMethod.displayName<<endl;
    // cout<<customMethod.feePercent<<endl;

    // cout<<PaymentMethod::customMethod.displayName<<endl;


    return 0;
    // Coin c = Coin :: DIME;
    // int val = getValueCoin(c);
    // cout<<val<<endl;

    // cout<<static_cast<int>(Coin::NICKEL)<<endl;


    // try{
    //     BankAccount acc1("123456", "Raghav singh");

    //     acc1.deposit(500);
    //     acc1.withdraw(200);

    //     acc1.withdraw(1000);
    //  }   
    //  catch (const InsufficientFundsException& e) {
    //     cerr << "Error: " << e.what()
    //          << " | Shortfall: $" << fixed << setprecision(2) << e.shortfall << "\n";

    // } catch (const InvalidAmountException& e) {
    //     cerr << "Invalid amount: " << e.what() << "\n";

    // } catch (const invalid_argument& e) {
    //     cerr << "Invalid argument: " << e.what() << "\n";

    // } catch (const exception& e) {
    //     cerr << "Unexpected error: " << e.what() << "\n";
    // }

}

//------------By My own --------------------------
// class BankAccount{
//     //fields
//     private:
//     int balance=0;
//     public:  
//     string accountNumber="";
//     string ownerName = "";
    
//     BankAccount(string number, string name):accountNumber(number), ownerName(name){}

//     //methods
//     void deposit(int amount){
//         if(amount <= 0){
//             cout<<"Amount can't be negative"<<endl;
//             return;
//         }
//         cout<<"--------------DEPOSIT-------------------"<<endl;
//         cout<<"Balance : "<<balance<<endl;
//         balance += amount;
//         cout<<"Deposit amount: "<<amount<<endl;
//         cout<<"New Balance: "<<balance<<endl;
//         cout<<"---------------------------------"<<endl;
        
//     }

//     void withdraw(int amount){
//         if(amount <= 0){
//             cout <<"Withdraw amount should be greter than 0."<<endl;
//             return;
//         }
//         cout<<"-----------WITHDRAW----------------------"<<endl;
//         cout<<"Balnce : "<<balance<<endl;

//         if(balance > amount){            
//         balance -= amount;
//         cout<<"Withdraw amount: "<<amount<<endl;
//         cout<<"Remaining Balance: "<<balance<<endl;
//         cout<<"---------------------------------"<<endl;
//         }else {
//                     cout <<"Withdraw amount should be greter than 0."<<endl;

//         }
//     }

//     void getBalance(){
//         cout<<"Balance: "<<balance<<endl;
//         return ;
//     }
// };

// int main(){
//     BankAccount acc1("123456", "Raghav singh");
//     acc1.deposit(100);
//     acc1.withdraw(50);
    
//     acc1.deposit(-90);
//     acc1.withdraw(1000);

// }