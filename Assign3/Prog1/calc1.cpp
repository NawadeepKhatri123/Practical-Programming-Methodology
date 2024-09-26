#include <iostream>

// Declarations of  the coin variables
int quarters = 0;
int dimes = 0;
int nickels = 0;
int pennies = 0;

// Function to calculate change from dollars
void calculateChange(int purchase) {
    // Total amount in pennies for a dollar
    const int dollar = 100;
    int change = dollar - purchase;

    // Calculate the number of quarters
    quarters = change / 25;
    change %= 25; // Remaining change after quarters

    // Calculate the number of dimes
    dimes = change / 10;
    change %= 10; // Remaining change after dimes

    // Calculate the number of nickels
    nickels = change / 5;
    change %= 5; // Remaining change after nickels

    // Remaining change is the number of pennies
    pennies = change;
}
