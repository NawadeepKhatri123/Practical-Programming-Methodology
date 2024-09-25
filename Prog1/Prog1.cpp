#include <iostream>
#include "calc.cpp"

int main(){
    int input{};
    int pennies{};
    int dimes{};
    int quarters{};


    std::cout<<"Enter a positive integer (<=100) : ";
    std::cin >> input;

    while(input > 100 || input < 0) {
        std::cout<<" Please enter a positive integer <=100 :  ";
        std::cin>>input;
    }

    pennies = calcPennies(input);
    dimes = calcDimes(input);
    quarters = calcQuarters(input);

    std::cout << "The amount of quarters in " << input << "$ is " << quarters <<'\n' << std::endl;
    std::cout << "The amount of dimes in " << input << "$ is " << dimes <<'\n' << std::endl;
    std::cout << "The amount of pennies in " << input << "$ is " << pennies <<'\n' << std::endl;

}