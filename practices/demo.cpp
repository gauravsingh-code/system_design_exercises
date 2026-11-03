#include<iostream>
#include<fstream>
using namespace std;

class Car{
    public:
      string brand;
      string color;
      int topSpeed;
      int buyYear;
      
      Car(string brand, string color, int topspeed , int year){
        this->brand = brand;
        this->color =color;
        this->topSpeed = topspeed;
        this->buyYear = year;
      }
      
      int upSpeed(){
        return topSpeed + 5;
      }
      int downSpeed(){
        return topSpeed-5;
      }
};

// int main(int a)
// {
//     cout << a << "\n";
//     return 0;
// }
// int main(char *a)
// {
//     cout << a << endl;
//     return 0;
// }
// int main(int a, int b)
// {
//     cout << a << " " << b;
//     return 0;
// }


int main(){

string name{"Rahul"};
cout<<name <<" has "<<name.length()<<endl;




    // Car myCar("BMW" ,"Red", 200 , 2013);
    // cout << "Brand: " << myCar.brand << endl;
    // cout << "Color: " << myCar.color << endl;
    // cout << "Top Speed: " << myCar.topSpeed << endl;
    // cout << "Buy Year: " << myCar.buyYear << endl;
    // cout << "Increased Speed: " << myCar.upSpeed() << endl;
    // cout << "Decreased Speed: " << myCar.downSpeed() << endl; 
    // cout<<"Hello world";

    // const int a=10;
    // printf("%d", a);
//  int a; string name;
//  cin>>a>>name;
//  cout<<"Hello "<<name<<", your age is "<<a<<endl;
// cin.get();

// char text[20];
// cout<<"Enter your name: ";
// cin.getline(text , 20);
// cin.get(text, 10);
// string str;
// cin.get(str, 3);
// cout<<"Hello "<<text<<endl;
// printf("Hello World\n");

    // main(3);
    // main("C++");
    // main(9, 6);
    
    // cerr<<"welcome to GFG! :: cerr\n";
    // cout<<"welcome to GFG! :: cout\n";
   
    // ofstream errorLog("error_log.txt");
    // cerr.rdbuf(errorLog.rdbuf());
    // cerr<<"This is an error message redirected to a file.\n";
   
    // errorLog.close();
    // cerr<<"lorem ipsum dolor sit amet, consectetur adipiscing elit.\n";

    return 0;
}