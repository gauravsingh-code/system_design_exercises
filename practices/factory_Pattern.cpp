#include <iostream>
#include <memory>
#include <string>
using namespace std;

/*
// ==========================================
//   -------- 1.  SIMPLE Factory---------
//  Common Product Interface
// ==========================================
class Notification {
public:
    virtual void send(const string &message) = 0;
    virtual ~Notification() = default;
};
// ==========================================
//  Concrete Products
// ==========================================
class EmailNotification : public Notification {
public:
    void send(const string &message) override {
        cout << "📧 [Email] " << message << endl;
    }
};
class SMSNotification : public Notification {
public:
    void send(const string &message) override {
        cout << "📱 [SMS] " << message << endl;
    }
};
class PushNotification : public Notification {
public:
    void send(const string &message) override {
        cout << "🔔 [Push] " << message << endl;
    }
};

// 3. Simple factory
class NotificationFactory{
    public:
    static unique_ptr<Notification>  createNotification(const string &type){
        if(type == "EMAIL") return make_unique<EmailNotification>();
        else if(type == "SMS") return make_unique<SMSNotification>();
        else if(type == "PUSH") return make_unique<PushNotification>();
        return nullptr;
    }    
};


//client only know about this
class NotificationService{
    public:
    void sendNotification(const string &type, const string &message){
        auto notification = NotificationFactory::createNotification(type);
        if(notification != nullptr){
            notification->send(message);
        }else{
            cout<<"Unknown Notification type: "<< type <<endl;
        }
    }
};

*/



/*
// ==========================================
//   -------- 2.   Factory Pattern (GoF ) ---------
//  Common Product Interface
// ==========================================
class Notification {
public:
    virtual void send(const string &message) = 0;
    virtual ~Notification() = default;
};
// ==========================================
//  Concrete Products
// ==========================================
class EmailNotification : public Notification {
public:
    void send(const string &message) override {
        cout << "📧 [Email] " << message << endl;
    }
};
class SmsNotification : public Notification {
public:
    void send(const string &message) override {
        cout << "📱 [SMS] " << message << endl;
    }
};
class PushNotification : public Notification {
public:
    void send(const string &message) override {
        cout << "🔔 [Push] " << message << endl;
    }
};

// Base Factory: defines the Factory Method - Abstract class 
//In design pattern : Abstract Creator 
class NotificationFactory {
public:
    // ◄── This is the FACTORY METHOD
    virtual unique_ptr<Notification> createNotification() = 0;
    
    // Core business logic (optional, but very common in GoF):
    void send(const string &message) {
        auto notification = createNotification(); // Subclass creates it
        notification->send(message);              // Base class uses it
    }
    virtual ~NotificationFactory() = default;
};


//1. Email Factory
class EmailFactory : public NotificationFactory{
    public: 
    unique_ptr<Notification> createNotification() override{
        return make_unique<EmailNotification>();
    }
};

//2.SMS factory
class SmsFactory : public NotificationFactory{
    public:
    unique_ptr<Notification> createNotification() override{
        return make_unique<SmsNotification>();
    }
};

//3.Push factory
class PushFactory : public NotificationFactory{
    public :
    unique_ptr<Notification>createNotification() override{
        return make_unique<PushNotification>();
    }
};

*/



// ==========================================
//   -------- 3.Abstract Factory Pattern---------
/*                       «interface»
                     NotificationSuiteFactory
                              △
                 ┌--──────────┴──────────┐
  UrgentSuiteFactory                    PromotionalSuiteFactory
  ├── createEmail() ──► UrgentEmail        ├── createEmail() ──► PromotionalEmail
  └── createSMS()   ──► UrgentSMS          └── createSMS()   ──► PromotionalSMS

  concept of "Families(Suits) of Related Products".
  🚨 Urgent / Critical Suite (for OTPs, Security Alerts):
            Uses high-cost, instant-delivery priority gateways.
            UrgentEmail + UrgentSMS
  🎉 Promotional / Marketing Suite (for Sales, Discounts):
            Uses cheap, bulk/batch delivery queues with unsubscribe links.
            PromotionalEmail + PromotionalSMS
*/
//  Common Product Interface
// ==========================================
// class Notification {
// public:
//     virtual void send(const string &message) = 0;
//     virtual ~Notification() = default;
// };


