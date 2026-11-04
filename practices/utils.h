#include<iostream>
#include<random>
#include<ctime>

using namespace std;

string generateRandomID(){
    mt19937 gen(static_cast<unsigned>(time(0)));

    uniform_int_distribution<int> dist(10000, 999999);

    return "PAY-" + to_string(dist(gen));
}