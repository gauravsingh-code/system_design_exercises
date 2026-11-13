#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
 ISubject (Publisher Interface): 
   Provides methods to attach() (subscribe), detach() (unsubscribe), and notify() observer

     «interface»                              «interface»
      ISubject                                IObserver
    (Publisher)                             (Subscriber)
         △                                       △
         │                                       │
         │  1                              0..*  │
   WeatherStation ◇──────────────────────── PhoneDisplay
 (Holds data & list)                     (Receives updates)

---- Critical Interview Traps to Watch Out For ---
1. The "Lapsed Listener" Memory Leak:
If an observer object is destroyed in memory but forgets to call detach(), the Subject still holds a dangling pointer to it! Calling notify() will crash the app (segmentation fault).
Fix: Make the observer unsubscribe in its destructor ~Observer() { subject->detach(this); }.
2. Order of Notifications:
Observers should never rely on the order in which they are notified.
3. Open-Closed Principle (OCP):
Want to add a SmartWatchDisplay? You just write a new class implementing IObserver. You never touch WeatherStation.

std::erase(observers, observer); // C++20 one-liner!

*/

//1. Subcriber interface
class IObserver{
    public:
    virtual void update(float temp) = 0;  //notification hook
    virtual ~IObserver() = default;
}

//2. Publisher Interface
class ISubject{
    public:
    virtual void attach(IObserver *observer) = 0;  //subcribe
    virtual void detach(IObserver* observer) = 0;  //unsubscribe
    virtual void notify() = 0;  
    virtual ~ISubject() = default;
}

//3. Concreate Publisher
class WeatherStation : public ISubject{
    private:
    vector<IObserver*> observers ; // ◄── List of subscribers (Aggregation: ◇)
    float temperature = 0.0f;  //value or data to notify about

    public:
    void attach(IObserver* observer) override{
        observers.push_back(observer);
    }

    void detach(IObserver* observer) override{
        observers.erase(remove(observers.begin(), observers.end(), observer),
                       observers.end()
        );
    }

    void notify() override{
        for(IObserver* obs : observers){
            obs->update(temperature);
        }
    }

    void setTemperature(float newTemp) {
        cout << "\n🌡️ [WeatherStation] Temperature changed to: " << newTemp << "°C" << endl;
        this->temperature = newTemp;
        notify(); // ◄── Automatically broadcast to all subscribers!
    }
};

// Subscriber 1: Mobile App
class PhoneDisplay : public IObserver {
private:
    string user;
public:
    PhoneDisplay(string name) : user(name) {}

    void update(float temp) override {
        cout << "📱 [PhoneDisplay - " << user << "] Temp updated: " << temp << "°C" << endl;
    }
};

// Subscriber 2: Public Billboard
class BillboardDisplay : public IObserver {
public:
    void update(float temp) override {
        cout << "🏢 [LED Billboard] Displaying Live Temp: " << temp << "°C" << endl;
    }
};

int main(){

    WeatherStation station;
    // Create Subscribers
    PhoneDisplay userAlice("Alice");
    PhoneDisplay userBob("Bob");
    BillboardDisplay billboard;
    // 1. Alice & Billboard Subscribe
    station.attach(&userAlice);
    station.attach(&billboard);
    // Weather changes -> Alice and Billboard receive update
    station.setTemperature(28.5f);
    // 2. Bob also subscribes; Billboard unsubscribes
    station.attach(&userBob);
    station.detach(&billboard);
    // Weather changes again -> Only Alice and Bob receive update!
    station.setTemperature(31.0f);

    cout<<"Hello world "<<endl;
    return 0;
}