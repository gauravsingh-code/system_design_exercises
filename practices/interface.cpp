#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

// =============================================================================
// PROBLEM 1: Payment Processor — Tight Coupling (WITHOUT Interface)
// Problem  : Adding a new payment method (e.g. Stripe) forces changes in
//            CheckOutSystem AND main(). Every new processor = class change.
// Concept  : Tight coupling — high-level class depends on concrete classes.
// =============================================================================


// class PaypalProcessor {
//     public:
//         void processPayment(double amount) {
//             cout << "-------- Paypal ------" << endl;
//             cout << "Processing the payment." << amount << endl;
//             cout << "Payment is complete...." << endl;
//         }
// };


// class stripeProcessor {
//     public:
//         void processPayment(double amount) {
//             cout << "-------- Stripe ------" << endl;
//             cout << "Processing the payment." << amount << endl;
//             cout << "Payment is complete...." << endl;
//         }
// };


// class checkOutSystem {
//     private:
//         PaypalProcessor paypal;
//         stripeProcessor stripe;
//     public:
//         void completePaymentPaypal(double amount) { paypal.processPayment(amount); }
//         void completePaymentStripe(double amount) { stripe.processPayment(amount); }
// };


// --- Driver (tight coupling) ---
//
//     checkOutSystem cs;
//     cs.completePaymentPaypal(788);
//     cs.completePaymentStripe(899);




// =============================================================================
// PROBLEM 2: Payment Processor — Loose Coupling (WITH Interface)
// Solution : Introduce an abstract interface IPaymentProcessor.
//            CheckOutSystem depends ONLY on the interface — never on concrete
//            classes. Adding a new processor requires ZERO changes to
//            CheckOutSystem or main().
// Concept  : Interface (abstract class with pure virtual functions),
//            Dependency Inversion Principle (DIP).
// =============================================================================


// --- Interface (abstract base class) ---
//
// class IPaymentProcessor
// {
// public:
//     virtual ~IPaymentProcessor() = default;
//     virtual bool processPayment(double amount) = 0;
//     virtual string name() const = 0;
// };


// --- Concrete Implementation: PaypalProcessor ---
//
// class PaypalProcessor final : public IPaymentProcessor
// {
// public:
//     bool processPayment(double amount) override
//     {
//         if (amount < 0.0)
//             throw invalid_argument("Amount must be greater than 0");
//
//         cout << "-------- PayPal ------\n";
//         cout << "Processing payment: $" << fixed << setprecision(2) << amount << "\n";
//         cout << "Payment completed via PayPal.\n";
//         return true;
//     }
//
//     string name() const override { return "paypal"; }
// };


// --- Concrete Implementation: StripeProcessor ---
//
// class StripeProcessor final : public IPaymentProcessor
// {
// public:
//     bool processPayment(double amount) override
//     {
//         if (amount < 0.0)
//             throw invalid_argument("Amount must be greater than 0");
//
//         cout << "-------- Stripe ------\n";
//         cout << "Processing payment: $" << fixed << setprecision(2) << amount << "\n";
//         cout << "Payment completed via Stripe.\n";
//         return true;
//     }
//
//     string name() const override { return "stripe"; }
// };


// --- High-level class depends on interface, NOT on concrete classes ---
//
// class CheckOutSystem
// {
// private:
//     unordered_map<string, unique_ptr<IPaymentProcessor>> processors;
//
// public:
//     void registerProcessor(unique_ptr<IPaymentProcessor> processor)
//     {
//         if (!processor)
//             throw invalid_argument("Cannot register null processor.");
//
//         string key = processor->name();
//         processors[key] = move(processor);
//     }
//
//     bool completePayment(const string &method, double amount)
//     {
//         auto it = processors.find(method);
//         if (it == processors.end())
//             throw runtime_error("Unsupported payment method: " + method);
//
//         return it->second->processPayment(amount);
//     }
// };


// --- Driver (loose coupling) ---
//
//     try
//     {
//         CheckOutSystem checkout;
//         checkout.registerProcessor(make_unique<PaypalProcessor>());
//         checkout.registerProcessor(make_unique<StripeProcessor>());
//         checkout.completePayment("paypal", 899);
//         cout << "\n";
//         checkout.completePayment("stripe", 765);
//     }
//     catch (exception &e)
//     {
//         cerr << "Payment Error: " << e.what() << endl;
//         return 1;
//     }




// =============================================================================
// PROBLEM 3: Notification System — Interface for Multiple Channels
// Problem  : AlertService needs to send alerts via Email, Slack, or Webhook.
//            Without an interface, AlertService must know about each channel.
// Solution : NotificationService interface — AlertService depends only on the
//            interface. Any new channel (e.g. SMS) plugs in without changes.
// Concept  : Interface, Polymorphism, Open/Closed Principle (OCP).
// =============================================================================


