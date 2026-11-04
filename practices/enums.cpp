
#include "./utils.h"



void processOrder(){
    cout<<"Order successful "<<endl;
}


enum Orders {
    PENDING = 23,
    IN_PROGRESS = 78,
    SUBMIT = 200,
    COMPLETE = 500
};

Orders status = SUBMIT;

//2. Payment example
enum class PaymentStatus {
    PENDING,
    PROGRESS,
    COMPLETE,
    ISSUE,
};

string statusTostring(PaymentStatus status){
    switch(status){
        case PaymentStatus::PENDING  : return "PENDING";
        case PaymentStatus::PROGRESS : return "PROGRESS";
        case PaymentStatus::COMPLETE : return "COMPLETE";
        case PaymentStatus::ISSUE    : return "ISSUE";
        default                      : return "UNKNOWN";

    }
}



class PaymentService{
    private:
    string paymentId;
    double amount;
    bool paymentstatus;

    public:
    PaymentService(double amt, PaymentStatus status){
        this->paymentId = generateRandomID();
        this->amount = amt;
        this->paymentstatus = static_cast<int>(status);
    }
    void processPayment(){
        if(paymentstatus == static_cast<int>(PaymentStatus ::COMPLETE)){
            cout<<"Paymennt Successful.."<<endl;
        }
        cout<<"Payment failed..0"<<endl;
    }

    void showPaymentDetails(){
        cout<<"--------------------"<<endl;
        cout<<"Payment Id : "<<paymentId<<endl;
        cout<<"Amount : "<<amount<<endl;
        cout<<"Payment status: "<<paymentstatus<<endl;
        cout<<"-----------------"<<endl;
    }
};

int main(){

    PaymentService py(300, PaymentStatus::PENDING);
    py.processPayment();
    py.showPaymentDetails();

    //when submit process orser
    // string status = "SUBMIT";
    /*
    status = Orders::COMPLETE;
    if(status == Orders::SUBMIT){
        processOrder();
        return -1;
    }

    cout<<static_cast<int>(status)<<endl;
    */

    cout<<"Hello word\n";


    return 0;
}