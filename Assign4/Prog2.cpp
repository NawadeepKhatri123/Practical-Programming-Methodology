#include<iostream>
#include<cstdlib>
#include<ctime>
#include <thread>     // For std::this_thread::sleep_for
#include <chrono>
void playGame();
void point();
int die();
int credits {100};
int wager{};

int main( ) {
    char ans;

    bool done = false;
    while ( ! done ) {
          while(true){
              std::cout << " you have " << credits << " how much do you want to wager? ";
              std::cin >> wager;
              if ( wager > credits || wager < 0 ) {
                std::cout << " your credits is out of range. Please try again. \n";
              }else {
                credits -= wager;
                break;
              }
           }
      playGame();   // YOU MUST WRITE THIS FUNCTION
      std::cout << " Play again (y/n) ? ";
      std::cin >> ans;
      if ( ans == 'n' || ans == 'N') done = true;
      else done = false;
    }
    return 0;
}

void playGame() {
    int sum = die();
    if ( sum == 7 || sum == 11 ) {
      std::cout<<"You won! " << wager << " Your new balance is "<< (wager*2) + credits<< '\n' ;
      credits = credits + (wager * 2);
      return;
    }
    else if ( sum == 2 || sum == 3 || sum == 12 ) {
        std::cout<<"You Lose! " << wager << " credits. Your new balance is" << credits <<'\n';
        return;
    }
    else if (sum == 4 || sum == 5 || sum == 6 || sum == 8 || sum == 9 || sum == 10 ) {std::cout<<" point is " << sum << '\n';point();return;}

}

void point(){
  int sum{};
  while(true){
    sum = die();
    if ( sum == 7 ){
        std::cout<<"You Lose! " << wager << " credits. Your new balance is" << credits <<'\n';
        return;
    }
    else if(sum == 4 || sum == 5 || sum == 6 || sum == 8 || sum == 9 || sum == 10 ) {
        std::cout<<"You won! " << wager << " Your new balance is "<< (wager*2) + credits<< '\n' ;
        credits = credits + (wager * 2);
        return;
    }

  }

}
   



int die() {
    std::srand(std::time(0));

    int die1 = (std::rand() % 6) + 1;
    std::this_thread::sleep_for(std::chrono::seconds(2));  // Delay for 3 seconds

    int die2 = (std::rand() % 6) + 1;
    std::cout<< "player rolled " << die1 <<" + " << die2 << " = " << die1+die2 << '\n';
    return die1+die2;
}