// ==========================================
// Product 1: Email Hierarchy
// ==========================================
class EmailNotification  {
public:
    virtual void sendEmail(const string &msg) = 0;
    virtual ~EmailNotification() = default;
};

// 1 suite of email : Urgent
class UrgentEmail : public EmailNotification{
    void sendEmail(const string &msg) override {
        cout << "🚨 [URGENT EMAIL - Priority Gateway]: " << msg << endl;
    }
};

//2 suite of email : Promotional
class PromotionalEmail : public EmailNotification{
    void sendEmail(const string &msg) override {
        cout << "📢 [PROMO EMAIL - Bulk Queue with Unsubscribe Link]: " << msg << endl;
    }
};

// ==========================================
// Product 2: SMS Hierarchy
// ==========================================
class SMSNotification {
public:
    virtual void sendSMS(const string &msg) = 0;
    virtual ~SMSNotification() = default;
};
class UrgentSMS : public SMSNotification {
public:
    void sendSMS(const string &msg) override {
        cout << "🚨 [URGENT SMS - Direct Route, 0s Delay]: " << msg << endl;
    }
};
class PromotionalSMS : public SMSNotification {
public:
    void sendSMS(const string &msg) override {
        cout << "📢 [PROMO SMS - Cheap Bulk Route]: " << msg << endl;
    }
};

// ==========================================
// ABSTRACT FACTORY (Defines the Suite / Family)
// ==========================================
class NotificationSuiteFactory{
    public:
    virtual unique_ptr<EmailNotification> createEmail() = 0;
    virtual unique_ptr<SMSNotification> createSMS() = 0;
    virtual ~NotificationSuiteFactory() = default;
};

// ------------------------------------------
// Concrete Factory 1: Urgent Suite (Only builds Urgent products)
// ------------------------------------------
class UrgentNotificationSuite : public NotificationSuiteFactory {
public:
    unique_ptr<EmailNotification> createEmail() override {
        return make_unique<UrgentEmail>();
    }
    unique_ptr<SMSNotification> createSMS() override {
        return make_unique<UrgentSMS>();
    }
};

// ------------------------------------------
// Concrete Factory 2: Promotional Suite (Only builds Promo products)
// -----------------------------------------
class PromotionalNotificationSuite : public NotificationSuiteFactory{
    unique_ptr<EmailNotification> createEmail() override{
        return make_unique<PromotionalEmail>();
    }
    unique_ptr<SMSNotification> createSMS() override{
        return make_unique<PromotionalSMS>();
    }
};

void dispatchNotification(NotificationSuiteFactory &suite, const string &message){
    auto email = suite.createEmail();
    auto sms = suite.createSMS();

    email->sendEmail(message);
    sms->sendSMS(message);
}

//client code
int main(){
    // 3. Abstract Factory Method
    cout << "=== 1. Sending OTP (Security Event) ===" << endl;
    UrgentNotificationSuite urgentSuite;
    dispatchNotification(urgentSuite, "Your OTP is 123456"); 
    // Output:
    // 🚨 [URGENT EMAIL - Priority Gateway]: Your OTP is 123456
    // 🚨 [URGENT SMS - Direct Route, 0s Delay]: Your OTP is 123456
    cout << "\n=== 2. Sending Black Friday Discount ===" << endl;
    PromotionalNotificationSuite promoSuite;
    dispatchNotification(promoSuite, "Flat 50% OFF this weekend!");


    /* 2. ----Factory Method----
    EmailFactory email;
    email.send("Hello Good evening ...");
   */


    /*1 ---- SIMPlE Factory ---
    NotificationService ns;

    ns.sendNotification("EMAIL", "Good NIght !");
    ns.sendNotification("SLACK", "HELlo how are you !");
    */

    // SMSNotification sms;
    // sms.send("Hello SMS");

    // PushNotification push;
    // push.send("HELLO push");

    cout<<"\n Hello world"<<endl;
}