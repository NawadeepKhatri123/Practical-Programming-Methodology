#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>     // For std::this_thread::sleep_for
#include <chrono>

void playGame();
int die();
int credits{100};
int wager{};

int main() {
    char ans;
    bool done = false;

    std::srand(static_cast<unsigned int>(std::time(0))); // Seed random number generator

    while (!done) {
        playGame();   // Call the playGame function
        std::cout << "Play again (y/n)? ";
        std::cin >> ans;
        if (ans == 'n' || ans == 'N') {
            done = true;
        } else {
            done = false;
        }
    }
    return 0;
}

void playGame() {
    while (true) {
        std::cout << "You have " << credits << " credits. How much do you want to wager? ";
        std::cin >> wager;

        if (wager > credits) {
            std::cout << "Your wager exceeds your balance. Try again.\n";
            continue; // Ask for the wager again
        } else if (wager <= 0) {
            std::cout << "Wager must be greater than 0. Try again.\n";
            continue; // Ask for the wager again
        }

        credits -= wager; // Deduct the wager from credits
        int sum = die(); // Roll the dice

        if (sum == 7 || sum == 11) {
            std::cout << "Player rolled " << sum << " - You win!\n";
            credits += wager * 2; // Player wins double the wager
            std::cout << "You won " << wager << " credits. Your new balance is " << credits << " credits.\n";
            break; // Exit the game
        } else if (sum == 2 || sum == 3 || sum == 12) {
            std::cout << "Player rolled " << sum << " - You lose.\n";
            std::cout << "You lost " << wager << " credits. Your new balance is " << credits << " credits.\n";
            break; // Exit the game
        } else {
            std::cout << "Point is " << sum << '\n';
            int point = sum; // Set the point
            while (true) {
                sum = die(); // Keep rolling the dice

                if (sum == 7) {
                    std::cout << "Player rolled " << sum << " - You lose.\n";
                    std::cout << "You lost " << wager << " credits. Your new balance is " << credits << " credits.\n";
                    return; // Exit the game
                } else if (sum == point) {
                    std::cout << "Player rolled " << sum << " - You win!\n";
                    credits += wager * 2; // Player wins double the wager
                    std::cout << "You won " << wager << " credits. Your new balance is " << credits << " credits.\n";
                    return; // Exit the game
                }
            }
        }

        // Check if the player is out of credits
        if (credits <= 0) {
            std::cout << "You are out of credits - game over!\n";
            exit(0); // End the game
        }
    }
}

int die() {
    int die1 = (std::rand() % 6) + 1; // Roll first die
    int die2 = (std::rand() % 6) + 1; // Roll second die
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay for 1 second
    std::cout << "Player rolled " << die1 << " + " << die2 << " = " << die1 + die2 << '\n';
    return die1 + die2; // Return the sum of the dice
}