// --- Interface ---
//
// class NotificationService
// {
// public:
//     virtual ~NotificationService() = default;
//     virtual void send(const string &recipient, const string &message) = 0;
// };


// --- Concrete Implementation: Email ---
//
// class Email : public NotificationService
// {
// public:
//     void send(const string &recipient, const string &message) override
//     {
//         cout << "----------- Email Alert ---------" << endl;
//         cout << "To: " << recipient << " | " << message << endl;
//     }
// };


// --- Concrete Implementation: Slack ---
//
// class Slack : public NotificationService
// {
// public:
//     void send(const string &recipient, const string &message) override
//     {
//         cout << "----------- Slack Alert ---------" << endl;
//         cout << "Channel: " << recipient << " | " << message << endl;
//     }
// };


// --- Concrete Implementation: Webhook ---
//
// class Webhook : public NotificationService
// {
// public:
//     void send(const string &recipient, const string &message) override
//     {
//         cout << "----------- Webhook Alert ---------" << endl;
//         cout << "URL: " << recipient << " | " << message << endl;
//     }
// };


// --- Old AlertService (without interface — tight coupling, broken) ---
//
// class AlertService {
//     private:
//         vector<Notification> notifier;
//     public:
//         AlertService(Notification notification) { notifier.push_back(notification); }
//         void triggerAlert(Notification notification) {
//             if (find(notifier.begin(), notifier.end(), notification) == notifier.end()) {
//                 cout << "Notification service do not exist" << endl;
//                 return;
//             }
//             notification.send(string recipient, string message);
//         }
// };


// --- AlertService depends on interface, NOT on Email/Slack/Webhook ---
//
// class AlertService
// {
// private:
//     NotificationService *notifier;
//
// public:
//     AlertService(NotificationService *notifier) : notifier(notifier) {}
//
//     void triggerAlert(const string &recipient, const string &issue)
//     {
//         string alertMessage = "ALERT: " + issue;
//         notifier->send(recipient, alertMessage);
//     }
// };


// --- Driver (notification system) ---
//
//     Email emailNotifier;
//     AlertService emailAlerts(&emailNotifier);
//     emailAlerts.triggerAlert("ops@company.com", "CPU usage at 95%");
//
//     Slack slackNotifier;
//     AlertService slackAlerts(&slackNotifier);
//     slackAlerts.triggerAlert("#incidents", "Database connection pool exhausted");
//
//     Webhook webhookNotifier;
//     AlertService webhookAlerts(&webhookNotifier);
//     webhookAlerts.triggerAlert("https://hooks.example.com/alerts", "Disk usage at 90%");




// =============================================================================
// PROBLEM 4: Logger — Interface for Multiple Channels
// Problem  : AlertService needs to send alerts via Email, Slack, or Webhook.
//            Without an interface, AlertService must know about each channel.
// Solution : NotificationService interface — AlertService depends only on the
//            interface. Any new channel (e.g. SMS) plugs in without changes.
// Concept  : Interface, Polymorphism, Open/Closed Principle (OCP).
// =============================================================================

/*
class IFormatter{
    public:
    virtual ~IFormatter() = default;
    virtual void format(const string &msg) = 0;  
};

class PlainText :  public IFormatter{
    public:
    void format(const string &msg) override{
        cout<<"-------Plain text format---------"<<endl;
        cout<<"Message: "<<msg<<endl;
    }
};

class JsonText: public IFormatter{
    public:
    void format(const string &msg) override{
        cout<<"-------Json text format---------"<<endl;
        cout<<"Json: { \"log\": "<<"\""<<msg<<"\""<<"}"<<endl;
    }
};

class Logger{
    private:
        IFormatter *formatter;

    public:
        Logger(IFormatter * formatter):formatter(formatter){};

        void setFormatter(IFormatter *newFormatter){
            formatter = newFormatter;
        }
        
        void log(const string &msg){
            formatter->format(msg);
        }
};

-----Driver CODE ----------
    // JsonText json ;
    // Logger logger(&json);
    // logger.log("This is error message :");

    // PlainText text;
    // logger.setFormatter(&text);
    // logger.log("This is plain message");
*/



// =============================================================================
// PROBLEM 5: Input Validator
// Problem  : AlertService needs to send alerts via Email, Slack, or Webhook.
//            Without an interface, AlertService must know about each channel.
// Solution : NotificationService interface — AlertService depends only on the
//            interface. Any new channel (e.g. SMS) plugs in without changes.
// Concept  : Interface, Polymorphism, Open/Closed Principle (OCP).
// =============================================================================




int main(){

    
    return 0;
}