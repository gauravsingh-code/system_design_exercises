#include<iostream>
using namespace std;

class PaymentGateway{
    public:
    //abstract method which is going to implemnt by all processors
    virtual void payment(double amount) = 0;
    virtual  ~PaymentGateway() = default;
    //virtual ~PaymentGateway(){}

    // virtual ~PaymentGateway() {
    //     cout<<"Payment Gateway(parent) destructor called."<<endl;
    // }
};

class UPIProcessor : public PaymentGateway{
    public:
    void payment(double amount)  override {
        cout<<"Payment using UPI: "<<amount<<endl;
    }

    ~UPIProcessor(){
        cout<<"Derived class destructor callled."<<endl;
    }
};

class CardProcessor : public PaymentGateway{
    public:
    void payment(double amount)  override {
        cout<<"Payment using Card: "<<amount<<endl;
    }
};

class PaypalProcessor : PaymentGateway{
    public:
    void payment(double amount)  override{
        cout<<"Payment using Paypal: "<<amount<<endl;
    }
};

//context for strategy pattern
class PaymentService {
    private:
    PaymentGateway * strategy;

    public:
    void setStrategy(PaymentGateway *strategyName){
        this->strategy = strategyName;
    }

    void checkOut(double amount){
        if(strategy){
            strategy->payment(amount);
        }else{
            cout<<"No Payment method selected..."<<endl;
        }
    }
};





int main(){

    PaymentService service;

    UPIProcessor upi;
    service.setStrategy(&upi);
    service.checkOut(456.0);

    CardProcessor cp;
    service.setStrategy(&cp);
    service.checkOut(900);


    // PaymentGateway* gateway = new UPIProcessor();
    // gateway->payment(89);

     
    // UPIProcessor *upi = new UPIProcessor();
    // upi->payment(35);
    // delete upi;

    // CardProcessor cd;
    // cd.payment(45);

    // PaypalProcessor py;
    // py.payment(40);

    return 0;
}