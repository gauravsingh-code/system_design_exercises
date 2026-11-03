#include<iostream>
#include<ctime>
using namespace std;

void greet(string name = "user"){
  time_t now = time(0);
  char* dt = ctime(&now);
  cout<<"Now: "<<now<<endl;
    cout<<"Welcome "<<name<<endl;
    cout<<"Today date is: "<<dt<<endl;
};