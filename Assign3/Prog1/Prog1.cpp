#include <iostream>

extern int quarters;
extern int dimes;
extern int nickels;
extern int pennies;

//letting the compiler know that there is a function
void calculateChange(int purchase);

int main() {
    // Prompt the user for a input
    int input;
    std::cout << "Enter a purchase amount in pennies (<= 100): ";
    std::cin >> input;

    // while looop if the user enters anything less than a 0 and greater than 100
    while(input <= 0 || input > 100){
        std::cout << "Enter a purchase amount in pennies (<= 100): ";
        std::cin >> input;
    }

    // Calculate the change
    calculateChange(input);

    // Display the results
    std::cout << "Change from a dollar:" << std::endl;
    std::cout << "Quarters: " << quarters << std::endl;
    std::cout << "Dimes: " << dimes << std::endl;
    std::cout << "Nickels: " << nickels << std::endl;
    std::cout << "Pennies: " << pennies << std::endl;

    return 0;
}
