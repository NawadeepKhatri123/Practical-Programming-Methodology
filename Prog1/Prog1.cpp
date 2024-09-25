#include <iostream>
#include "calc.cpp"  // basically intertwines the other .cpp program

int main(){
  // variable declarations
    int input{};
    int pennies{};
    int dimes{};
    int quarters{};


    std::cout<<"Enter a positive integer (<=100) : ";
    std::cin >> input;

   // while loop in case the user doesn't input the value we donot allow
    while(input > 100 || input < 0) {
        std::cout<<" Please enter a positive integer <=100 :  ";
        std::cin>>input;
    }

   // passes input as the parameter to their respective functions and gets a return value
    pennies = calcPennies(input);
    dimes = calcDimes(input);
    quarters = calcQuarters(input);

    // the lines below print the currencies using the values returned
    std::cout << "The amount of quarters in " << input << "$ is " << quarters <<'\n' << std::endl;
    std::cout << "The amount of dimes in " << input << "$ is " << dimes <<'\n' << std::endl;
    std::cout << "The amount of pennies in " << input << "$ is " << pennies <<'\n' << std::endl;

    return 0;
}