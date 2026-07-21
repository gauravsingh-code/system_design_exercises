#include<iostream>
using namespace std;

class Base{
    public:
    virtual void display(){
        cout<<"Base Class Display"<<endl;
    }
    virtual void show(){
        cout<<"Base Class Show"<<endl;
    }

    void fun_1(){
        cout<<"Base Class Fun_1"<<endl;
    }
    virtual void fun_2(){
        cout<<"Base Class Fun_2"<<endl;
    }
    virtual void fun_3(){
        cout<<"Base Class Fun_3"<<endl;
    }
    virtual void fun_4(){
        cout<<"Base Class Fun_4"<<endl;
    }

};

class Derived:public Base{
    public:
    void display() override{
        cout<<"Derived Class Display"<<endl;
    }
    void show(string str){
        cout<<"Derived Class Show: "<<str<<endl;
    }
    void fun_1(){
        cout<<"Derived Class Fun_1"<<endl;
    }
    void fun_2() {
        cout<<"Derived Class Fun_2"<<endl;
    }
    void fun_4(int  x){
        cout<<"Derived Class Fun_4 with int: "<<x<<endl;
    }
};


class Complex{
    public:
    int real, image;

    Complex(int r, int i):  real(r), image(i){}

    Complex operator=(const Complex& obj){
        cout<<"Overloading + operator"<<endl;
        cout<<"Real: "<<real<<" Image: "<<image<<endl;
        cout<<"Obj Real: "<<obj.real<<" Obj Image: "<<obj.image<<endl;
        return Complex(real + obj.real, image + obj.image);
    }
};

int main(){

    // Base *basePtr;
    // Derived derivedObj; 

    // basePtr = &derivedObj;

    // basePtr->display();
    // basePtr->show();
    //basePtr.show(); // This will cause a compile-time error since 'show' is not a member of Base
    

    // basePtr->fun_1();
    // basePtr->fun_2();
    // basePtr->fun_3();
    // basePtr->fun_4();

    // basePtr->fun_4(67);

    Complex c1(10, 5), c2(20, 10);
    cout<<"C1: "<<c1.real<<" + "<<c1.image<<"i"<<endl;
    cout<<"C2: "<<c2.real<<" + "<<c2.image<<"i"<<endl;

    Complex c3 = c2 = c1;
    cout<<"C3: "<<c3.real<<" + "<<c3.image<<"i"<<endl;
    cout<<"Hello world!"<<endl;
    return 0;
}