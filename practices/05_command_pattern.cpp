#include<iostream>
#include<memory>

using namespace std;


/*
The Command Pattern is a behavioral design pattern that turns a request into a stand-alone object containing all information about the request.

This transformation lets you:

Parameterize clients with different requests (e.g., plug any action into any UI button)
Delay or queue a request's execution
Support reversible operations (Undo / Redo)
Log actions for auditing or rollback

[Customer] ---> Creates order ---> [Waiter] ---> Places on queue ---> [Chef]
 (Client)         (Command)        (Invoker)                           (Receiver)

*/

// 1. RECEIVER: The actual worker
class Light {
public:
    void turnOn()  { cout << "Light is ON\n"; }
    void turnOff() { cout << "Light is OFF\n"; }
};

class TV {
    public:
    void turnOn()  { cout << "TV is ON\n"; }
    void turnOff() { cout << "TV is OFF\n"; }
};


//2.command interface
class ICommand{
    public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// 3. CONCRETE COMMAND: Encapsulates the request
class LighOnCommand : public ICommand{
    private:
    shared_ptr<Light> light; //receiver which actually perform action

    public:
    LighOnCommand(shared_ptr<Light> l) : light(l){}

    void execute() override{
        light->turnOn();
    }

    void undo() override{
        light->turnOff(); 
    }
};

class TVOnCommand : public ICommand{
    private:
    shared_ptr<TV> tv;

    public:
    TVOnCommand(shared_ptr<TV> t) : tv(t){}

    void execute() override{
        tv->turnOn();
    }

    void undo() override{
        tv->turnOff();
    }
};

//4. INVOKER : The button trigger
class RemoteControl{
    private:
    shared_ptr<ICommand> slot;   //this invokers have all command's list like waiter have list of all orders from clients

    public:
    void setCommand(shared_ptr<ICommand> cmd){
        slot = cmd;
    }

    void pressButton(){
        if(slot) slot->execute();
    }

    void pressUndo(){
        if(slot) slot->undo();
    }
};




int main()
{

    // creat a real device (receiver)
    auto livingRoomLight = make_shared<Light>();
    
    //wrap that receiver to command
    auto lightOn = make_shared<LighOnCommand>(livingRoomLight);
    
    //give the command to remote (invoker)
    RemoteControl remote;
    remote.setCommand(lightOn);

    cout<<"----Light Actions----\n";
    remote.pressButton();
    remote.pressUndo();

    // ==========================================
    // 2. Controlling the TV (Just swap the command!)
    // ==========================================

    auto bedRoomTv = make_shared<TV>();
    auto tvOn = make_shared<TVOnCommand>(bedRoomTv);

    remote.setCommand(tvOn);

    cout << "\n--- TV Actions ---\n";
    remote.pressButton(); // Output: TV is ON
    remote.pressUndo();   // Output: TV is OFF

    cout<<"Hello world"<<endl;
    
    return 0;
}