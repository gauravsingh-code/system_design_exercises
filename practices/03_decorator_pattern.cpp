#include<iostream>
#include<memory>

using namespace std;



 /*
 --- Structural Pattern ---------
 -- Solves The Nightmare Problem: The "Class Explosion" 
 "Start with a plain base object, and WRAP it in layers dynamically at runtime."
┌──────────────────────────────────────────────┐
│  Caramel Decorator (+$3)                     │
│  ┌────────────────────────────────────────┐  │
│  │  Milk Decorator (+$2)                  │  │
│  │  ┌──────────────────────────────────┐  │  │
│  │  │  SimpleCoffee ($5)               │  │  │
│  │  └──────────────────────────────────┘  │  │
│  └────────────────────────────────────────┘  │
└──────────────────────────────────────────────┘
When you ask for the price, the outer layer asks the middle layer, which asks the core:
Total Cost= $3(Caramel) +$2(Milk) +$5(Coffee) =$10

A Decorator IS-A Component AND it HAS-A Component!
                  «interface»
                   Beverage
                      △
         ┌────────────┴────────────┐
   SimpleCoffee             BeverageDecorator
 (Base Product)               ◇ (HAS-A Beverage*)
                              △
                     ┌────────┴────────┐
                MilkDecorator    SugarDecorator

It IS-A Beverage (Inheritance): So it can masquerade as a beverage anywhere in your code.
It HAS-A Beverage (Aggregation/Pointer): So it can hold the inner object it is wrapping.

"Masquerade" means "to disguise itself as" or "pretend to be".
 */
class Beverage{
    public:
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Beverage() = default;
};

// 2. Concrete Base Component
class SimpleCoffee : public Beverage {
public:
    string getDescription() const override {
        return "Simple Coffee";
    }
    double cost() const override {
        return 5.0; // Base price $5
    }
};
class Espresso : public Beverage {
public:
    string getDescription() const override {
        return "Espresso";
    }
    double cost() const override {
        return 7.0; // Base price $7
    }
};


// 3. Base Decorator (Implements Beverage AND Wraps a Beverage)
class BeverageDecorator : public Beverage {
protected:
    unique_ptr<Beverage> wrappedBeverage; // ◄── THE INNER OBJECT

public:
    BeverageDecorator(unique_ptr<Beverage> bev) : wrappedBeverage(move(bev)) {}

    string getDescription() const override {
        return wrappedBeverage->getDescription();
    }

    double cost() const override {
        return wrappedBeverage->cost();
    }
};

// Add-on 1: Milk (+$2)
class Milk : public BeverageDecorator {
public:
    Milk(unique_ptr<Beverage> bev) : BeverageDecorator(move(bev)) {}

    string getDescription() const override {
        return wrappedBeverage->getDescription() + ", Milk";
    }

    double cost() const override {
        return wrappedBeverage->cost() + 2.0; // Inner cost + $2
    }
};

// Add-on 2: Sugar (+$1)
class Sugar : public BeverageDecorator {
public:
    Sugar(unique_ptr<Beverage> bev) : BeverageDecorator(move(bev)) {}

    string getDescription() const override {
        return wrappedBeverage->getDescription() + ", Sugar";
    }

    double cost() const override {
        return wrappedBeverage->cost() + 1.0; // Inner cost + $1
    }
};

// Add-on 3: Caramel (+$3)
class Caramel : public BeverageDecorator {
public:
    Caramel(unique_ptr<Beverage> bev) : BeverageDecorator(move(bev)) {}

    string getDescription() const override {
        return wrappedBeverage->getDescription() + ", Caramel";
    }

    double cost() const override {
        return wrappedBeverage->cost() + 3.0; // Inner cost + $3
    }
};


int main(){

    unique_ptr<Beverage> order1 = make_unique<SimpleCoffee>();
    cout<<order1->getDescription() << " : $"<<order1->cost() <<endl;

    unique_ptr<Beverage> order2 = make_unique<Espresso>();
    order2 = make_unique<Milk>(move(order2));
    order2 = make_unique<Sugar>(move(order2));
    cout<<order2->getDescription() << "  : $"<<order2->cost()<<endl;


    cout<<"Hello world"<<endl;
    return 0;
}